import FShow::*;
import Config::*;
import VerifMaster::*;

// types
import Types::*;
import ProcTypes::*;
import LSUTypes::*;
import CMRTypes::*;

// include
import Fifo::*;
import Vector::*;
import Ehr::*;

// mem
import WideMemSplit::*;
import LSU::*;

// front
import Decoder::*;
import Stream::*;
import Fetch::*;

// back
import Scoreboard::*;
import RFile::*;
import Execution::*;
import NTTX::*;



interface Core;

	method Action start (FrontID feID, ContToken token);
	method Action evict(FrontID feID);
	method Bool   available(FrontID feID);
	method Data   getNumCommit();

	method ActionValue#(ContToken)    getContToken();
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Message)      getMSG();
	method ActionValue#(MemStat)      getMSR();

endinterface

module mkCore6S(WideMem mem, VerifMaster verif, Core ifc);

	//////////// EXT STATE ////////////

	Reg#(Bool)                  coreStarted    <- mkReg(False);
	Ehr#(2,Data)                numCommit      <- mkEhr(0);
	Ehr#(2,Data)                numCycles      <- mkEhr(0);
	Fifo#(THQ_LEN,CommitReport) commitReportQ  <- mkPipelineFifo();
	Fifo#(THQ_LEN,Message)      messageReportQ <- mkPipelineFifo();
	Fifo#(THQ_LEN,MemStat)      memStatReportQ <- mkPipelineFifo();


	//////////// MEMORY ////////////

	SplitWideMem#(FrontWidth,TMul#(2,FrontWidth)) mainSplit <- mkSplitWideMem(True, mem);
	BareDataCache                                 l1d       <- (lsuAssociative ? mkAssociativeDataCache() : mkDirectDataCache());
	LSU#(WBToken)                                 lsu       <- mkLSU(mainSplit.port[1], l1d);

	Vector#(FrontWidth, Ehr#(2,Epoch)) wbEpoch <- replicateM(mkEhr('0));

	//////////// FETCH ////////////

	Fetch#(FrontWidth) fetch <- mkFetch(mainSplit.port[0], coreStarted);
	Vector#(FrontWidth, Stream) stream = fetch.stream;

	//////////// DECODE ////////////

	Vector#(FrontWidth,  Fifo#(1,RFToken)) regfetchQ <- replicateM(mkStageFifo());

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_decode;

			let dToken  <- stream[i].fetch();
			let inst    = dToken.inst;

			if(dToken.ghost) begin
				DecodedInst decInst = DecodedInst{
				                   		iType  : Ghost,
				                   		aluFunc: ?,
				                   		mulFunc: ?,
				                   		ldFunc : ?,
				                   		stFunc : ?,
				                   		brFunc : NT,
				                   		dst    : tagged Invalid,
				                   		src1   : tagged Invalid,
				                   		src2   : tagged Invalid,
				                   		imm    : tagged Invalid};

				Addr        pc      = dToken.pc;
				RFToken     rfToken = RFToken{
										inst   : decInst,
										pc     : pc,
										epoch  : dToken.epoch,
										rawInst: inst};

				regfetchQ[i].enq(rfToken);

			end else begin

				DecodedInst decInst = decode(inst);

				Addr        pc      = dToken.pc;
				RFToken     rfToken = RFToken{
										inst   : decInst,
										pc     : pc,
										epoch  : dToken.epoch,
										rawInst: inst};

				regfetchQ[i].enq(rfToken);

			end

		endrule

	end


	//////////// REG FETCH ////////////

	Vector#(FrontWidth, RFile             ) rf        <- replicateM(mkBypassRFile       );
	Vector#(FrontWidth, Scoreboard#(8)    ) sb        <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, Fifo#(1,ExecToken)) executeQ  <- replicateM(mkStageFifo()       );

	Vector#(FrontWidth, Fifo#(1,Redirect) ) redirectQ <- replicateM(mkBypassFifo());
	Vector#(FrontWidth, Ehr#(2,Bool)      ) rfLock    <- replicateM(mkEhr(False));

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_regfetch;

			if (regfetchQ[i].first().epoch != wbEpoch[i][1]) begin
				regfetchQ[i].deq();
			end else if(!rfLock[i][1] && (!sb[i].search1(regfetchQ[i].first().inst.src1) && !sb[i].search2(regfetchQ[i].first().inst.src2))) begin

				let rfToken = regfetchQ[i].first();
				let decInst = rfToken.inst;
					
				let arg1    = rf[i].rd1(fromMaybe(?, decInst.src1));
				let arg2    = rf[i].rd2(fromMaybe(?, decInst.src2));
				let eToken  = ExecToken{
								inst   : decInst,
								arg1   : arg1,
								arg2   : arg2,
								pc     : rfToken.pc,
								feID   : fromInteger(i),
								epoch  : rfToken.epoch,
								rawInst: rfToken.rawInst};

				sb[i].insert(decInst.dst);
				regfetchQ[i].deq();
				executeQ[i].enq(eToken);

				if(decInst.iType == Br || decInst.iType == J || decInst.iType == Jr) begin
					rfLock[i][1] <= True;
				end

			end

		endrule

	end

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_rfLock;
			Redirect r = redirectQ[i].first(); redirectQ[i].deq();
			rfLock[i][0] <= r.lock;
			if(r.redirect || r.kill) begin
				stream[i].redirect(r);
			end
		endrule

	end

	//////////// EXECUTE ////////////

	Fifo#(1,MemToken) memoryQ <- mkStageFifo();
	Reg#(FrontID)     rrfeID  <- mkReg(0);

	rule do_execute;

		FrontID hart = rrfeID;

		if(valueOf(FrontWidth) != 1) begin
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
				if(!executeQ[hart].notEmpty()) begin
					hart = (hart == lastFrontID) ? '0 : hart+1;
				end
			end
			rrfeID <= (hart == lastFrontID) ? '0 : hart+1;
		end

		if (executeQ[hart].notEmpty()) begin

			let eToken = executeQ[hart].first(); executeQ[hart].deq();

			let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);
			let mToken   = MemToken{
							inst   : execInst,
							pc     : eToken.pc,
							feID   : eToken.feID,
							epoch  : eToken.epoch,
							rawInst: eToken.rawInst};

			memoryQ.enq(mToken);

		end

	endrule

 
	//////////// MEMORY ////////////

	Fifo#(1,WBToken)   wrbackQ   <- mkStageFifo();

	rule do_mem;

		let mToken   = memoryQ.first(); memoryQ.deq();
		let execInst = mToken.inst;
		let feID     = mToken.feID;

		let wToken   = WBToken{
							inst: execInst,
							pc: mToken.pc,
							feID: mToken.feID,
							epoch: mToken.epoch,
							rawInst: mToken.rawInst};

		if (mToken.epoch == wbEpoch[feID][1]) begin
			// Prevent instruction from requesting MEM operations if epoch is changed

			if(execInst.iType == Ld) begin

    		    lsu.req(LSUReq{ op     : Ld,
    		                    ldFunc : execInst.ldFunc,
    		                    stFunc : ?,
    		                    addr   : execInst.addr,
    		                    data   : ?,
    		                    transId: wToken });

    		end else if(execInst.iType == St) begin

    		    lsu.req(LSUReq{ op     : St,
    		                    ldFunc : ?,
    		                    stFunc : execInst.stFunc,
    		                    addr   : execInst.addr,
    		                    data   : execInst.data,
    		                    transId: wToken });

    		end else if(execInst.iType == Join) begin

    		    lsu.req(LSUReq{ op     : Join,
    		                    ldFunc : ?,
    		                    stFunc : ?,
    		                    addr   : execInst.addr,
    		                    data   : 'b1,
    		                    transId: wToken });

    		end
    	end

		wrbackQ.enq(wToken);

	endrule


	//////////// WRBACK ////////////

	NTTX nttx <- mkNTTX(rf, verif);

	Ehr#(2,Bool)            perf_doWB     <- mkEhr(False);
	Ehr#(2,Bool)            perf_doMissWB <- mkEhr(False);
	Ehr#(2,Maybe#(WBToken)) perf_wToken   <- mkEhr(tagged Invalid);

	rule do_wb;

		let wToken = wrbackQ.first(); wrbackQ.deq();
		let feID   = wToken.feID;

		sb[feID].remove();

		if (wToken.epoch == wbEpoch[feID][0])  begin

			let commitInst = wToken.inst;

			if(commitInst.iType == Ghost) begin

				nttx.evict(feID, wToken.pc);
				stream[feID].backendDry();

			end else begin

				numCommit[0] <= numCommit[0]+1;

				Data    loadRes      = '1;
				Bool    memValid     = True;
				VerifID childVerifID = '0;

				if(commitInst.iType == Ld) begin

					let resp <- lsu.resp();
					if(resp.valid) begin
						loadRes = resp.data;
	        	    	rf[feID].wr(fromMaybe(?, commitInst.dst), loadRes);
					end else begin
						wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
						redirectQ[feID].enq(Redirect{ lock    : True,
						                              kill    : False,
						                              redirect: True,
						                              epoch   : wbEpoch[feID][0]+1,
						                              nextPc  : wToken.pc+4 });
						memValid = False;
					end

	        	end else if(commitInst.iType == St) begin

					let resp <- lsu.resp();
					if(!resp.valid) begin
						wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
						redirectQ[feID].enq(Redirect{ lock    : True,
							                          kill    : False,
						                              redirect: True,
						                              epoch   : wbEpoch[feID][0]+1,
						                              nextPc  : wToken.pc+4 });
						memValid = False;
					end

	        	end else if(commitInst.iType == Fork || commitInst.iType == Forkr) begin

					childVerifID <- nttx.efork(feID, commitInst.addr);

				end else if(commitInst.iType == Join) begin

					let resp <- lsu.resp();
					if(resp.valid) begin
						loadRes = resp.data;
						if(resp.data == '0) begin
							wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
							redirectQ[feID].enq(Redirect{ lock    : False,
    	    	                                          kill    : True,
			                                              redirect: False,
			                                              epoch   : wbEpoch[feID][0]+1,
			                                              nextPc  : ? });
						end
					end else begin
						wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
						redirectQ[feID].enq(Redirect{ lock    : True,
							                          kill    : False,
						                              redirect: True,
						                              epoch   : wbEpoch[feID][0]+1,
						                              nextPc  : wToken.pc+4 });
						memValid = False;
					end

	        	end else begin

	        		if(isValid(commitInst.dst)) begin
						rf[feID].wr(fromMaybe(?, commitInst.dst), commitInst.data);
					end

					if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
						redirectQ[feID].enq(Redirect{ lock    : False,
							                          kill    : False,
						                              redirect: True,
						                              epoch   : wbEpoch[feID][0]+1,
						                              nextPc  : commitInst.addr });
						wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
					end else if (commitInst.iType == Br) begin
						redirectQ[feID].enq(Redirect{ lock    : False,
							                          kill    : False,
						                              redirect: False,
						                              epoch   : ?,
						                              nextPc  : ?});
					end

				end

				if (wb_ext_DEBUG == True && memValid) begin
					commitReportQ.enq(generateCMR(numCycles[0], verif.getVerifID(feID), childVerifID, wToken, loadRes));
				end

				if (msg_ext_DEBUG == True) begin
					if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
						messageReportQ.enq(Message { verifID: verif.getVerifID(feID),
													 cycle:   numCycles[0],
													 commit:  numCommit[0],
													 data:    commitInst.data });
					end
				end

				if (mem_ext_DEBUG == True) begin
					if(commitInst.iType == St && commitInst.addr == lsu_ADDR) begin
						FetchStat fsr = fetch.getStat();
						LSUStat   lsr = lsu.getStat();
						MemStat   msr = MemStat{ verifID: verif.getVerifID(feID),
						                         cycle  : numCycles[0],
						                         commit : numCommit[0],
						                         data   : commitInst.data,
						                         fetch  : fsr,
						                         lsu    : lsr };
						memStatReportQ.enq(msr);
					end
				end

				if(perf_DEBUG == True) begin
					if(memValid) begin
						perf_doWB[0] <= True;
					end else begin
						perf_doMissWB[0] <= True;
					end
				end

			end

		end

		if(perf_DEBUG == True) begin
			perf_wToken[0] <= tagged Valid wToken;
		end

	endrule

	//////////// OLD WRBACK ////////////

	Ehr#(2,Bool)            perf_old_doWB    <- mkEhr(False);
	Ehr#(2,Maybe#(WBToken)) perf_old_wToken  <- mkEhr(tagged Invalid);

	rule do_old_wb;

		let resp <- lsu.oldResp();
		let wToken     = resp.transId;
		let commitInst = wToken.inst;
		let feID       = wToken.feID;
		Data loadRes   = 'hdeadbeef;

		if(commitInst.iType == Ld) begin

			loadRes = resp.data;
    	    rf[feID].wr(fromMaybe(?, commitInst.dst), loadRes);
    	    redirectQ[feID].enq(Redirect{ lock    : False,
    	    	                          kill    : False,
			                              redirect: False,
			                              epoch   : ?,
			                              nextPc  : ? });

    	end else if(commitInst.iType == St) begin

    	    redirectQ[feID].enq(Redirect{ lock    : False,
    	    	                          kill    : False,
			                              redirect: False,
			                              epoch   : ?,
			                              nextPc  : ? });

    	end else if(commitInst.iType == Join) begin

    		loadRes = resp.data;
			if(resp.data == '0) begin
				wbEpoch[feID][0] <= wbEpoch[feID][0]+1;
				redirectQ[feID].enq(Redirect{ lock    : False,
    		                                  kill    : True,
			                                  redirect: False,
			                                  epoch   : wbEpoch[feID][0]+1,
			                                  nextPc  : ? });
			end else begin
				redirectQ[feID].enq(Redirect{ lock    : False,
					                          kill    : False,
				                              redirect: False,
				                              epoch   : ?,
				                              nextPc  : ? });
			end

    	end

    	if (wb_ext_DEBUG == True) begin
    		commitReportQ.enq(generateCMR(numCycles[0], verif.getVerifID(feID), ?, wToken, loadRes));
		end

		if(perf_DEBUG == True) begin
			perf_old_doWB  [0] <= True;
			perf_old_wToken[0] <= tagged Valid wToken;
		end

	endrule

	//////////// PERFORMANCE CNT ////////////

	rule do_cnt_cycles if(coreStarted);
		numCycles[0] <= numCycles[0]+1;
	endrule

	rule do_perf_DEBUG if(perf_DEBUG == True && coreStarted);
		
		perf_doWB      [1] <= False;
		perf_doMissWB  [1] <= False;
		perf_wToken    [1] <= tagged Invalid;
		perf_old_doWB  [1] <= False;
		perf_old_wToken[1] <= tagged Invalid;

		FrontID hart = rrfeID;
		if(valueOf(FrontWidth) != 1) begin
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
				if(!executeQ[hart].notEmpty()) begin
					hart = (hart == lastFrontID) ? '0 : hart+1;
				end
			end
		end
		
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

			     if(i == 0) $write("%d ", numCycles[1]);
			else if(i == 1) $write("%d ", numCommit[1]);
			else            $write("           ");

			if(stream[i].currentState() != Empty) $write("|| %d ", verif.getVerifID(fromInteger(i))); else $write("||            ");

			case (stream[i].currentState())
				Full :   $write("|| Full  ");
				Evict:   $write("|| Evict ");
				Ghost:   $write("|| Ghost ");
				Dry  :   $write("|| Dry   ");
				Empty:   $write("|| Empty ");
				default: $write("||       ");
			endcase

			if(stream   [i].isl0Ihit) $write("h "); else $write("m ");
			if(stream   [i].currentState() != Empty) $write("| F 0x%h |", stream[i].currentPC()); else $write("| F            |");
			if(stream   [i].notEmpty) $write(" D 0x%h |", stream   [i].firstPC() ); else $write(" D            |");
			if(regfetchQ[i].notEmpty) $write(" R 0x%h |", regfetchQ[i].first().pc); else $write(" R            |");
			if(executeQ [i].notEmpty && hart == fromInteger(i)) $write(" E 0x%h |", executeQ [i].first().pc);
			else if(executeQ [i].notEmpty) $write("%c[2;97m E 0x%h %c[0;0m|", 27, executeQ [i].first().pc, 27);
			else $write(" E            |");

			if(memoryQ.notEmpty && (memoryQ.first().feID == fromInteger(i))) $write(" M 0x%h |",  memoryQ.first().pc); else $write("              |");

			if(isValid(perf_wToken[1]) && (fromMaybe(?,perf_wToken[1]).feID == fromInteger(i))) $write(" W 0x%h | ", fromMaybe(?,perf_wToken[1]).pc); else $write("              | ");

			if(perf_doWB[1] && isValid(perf_wToken[1]) && (fromMaybe(?,perf_wToken[1]).feID == fromInteger(i))) begin
				$write("%c[1;93m",27);
				$write("", showInst(fromMaybe(?,perf_wToken[1]).rawInst));
				$write("%c[0m",27);
			end else if(perf_doMissWB[1] && isValid(perf_wToken[1]) && (fromMaybe(?,perf_wToken[1]).feID == fromInteger(i))) begin
				$write("%c[2;97m",27);
				$write("", showInst(fromMaybe(?,perf_wToken[1]).rawInst));
				$write("%c[0m",27);
			end else if(perf_old_doWB[1] && isValid(perf_old_wToken[1]) && (fromMaybe(?,perf_old_wToken[1]).feID == fromInteger(i))) begin
				$write("%c[1;33m",27);
				$write("", showInst(fromMaybe(?,perf_old_wToken[1]).rawInst));
				$write("%c[0m",27);
			end

			$display("");
		end

		$write("------------------------------------------------------------------------------------------------------------------------------\n");

	endrule


	//////////// INTERFACE ////////////

	method Action start (FrontID feID, ContToken token);

		stream [feID].start(token.pc);
		rf     [feID].setL (token.rfL);
		rf     [feID].setH (token.rfH);

		verif.setVerifID(feID, token.verifID);

		if(!coreStarted) begin
			coreStarted <= True;
			commitReportQ.clear();
			messageReportQ.clear();	
			memStatReportQ.clear();
		end

	endmethod

	method Action evict(FrontID feID);

		stream[feID].evict();

	endmethod

	method Bool available(FrontID feID);

		return stream[feID].available();

	endmethod

	method Data getNumCommit();

		return numCommit[0];

	endmethod

	method ActionValue#(ContToken) getContToken();

		let latest = nttx.first(); nttx.deq();
		return latest;

	endmethod

	method ActionValue#(CommitReport) getCMR();

		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;

	endmethod

	method ActionValue#(Message) getMSG();

		let latest = messageReportQ.first(); messageReportQ.deq();
		return latest;

	endmethod

	method ActionValue#(MemStat) getMSR();

		let latest = memStatReportQ.first(); memStatReportQ.deq();
		return latest;

	endmethod

endmodule // mkBackend
