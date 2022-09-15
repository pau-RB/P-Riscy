import Types::*;
import ProcTypes::*;
import CMemTypes::*;
import Scoreboard::*;
import decoder::*;
import execution::*;
import DelayedMemory::*;
import RFile::*;
import FIFO::*;
import Ehr::*;

interface Core;

endinterface // backend


module mkCore5S(Core);

	//////////// CORE STATE ////////////

	Reg#(Addr)       pc        <- mkRegU;
	DelayedMemory    l1I       <- mkDelayedMemory;
	DelayedMemory    l1D       <- mkDelayedMemory;
	RFile            rf        <- mkRFile;
	Scoreboard#(5)   sb        <- mkBypassScoreboard;
	Ehr#(2,Bool)     wbEpoch   <- mkEhr(False);


	//////////// PIPELINE ////////////

	FIFO#(DecToken)  decodeQ   <- mkFIFO;
	FIFO#(ExecToken) executeQ  <- mkFIFO;
	FIFO#(MemToken)  memoryQ   <- mkFIFO;
	FIFO#(WBToken)   wrbackQ   <- mkFIFO;
	FIFO#(ContToken) redirectQ <- mkFIFO;


	//////////// FETCH ////////////

	rule do_fetch;

		l1I.req(MemReq{op: Ld, addr: pc, data: ?});
		pc <= pc+4;

	endrule


	//////////// DECODE ////////////

	rule do_decode;

		let dToken = decodeQ.first();
		let inst   = l1I.read(); l1I.resp();

		let decInst = decode(inst);
		let arg1    = rf.rd1(fromMaybe(?, decInst.src1));
		let arg2    = rf.rd2(fromMaybe(?, decInst.src2));
		let pc      = dToken.pc;
		let eToken  = ExecToken{inst: decInst, arg1: arg1, arg2: arg2, pc: pc, epoch: dToken.epoch};

		if (dToken.epoch != wbEpoch[1]) begin

			decodeQ.deq();

		end else if (!sb.search1(decInst.src1) && !sb.search1(decInst.src2)) begin

			sb.insert(decInst.dst);
			decodeQ.deq();
			executeQ.enq(eToken);

		end

	endrule


	//////////// EXECUTE ////////////

	rule do_execute;

		let eToken = executeQ.first(); executeQ.deq();

		let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, ?, ?);
		let mToken   = MemToken{inst: execInst, epoch: eToken.epoch};

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
		
			let wToken   = WBToken{inst: execInst, epoch: mToken.epoch};

			wrbackQ.enq(wToken);

		end

	endrule


	//////////// WRBACK ////////////

	rule do_wb;

		let wToken     = wrbackQ.first(); wrbackQ.deq();

		if (wToken.epoch == wbEpoch[1])  begin

			let commitInst = wToken.inst;

			if(commitInst.iType == Ld) begin
        	    rf.wr(fromMaybe(?, commitInst.dst), l1D.read());
        	    l1D.resp();
        	    sb.remove();
        	end else if(isValid(commitInst.dst)) begin
				rf.wr(fromMaybe(?, commitInst.dst), commitInst.data);
				sb.remove();
			end

			if(commitInst.brTaken) begin
				redirectQ.enq(ContToken{redirect: commitInst.addr, epoch:!wToken.epoch});
				sb.clear();
				wbEpoch[0] <= !wbEpoch[0];
			end

		end

	endrule

endmodule // mkBackend