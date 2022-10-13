import Types::*;
import ProcTypes::*;
import Scoreboard::*;
import decoder::*;
import execution::*;
import MemTypes::*;
import MemUtil::*;
import Cache::*;
import Stream::*;
import NTTX::*;
import WideMemSplit::*;
import RFile::*;
import Fifo::*;
import FIFO::*;
import Vector::*;
import Ehr::*;
import FShow::*;




interface Core;

	method Action start(Addr spc);

	method Action evict();

	method Data getNumCommit();

	method ActionValue#(ContToken) getContToken();

	method ActionValue#(CommitReport) getCMR();

	method ActionValue#(Data) getMSG();

endinterface

module mkCore6S(WideMem mem, Core ifc);

	//////////// CORE DEBUG ////////////

	// Connectal (FPGA)
	Bool wb_ext_DEBUG  = True;
	Bool msg_ext_DEBUG = True;

	// Verilog (SIM)
	Bool wb_DEBUG      = False;
	Bool msg_DEBUG     = False;
	Bool perf_DEBUG    = False;

	Addr msg_ADDR      = 'h10000;


	//////////// CORE STATE ////////////

	RFile            rf        <- mkBypassRFile;
	Scoreboard#(8)   sb        <- mkPipelineScoreboard;


	//////////// EPOCH ////////////

	Ehr#(2,Bool)     wbEpoch   <- mkEhr(False);


	//////////// PIPELINE ////////////

	Fifo#(1,RFToken)   regfetchQ <- mkStageFifo();

	Fifo#(2,ExecToken) executeQ  <- mkPipelineFifo();
	Fifo#(1,MemToken)  memoryQ   <- mkStageFifo();
	Fifo#(1,WBToken)   wrbackQ   <- mkStageFifo();


	//////////// MEMORY ////////////

	Vector#(2,WideMem) memSplit   <- mkSplitWideMem(True, mem);
	Cache              l1D        <- mkDirectCache(memSplit[1]);

	//////////// FRONTEND ////////////

	Stream s0 <- mkStream(memSplit[0]);


	//////////// NTTX ////////////

	NTTX nttx <- mkNTTX();


	//////////// EXT STATE ////////////

	Reg#(Bool)            coreStarted    <- mkReg(False);
	Reg#(Data)            numCommit      <- mkReg(0);
	Reg#(Data)            numCycles      <- mkReg(0);
	Fifo#(8,CommitReport) commitReportQ  <- mkPipelineFifo();
	Fifo#(8,Data)         messageReportQ <- mkPipelineFifo();

	rule cntCycles if (coreStarted);
		numCycles <= numCycles+1;

		if (perf_DEBUG == True) begin
			$display("0x%h || F 0x%h | D 0x%h | R 0x%h | E 0x%h | M 0x%h | W 0x%h",
				numCycles,
				s0.currentPC(),
				32'b0, //(decodeQ.notEmpty   == True? decodeQ.first().pc   : 0),
				(regfetchQ.notEmpty == True? regfetchQ.first().pc : 0),
				(executeQ.notEmpty  == True? executeQ.first().pc  : 0),
				(memoryQ.notEmpty   == True? memoryQ.first().pc   : 0),
				(wrbackQ.notEmpty   == True? wrbackQ.first().pc   : 0)
				);
		end

	endrule


	//////////// DECODE ////////////

	rule do_decode;

		let dToken  <- s0.fetch();
		let inst    = dToken.inst;

		if(dToken.ghost) begin
			DecodedInst decInst = DecodedInst{
			                   		iType  : Ghost,
			                   		aluFunc: ?,
			                   		brFunc : NT,
			                   		dst    : tagged Invalid,
			                   		src1   : tagged Invalid,
			                   		src2   : tagged Invalid,
			                   		imm    : tagged Invalid};

			Addr        pc      = dToken.pc;
			RFToken     rfToken = RFToken{inst: decInst, pc: pc, epoch: dToken.epoch, rawInst: inst};
			regfetchQ.enq(rfToken);

		end else begin

			DecodedInst decInst = decode(inst);
			Addr        pc      = dToken.pc;
			RFToken     rfToken = RFToken{inst: decInst, pc: pc, epoch: dToken.epoch, rawInst: inst};
			regfetchQ.enq(rfToken);

		end

	endrule


	//////////// REG FETCH ////////////

	rule do_regfetch if (!sb.search1(regfetchQ.first().inst.src1) && !sb.search2(regfetchQ.first().inst.src2));

		let rfToken = regfetchQ.first();
		let decInst = rfToken.inst;
			
		let arg1    = rf.rd1(fromMaybe(?, decInst.src1));
		let arg2    = rf.rd2(fromMaybe(?, decInst.src2));
		let eToken  = ExecToken{inst: decInst, arg1: arg1, arg2: arg2, pc: rfToken.pc, epoch: rfToken.epoch, rawInst: rfToken.rawInst};

		sb.insert(decInst.dst);
		regfetchQ.deq();
		executeQ.enq(eToken);

	endrule


	//////////// EXECUTE ////////////

	rule do_execute;

		let eToken = executeQ.first(); executeQ.deq();

		let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);
		let mToken   = MemToken{inst: execInst, pc:eToken.pc, epoch: eToken.epoch, rawInst: eToken.rawInst};

		memoryQ.enq(mToken);

	endrule

 
	//////////// MEMORY ////////////

	rule do_mem;

		let mToken   = memoryQ.first(); memoryQ.deq();

		let execInst = mToken.inst;

		if (mToken.epoch == wbEpoch[1]) begin
			// Prevent instruction from requesting MEM operations if epoch is changed
			if(execInst.iType == Ld) begin
    		    l1D.req(MemReq{op: Ld, addr: execInst.addr, data: ?, func: ?});
    		end else if(execInst.iType == St) begin
    		    l1D.req(MemReq{op: St, addr: execInst.addr, data: execInst.data, func: execInst.stFunc});
    		end
    	end
	
		let wToken   = WBToken{inst: execInst, pc: mToken.pc, epoch: mToken.epoch,  rawInst: mToken.rawInst};

		wrbackQ.enq(wToken);

	endrule


	//////////// WRBACK ////////////

	rule do_wb;

		let wToken = wrbackQ.first(); wrbackQ.deq(); sb.remove();

		if (wToken.epoch == wbEpoch[0])  begin

			let commitInst = wToken.inst;

			if(commitInst.iType == Ghost) begin

				nttx.evict(wToken.pc);
				s0.backendDry();

			end else begin

				numCommit <= numCommit+1;

				Data loadRes = '0;

				if(commitInst.iType == Ld) begin
					Data loadResRaw <- l1D.resp();
					loadRes = extendLoad(loadResRaw, commitInst.addr, commitInst.ldFunc);
	        	    rf.wr(fromMaybe(?, commitInst.dst), loadRes);
	        	end else if(isValid(commitInst.dst)) begin
					rf.wr(fromMaybe(?, commitInst.dst), commitInst.data);
				end

				if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
					s0.redirect(Redirect{pc: wToken.pc, epoch:!wToken.epoch, nextPc: commitInst.addr,
										   brType: commitInst.iType, taken: commitInst.brTaken, mispredict: commitInst.mispredict});
					wbEpoch[0] <= !wbEpoch[0];
				end

				if (wb_ext_DEBUG == True) begin

					if(commitInst.iType == J || commitInst.iType == Jr || commitInst.iType == Br) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   '0,
														addr:    commitInst.addr});
					end else if(commitInst.iType == Ld) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   fromMaybe('0,commitInst.dst),
														wbRes:   loadRes,
														addr:    commitInst.addr});
					end else if(commitInst.iType == St) begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
														pc:      wToken.pc,
														rawInst: wToken.rawInst,
														iType:   commitInst.iType,
														wbDst:   '0,
														wbRes:   '0,
														addr:    commitInst.addr});
					end else begin
						commitReportQ.enq(CommitReport {cycle:   numCycles,
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


	//////////// INTERFACE ////////////

	method Action start (Addr spc);

		s0.start(spc);
		wbEpoch[1] <= False;

		if(!coreStarted) begin
			coreStarted <= True;
			commitReportQ.clear();
			messageReportQ.clear();	
		end

	endmethod

	method Action evict();

		s0.evict();

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
