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
import MFifo::*;
import Vector::*;
import Ehr::*;

// mem
import WideMemSplit::*;
import LSU::*;

// Arbiter
import SyncArbiter::*;

// front
import FrontEnd::*;
import Decoder::*;
import Stream::*;
import Fetch::*;

// back
import Scoreboard::*;
import RFile::*;
import Execution::*;
import NTTX::*;

function Bool isMemInst(ExecToken inst);
	return True;
endfunction

function Bool isArithInst(ExecToken inst);
	return (inst.inst.iType == Unsupported || inst.inst.iType == Alu   ||
	        inst.inst.iType == Mul         || inst.inst.iType == J     ||
	        inst.inst.iType == Jr          || inst.inst.iType == Br    ||
	        inst.inst.iType == Auipc );
endfunction

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

	Reg#(Bool)                             coreStarted    <- mkReg(False);
	Ehr#(3,Data)                           numCommit      <- mkEhr(0);
	Ehr#(2,Data)                           numCycles      <- mkEhr(0);
	MFifo#(THQ_LEN,BackWidth,CommitReport) commitReportQ  <- mkPipelineMFifo();
	Fifo#(THQ_LEN,Message)                 messageReportQ <- mkPipelineFifo();
	Fifo#(THQ_LEN,MemStat)                 memStatReportQ <- mkPipelineFifo();


	//////////// MEMORY ////////////

	SplitWideMem#(FrontWidth,TMul#(2,FrontWidth)) mainSplit <- mkSplitWideMem(True, mem);
	BareDataCache                                 l1d       <- (lsuAssociative ? mkAssociativeDataCache() : mkDirectDataCache());
	LSU#(WBToken)                                 lsu       <- mkLSU(mainSplit.port[1], l1d);


	//////////// INT STATE ////////////

	Vector#(FrontWidth, RFile         ) regFile    <- replicateM(mkBypassRFile);
	Vector#(FrontWidth, Scoreboard#(8)) scoreboard <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, Ehr#(2,Epoch) ) wbEpoch    <- replicateM(mkEhr('0)    );

	//////////// FRONT END ////////////

	Vector#(FrontWidth, Epoch) frontWBepoch = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) frontWBepoch[i] = wbEpoch[i][1];

	Vector#(FrontWidth, Hart) frontEnd <- mkFrontEnd(mainSplit.port[0], regFile, scoreboard, frontWBepoch, coreStarted);


	//////////// ARBITER ////////////

	Vector#(BackWidth, function Bool accept(ExecToken inst)) filter = newVector;
	for(Integer i = 1; i < valueOf(BackWidth); i = i+1) filter[i] = isArithInst; filter[0] = isMemInst;

	SyncArbiter#(FrontWidth, BackWidth, ExecToken) arbiter <- mkSyncArbiter(coreStarted, filter);


	//////////// FTA ////////////

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_frontEnd;
			let inst <- frontEnd[i].readInst();
			arbiter.eport[i].enq(inst);
		endrule
	end


	//////////// EXECUTE ////////////

	Fifo#(1,Vector#(BackWidth,Maybe#(MemToken))) memoryQ <- mkStageFifo();

	Ehr#(2,Vector#(BackWidth,Maybe#(ExecToken))) perf_exec_inst  <- mkEhr(replicate(tagged Invalid));

	rule do_execute;

		Vector#(BackWidth, Maybe#(ExecToken)) toExec = arbiter.dport.first(); arbiter.dport.deq();
		Vector#(BackWidth, Maybe#(MemToken) ) toMem  = replicate(tagged Invalid);

		// Instruction Execute
		for (Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
			if(isValid(toExec[i])) begin
				let eToken = fromMaybe(?,toExec[i]);
				let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);
				let mToken   = MemToken{
								inst   : execInst,
								pc     : eToken.pc,
								feID   : eToken.feID,
								epoch  : eToken.epoch,
								rawInst: eToken.rawInst};

				toMem[i] = tagged Valid mToken;
			end
		end

		memoryQ.enq(toMem);

		if(perf_DEBUG) begin
			perf_exec_inst[0] <= toExec;
		end

	endrule

 
	//////////// MEMORY ////////////

	Fifo#(1,Vector#(BackWidth, Maybe#(WBToken))) commitQ <- mkStageFifo();

	Ehr#(2,Vector#(BackWidth,Maybe#(MemToken))) perf_mem_inst  <- mkEhr(replicate(tagged Invalid));

	rule do_mem;

		Vector#(BackWidth, Maybe#(MemToken)) toMem    = memoryQ.first(); memoryQ.deq();
		Vector#(BackWidth, Maybe#(WBToken))  toCommit = replicate(tagged Invalid);

		if(isValid(toMem[0])) begin

			let mToken = fromMaybe(?, toMem[0]);
			let wToken = WBToken{ inst   : mToken.inst,
			                      pc     : mToken.pc,
			                      feID   : mToken.feID,
			                      epoch  : mToken.epoch,
			                      rawInst: mToken.rawInst};
			toCommit[0] = tagged Valid wToken;

			// Send LSU req, if the instruction is valid
			Maybe#(MemOp) memOp = case (mToken.inst.iType)
				Ld  : tagged Valid Ld;
				St  : tagged Valid St;
				Join: tagged Valid Join;
				default: tagged Invalid;
			endcase;

			if (mToken.epoch == wbEpoch[mToken.feID][1] && isValid(memOp)) begin

	    		lsu.req(LSUReq{ op     : fromMaybe(?,memOp),
	    		                ldFunc : mToken.inst.ldFunc,
	    		                stFunc : mToken.inst.stFunc,
	    		                addr   : mToken.inst.addr,
	    		                data   : mToken.inst.data,
	    		                transId: wToken });

	    	end

	    end

	    for(Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
	    	if(isValid(toMem[i])) begin

	    		let mToken = fromMaybe(?, toMem[i]);
				let wToken = WBToken{ inst   : mToken.inst,
				                      pc     : mToken.pc,
				                      feID   : mToken.feID,
				                      epoch  : mToken.epoch,
				                      rawInst: mToken.rawInst};
				toCommit[i] = tagged Valid wToken;

			end
	    end

		commitQ.enq(toCommit);

		if(perf_DEBUG) begin
			perf_mem_inst[0] <= toMem;
		end

	endrule


	//////////// COMMIT ////////////

	NTTX nttx <- mkNTTX(regFile, verif);

	Vector#(BackWidth, Ehr#(2,Maybe#(WBToken))) perf_wb_inst  <- replicateM(mkEhr(tagged Invalid));
	Vector#(BackWidth, Ehr#(2,Bool))            perf_wb_valid <- replicateM(mkEhr(       False  ));
	Vector#(BackWidth, Ehr#(2,Bool))            perf_wb_miss  <- replicateM(mkEhr(       False  ));

	Vector#(FrontWidth, Ehr#(3, Maybe#(void    ))) toWBsbRemove    <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(RFwb    ))) toWBrfWriteBack <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(void    ))) toWBstDry       <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Epoch   ))) toWBstEpoch     <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Redirect))) toWBstRedirect  <- replicateM(mkEhr(tagged Invalid));

	rule do_commit;

		// Upstream actions
		Vector#(FrontWidth, Maybe#(void    )) sbRemove    = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(RFwb    )) rfWriteBack = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(void    )) stDry       = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Epoch   )) stEpoch     = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Redirect)) stRedirect  = replicate(tagged Invalid);

		// WB
		Vector#(BackWidth, Maybe#(WBToken)) toCommit = commitQ.first(); commitQ.deq();
		Data numWB = 0;

		// LSU Pipeline WB
		if(isValid(toCommit[0])) begin

			let wToken = fromMaybe(?, toCommit[0]);
			let feID   = wToken.feID;

			sbRemove[feID] = tagged Valid(?);

			if (wToken.epoch == wbEpoch[feID][0])  begin

				let commitInst = wToken.inst;

				if(commitInst.iType == Ghost) begin

					nttx.evict(feID, wToken.pc);
					stDry[feID] = tagged Valid(?);

				end else begin

					Data    loadRes      = '1;
					Bool    memValid     = True;
					VerifID childVerifID = '0;

					if(commitInst.iType == Ld) begin

						let resp <- lsu.resp();
						if(resp.valid) begin
							loadRes = resp.data;
		        	    	rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: loadRes};
						end else begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else if(commitInst.iType == St) begin

						let resp <- lsu.resp();
						if(!resp.valid) begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
								                                      kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else if(commitInst.iType == Fork || commitInst.iType == Forkr) begin

						childVerifID <- nttx.efork(feID, commitInst.addr);

					end else if(commitInst.iType == Join) begin

						let resp <- lsu.resp();
						if(resp.valid) begin
							loadRes = resp.data;
							if(resp.data == '0) begin
								stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
								stRedirect[feID] = tagged Valid Redirect{ lock    : False,
	    	    	                                                      kill    : True,
				                                                          redirect: False,
				                                                          epoch   : wbEpoch[feID][0]+1,
				                                                          nextPc  : ? };
							end
						end else begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else begin

		        		if(isValid(commitInst.dst)) begin
							rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: commitInst.data};
						end

						if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : False,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : commitInst.addr };
						end else if (commitInst.iType == Br) begin
							stRedirect[feID] = tagged Valid Redirect{ lock    : False,
							                                          kill    : False,
							                                          redirect: False,
							                                          epoch   : ?,
							                                          nextPc  : ?};
						end

					end

					if (memValid) begin
						numWB = numWB+1;
					end

					if (wb_ext_DEBUG == True && memValid) begin
						commitReportQ.port[0].enq(generateCMR(numCycles[0], verif.getVerifID(feID), childVerifID, wToken, loadRes));
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
							FetchStat fsr = ?; //fetch.getStat();
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
						perf_wb_valid[0][0] <= True;
						perf_wb_miss [0][0] <= !memValid;
					end

				end

			end

		end

		// GP Pipeline WB
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin

			if(isValid(toCommit[i])) begin

				let wToken = fromMaybe(?, toCommit[i]);
				let feID   = wToken.feID;

				sbRemove[feID] = tagged Valid(?);

				if (wToken.epoch == wbEpoch[feID][0])  begin

					let commitInst = wToken.inst;

					if(isValid(commitInst.dst)) begin
						rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: commitInst.data};
					end

					if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
						stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
						stRedirect[feID] = tagged Valid Redirect{ lock    : False,
						                                          kill    : False,
						                                          redirect: True,
						                                          epoch   : wbEpoch[feID][0]+1,
						                                          nextPc  : commitInst.addr };
					end else if (commitInst.iType == Br) begin
						stRedirect[feID] = tagged Valid Redirect{ lock    : False,
						                                          kill    : False,
						                                          redirect: False,
						                                          epoch   : ?,
						                                          nextPc  : ?};
					end

					numWB = numWB+1;

					if (wb_ext_DEBUG == True) begin
						commitReportQ.port[i].enq(generateCMR(numCycles[0], verif.getVerifID(feID), ?, wToken, ?));
					end

					if(perf_DEBUG == True) begin
						perf_wb_valid[i][0] <= True;
					end

				end

			end

		end

		// To WB
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			toWBsbRemove   [i][0] <= sbRemove   [i];
			toWBrfWriteBack[i][0] <= rfWriteBack[i];
			toWBstDry      [i][0] <= stDry      [i];
			toWBstEpoch    [i][0] <= stEpoch    [i];
			toWBstRedirect [i][0] <= stRedirect [i];
		end

		// Num  commit
		numCommit[0] <= numCommit[0]+numWB;

		// Perf debug
		if(perf_DEBUG == True) begin
			for(Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
				perf_wb_inst[i][0] <= toCommit[i];
			end
		end

	endrule

	//////////// OLD COMMIT ////////////

	Ehr#(2,Maybe#(WBToken)) perf_old_wb_inst  <- mkEhr(tagged Invalid);

	rule do_old_commit;

		LSUResp#(WBToken) resp      <- lsu.oldResp();
		WBToken           wToken     = resp.transId;
		ExecInst          commitInst = wToken.inst;
		FrontID           feID       = wToken.feID;
		Data              loadRes    = 'hdeadbeef;

		if(commitInst.iType == Ld) begin

			loadRes = resp.data;
    	    toWBrfWriteBack[feID][1] <= tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: loadRes};
    	    toWBstRedirect [feID][1] <= tagged Valid Redirect{ lock    : False,
    	    	                                               kill    : False,
			                                                   redirect: False,
			                                                   epoch   : ?,
			                                                   nextPc  : ? };

    	end else if(commitInst.iType == St) begin

    	    toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
    	    	                                    kill    : False,
			                                        redirect: False,
			                                        epoch   : ?,
			                                        nextPc  : ? };

    	end else if(commitInst.iType == Join) begin

    		loadRes = resp.data;
			if(resp.data == '0) begin
				toWBstEpoch   [feID][1] <= tagged Valid (wbEpoch[feID][0]+1);
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
    		                                            kill    : True,
			                                            redirect: False,
			                                            epoch   : wbEpoch[feID][0]+1,
			                                            nextPc  : ? };
			end else begin
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
					                                    kill    : False,
				                                        redirect: False,
				                                        epoch   : ?,
				                                        nextPc  : ? };
			end

    	end

    	numCommit[1] <= numCommit[1]+1;

		if (wb_ext_DEBUG == True) begin
			commitReportQ.port[0].enq(generateCMR(numCycles[0], verif.getVerifID(feID), ?, wToken, loadRes));
		end

		if(perf_DEBUG == True) begin
			perf_old_wb_inst[0] <= tagged Valid wToken;
		end

	endrule

	//////////// WRBACK ////////////
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		rule do_wb;

			if(isValid(toWBsbRemove[i][2])) begin
				scoreboard[i].remove();
			end

			regFile[i].wr(fromMaybe(RFwb{dst: '0, res: 'hdeadbeef}, toWBrfWriteBack[i][2]));

			if(isValid(toWBstDry[i][2])) begin
				frontEnd[i].backendDry();
			end

			wbEpoch[i][0] <= fromMaybe(wbEpoch[i][0], toWBstEpoch[i][2]);

			if(isValid(toWBstRedirect[i][2])) begin
				frontEnd[i].redirect(fromMaybe(?,toWBstRedirect[i][2]));
			end

			toWBsbRemove   [i][2] <= tagged Invalid;
			toWBrfWriteBack[i][2] <= tagged Invalid;
			toWBstDry      [i][2] <= tagged Invalid;
			toWBstEpoch    [i][2] <= tagged Invalid;
			toWBstRedirect [i][2] <= tagged Invalid;

		endrule

	end

	//////////// PERFORMANCE CNT ////////////

	rule do_cnt_cycles if(coreStarted);
		numCycles[0] <= numCycles[0]+1;
	endrule
/*
	rule do_perf_DEBUG if(perf_DEBUG == True && coreStarted);

		Vector#(FrontWidth,Maybe#(ExecToken)) perf_sel_inst  = arbiter.perf_get_inst ();
		Vector#(FrontWidth,Bool)              perf_sel_taken = arbiter.perf_get_taken();

		perf_exec_inst[1] <= replicate(tagged Invalid);
		perf_mem_inst [1] <= replicate(tagged Invalid);
		
		for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
			perf_wb_inst [j][1] <= tagged Invalid;
			perf_wb_valid[j][1] <= False;
			perf_wb_miss [j][1] <= False;
		end

		perf_old_wb_inst[1] <= tagged Invalid;

		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

			     if(i == 0) $write("%d ", numCycles[1]);
			else if(i == 1) $write("%d ", numCommit[2]);
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
			
			if(perf_sel_taken[i]) $write(" S 0x%h |", fromMaybe(?,perf_sel_inst[i]).pc);
			else if(isValid(perf_sel_inst[i])) $write("%c[2;97m S 0x%h %c[0;0m|", 27, fromMaybe(?,perf_sel_inst[i]).pc, 27);
			else $write(" S            |");

			Bool exec = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_exec_inst[1][j]) && (fromMaybe(?,perf_exec_inst[1][j]).feID == fromInteger(i))) begin
					$write(" E 0x%h |",  fromMaybe(?,perf_exec_inst[1][j]).pc);
					exec = True;
				end
			end
			if(!exec) $write("              |");

			Bool mem = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_mem_inst[1][j]) && (fromMaybe(?,perf_mem_inst[1][j]).feID == fromInteger(i))) begin
					$write(" M 0x%h |",  fromMaybe(?,perf_mem_inst[1][j]).pc);
					mem = True;
				end
			end
			if(!mem) $write("              |");

			Bool wb = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_wb_inst[j][1]) && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write(" W 0x%h | ", fromMaybe(?,perf_wb_inst[j][1]).pc);
					wb = True;
				end
			end
			if(!wb) $write("              | ");

			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(perf_wb_valid[j][1] && !perf_wb_miss[j][1] && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write("%c[1;93m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j][1]).rawInst));
					$write("%c[0m",27);
				end else if(perf_wb_miss[j][1] && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write("%c[2;97m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j][1]).rawInst));
					$write("%c[0m",27);
				end
			end

			if(isValid(perf_old_wb_inst[1]) && (fromMaybe(?,perf_old_wb_inst[1]).feID == fromInteger(i))) begin
				$write("%c[1;33m",27);
				$write("", showInst(fromMaybe(?,perf_old_wb_inst[1]).rawInst));
				$write("%c[0m",27);
			end

			$display("");
		end

		$write("---------------------------------------------------------------------------------------------------------------------------------------------\n");

	endrule

*/
	//////////// INTERFACE ////////////

	method Action start (FrontID feID, ContToken token);

		frontEnd[feID].start(token.pc);
		regFile [feID].setL (token.rfL);
		regFile [feID].setH (token.rfH);

		verif.setVerifID(feID, token.verifID);

		if(!coreStarted) begin
			coreStarted <= True;
			commitReportQ.clear();
			messageReportQ.clear();	
			memStatReportQ.clear();
		end

	endmethod

	method Action evict(FrontID feID);

		frontEnd[feID].evict();

	endmethod

	method Bool available(FrontID feID);

		return frontEnd[feID].available();

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
