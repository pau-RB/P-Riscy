import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Fifo::*;
import Ehr::*;


typedef Bit#(TSub#(AddrSz,TLog#(CacheLineBytes))) CacheLineNum;

typedef enum {
	Full,
	Evict,
	Ghost,
	Dry,
	Empty
} StreamStatus deriving(Bits, Eq, FShow);


interface Stream;

	// Flow control
	method ActionValue#(DecToken) fetch();
	method Action                 redirect(Redirect r);

	// Thread control
	method Action                 start(Addr sPC);
	method Action                 evict();
	method Action                 backendDry();
	method Addr                   currentPC();

	// Debug
	method StreamStatus           currentState();
	method Addr                   firstPC();
	method Bool                   notEmpty();
	method Bool                   isl0Ihit();

endinterface

// {Redirect, Fetch} < Thread control
// Redirect C Fetch
module mkStream (WideMem l1I, Stream ifc);

	Ehr#(2,StreamStatus)   state     <- mkEhr(Empty);
	Ehr#(2,Addr)           pc        <- mkEhr('0);
	Reg#(Bool)             epoch     <- mkReg(False);

	Fifo#(1,DecToken)      inst      <- mkStageFifo();
	Fifo#(1,Redirect)      redirectQ <- mkBypassFifo();
	Fifo#(1,void)          dryQ      <- mkBypassFifo();
	
	Reg #(CacheLine)       l0I       <- mkRegU();
	Reg #(CacheLineNum)    l0Iline   <- mkRegU();
	Reg #(Bool)            l0Ival    <- mkReg(False);
	Fifo#(1, CacheLineNum) l1Ireq    <- mkPipelineFifo();

	// Note: After pc+4 we might request a new line. Then, we might receive
	// a redirect request and generate a new L1I request. When getting the
	// responses, we will only keep the last ones

	CacheLineNum pcline = truncateLSB(pc[0]);
	Bool l0Ihit = (pcline==l0Iline)&&l0Ival;

	// 0 - Interact with L1I

	rule do_l1Ireq;

		CacheLineNum nextpcline = truncateLSB(pc[1]);

		if(nextpcline != l0Iline) begin
    		l1I.req(WideMemReq {
        	        		write_en: '0,
        	        		addr:     {nextpcline,'0},
        	        		data:     ?             });
    		l1Ireq.enq(pcline);
    	end

	endrule

	rule do_l1Iresp;

		CacheLine data <- l1I.resp();

		l0I     <= data;
		l0Iline <= l1Ireq.first(); l1Ireq.deq();
		l0Ival  <= True;

	endrule
	

	// 1 - Consider redirect

	rule do_redirect if (state[0] == Full || state[0] == Evict || state[0] == Ghost || state[0] == Dry);

		// Do redirect
		let redirect = redirectQ.first(); redirectQ.deq();
		pc[0] <= redirect.nextPc;
		epoch <= redirect.epoch;

		if(state[0] == Evict || state[0] == Dry) begin
			state[0] <= Ghost;
		end

	endrule


	// 2 - Try to fetch

	rule do_fetch if ((state[0] == Full && l0Ihit) || state[0] == Evict || state[0] == Ghost);

		if(state[0] == Full && l0Ihit) begin

			// Fetch real instruction
			CacheWordSelect wordSelect = truncate(pc[0] >> 2);
			inst.enq(DecToken{ inst:  l0I[wordSelect],
							   pc:    pc[0],
							   ghost: False,
							   epoch: epoch});
			pc[0] <= pc[0]+4;

		end else if (state[0] == Evict) begin
			
			if(l0Ihit) begin

				// Fetch real instruction
				CacheWordSelect wordSelect = truncate(pc[0] >> 2);
				inst.enq(DecToken{ inst:  l0I[wordSelect],
								   pc:    pc[0],
								   ghost: False,
								   epoch: epoch});
				pc[0] <= pc[0]+4;

			end else begin
				
				// Fetch ghost
				state[0] <= Dry;
				inst.enq(DecToken{ inst:  ?,
								   pc:    pc[0],
								   ghost: True,
								   epoch: epoch});

			end

		end else begin
			
			// Fetch ghost
			state[0] <= Dry;
			inst.enq(DecToken{ inst:  ?,
							   pc:    pc[0],
							   ghost: True,
							   epoch: epoch});

		end

	endrule

	// 3 - Check if pipeline is flush

	rule do_dry if(state[0] == Dry);

		dryQ.deq();
		state[0] <= Empty;

	endrule

	// 4 - Consider external requests

	method Action start(Addr sPC) if(state[1] == Empty);
		state [1] <= Full;
		pc[1]     <= sPC;
		epoch     <= False;
	endmethod


	method Action evict()         if(state[0] == Full);
		state [0] <= Evict;
	endmethod


	method Action backendDry()    if(state[0] == Dry);
		dryQ.enq(?);
	endmethod


	// Attend backend requests

	method ActionValue#(DecToken) fetch();
		DecToken i = inst.first(); inst.deq();
		return i;
	endmethod	

	method Action redirect(Redirect r);
		redirectQ.enq(r);
	endmethod

	method Addr currentPC();
		return pc[0];
	endmethod

	method StreamStatus currentState();
		return state[0];
	endmethod

	method Addr firstPC();
		if(inst.notEmpty()) begin
			return inst.first().pc;
		end else begin
			return '0;
		end
	endmethod

	method Bool notEmpty();
		return  inst.notEmpty();
	endmethod

	method Bool isl0Ihit();
		return  l0Ihit;
	endmethod

endmodule