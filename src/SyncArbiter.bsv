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

interface SyncArbiter#(numeric type e, numeric type d, numeric type n, numeric type m, type t);
	interface Vector#(e,FifoEnq#(t)) eport;
	interface FifoDeq#(Vector#(d,Maybe#(t))) dport;
	method Vector#(e,Maybe#(t)) perf_get_inst;
	method Vector#(e,Bool) perf_get_taken;
endinterface

module mkSyncArbiter(Bool coreStarted, function Bool isMemOp(t inst), SyncArbiter#(e, d, 1, 1, t) ifc) provisos(Bits#(t,tSz), FShow#(t));

	// Queues
	Vector#(e, Fifo#(1,t))         inputQueue  <- replicateM(mkStageFifo());
	Fifo#(1, Vector#(d,Maybe#(t))) outputQueue <- mkStageFifo();

	// Round robin
	Reg#(Bit#(TLog#(e))) hRoundRobin <- mkReg('0);

	// Performance debug
	Ehr#(3,Vector#(e,Maybe#(t))) perf_sel_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(3,Vector#(e,Bool             )) perf_sel_taken <- mkEhr(replicate(False));

	rule do_select if(coreStarted);

		Vector#(e,Maybe#(t)) inst     = replicate(tagged Invalid);
		Vector#(e,Bool             ) taken    = replicate(False);
		Bool                         takenAny = False;

		Vector#(d, Maybe#(t)) toExec = replicate(tagged Invalid);

		// Candidate instructions
		for (Integer i = 0; i < valueOf(e); i=i+1) begin
			if(inputQueue[i].notEmpty()) begin
				inst[i] = tagged Valid inputQueue[i].first();
			end
		end

		for (Integer i = 0; i < valueOf(e); i=i+1) begin
			Bit#(TLog#(e)) idx = hRoundRobin+fromInteger(i);
			// GP Pipeline
			for (Integer j = 1; j < valueOf(d); j=j+1) begin
				if(isValid(inst[idx]) && !taken[idx] && !isValid(toExec[j]) && !isMemOp(fromMaybe(?,inst[idx]))) begin
					toExec[j]  = inst[idx];
					taken[idx] = True;
				end
			end
			// Mem Pipeline
			if(isValid(inst[idx]) && !taken[idx] && !isValid(toExec[0])) begin
				toExec[0]  = inst[idx];
				taken[idx] = True;
			end
		end

		// Dequeue taken instructions
		for (Integer i = 0; i < valueOf(e); i=i+1) begin
			if(taken[i]) begin
				takenAny = True;
				inputQueue[i].deq();
			end
		end

		hRoundRobin <= hRoundRobin+1;

		if(takenAny) begin
			outputQueue.enq(toExec);
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
 	Vector#(e, FifoEnq#(t)) enqIfc = newVector;
 	for(Integer i = 0; i < valueOf(e); i=i+1) begin
		enqIfc[i] =
			(interface FifoEnq#(t);
				method notFull  = inputQueue[i].notFull;
				method enq(t x) = inputQueue[i].enq(x);
			endinterface);
	end

	FifoDeq#(Vector#(d,Maybe#(t))) deqIfc =
		(interface FifoDeq#(t);
			method notEmpty = outputQueue.notEmpty;
			method deq      = outputQueue.deq;
			method first    = outputQueue.first;
		endinterface);

	interface eport = enqIfc;
	interface dport = deqIfc;

	method Vector#(e,Maybe#(t)) perf_get_inst();
		return perf_sel_inst[2];
	endmethod

	method Vector#(e,Bool) perf_get_taken();
		return perf_sel_taken[2];
	endmethod

endmodule