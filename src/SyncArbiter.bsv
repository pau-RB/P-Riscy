import Types::*;
import Config::*;
import Fifo::*;
import CMRTypes::*;
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

	// IO
	interface Vector#(n,FifoEnq#(t)) eport;
	interface FifoDeq#(Vector#(m,Maybe#(t))) dport;

	// Performance debug
	method Vector#(n,Maybe#(t)) perf_get_inst;
	method Vector#(n,Bool) perf_get_taken;

	// Stats
	method ArbiterStat getStat();

endinterface

module mkSyncArbiter(Bool                                     coreStarted,
	                 Vector#(m, function Bool accept(t inst)) filter1    ,
	                 Vector#(m, function Bool accept(t inst)) filter2    ,
	                 SyncArbiter#(n, m, t) ifc) provisos(Bits#(t,tSz), FShow#(t));

	// Queues
	Vector#(n, Fifo#(1,t))         inputQueue  <- replicateM(mkStageFifo());
	Fifo#(1, Vector#(m,Maybe#(t))) outputQueue <- mkStageFifo();

	// Performance debug
	Ehr#(3,Vector#(n,Maybe#(t))) perf_sel_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(3,Vector#(n,Bool     )) perf_sel_taken <- mkEhr(replicate(False));

	// Stats
	Reg#(Data) numMemOvb   <- mkReg(0);
	Reg#(Data) numArithOvb <- mkReg(0);
	Reg#(Data) numEmpty    <- mkReg(0);

	//////////// SELECT ////////////

	Vector#(n,Reg#(Bool)) selectPriority <- replicateM(mkReg(True));

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
			for (Integer j = 0; j < valueOf(m); j=j+1) begin
				if(isValid(inst[i]) && !taken[i] && !isValid(forward[j]) && filter1[j](fromMaybe(?,inst[i])) && selectPriority[i]) begin
					forward[j] = inst[i];
					taken  [i] = True;
				end
			end
		end

		for (Integer i = 0; i < valueOf(n); i=i+1) begin
			for (Integer j = 0; j < valueOf(m); j=j+1) begin
				if(isValid(inst[i]) && !taken[i] && !isValid(forward[j]) && filter2[j](fromMaybe(?,inst[i]))) begin
					forward[j] = inst[i];
					taken  [i] = True;
				end
			end
		end

		// Dequeue taken instructions
		for (Integer i = 0; i < valueOf(n); i=i+1) begin
			if(taken[i]) begin
				takenAny = True;
				inputQueue[i].deq();
				selectPriority[i] <= False;
			end else begin
				selectPriority[i] <= True;
			end
		end

		if(takenAny) begin
			outputQueue.enq(forward);
		end

		if(perf_DEBUG) begin
			perf_sel_taken[0] <= taken;
			perf_sel_inst [0] <= inst;
		end

		if(mem_ext_DEBUG) begin

			Bool isMemOvb   = False;
			Bool isArithOvb = False;
			for(Integer i = 0; i < valueOf(n); i=i+1)
				if(isValid(inst[i]) && !taken[i])
					if(filter1[0](fromMaybe(?,inst[i])))
						isMemOvb = True;
					else
						isArithOvb = True;
			if(isMemOvb)
				numMemOvb <= numMemOvb+1;
			if(isArithOvb)
				numArithOvb <= numArithOvb+1;

			Bool isEmpty = True;
			for(Integer i = 0; i < valueOf(n); i=i+1)
				if(isValid(inst[i]))
					isEmpty = False;
			if(isEmpty)
				numEmpty <= numEmpty+1;

		end

	endrule

	rule do_reset if(coreStarted && perf_DEBUG);

		perf_sel_inst [2] <= replicate(tagged Invalid);
		perf_sel_taken[2] <= replicate(False);

	endrule

	//////////// INTERFACE ////////////

	// IO
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

	// Performance debug
	method Vector#(n,Maybe#(t)) perf_get_inst();
		return perf_sel_inst[2];
	endmethod

	method Vector#(n,Bool) perf_get_taken();
		return perf_sel_taken[2];
	endmethod

	// Stats
	method ArbiterStat getStat();
		return ArbiterStat{ memOvb   : numMemOvb,
		                    arithOvb : numArithOvb,
		                    empty    : numEmpty};
	endmethod

endmodule