import Types::*;
import ProcTypes::*;
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

interface SyncArbiter;

	// IO
	interface Vector#(FrontWidth,FifoEnq#(ExecToken)) eport;
	interface FifoDeq#(Vector#(BackWidth,Maybe#(ExecToken))) dport;

	// Performance debug
	method Vector#(FrontWidth,Maybe#(ExecToken)) perf_get_inst;
	method Vector#(FrontWidth,Bool) perf_get_taken;

	// Stats
	method ArbiterStat getStat();

endinterface


function Bool isAnyInst(ExecToken inst);
	return True;
endfunction

function Bool isNonInst(ExecToken inst);
	return False;
endfunction

function Bool isMemInst(ExecToken inst);
	return (inst.inst.iType == Ld          || inst.inst.iType == St    ||
	        inst.inst.iType == Fork        || inst.inst.iType == Forkr ||
	        inst.inst.iType == Join        || inst.inst.iType == Ghost );
endfunction

function Bool isArithInst(ExecToken inst);
	return (inst.inst.iType == Unsupported || inst.inst.iType == Alu   ||
	        inst.inst.iType == Mul         || inst.inst.iType == J     ||
	        inst.inst.iType == Jr          || inst.inst.iType == Br    ||
	        inst.inst.iType == Auipc );
endfunction


typedef struct {
	Vector#(FrontWidth,Bool)             taken;
	Vector#(BackWidth,Maybe#(ExecToken)) forward; 	
} InstSelect deriving(Bits);


(*noinline*) function InstSelect select(Vector#(FrontWidth,Maybe#(ExecToken)) inst, Vector#(FrontWidth,Bool) instPriority);

	Vector#(BackWidth,Maybe#(ExecToken)) forward  = replicate(tagged Invalid);
	Vector#(FrontWidth,Bool)             taken    = replicate(False);

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		if(isValid(inst[i]) && !taken[i] && !isValid(forward[0]) && isMemInst(fromMaybe(?,inst[i]))) begin
			forward[0] = inst[i];
			taken  [i] = True;
		end

		for (Integer j = 1; j < valueOf(BackWidth); j=j+1) begin
			if(isValid(inst[i]) && !taken[i] && !isValid(forward[j]) && isArithInst(fromMaybe(?,inst[i]))) begin
				forward[j] = inst[i];
				taken  [i] = True;
			end
		end

	end
/*
	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		if(isValid(inst[i]) && !taken[i] && !isValid(forward[0]) && isAnyInst(fromMaybe(?,inst[i]))) begin
			forward[0] = inst[i];
			taken  [i] = True;
		end

		for (Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
			if(isValid(inst[i]) && !taken[i] && !isValid(forward[j]) && isArithInst(fromMaybe(?,inst[i]))) begin
				forward[j] = inst[i];
				taken  [i] = True;
			end
		end

	end
*/
	return InstSelect{ taken: taken, forward: forward};

endfunction


module mkSyncArbiter(SyncArbiter ifc);

	// Queues
	Vector#(FrontWidth, Fifo#(1,ExecToken))        inputQueue  <- replicateM(mkStageFifo());
	Fifo#(1, Vector#(BackWidth,Maybe#(ExecToken))) outputQueue <- mkStageFifo();

	// Performance debug
	Ehr#(3,Vector#(FrontWidth,Maybe#(ExecToken)))  perf_sel_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(3,Vector#(FrontWidth,Bool             ))  perf_sel_taken <- mkEhr(replicate(False));

	// Stats
	Reg#(Data) numMemOvb   <- mkReg(0);
	Reg#(Data) numArithOvb <- mkReg(0);
	Reg#(Data) numEmpty    <- mkReg(0);

	//////////// SELECT ////////////

	Vector#(FrontWidth,Reg#(Bool)) selectPriority <- replicateM(mkReg(True));

	rule do_select;

		Vector#(FrontWidth,Maybe#(ExecToken)) inst         = replicate(tagged Invalid);
		Vector#(FrontWidth,Bool             ) instPriority = replicate(False);
		Bool takenAny = False;

		// Candidate instructions
		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty()) begin
				inst        [i] = tagged Valid inputQueue[i].first();
				instPriority[i] = selectPriority[i];
			end
		end

		// Select
		InstSelect sel = select(inst, instPriority);

		// Dequeue taken instructions
		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(sel.taken[i]) begin
				takenAny = True;
				inputQueue[i].deq();
				selectPriority[i] <= False;
			end else begin
				selectPriority[i] <= True;
			end
		end

		if(takenAny) begin
			outputQueue.enq(sel.forward);
		end

		if(perf_DEBUG) begin
			perf_sel_taken[0] <= sel.taken;
			perf_sel_inst [0] <= inst;
		end

		if(mem_ext_DEBUG) begin

			Bool isMemOvb   = False;
			Bool isArithOvb = False;
			for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
				if(isValid(inst[i]) && !sel.taken[i])
					if(isMemInst(fromMaybe(?,inst[i])))
						isMemOvb = True;
					else
						isArithOvb = True;
			if(isMemOvb)
				numMemOvb <= numMemOvb+1;
			if(isArithOvb)
				numArithOvb <= numArithOvb+1;

			Bool isEmpty = True;
			for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
				if(isValid(inst[i]))
					isEmpty = False;
			if(isEmpty)
				numEmpty <= numEmpty+1;

		end

	endrule

	rule do_reset if(perf_DEBUG);

		perf_sel_inst [2] <= replicate(tagged Invalid);
		perf_sel_taken[2] <= replicate(False);

	endrule

	//////////// INTERFACE ////////////

	// IO
 	Vector#(FrontWidth, FifoEnq#(ExecToken)) enqIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		enqIfc[i] =
			(interface FifoEnq#(ExecToken);
				method notFull  = inputQueue[i].notFull;
				method enq(ExecToken x) = inputQueue[i].enq(x);
			endinterface);
	end

	FifoDeq#(Vector#(BackWidth,Maybe#(ExecToken))) deqIfc =
		(interface FifoDeq#(ExecToken);
			method notEmpty = outputQueue.notEmpty;
			method deq      = outputQueue.deq;
			method first    = outputQueue.first;
		endinterface);

	interface eport = enqIfc;
	interface dport = deqIfc;

	// Performance debug
	method Vector#(FrontWidth,Maybe#(ExecToken)) perf_get_inst();
		return perf_sel_inst[2];
	endmethod

	method Vector#(FrontWidth,Bool) perf_get_taken();
		return perf_sel_taken[2];
	endmethod

	// Stats
	method ArbiterStat getStat();
		return ArbiterStat{ memOvb   : numMemOvb,
		                    arithOvb : numArithOvb,
		                    empty    : numEmpty};
	endmethod

endmodule