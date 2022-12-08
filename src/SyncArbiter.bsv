import Config::*;
import Fifo::*;
import Vector::*;
import Ehr::*;

interface FifoEnq#(type t);
	method Bool notFull;
	method Action enq(t x);
endinterface

interface FifoDeq#(type t);
	method Bool notEmpty;
	method Action deq;
	method t first;
endinterface

interface SyncArbiter#(numeric type n, numeric type m, type t);
	interface Vector#(n,FifoEnq#(t)) eport;
	interface FifoDeq#(Vector#(m,Maybe#(t))) dport;
	method Vector#(n,Maybe#(t)) perf_get_inst;
	method Vector#(n,Bool) perf_get_taken;
endinterface

module mkSyncArbiter(Bool coreStarted, Vector#(m, function Bool accept(t inst)) filter, SyncArbiter#(n, m, t) ifc) provisos(Bits#(t,tSz), FShow#(t));

	// Queues
	Vector#(n, Fifo#(1,t))         inputQueue  <- replicateM(mkStageFifo());
	Fifo#(1, Vector#(m,Maybe#(t))) outputQueue <- mkStageFifo();

	// Round robin
	Reg#(Bit#(TLog#(n))) hRoundRobin <- mkReg('0);

	// Performance debug
	Ehr#(3,Vector#(n,Maybe#(t))) perf_sel_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(3,Vector#(n,Bool     )) perf_sel_taken <- mkEhr(replicate(False));

	rule do_select if(coreStarted);

		Vector#(n,Maybe#(t)) inst     = replicate(tagged Invalid);
		Vector#(m,Maybe#(t)) forward  = replicate(tagged Invalid);
		Vector#(n,Bool)      taken    = replicate(False);
		Bool                 takenAny = False;

		// Candidate instructions
		for (Integer i = 0; i < valueOf(n); i=i+1) begin
			if(inputQueue[i].notEmpty()) begin
				inst[i] = tagged Valid inputQueue[i].first();
			end
		end

		// Select
		for (Integer i = 0; i < valueOf(n); i=i+1) begin
			Bit#(TLog#(n)) idx = hRoundRobin+fromInteger(i);
			for (Integer j = 0; j < valueOf(m); j=j+1) begin
				if(isValid(inst[idx]) && !taken[idx] && !isValid(forward[j]) && filter[j](fromMaybe(?,inst[idx]))) begin
					forward[j] = inst[idx];
					taken[idx] = True;
				end
			end
		end

		// Dequeue taken instructions
		for (Integer i = 0; i < valueOf(n); i=i+1) begin
			if(taken[i]) begin
				takenAny = True;
				inputQueue[i].deq();
			end
		end

		hRoundRobin <= hRoundRobin+1;

		if(takenAny) begin
			outputQueue.enq(forward);
		end

		if(perf_DEBUG) begin
			perf_sel_taken[0] <= taken;
			perf_sel_inst [0] <= inst;
		end

	endrule

	rule do_reset if(coreStarted && perf_DEBUG);

		perf_sel_inst [2] <= replicate(tagged Invalid);
		perf_sel_taken[2] <= replicate(False);

	endrule

	// Interface
 	Vector#(n, FifoEnq#(t)) enqIfc = newVector;
 	for(Integer i = 0; i < valueOf(n); i=i+1) begin
		enqIfc[i] =
			(interface FifoEnq#(t);
				method notFull  = inputQueue[i].notFull;
				method enq(t x) = inputQueue[i].enq(x);
			endinterface);
	end

	FifoDeq#(Vector#(m,Maybe#(t))) deqIfc =
		(interface FifoDeq#(t);
			method notEmpty = outputQueue.notEmpty;
			method deq      = outputQueue.deq;
			method first    = outputQueue.first;
		endinterface);

	interface eport = enqIfc;
	interface dport = deqIfc;

	method Vector#(n,Maybe#(t)) perf_get_inst();
		return perf_sel_inst[2];
	endmethod

	method Vector#(n,Bool) perf_get_taken();
		return perf_sel_taken[2];
	endmethod

endmodule