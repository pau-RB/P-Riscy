import Types::*;
import ProcTypes::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Ehr::*;

interface Stream;

	// Flow control
	method ActionValue#(DecToken) fetch();
	method Action                 redirect(Redirect r);

	// Thread control - from upstream
	method Bool                   available();
	method Action                 start(Addr sPC);
	method Action                 evict();
	
	// Debug
	method StreamStatus           currentState();
	method Addr                   currentPC();
	method Addr                   firstPC();
	method Bool                   notEmpty();
	method Bool                   isl0Ihit();

endinterface

// evict < "do_wb" < Redirect < Fetch < l1Iresp < l1Ireq < start/available
// 0        1        2          2       2         3        3
//
// Redirect C Fetch
// Redirect C l1Ireq
//
// Fetch    C l1Ireq
//
// l1Iresp  C l1Ireq
//
module mkStream (WideMem l1I, Stream ifc);

	Ehr#(4,StreamStatus)    state     <- mkEhr(Empty);
	Ehr#(2,Addr)            pc        <- mkEhr('0);
	Reg#(Epoch)             epoch     <- mkReg('0);

	FIFOF#(DecToken)        instQ     <- mkPipelineFIFOF();
	FIFOF#(Redirect)        redirectQ <- mkBypassFIFOF();
	
	Reg  #(CacheLine)       l0I       <- mkRegU();
	Ehr  #(2, CacheLineNum) l0Iline   <- mkEhr(?);
	Ehr  #(2, Bool)         l0Ival    <- mkEhr(False);
	FIFOF#(CacheLineNum)    l1Ireq    <- mkPipelineFIFOF();

	// Note: After pc+4 we might request a new line. Then, we might receive
	// a redirect request and generate a new L1I request. When getting the
	// responses, we will only keep the last ones

	CacheLineNum pcline     = truncateLSB(pc[0]);
	CacheLineNum nextpcline = truncateLSB(pc[1]);
	Bool l0Ihit     = (pcline==l0Iline[0])&&l0Ival[0];
	Bool nextl0Ihit = (nextpcline==l0Iline[1])&&l0Ival[1];

	// 1 - Consider redirect

	rule do_redirect if (state[2] == Full || state[2] == Evict || state[2] == Ghost || state[2] == Dry);

		// Do redirect
		let redirect = redirectQ.first(); redirectQ.deq();

		if(redirect.kill) begin
			epoch <= redirect.epoch;
			state[2] <= Empty;
		end else if(redirect.dry) begin
			state[2] <= Empty;
		end else if(redirect.redirect) begin
			pc[0] <= redirect.nextPc;
			epoch <= redirect.epoch;

			if(state[2] == Evict || state[2] == Dry) begin
				state[2] <= Ghost;
			end
		end

	endrule


	// 2 - Try to fetch

	rule do_fetch if ((state[2] == Full && l0Ihit) || state[2] == Evict || state[2] == Ghost);

		if(state[2] == Full && l0Ihit) begin

			// Fetch real instruction
			CacheWordSelect wordSelect = truncate(pc[0] >> 2);
			instQ.enq(DecToken{ inst : tagged Valid l0I[wordSelect],
			                    pc   : pc[0],
			                    epoch: epoch});
			pc[0] <= pc[0]+4;

		end else if (state[2] == Evict) begin
			
			if(l0Ihit) begin

				// Fetch real instruction
				CacheWordSelect wordSelect = truncate(pc[0] >> 2);
				instQ.enq(DecToken{ inst : tagged Valid l0I[wordSelect],
				                    pc   : pc[0],
				                    epoch: epoch});
				pc[0] <= pc[0]+4;

			end else begin
				
				// Fetch ghost
				state[2] <= Dry;
				instQ.enq(DecToken{ inst : tagged Invalid,
				                    pc   : pc[0],
				                    epoch: epoch});

			end

		end else begin
			
			// Fetch ghost
			state[2] <= Dry;
			instQ.enq(DecToken{ inst : tagged Invalid,
			                    pc   : pc[0],
			                    epoch: epoch});

		end

	endrule

	// 3 - Interact with L1I

	rule do_l1Iresp;

		CacheLine data <- l1I.resp();
		l1Ireq.deq();

		if(l1Ireq.first() == nextpcline) begin
			l0I        <= data;
			l0Iline[0] <= l1Ireq.first();
			l0Ival [0] <= True;
		end

	endrule

	// 4 - Interact with l1I

	rule do_l1Ireq if (state[3] == Full && !nextl0Ihit);

    	l1I.req(WideMemReq { write: False,
    	                     num  : nextpcline,
    	                     line : ? } );
    	l1Ireq.enq(nextpcline);

	endrule

	// 5 - Consider external requests
	// Flow control
	method ActionValue#(DecToken) fetch();
		DecToken i = instQ.first(); instQ.deq();
		return i;
	endmethod	

	method Action redirect(Redirect r);
		redirectQ.enq(r);
	endmethod

	// Thread control - from upstream
	method Bool available();
		return (state[3] == Empty);
	endmethod

	method Action start(Addr sPC) if(state[3] == Empty);
		state [3] <= Full;
		pc[1]     <= sPC;
	endmethod

	method Action evict();
		if(state[0] == Full) begin
			state [0] <= Evict;
		end
	endmethod

	// Debug

	method StreamStatus currentState();
		return state[1];
	endmethod

	method Addr currentPC();
		return pc[0];
	endmethod

	method Addr firstPC();
		if(instQ.notEmpty()) begin
			return instQ.first().pc;
		end else begin
			return '0;
		end
	endmethod

	method Bool notEmpty();
		return  instQ.notEmpty();
	endmethod

	method Bool isl0Ihit();
		return  l0Ihit;
	endmethod

endmodule