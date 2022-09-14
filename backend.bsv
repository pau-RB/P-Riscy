import Types::*;
import ProcTypes::*;
import CMemTypes::*;
import BackendTypes::*;
import Scoreboard::*;
import decoder::*;
import execution::*;
import DelayedMemory::*;
import RFile::*;
import FIFO::*;

interface Backend;
	
	//method Action    setRegFile ( RegSet data );
	//method RegSet    getRegFile ();
	method Action    execute    ( DecToken e );
	method ContToken getRedirect();
	method Action    deqRedirect();

endinterface // backend


module mkBackend4S(Backend);

	//////////// BE STATE ////////////

	RFile            rf        <- mkRFile;
	Scoreboard#(5)   sb        <- mkBypassScoreboard;

	//////////// MEM ////////////

	DelayedMemory    l1D       <- mkDelayedMemory;

	//////////// PIPELINE ////////////

	FIFO#(DecToken)  decodeQ   <- mkFIFO;
	FIFO#(ExecToken) executeQ  <- mkFIFO;
	FIFO#(MemToken)  memoryQ   <- mkFIFO;
	FIFO#(WBToken)   wrbackQ   <- mkFIFO;
	FIFO#(ContToken) redirectQ <- mkFIFO;

	//////////// EPOCH ////////////

	Reg#(Bool)       wbEpoch   <- mkReg(False);

	//////////// DECODE ////////////

	rule do_decode;

		let dToken = decodeQ.first();

		let decInst = decode(dToken.inst);
		let arg1    = rf.rd1(fromMaybe(?, decInst.src1));
		let arg2    = rf.rd2(fromMaybe(?, decInst.src2));
		let pc      = dToken.pc;
		let eToken  = ExecToken{inst: decInst, arg1: arg1, arg2: arg2, pc: pc, epoch: dToken.epoch};

		if (dToken.epoch != wbEpoch) begin

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

		if (mToken.epoch == wbEpoch) begin

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

		if (wToken.epoch != wbEpoch) begin

			let commitInst = wToken.inst;
			
			if(commitInst.iType == Ld) begin
        	    l1D.resp();
        	    sb.remove();
        	end else if(isValid(commitInst.dst)) begin
				sb.remove();
			end

		end else begin

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
				wbEpoch <= !wbEpoch;
			end

		end

	endrule


	//////////// REGFILE ////////////
	/*
	method Action setRegFile( RegSet data );

		rf.wrSet(data);

	endmethod

	method RegSet getRegFile();

		return rf.rdSet();

	endmethod
	*/

	//////////// IO ////////////

	method Action execute( DecToken e );

		decodeQ.enq(e);

	endmethod

	method ContToken getRedirect ();

		return redirectQ.first();

	endmethod

	method Action deqRedirect ();

		redirectQ.deq();

	endmethod

endmodule // mkBackend