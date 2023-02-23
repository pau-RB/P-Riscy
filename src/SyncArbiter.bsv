import Types::*;
import ProcTypes::*;
import Config::*;
import FIFOF::*;
import SpecialFIFOs::*;
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

	// Redirect

	interface Vector#(FrontWidth,FifoEnq#(Redirect)) enqRedirect;
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// Performance debug
	method Vector#(FrontWidth,Maybe#(ExecToken)) perf_get_inst;
	method Vector#(FrontWidth,Bool) perf_get_taken;

	// Stats
	method ArbiterStat getStat();

endinterface

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

function Bool isSpecInst(ExecToken inst);
	return (inst.inst.iType == J           || inst.inst.iType == Jr    ||
	        inst.inst.iType == Br          || inst.inst.iType == Ld    ||
	        inst.inst.iType == St          || inst.inst.iType == Join  );
endfunction

typedef Bit#(3) SpecLvl;

typedef struct {
	Bool      valid;
	FrontID   feID;
	SpecLvl   specLvl;
	ExecToken inst;
} ASNinst deriving(Bits);

(*noinline*) function Vector#(FrontWidth,ASNinst) evenLayer (Vector#(FrontWidth,ASNinst) in) provisos(Add#(a__,a__,FrontWidth));
	Vector#(FrontWidth,ASNinst) out;
	for (Integer i = 0; i+1 < valueOf(FrontWidth); i=i+2) begin
		Bool switch = !in[i].valid || (in[i+1].valid && in[i+1].specLvl[2:1] < in[i].specLvl[2:1]);
		out[i  ] = switch ? in[i+1] : in[i  ];
		out[i+1] = switch ? in[i  ] : in[i+1];
	end
	return out;
endfunction

(*noinline*) function Vector#(FrontWidth,ASNinst) oddLayer (Vector#(FrontWidth,ASNinst) in) provisos(Add#(a__,a__,FrontWidth));
	Vector#(FrontWidth,ASNinst) out;
	out[0] = in[0]; out[valueOf(FrontWidth)-1] = in[valueOf(FrontWidth)-1];
	for (Integer i = 1; i+1 < valueOf(FrontWidth); i=i+2) begin
		Bool switch = !in[i].valid || (in[i+1].valid && in[i+1].specLvl[2:1] < in[i].specLvl[2:1]);
		out[i  ] = switch ? in[i+1] : in[i  ];
		out[i+1] = switch ? in[i  ] : in[i+1];
	end
	return out;
endfunction

(*noinline*) function Vector#(FrontWidth,ASNinst) arbSortNet (Vector#(FrontWidth,ASNinst) inst) provisos(Add#(a__,a__,FrontWidth));
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
		inst = oddLayer(evenLayer(inst));
	return inst;
endfunction

module mkSyncArbiter(Bool coreStarted, SyncArbiter ifc) provisos(Add#(a__,BackWidth,FrontWidth));

	// Queues
	Vector#(FrontWidth, FIFOF#(ExecToken))        inputQueue  <- replicateM(mkPipelineFIFOF());
	FIFOF#(Vector#(BackWidth, Maybe#(ExecToken))) outputQueue <- mkPipelineFIFOF();

	// Redirect
	Vector#(FrontWidth, Reg#(Epoch)) arbiterEpoch <- replicateM(mkReg('0));
	Vector#(FrontWidth, FIFOF#(Redirect)) redInpQ <- replicateM(mkBypassFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect)) redOutQ <- replicateM(mkBypassFIFOF());

	// Speculation counter
	Vector#(FrontWidth,Reg#(SpecLvl))             specLvl <- replicateM(mkReg('0));

	// Performance debug
	Ehr#(3,Vector#(FrontWidth,Maybe#(ExecToken))) perf_sel_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(3,Vector#(FrontWidth,Bool             )) perf_sel_taken <- mkEhr(replicate(False));

	// Stats
	Reg#(Data) numMemOvb   <- mkReg(0);
	Reg#(Data) numArithOvb <- mkReg(0);
	Reg#(Data) numEmpty    <- mkReg(0);

	//////////// SELECT ////////////

	rule do_select if(coreStarted);

		// Prepare inst

		Vector#(FrontWidth,ASNinst) memInst;
		Vector#(FrontWidth,ASNinst) ariInst;

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty && inputQueue[i].first.epoch ==  arbiterEpoch[i] && isMemInst(inputQueue[i].first))
				memInst[i] = ASNinst{valid: True, feID: fromInteger(i), specLvl: specLvl[i], inst: inputQueue[i].first};
			else
				memInst[i] = ASNinst{valid: False, feID: ?, specLvl: ?, inst: ?};
		end

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty && inputQueue[i].first.epoch ==  arbiterEpoch[i] && isArithInst(inputQueue[i].first))
				ariInst[i] = ASNinst{valid: True, feID: fromInteger(i), specLvl: specLvl[i], inst: inputQueue[i].first};
			else
				ariInst[i] = ASNinst{valid: False, feID: ?, specLvl: ?, inst: ?};
		end

		// Sort inst according to validity

		memInst = arbSortNet(memInst);
		ariInst = arbSortNet(ariInst);

		Vector#(BackWidth,Maybe#(ExecToken)) instForward;

		instForward[0] = memInst[0].valid ? tagged Valid memInst[0].inst : tagged Invalid;
		for(Integer j = 1; j < valueOf(BackWidth); j=j+1)
			instForward[j] = ariInst[j-1].valid ? tagged Valid ariInst[j-1].inst : tagged Invalid;

		// Dequeue taken inst

		Vector#(FrontWidth, Bool) instTaken = replicate(False);

		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			instTaken[i] = (memInst[0].valid && memInst[0].feID == fromInteger(i));
			for(Integer j = 1; j < valueOf(BackWidth); j=j+1)
				instTaken[i] = instTaken[i] || (ariInst[j-1].valid && ariInst[j-1].feID == fromInteger(i));
		end

		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty && (instTaken[i] || inputQueue[i].first.epoch !=  arbiterEpoch[i]))
				inputQueue[i].deq();
			if(inputQueue[i].notEmpty && instTaken[i] && isSpecInst(inputQueue[i].first))
				specLvl[i] <= '1;
			else if(specLvl[i] != '0)
				specLvl[i] <= specLvl[i]-1;
		end
				
		// Forward

		if(unpack(|(pack(instTaken))))
			outputQueue.enq(instForward);


		if(perf_DEBUG) begin

			Vector#(FrontWidth,Maybe#(ExecToken)) inst = replicate(tagged Invalid);
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1)
				if(inputQueue[i].notEmpty)
					inst[i] = tagged Valid inputQueue[i].first();

			perf_sel_taken[0] <= instTaken;
			perf_sel_inst [0] <= inst;

		end

		if(mem_ext_DEBUG) begin

			Vector#(FrontWidth,Maybe#(ExecToken)) inst = replicate(tagged Invalid);
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1)
				if(inputQueue[i].notEmpty)
					inst[i] = tagged Valid inputQueue[i].first();

			Bool isMemOvb   = False;
			Bool isArithOvb = False;
			for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
				if(isValid(inst[i]) && !instTaken[i])
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

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
		rule do_redirect;
			Redirect red = redInpQ[i].first(); redInpQ[i].deq(); redOutQ[i].enq(red);
			if(red.kill || red.redirect)
				arbiterEpoch[i] <= red.epoch;
		endrule
	end

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

	// Redirect
	Vector#(FrontWidth, FifoEnq#(Redirect)) enqRedirectIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		enqRedirectIfc[i] =
			(interface FifoEnq#(Redirect);
				method notFull = redInpQ[i].notFull;
				method enq(Redirect x) = redInpQ[i].enq(x);
			endinterface);
	end

	Vector#(FrontWidth, FifoDeq#(Redirect)) deqRedirectIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deqRedirectIfc[i] =
			(interface FifoDeq#(Redirect);
				method notEmpty = redOutQ[i].notEmpty;
				method deq      = redOutQ[i].deq;
				method first    = redOutQ[i].first;
			endinterface);
	end

	interface eport       = enqIfc;
	interface dport       = deqIfc;
	interface enqRedirect = enqRedirectIfc;
	interface deqRedirect = deqRedirectIfc;

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