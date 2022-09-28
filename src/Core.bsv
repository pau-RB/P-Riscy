import Types::*;
import ProcTypes::*;
import Scoreboard::*;
import decoder::*;
import execution::*;
import MemTypes::*;
import MemUtil::*;
import Cache::*;
import RFile::*;
import Fifo::*;
import FIFO::*;
import Vector::*;
import Ehr::*;

interface Core;

	method Action start(Addr spc);

	method ActionValue#(CommitReport) getCMR();

endinterface

module mkCore6S(WideMem mem, Core ifc);

	//////////// CORE DEBUG ////////////

	Bool wb_ext_DEBUG = False;
	Bool wb_DEBUG     = True;
	Bool perf_DEBUG   = False;


	//////////// CORE STATE ////////////

	Reg#(Addr)       pc        <- mkRegU;
	RFile            rf        <- mkBypassRFile;
	Scoreboard#(8)   sb        <- mkPipelineScoreboard;


	//////////// EPOCH ////////////

	Reg#(Bool)       feEpoch   <- mkReg(False);
	Ehr#(2,Bool)     wbEpoch   <- mkEhr(False);


	//////////// PIPELINE ////////////

	Fifo#(2,Redirect) redirectQ <- mkBypassFifo();
	Fifo#(1,DecToken)  decodeQ   <- mkStageFifo();
	Fifo#(1,RFToken)   regfetchQ <- mkStageFifo();

	Fifo#(2,ExecToken) executeQ  <- mkPipelineFifo();
	Fifo#(1,MemToken)  memoryQ   <- mkStageFifo();
	Fifo#(1,WBToken)   wrbackQ   <- mkStageFifo();


	//////////// MEMORY ////////////

	Vector#(2,WideMem) memSplit   <- mkSplitWideMem(True, mem);
	Cache              l1I        <- mkReadCache(memSplit[0]);
	Cache              l1D        <- mkNullCache(memSplit[1]);


	//////////// EXT STATE ////////////

	Reg#(Bool)          coreStarted   <- mkReg(False);
	Reg#(Data)          numCommit     <- mkReg(0);
	Reg#(Data)          numCycles     <- mkReg(0);
	FIFO#(CommitReport) commitReportQ <- mkFIFO;

	rule cntCycles if (coreStarted);
		numCycles <= numCycles+1;

		if (perf_DEBUG == True) begin
			$display("0x%h || F 0x%h | D 0x%h | R 0x%h | E 0x%h | M 0x%h | W 0x%h",
				numCycles,
				pc,
				(decodeQ.notEmpty   == True? decodeQ.first().pc   : 0),
				(regfetchQ.notEmpty == True? regfetchQ.first().pc : 0),
				(executeQ.notEmpty  == True? executeQ.first().pc  : 0),
				(memoryQ.notEmpty   == True? memoryQ.first().pc   : 0),
				(wrbackQ.notEmpty   == True? wrbackQ.first().pc   : 0)
				);
		end

	endrule


	//////////// FETCH ////////////

	rule do_fetch if (coreStarted);

		if (redirectQ.notEmpty) begin
			
			let redirect = redirectQ.first(); redirectQ.deq();
			feEpoch <= redirect.epoch;
			pc <= redirect.nextPc;

		end else begin

			l1I.req(MemReq{op: Ld, addr: pc, data: ?, func: ?});
			decodeQ.enq(DecToken{pc: pc, epoch: feEpoch});
			pc <= pc+4;

		end

	endrule


	//////////// DECODE ////////////

	rule do_decode;

		let dToken = decodeQ.first(); decodeQ.deq();
		let inst   <-l1I.resp();

		let decInst = decode(inst);
		let pc      = dToken.pc;
		let rfToken = RFToken{inst: decInst, pc: pc, epoch: dToken.epoch, rawInst: inst};

		regfetchQ.enq(rfToken);

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

			if(commitInst.iType == Ld) begin
				Data res <- l1D.resp();
        	    rf.wr(fromMaybe(?, commitInst.dst), extendLoad(res, commitInst.addr, commitInst.ldFunc));
        	end else if(isValid(commitInst.dst)) begin
				rf.wr(fromMaybe(?, commitInst.dst), commitInst.data);
			end

			if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
				redirectQ.enq(Redirect{pc: wToken.pc, epoch:!wToken.epoch, nextPc: commitInst.addr,
									   brType: commitInst.iType, taken: commitInst.brTaken, mispredict: commitInst.mispredict});
				wbEpoch[0] <= !wbEpoch[0];
			end

			if (wb_ext_DEBUG == True) begin

				if(commitInst.iType == J ||commitInst.iType == Jr || commitInst.iType == Br) begin
					if(commitInst.brTaken) begin
						commitReportQ.enq(CommitReport{cycle: numCycles, pc: wToken.pc,
										iType:wToken.inst.iType, res: commitInst.addr, rawInst: wToken.rawInst});
					end else begin
						commitReportQ.enq(CommitReport{cycle: numCycles, pc: wToken.pc,
										iType:wToken.inst.iType, res: '0, rawInst: wToken.rawInst});
					end
				end else begin
					commitReportQ.enq(CommitReport{cycle: numCycles, pc: wToken.pc,
										iType:wToken.inst.iType, res: commitInst.data, rawInst: wToken.rawInst});
				end

			end

			if (wb_DEBUG == True) begin

				if(commitInst.iType == J ||commitInst.iType == Jr || commitInst.iType == Br) begin
					if(commitInst.brTaken) begin
						$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, commitInst.addr, showInst(wToken.rawInst));
					end else begin
						$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, 0, showInst(wToken.rawInst));
					end
				end else begin
					$display(" cycle: %d | pc: 0x%h | res: 0x%h | ", numCycles, wToken.pc, commitInst.data, showInst(wToken.rawInst));
				end

			end

		end

	endrule


	//////////// INTERFACE ////////////

	method Action start (Addr spc) if (!coreStarted);

		coreStarted <= True;
		pc          <= spc;
		commitReportQ.clear();

	endmethod

	method ActionValue#(CommitReport) getCMR();

		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;

	endmethod

endmodule // mkBackend
