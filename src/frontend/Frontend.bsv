import FShow::*;
import Config::*;

// types
import Types::*;
import WideMemTypes::*;
import Connectable::*;
import ProcTypes::*;
import CMRTypes::*;

// include
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;
import Ehr::*;

// front
import Decoder::*;
import Stream::*;
import L1I::*;

// back
import Scoreboard::*;
import RFile::*;

interface  Hart;

	// Thread control
	method Bool   available();
	method Action start(Addr pc);
	method Action evict();

	// To downstream
	method ActionValue#(ExecToken) readInst();

	// From downstream
	method Action redirect(Redirect r);

endinterface

interface FetchDebug;

	// Performance Debug
	method StreamStatus currentState();
	method Addr         currentPC();
	method Bool         isl0Ihit();

endinterface

interface DecodeDebug;

	// Performance Debug
	method Addr         firstPC();
	method Bool         notEmpty();

endinterface

interface RegFetchDebug;

	// Performance Debug
	method Addr         firstPC();
	method Bool         notEmpty();

endinterface

interface Frontend;

	// IMEM
	interface WideMemClient#(FrontID) mem;

	// Function
	interface Vector#(FrontWidth, Hart) hart;

	// SB and RF
	interface Vector#(FrontWidth, Scoreboard#(8)) scoreboard;
	interface Vector#(FrontWidth, RFile         ) regFile;

	// Debug
	interface Vector#(FrontWidth, FetchDebug)    fetch;
	interface Vector#(FrontWidth, DecodeDebug)   decode;
	interface Vector#(FrontWidth, RegFetchDebug) regfetch;

	// Stats
	method Action startCore();
	method FetchStat getStat();

endinterface

module mkFrontend (Frontend ifc);

	// Data cache
	L1I#(FrontWidth, L1ICacheRows) l1I <- mkDirectL1I();

	// Stages
	Vector#(FrontWidth, FIFOF#(RFToken)  ) regfetchQ  <- replicateM(mkPipelineFIFOF());
	Vector#(FrontWidth, FIFOF#(ExecToken)) arbiterQ   <- replicateM(mkBypassFIFOF  ());
	Vector#(FrontWidth, FIFOF#(Redirect) ) redirectQ  <- replicateM(mkBypassFIFOF  ());

	// SB and RF
	Vector#(FrontWidth, Scoreboard#(8)) scoreboardArray <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, RFile         ) regFileArray    <- replicateM(mkBypassRFile);

	// Stats
	Reg#(Data) numEmpty <- mkReg(0);

	//////////// COUNTERS ////////////

	Reg#(Bool) coreStarted <- mkReg(False);
	Reg#(Data) numCycles   <- mkReg('0);

	rule do_cnt_cycles if(coreStarted);
		numCycles <= numCycles+1;
	endrule

	//////////// FETCH ////////////

	Vector#(FrontWidth, Stream) stream <- replicateM(mkStream);

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1)
		mkConnection(stream[i].mem,l1I.port[i]);

	rule do_EMPTYCNT if(mem_ext_DEBUG == True && coreStarted);

		Bool empty = True;
		for (Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
			if(stream[i].currentState() != Empty && stream[i].isl0Ihit()) begin
				empty = False;
			end
		end
		if (empty) begin
			numEmpty <= numEmpty+1;
		end

	endrule

	//////////// DECODE ////////////

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_decode;

			DecToken dToken <- stream[i].fetch();

			DecodedInst decInst = (isValid(dToken.inst) ? decode(fromMaybe('hdeadbeef, dToken.inst)) :
			                                              DecodedInst{ iType  : Ghost,
			                                                           aluFunc: ?,
			                                                           mulFunc: ?,
			                                                           ldFunc : ?,
			                                                           stFunc : ?,
			                                                           brFunc : NT,
			                                                           dst    : tagged Invalid,
			                                                           src1   : tagged Invalid,
			                                                           src2   : tagged Invalid,
			                                                           imm    : tagged Invalid } );

			RFToken rfToken = RFToken{ inst   : decInst,
			                           pc     : dToken.pc,
			                           epoch  : dToken.epoch,
			                           rawInst: fromMaybe('hdeadbeef, dToken.inst) };

			regfetchQ[i].enq(rfToken);

		endrule

	end

	//////////// REG FETCH ////////////

	Vector#(FrontWidth, Reg#(Epoch)) regfetchEpoch <- replicateM(mkReg('0));
	Vector#(FrontWidth, Reg#(Bool )) regfetchLock  <- replicateM(mkReg(False));

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_regfetch;

			if (redirectQ[i].notEmpty) begin

				Redirect red = redirectQ[i].first(); redirectQ[i].deq();
				if(red.kill || red.redirect) begin
					regfetchEpoch[i] <= red.epoch;
					scoreboardArray   [i].clear();
				end
				regfetchLock[i] <= red.lock;
				if(red.dry || red.kill || red.redirect)
					stream[i].redirect(red);

			end else if (regfetchQ[i].first.epoch != regfetchEpoch[i]) begin

				regfetchQ[i].deq();

			end else if(!regfetchLock[i] && !scoreboardArray[i].search1(regfetchQ[i].first.inst.src1)
			                             && !scoreboardArray[i].search2(regfetchQ[i].first.inst.src2)) begin

				let rfToken = regfetchQ[i].first(); regfetchQ[i].deq();

				let arg1    = regFileArray[i].rd1(fromMaybe(?, rfToken.inst.src1));
				let arg2    = regFileArray[i].rd2(fromMaybe(?, rfToken.inst.src2));
				let eToken  = ExecToken{ inst   : rfToken.inst,
				                         arg1   : arg1,
				                         arg2   : arg2,
				                         pc     : rfToken.pc,
				                         feID   : fromInteger(i),
				                         epoch  : rfToken.epoch,
				                         rawInst: rfToken.rawInst};

				scoreboardArray[i].insert(rfToken.inst.dst);

				arbiterQ[i].enq(eToken);

			end

		endrule

	end

	//////////// INTERFACE ////////////

 	Vector#(FrontWidth, Hart) hartIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		hartIfc[i] =
			(interface Hart;

				// Thread control
				method Bool   available()    = stream[i].available();
				method Action start(Addr pc) = stream[i].start(pc);
				method Action evict()        = stream[i].evict();

				// To downstream
				method ActionValue#(ExecToken) readInst();
					arbiterQ[i].deq();
					return arbiterQ[i].first();
				endmethod

				// From downstream
				method Action redirect(Redirect r) = redirectQ[i].enq(r);

			endinterface);
	end

 	Vector#(FrontWidth, FetchDebug) fetchIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		fetchIfc[i] =
			(interface FetchDebug;

				// Performance Debug
				method StreamStatus currentState() = stream[i].currentState(); 
				method Addr         currentPC()    = stream[i].currentPC();
				method Bool         isl0Ihit()     = stream[i].isl0Ihit(); 

			endinterface);
	end

 	Vector#(FrontWidth, DecodeDebug) decodeIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		decodeIfc[i] =
			(interface DecodeDebug;

				// Performance Debug
				method Addr         firstPC()      = stream[i].firstPC();
				method Bool         notEmpty()     = stream[i].notEmpty();

			endinterface);
	end

 	Vector#(FrontWidth, RegFetchDebug) regfetchIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		regfetchIfc[i] =
			(interface RegFetchDebug;

				// Performance Debug
				method Addr         firstPC()      = regfetchQ[i].first().pc;
				method Bool         notEmpty()     = regfetchQ[i].notEmpty();

			endinterface);
	end

	interface mem        = l1I.mem;
	interface hart       = hartIfc;
	interface scoreboard = scoreboardArray;
	interface regFile    = regFileArray;
	interface fetch      = fetchIfc;
	interface decode     = decodeIfc;
	interface regfetch   = regfetchIfc;

	method Action startCore();
		coreStarted <= True;
	endmethod

	method FetchStat getStat();
		return FetchStat { hit  : l1I.getNumHit(),
		                   miss : l1I.getNumMiss(),
		                   empty: numEmpty };
	endmethod

endmodule