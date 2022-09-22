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

	Bool wb_DEBUG = True;


	//////////// CORE STATE ////////////

	Reg#(Addr)       pc        <- mkRegU;
	RFile            rf        <- mkRFile;
	Scoreboard#(5)   sb        <- mkBypassScoreboard;


	//////////// EPOCH ////////////

	Reg#(Bool)       feEpoch   <- mkReg(False);
	Ehr#(2,Bool)     wbEpoch   <- mkEhr(False);


	//////////// PIPELINE ////////////

	FIFO#(DecToken)  decodeQ   <- mkFIFO;
	FIFO#(RFToken)   regfetchQ <- mkFIFO;
	FIFO#(ExecToken) executeQ  <- mkFIFO;
	FIFO#(MemToken)  memoryQ   <- mkFIFO;
	FIFO#(WBToken)   wrbackQ   <- mkFIFO;
	FIFO#(ContToken) redirectQ <- mkFIFO;


	//////////// MEMORY ////////////

	Vector#(2,WideMem) memSplit   <- mkSplitWideMem(True, mem);
	Cache              l1I        <- mkNullCache(memSplit[0]);
	Cache              l1D        <- mkNullCache(memSplit[1]);


	//////////// EXT STATE ////////////

	Reg#(Bool)          coreStarted   <- mkReg(False);
	Reg#(Data)          numCommit     <- mkReg(0);
	Reg#(Data)          numCycles     <- mkReg(0);
	FIFO#(CommitReport) commitReportQ <- mkFIFO;

	rule cntCycles if (coreStarted);
		numCycles <= numCycles+1;
	endrule


	//////////// FETCH ////////////

	rule do_fetch if (coreStarted);

		if (wbEpoch[0] == feEpoch) begin
			
			l1I.req(MemReq{op: Ld, addr: pc, data: ?});
			decodeQ.enq(DecToken{pc: pc, epoch: feEpoch});
			pc <= pc+4;
		
		end else begin
			
			let redirect = redirectQ.first(); redirectQ.deq();
			feEpoch <= redirect.epoch;
			pc <= redirect.pc;

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

	rule do_regfetch;

		let rfToken = regfetchQ.first();
		let decInst = rfToken.inst;

		if (rfToken.epoch != wbEpoch[0]) begin

			regfetchQ.deq();

		end else if (!sb.search1(decInst.src1) && !sb.search2(decInst.src2)) begin
			
			let arg1    = rf.rd1(fromMaybe(?, decInst.src1));
			let arg2    = rf.rd2(fromMaybe(?, decInst.src2));
			let eToken  = ExecToken{inst: decInst, arg1: arg1, arg2: arg2, pc: rfToken.pc, epoch: rfToken.epoch, rawInst: rfToken.rawInst};

			sb.insert(decInst.dst);
			regfetchQ.deq();
			executeQ.enq(eToken);

		end

	endrule


	//////////// EXECUTE ////////////

	rule do_execute;

		let eToken = executeQ.first(); executeQ.deq();

		let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4, ?);
		let mToken   = MemToken{inst: execInst, pc:eToken.pc, epoch: eToken.epoch, rawInst: eToken.rawInst};

		memoryQ.enq(mToken);

	endrule

 
	//////////// MEMORY ////////////

	rule do_mem;

		let mToken   = memoryQ.first(); memoryQ.deq();

		let execInst = mToken.inst;

		if (mToken.epoch == wbEpoch[1]) begin

			if(execInst.iType == Ld) begin
        	    l1D.req(MemReq{op: Ld, addr: execInst.addr, data: ?});
        	end else if(execInst.iType == St) begin
        	    l1D.req(MemReq{op: St, addr: execInst.addr, data: execInst.data});
        	end
		
			let wToken   = WBToken{inst: execInst, pc: mToken.pc, epoch: mToken.epoch,  rawInst: mToken.rawInst};

			wrbackQ.enq(wToken);

		end

	endrule


	//////////// WRBACK ////////////

	rule do_wb;

		let wToken     = wrbackQ.first(); wrbackQ.deq();

		if (wToken.epoch == wbEpoch[0])  begin

			let commitInst = wToken.inst;
			sb.remove();

			if(commitInst.iType == Ld) begin
				Data res <- l1D.resp();
        	    rf.wr(fromMaybe(?, commitInst.dst), res);
        	end else if(isValid(commitInst.dst)) begin
				rf.wr(fromMaybe(?, commitInst.dst), commitInst.data);
			end

			if(commitInst.brTaken) begin
				redirectQ.enq(ContToken{pc: commitInst.addr, epoch:!wToken.epoch});
				sb.clear();
				wbEpoch[0] <= !wbEpoch[0];
			end

			if (wb_DEBUG == True) begin

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
