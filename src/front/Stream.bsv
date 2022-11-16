import Types::*;
import ProcTypes::*;
import Fifo::*;
import Ehr::*;



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

	// Thread control - from downstream
	method Action                 backendKill(Bool epoch);
	method Action                 backendDry();

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

// evict < "do_wb" < do_Kill < Redirect < Fetch < l1Iresp < do_dry < l1Ireq < start/available
// 0        1        1         2          2       2         2        3        3
//
// Kill     C Fetch
//
// Redirect C Fetch
// Redirect C do_dry
// Redirect C l1Ireq
//
// Redirect C do_dry
// Fetch    C l1Ireq
//
// l1Iresp  C l1Ireq
//
module mkStream (WideMem l1I, Stream ifc);

	Ehr#(4,StreamStatus)   state     <- mkEhr(Empty);
	Ehr#(2,Addr)           pc        <- mkEhr('0);
	Reg#(Bool)             epoch     <- mkReg(False);

	Fifo#(1,DecToken)      inst      <- mkStageFifo();
	Fifo#(1,Redirect)      redirectQ <- mkBypassFifo();
	Fifo#(1,Bool)          killQ     <- mkBypassFifo();
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

	// 0 - Consider kills
	rule do_kill if(state[1] != Empty);

		Bool newEpoch = killQ.first(); killQ.deq();
		epoch    <= newEpoch;
		state[1] <= Empty;

	endrule

	// 1 - Consider redirect

	rule do_redirect if (state[2] == Full || state[2] == Evict || state[2] == Ghost || state[2] == Dry);

		// Do redirect
		let redirect = redirectQ.first(); redirectQ.deq();
		pc[0] <= redirect.nextPc;
		epoch <= redirect.epoch;

		if(state[2] == Evict || state[2] == Dry) begin
			state[2] <= Ghost;
		end

	endrule


	// 2 - Try to fetch

	rule do_fetch if ((state[2] == Full && l0Ihit) || state[2] == Evict || state[2] == Ghost);

		if(state[2] == Full && l0Ihit) begin

			// Fetch real instruction
			CacheWordSelect wordSelect = truncate(pc[0] >> 2);
			inst.enq(DecToken{ inst:  l0I[wordSelect],
							   pc:    pc[0],
							   ghost: False,
							   epoch: epoch});
			pc[0] <= pc[0]+4;

		end else if (state[2] == Evict) begin
			
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
				state[2] <= Dry;
				inst.enq(DecToken{ inst:  ?,
								   pc:    pc[0],
								   ghost: True,
								   epoch: epoch});

			end

		end else begin
			
			// Fetch ghost
			state[2] <= Dry;
			inst.enq(DecToken{ inst:  ?,
							   pc:    pc[0],
							   ghost: True,
							   epoch: epoch});

		end

	endrule

	// 3 - Interact with L1I

	rule do_l1Iresp;

		CacheLine data <- l1I.resp();

		l0I     <= data;
		l0Iline <= l1Ireq.first(); l1Ireq.deq();
		l0Ival  <= True;

	endrule

	// 4 - Check if pipeline is flush

	rule do_dry if(state[2] == Dry);

		dryQ.deq();
		state[2] <= Empty;

	endrule

	// 5 - Interact with l1I

	rule do_l1Ireq if (state[3] == Full);

		CacheLineNum nextpcline = truncateLSB(pc[1]);

		if(nextpcline != l0Iline) begin
    		l1I.req(WideMemReq {
        	        		write_en: '0,
        	        		addr:     {nextpcline,'0},
        	        		data:     ?             });
    		l1Ireq.enq(pcline);
    	end

	endrule

	// 6 - Consider external requests
	// Flow control
	method ActionValue#(DecToken) fetch();
		DecToken i = inst.first(); inst.deq();
		return i;
	endmethod	

	method Action redirect(Redirect r);
		redirectQ.enq(r);
	endmethod

	// Thread control - from downstream
	method Action backendKill(Bool epoch)   if(state[1] != Empty);
		killQ.enq(epoch);
	endmethod

	method Action backendDry()    if(state[1] == Dry);
		dryQ.enq(?);
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