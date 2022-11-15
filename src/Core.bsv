import FShow::*;
import Config::*;
import VerifMaster::*;

// types
import Types::*;
import ProcTypes::*;
import LSUTypes::*;

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

endinterface

module mkCore6S(WideMem mem, VerifMaster verif, Core ifc);

	//////////// EXT STATE ////////////

	Reg#(Bool)                  coreStarted    <- mkReg(False);
	Reg#(Data)                  numCommit      <- mkReg(0);
	Reg#(Data)                  numCycles      <- mkReg(0);
	Fifo#(THQ_LEN,CommitReport) commitReportQ  <- mkPipelineFifo();
	Fifo#(THQ_LEN,Message)      messageReportQ <- mkPipelineFifo();


	//////////// MEMORY ////////////

	Vector#(TAdd#(FrontWidth,1), WideMem) memSplit   <- mkSplitWideMem(True, mem);
	BareDataCache                         l1d        <- mkDirectDataCache();
	LSU#(WBToken)                         lsu        <- mkLSU(memSplit[valueOf(FrontWidth)], l1d);

	//////////// FETCH ////////////

	Vector#(FrontWidth, Stream) stream;

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
		stream[i] <- mkStream(memSplit[i]);
	end


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

	Vector#(FrontWidth, RFile             ) rf       <- replicateM(mkBypassRFile       );
	Vector#(FrontWidth, Scoreboard#(8)    ) sb       <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, Fifo#(1,ExecToken)) executeQ <- replicateM(mkStageFifo()       );

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_regfetch if (!sb[i].search1(regfetchQ[i].first().inst.src1) && !sb[i].search2(regfetchQ[i].first().inst.src2));

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

	Vector#(FrontWidth, Ehr#(2,Bool)) wbEpoch <- replicateM(mkEhr(False));

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
    		                    func   : ?,
    		                    addr   : execInst.addr,
    		                    data   : ?,
    		                    transId: wToken });

    		end else if(execInst.iType == St) begin

    		    lsu.req(LSUReq{ op     : St,
    		                    func   : execInst.stFunc,
    		                    addr   : execInst.addr,
    		                    data   : execInst.data,
    		                    transId: wToken });

    		end else if(execInst.iType == Join) begin

    		    lsu.req(LSUReq{ op  : Join,
    		                    func: ?,
    		                    addr: execInst.addr,
    		                    data: 'b1,
    		                    transId: wToken });

    		end
    	end

		wrbackQ.enq(wToken);

	endrule


	//////////// WRBACK ////////////

	NTTX nttx <- mkNTTX(rf, verif);

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

				numCommit <= numCommit+1;

				Data    loadRes      = '1;
				Bool    memValid     = True;
				VerifID childVerifID = '0;

				if(commitInst.iType == Ld) begin

					let resp <- lsu.resp();
					if(resp.valid) begin
						loadRes = extendLoad(resp.data, commitInst.addr, commitInst.ldFunc);
	        	    	rf[feID].wr(fromMaybe(?, commitInst.dst), loadRes);
					end else begin
						wbEpoch[feID][0] <= !wbEpoch[feID][0];
						memValid = False;
					end

	        	end else if(commitInst.iType == St) begin

					let resp <- lsu.resp();
					if(!resp.valid) begin
						wbEpoch[feID][0] <= !wbEpoch[feID][0];
						memValid = False;
					end

	        	end else if(commitInst.iType == Fork || commitInst.iType == Forkr) begin

					childVerifID <- nttx.efork(feID, commitInst.addr);

				end else if(commitInst.iType == Join) begin

					let resp <- lsu.resp();
					if(resp.valid) begin
						loadRes = resp.data;
						if(resp.data == '0) begin
							stream[feID].backendKill(!wbEpoch[feID][0]);
							wbEpoch[feID][0] <= !wbEpoch[feID][0];
						end
					end else begin
						wbEpoch[feID][0] <= !wbEpoch[feID][0];
						memValid = False;
					end

	        	end else begin

	        		if(isValid(commitInst.dst)) begin
						rf[feID].wr(fromMaybe(?, commitInst.dst), commitInst.data);
					end

					if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
						stream[feID].redirect(Redirect{
												pc        : wToken.pc,
												epoch     :!wbEpoch[feID][0],
												nextPc    : commitInst.addr,
											   	brType    : commitInst.iType,
											   	taken     : commitInst.brTaken,
											   	mispredict: commitInst.mispredict});
						wbEpoch[feID][0] <= !wbEpoch[feID][0];
					end

				end

				if (wb_ext_DEBUG == True) begin

					if(commitInst.iType == J || commitInst.iType == Jr || commitInst.iType == Br) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														verifID: verif.getVerifID(feID),
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   '0,
														addr:    commitInst.addr});
					end else if(commitInst.iType == Fork || commitInst.iType == Forkr) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														verifID: verif.getVerifID(feID),
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   childVerifID,
														addr:    commitInst.addr});
					end else if(commitInst.iType == Join) begin
						if(memValid) begin
							commitReportQ.enq(CommitReport {cycle:   numCycles,
															verifID: verif.getVerifID(feID),
															pc:      wToken.pc,
															rawInst: wToken.rawInst,
															iType:   commitInst.iType,
															wbDst:   '0,
															wbRes:   loadRes,
															addr:    commitInst.addr});
						end
					end else if(commitInst.iType == Ld) begin
						if(memValid) begin
							commitReportQ.enq(CommitReport {cycle:   numCycles,
															verifID: verif.getVerifID(feID),
															pc:      wToken.pc,
															rawInst: wToken.rawInst,
															iType:   commitInst.iType,
															wbDst:   fromMaybe('0,commitInst.dst),
															wbRes:   loadRes,
															addr:    commitInst.addr});
						end
					end else if(commitInst.iType == St) begin
						if(memValid) begin
							commitReportQ.enq(CommitReport {cycle:   numCycles,
															verifID: verif.getVerifID(feID),
															pc:      wToken.pc,
															rawInst: wToken.rawInst,
															iType:   commitInst.iType,
															wbDst:   '0,
															wbRes:   '0,
															addr:    commitInst.addr});
						end
					end else begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														verifID: verif.getVerifID(feID),
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   fromMaybe('0,commitInst.dst),
														wbRes:   commitInst.data,
														addr:    '0});
					end

				end

				if (msg_ext_DEBUG == True) begin
					
					if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
						messageReportQ.enq(Message { verifID: verif.getVerifID(feID),
													 cycle:   numCycles,
													 commit:  numCommit,
													 data:    commitInst.data });
					end

				end

				if (msg_DEBUG == True) begin
					
					if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
						$display(" [id: %d ] MESSAGE | cycle: %d | commit: %d | %c ", verif.getVerifID(feID), numCycles, numCommit, commitInst.data);
					end

				end

			end

		end

	endrule

	rule do_old_wb;

		let resp <- lsu.oldResp();
		let wToken     = resp.transId;
		let commitInst = wToken.inst;
		let feID       = wToken.feID;
		Data loadRes   = 'hdeadbeef;

		if(commitInst.iType == Ld) begin

			loadRes = extendLoad(resp.data, commitInst.addr, commitInst.ldFunc);
    	    rf[feID].wr(fromMaybe(?, commitInst.dst), loadRes);
    	    stream[feID].redirect(Redirect{ pc        : wToken.pc,
			                                epoch     : wbEpoch[feID][0],
			                                nextPc    : wToken.pc+4,
			                                brType    : commitInst.iType,
			                                taken     : commitInst.brTaken,
			                                mispredict: commitInst.mispredict});

    	end else if(commitInst.iType == St) begin

    	    stream[feID].redirect(Redirect{ pc        : wToken.pc,
			                                epoch     : wbEpoch[feID][0],
			                                nextPc    : wToken.pc+4,
			                                brType    : commitInst.iType,
			                                taken     : commitInst.brTaken,
			                                mispredict: commitInst.mispredict});

    	end else if(commitInst.iType == Join) begin

    		loadRes = resp.data;
			if(resp.data == '0) begin
				stream[feID].backendKill(wbEpoch[feID][0]);
			end else begin
				stream[feID].redirect(Redirect{ pc        : wToken.pc,
			                                	epoch     : wbEpoch[feID][0],
			                                	nextPc    : wToken.pc+4,
			                                	brType    : commitInst.iType,
			                                	taken     : commitInst.brTaken,
			                                	mispredict: commitInst.mispredict});
			end

    	end

    	if (wb_ext_DEBUG == True) begin

			if(commitInst.iType == Join) begin
				commitReportQ.enq(CommitReport {cycle:   numCycles,
												verifID: verif.getVerifID(feID),
												pc:      wToken.pc,
												rawInst: wToken.rawInst,
												iType:   commitInst.iType,
												wbDst:   '0,
												wbRes:   loadRes,
												addr:    commitInst.addr});
			end else if(commitInst.iType == Ld) begin
				commitReportQ.enq(CommitReport {cycle:   numCycles,
												verifID: verif.getVerifID(feID),
												pc:      wToken.pc,
												rawInst: wToken.rawInst,
												iType:   commitInst.iType,
												wbDst:   fromMaybe('0,commitInst.dst),
												wbRes:   loadRes,
												addr:    commitInst.addr});
			end else if(commitInst.iType == St) begin
				commitReportQ.enq(CommitReport {cycle:   numCycles,
												verifID: verif.getVerifID(feID),
												pc:      wToken.pc,
												rawInst: wToken.rawInst,
												iType:   commitInst.iType,
												wbDst:   '0,
												wbRes:   '0,
												addr:    commitInst.addr});
			end

		end

	endrule

	//////////// PERFORMANCE CNT ////////////

	rule do_cnt_cycles if(coreStarted);

		numCycles <= numCycles+1;

		if (perf_DEBUG == True) begin

			FrontID hart = rrfeID;
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
				if(!executeQ[hart].notEmpty()) begin
					hart = hart+1;
				end
			end
			
			for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

				     if(i == 0) $write("%d ", numCycles);
				else if(i == 1) $write("%d ", numCommit);
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
				
				if(wrbackQ.notEmpty && (wrbackQ.first().feID == fromInteger(i))) $write(" W 0x%h | ", wrbackQ.first().pc); else $write("              |");
				if(wrbackQ.notEmpty && (wrbackQ.first().feID == fromInteger(i))) begin
					$write("%c[1;33m",27);
					$write("", showInst(wrbackQ.first().rawInst));
					$write("%c[0m",27); 
				end

				$display("");
			end

			$write("------------------------------------------------------------------------------------------------------------------------------\n");

		end

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
		end

	endmethod

	method Action evict(FrontID feID);

		stream[feID].evict();

	endmethod

	method Bool available(FrontID feID);

		return stream[feID].available();

	endmethod

	method Data getNumCommit();

		return numCommit;

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

endmodule // mkBackend
