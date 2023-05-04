import Types::*;
import ProcTypes::*;
import Config::*;
import FIFOF::*;
import SpecialFIFOs::*;
import CMRTypes::*;
import Vector::*;
import Ehr::*;
import BitonicSort::*;

interface FifoEnq#(type t);
	method Bool notFull;
	method Action enq(t x);
endinterface

interface FifoDeq#(type t);
	method Bool notEmpty;
	method Action deq;
	method t first;
endinterface

`ifdef DEBUG_CYC
interface DEB_CYC_arb;
	method Bool notEmpty;
	method Bool notStall;
	method Addr nextPC  ;
endinterface
`endif

interface SyncArbiter;

	// IO
	interface Vector#(FrontWidth,FifoEnq#(ExecToken)) eport;
	interface FifoDeq#(Vector#(BackWidth,Maybe#(ExecToken))) dport;

	// Redirect

	interface Vector#(FrontWidth,FifoEnq#(Redirect)) enqRedirect;
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// Performance debug
	`ifdef DEBUG_CYC
	method Vector#(FrontWidth, DEB_CYC_arb) cycArb;
	`endif

	// Stats
	method Action startCore();
/*
	`ifdef DEBUG_STATS
	method ArbiterStat getStat();
	`endif
*/
endinterface

typedef Bit#(3) SpecLvl;

typedef struct {
	Bool      valid;
	FrontID   feID;
	SpecLvl   specLvl;
	ExecToken inst;
} ASNinst deriving(Bits);

(*noinline*) function Vector#(FrontWidth,ASNinst) arbSortNet(Vector#(FrontWidth,ASNinst) inst) provisos(NumAlias#(virtFrontWidth,TExp#(TLog#(FrontWidth))));

	function Bool le(ASNinst x1, ASNinst x2);
		return (!x2.valid || (x1.valid && x1.specLvl <= x2.specLvl));
	endfunction

	Vector#(virtFrontWidth,ASNinst) virtInst = replicate(ASNinst{valid: False});
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
		virtInst[i] = inst[i];

	virtInst = sortLe(le, virtInst);
	
	return take(virtInst);

endfunction

(*synthesize*)
module mkSyncArbiter(SyncArbiter ifc) provisos(Add#(a__,BackWidth,FrontWidth));

	// Queues
	Vector#(FrontWidth, FIFOF#(ExecToken))        inputQueue  <- replicateM(mkPipelineFIFOF());
	FIFOF#(Vector#(BackWidth, Maybe#(ExecToken))) outputQueue <- mkPipelineFIFOF();

	// Redirect
	Vector#(FrontWidth, Reg#(Epoch)) arbiterEpoch <- replicateM(mkReg('0));
	Vector#(FrontWidth, FIFOF#(Redirect)) redInpQ <- replicateM(mkBypassFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect)) redOutQ <- replicateM(mkBypassFIFOF());

	// Speculation counter
	Vector#(FrontWidth,Reg#(SpecLvl))             specLvl <- replicateM(mkReg('0));

	// Stats
	`ifdef DEBUG_STATS
	Reg#(PerfCnt) numMemOvb   <- mkReg(0);
	Reg#(PerfCnt) numArithOvb <- mkReg(0);
	Reg#(PerfCnt) numEmpty    <- mkReg(0);
	`endif

	//////////// COUNTERS ////////////

	Reg#(Bool) coreStarted <- mkReg(False);
	Reg#(Data) numCycles   <- mkReg('0);

	rule do_cnt_cycles if(coreStarted);
		numCycles <= numCycles+1;
	endrule

	//////////// SELECT ////////////

	`ifdef DEBUG_CYC
	Vector#(FrontWidth, Wire#(Bool)) deb_cyc_arb_notEmpty <- replicateM(mkWire);
	Vector#(FrontWidth, Wire#(Bool)) deb_cyc_arb_notStall <- replicateM(mkWire);
	Vector#(FrontWidth, Wire#(Addr)) deb_cyc_arb_nextPC   <- replicateM(mkWire);
	`endif

	rule do_select if(coreStarted);

		// Prepare inst

		Vector#(FrontWidth,ASNinst) memInst;
		Vector#(FrontWidth,ASNinst) ariInst;

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty && inputQueue[i].first.epoch ==  arbiterEpoch[i] && isMemInst(inputQueue[i].first.iType))
				memInst[i] = ASNinst{valid: True, feID: fromInteger(i), specLvl: specLvl[i], inst: inputQueue[i].first};
			else
				memInst[i] = ASNinst{valid: False, feID: ?, specLvl: ?, inst: ?};
		end

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty && inputQueue[i].first.epoch ==  arbiterEpoch[i] && isArithInst(inputQueue[i].first.iType))
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
			if(inputQueue[i].notEmpty && instTaken[i] && isFlowInst(inputQueue[i].first.iType))
				specLvl[i] <= '1;
			else if(inputQueue[i].notEmpty && instTaken[i] && isSpecInst(inputQueue[i].first.iType))
				specLvl[i][2] <= '1;
			else if(specLvl[i] != '0)
				specLvl[i] <= specLvl[i]-1;
		end
				
		// Forward

		if(unpack(|(pack(instTaken))))
			outputQueue.enq(instForward);

		`ifdef DEBUG_CYC
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(inputQueue[i].notEmpty) begin
				deb_cyc_arb_notEmpty[i] <= True;
				deb_cyc_arb_notStall[i] <= instTaken[i];
				deb_cyc_arb_nextPC  [i] <= inputQueue[i].first.pc;
			end else begin
				deb_cyc_arb_notEmpty[i] <= False;
				deb_cyc_arb_notStall[i] <= ?;
				deb_cyc_arb_nextPC  [i] <= ?;
			end
		end
		`endif

		`ifdef DEBUG_STATS
		Vector#(FrontWidth,Maybe#(ExecToken)) inst = replicate(tagged Invalid);
		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1)
			if(inputQueue[i].notEmpty)
				inst[i] = tagged Valid inputQueue[i].first();

		Bool isMemOvb   = False;
		Bool isArithOvb = False;
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1)
			if(isValid(inst[i]) && !instTaken[i])
				if(isMemInst(fromMaybe(?,inst[i]).iType))
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
		`endif

	endrule

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
		rule do_redirect;
			Redirect red = redInpQ[i].first(); redInpQ[i].deq(); redOutQ[i].enq(red);
			if(red.kill || red.redirect)
				arbiterEpoch[i] <= red.epoch;
		endrule
	end

	`ifdef DEBUG_CYC
	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
		rule do_cyc_deb_arb;
			if(inputQueue[i].notEmpty) begin
				deb_cyc_arb_notEmpty[i] <= True;
				deb_cyc_arb_notStall[i] <= False;
				deb_cyc_arb_nextPC  [i] <= inputQueue[i].first.pc;
			end else begin
				deb_cyc_arb_notEmpty[i] <= False;
				deb_cyc_arb_notStall[i] <= False;
				deb_cyc_arb_nextPC  [i] <= ?;
			end
		endrule
	end
	`endif

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

	`ifdef DEBUG_CYC
	Vector#(FrontWidth, DEB_CYC_arb) deb_cyc_arbIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deb_cyc_arbIfc[i] =
			(interface DEB_CYC_arb;
				method notEmpty; return deb_cyc_arb_notEmpty[i]; endmethod
				method notStall; return deb_cyc_arb_notStall[i]; endmethod
				method nextPC;   return deb_cyc_arb_nextPC  [i]; endmethod
			endinterface);
	end
	`endif

	interface eport       = enqIfc;
	interface dport       = deqIfc;
	interface enqRedirect = enqRedirectIfc;
	interface deqRedirect = deqRedirectIfc;
	`ifdef DEBUG_CYC
	interface cycArb      = deb_cyc_arbIfc;
	`endif

	// Stats
	method Action startCore();
		coreStarted <= True;
	endmethod
/*
	`ifdef DEBUG_STATS
	method ArbiterStat getStat();
		return ArbiterStat{ memOvb  : numMemOvb  ,
		                    arithOvb: numArithOvb,
		                    empty   : numEmpty   };
	endmethod
	`endif
*/
endmodule
