import FShow::*;
import Config::*;

// types
import Types::*;
import ProcTypes::*;
import MemTypes::*;

// include
import Fifo::*;
import Vector::*;
import Ehr::*;

// mem
import MemUtil::*;
import Cache::*;
import WideMemSplit::*;

// front
import Decoder::*;
import Stream::*;

// back
import Scoreboard::*;
import RFile::*;
import Execution::*;
import NTTX::*;



interface Core;

	method Action start(FrontID feID, Addr spc);
	method Action evict(FrontID feID);
	method Data   getNumCommit();

	method ActionValue#(ContToken)    getContToken();
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Data)         getMSG();

endinterface

module mkCore6S(WideMem mem, Core ifc);

	//////////// EXT STATE ////////////

	Reg#(Bool)            coreStarted    <- mkReg(False);
	Reg#(Data)            numCommit      <- mkReg(0);
	Reg#(Data)            numCycles      <- mkReg(0);
	Fifo#(8,CommitReport) commitReportQ  <- mkPipelineFifo();
	Fifo#(8,Data)         messageReportQ <- mkPipelineFifo();


	//////////// MEMORY ////////////

	Vector#(TAdd#(FrontWidth,1), WideMem) memSplit   <- mkSplitWideMem(True, mem);
	Cache                                 l1D        <- mkDirectCache(memSplit[valueOf(FrontWidth)]);


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
	Vector#(FrontWidth, Fifo#(2,ExecToken)) executeQ <- replicateM(mkPipelineFifo()    );

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

		FrontID hart = rrfeID; rrfeID <= rrfeID+1;

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(!executeQ[hart].notEmpty()) begin
				hart = hart+1;
			end
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

		if (mToken.epoch == wbEpoch[feID][1]) begin
			// Prevent instruction from requesting MEM operations if epoch is changed
			if(execInst.iType == Ld) begin

    		    l1D.req(MemReq{
    		    			op  : Ld,
    		    			addr: execInst.addr,
    		    			data: ?,
    		    			func: ?});

    		end else if(execInst.iType == St) begin

    		    l1D.req(MemReq{
    		    			op  : St,
    		    			addr: execInst.addr,
    		    			data: execInst.data,
    		    			func: execInst.stFunc});

    		end
    	end
	
		let wToken   = WBToken{
							inst: execInst,
							pc: mToken.pc,
							feID: mToken.feID,
							epoch: mToken.epoch,
							rawInst: mToken.rawInst};

		wrbackQ.enq(wToken);

	endrule


	//////////// WRBACK ////////////

	NTTX nttx <- mkNTTX();

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

				Data loadRes = '0;

				if(commitInst.iType == Ld) begin
					Data loadResRaw <- l1D.resp();
					loadRes = extendLoad(loadResRaw, commitInst.addr, commitInst.ldFunc);
	        	    rf[feID].wr(fromMaybe(?, commitInst.dst), loadRes);
	        	end else if(isValid(commitInst.dst)) begin
					rf[feID].wr(fromMaybe(?, commitInst.dst), commitInst.data);
				end

				if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
					stream[feID].redirect(Redirect{
											pc        : wToken.pc,
											epoch     :!wToken.epoch,
											nextPc    : commitInst.addr,
										   	brType    : commitInst.iType,
										   	taken     : commitInst.brTaken,
										   	mispredict: commitInst.mispredict});
					wbEpoch[feID][0] <= !wbEpoch[feID][0];
				end

				if (wb_ext_DEBUG == True) begin

					if(commitInst.iType == J || commitInst.iType == Jr || commitInst.iType == Br) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														feID:    feID,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   '0,
														addr:    commitInst.addr});
					end else if(commitInst.iType == Ld) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														feID:    feID,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   fromMaybe('0,commitInst.dst),
														wbRes:   loadRes,
														addr:    commitInst.addr});
					end else if(commitInst.iType == St) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														feID:    feID,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   '0,
														addr:    commitInst.addr});
					end else begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														feID:    feID,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   fromMaybe('0,commitInst.dst),
														wbRes:   commitInst.data,
														addr:    '0});
					end

				end

				if(msg_ext_DEBUG == True) begin
					
					if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
						messageReportQ.enq(commitInst.data);
					end

				end

				if (wb_DEBUG == True) begin

					if(commitInst.iType == J ||commitInst.iType == Jr || commitInst.iType == Br) begin
						$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, commitInst.addr, showInst(wToken.rawInst));
					end else if (commitInst.iType == Ld) begin
						$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, loadRes, showInst(wToken.rawInst));
					end else begin
						$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, commitInst.data, showInst(wToken.rawInst));
					end

				end

				if(msg_DEBUG == True) begin
					
					if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
						$display("MESSAGE: %h", commitInst.data);
					end

				end

			end

		end

	endrule

	//////////// PERFORMANCE CNT ////////////

	rule cntCycles if (coreStarted);
		numCycles <= numCycles+1;

		if (perf_DEBUG == True) begin
			$display("0x%h || F 0x%h | D 0x%h | R 0x%h | E 0x%h | M 0x%h | W 0x%h",
				numCycles,
				stream[0].currentPC(),
				32'b0, //(decodeQ.notEmpty   == True? decodeQ.first().pc   : 0),
				(regfetchQ[0].notEmpty == True? regfetchQ[0].first().pc : 0),
				(executeQ[0].notEmpty  == True? executeQ[0].first().pc  : 0),
				(memoryQ.notEmpty   == True? memoryQ.first().pc   : 0),
				(wrbackQ.notEmpty   == True? wrbackQ.first().pc   : 0)
				);
		end

	endrule


	//////////// INTERFACE ////////////

	method Action start (FrontID feID, Addr spc);

		stream [feID].start(spc);
		wbEpoch[feID][1] <= False;

		if(!coreStarted) begin
			coreStarted <= True;
			commitReportQ.clear();
			messageReportQ.clear();	
		end

	endmethod

	method Action evict(FrontID feID);

		stream[feID].evict();

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

	method ActionValue#(Data) getMSG();

		let latest = messageReportQ.first(); messageReportQ.deq();
		return latest;

	endmethod

endmodule // mkBackend
