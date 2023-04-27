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

	`ifdef DEBUG_STATS
	method FetchStat getStat();
	`endif

endinterface

module mkFrontend (Frontend ifc);

	// Data cache
	L1I#(FrontWidth, L1ICacheRows, L1ICacheColumns) l1I <- mkL1I();

	// Stages
	Vector#(FrontWidth, FIFOF#(ExecToken)) arbiterQ   <- replicateM(mkBypassFIFOF  ());
	Vector#(FrontWidth, FIFOF#(Redirect) ) redirectQ  <- replicateM(mkBypassFIFOF  ());

	// SB and RF
	Vector#(FrontWidth, Scoreboard#(8)) scoreboardArray <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, RFile         ) regFileArray    <- replicateM(mkBypassRFile);

	// Stats
	`ifdef DEBUG_STATS
	Reg#(PerfCnt) numEmpty <- mkReg(0);
	`endif

	//////////// COUNTERS ////////////

	Reg#(Bool)    coreStarted <- mkReg(False);
	Reg#(PerfCnt) numCycles   <- mkReg('0);

	rule do_cnt_cycles if(coreStarted);
		numCycles <= numCycles+1;
	endrule

	//////////// FETCH ////////////

	Vector#(FrontWidth, Stream) stream <- replicateM(mkStream);

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1)
		mkConnection(stream[i].mem,l1I.port[i]);

	`ifdef DEBUG_STATS
	rule do_EMPTYCNT if(coreStarted);

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
	`endif

	//////////// DECODE ////////////

	Vector#(FrontWidth, Reg#(Epoch)) regfetchEpoch <- replicateM(mkReg('0));
	Vector#(FrontWidth, Reg#(Bool )) regfetchLock  <- replicateM(mkReg(False));

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_decode;

			if (redirectQ[i].notEmpty) begin

				Redirect red = redirectQ[i].first(); redirectQ[i].deq();
				if(red.kill || red.redirect)
					regfetchEpoch[i] <= red.epoch;
				regfetchLock[i] <= red.lock;
				if(red.dry || red.kill || red.redirect)
					stream[i].redirect(red);

			end else if (stream[i].firstInst.epoch != regfetchEpoch[i]) begin

				stream[i].deqInst();

			end else begin

				DecToken dToken = stream[i].firstInst();
				RFToken rfToken;

				if(dToken.inst matches tagged Valid .inst) begin
					DecodedInst dec = decode(inst);
					rfToken = RFToken { pc     : dToken.pc      ,
					                    epoch  : dToken.epoch   ,
					                    `ifdef DEBUG_RAW_INST
					                    rawInst: inst           ,
					                    `endif
					                    // iType
					                    iType  : dec.iType      ,
					                    aluFunc: dec.aluFunc    ,
					                    mulFunc: dec.mulFunc    ,
					                    divFunc: dec.divFunc    ,
					                    brFunc : dec.brFunc     ,
					                    ldFunc : dec.ldFunc     ,
					                    stFunc : dec.stFunc     ,
					                    // Op
					                    dst    : dec.dst        ,
					                    src1   : dec.src1       ,
					                    src2   : dec.src2       ,
					                    imm    : dec.imm        };

				end else begin
					rfToken = RFToken { pc     : dToken.pc      ,
					                    epoch  : dToken.epoch   ,
					                    `ifdef DEBUG_RAW_INST
					                    rawInst: ?              ,
					                    `endif
					                    // iType
					                    iType  : Ghost          ,
					                    aluFunc: ?              ,
					                    mulFunc: ?              ,
					                    divFunc: ?              ,
					                    brFunc : ?              ,
					                    ldFunc : ?              ,
					                    stFunc : ?              ,
					                    // Op
					                    dst    : tagged Invalid ,
					                    src1   : tagged Invalid ,
					                    src2   : tagged Invalid ,
					                    imm    : tagged Invalid };
				end

				if(!regfetchLock[i] && !scoreboardArray[i].hasDest1(rfToken.src1)
				                    && !scoreboardArray[i].hasDest2(rfToken.src2)) begin

					stream[i].deqInst();

					let arg1 = regFileArray[i].rd1(fromMaybe('0, rfToken.src1));
					let arg2 = regFileArray[i].rd2(fromMaybe('0, rfToken.src2));

					if(rfToken.dst matches tagged Valid .dv)
						scoreboardArray[i].insert(dv);

					arbiterQ[i].enq(ExecToken{ feID   : fromInteger(i) ,
					                           pc     : rfToken.pc     ,
					                           epoch  : rfToken.epoch  ,
					                           `ifdef DEBUG_RAW_INST
					                           rawInst: rfToken.rawInst,
					                           `endif
					                           // iType
					                           iType  : rfToken.iType  ,
					                           aluFunc: rfToken.aluFunc,
					                           mulFunc: rfToken.mulFunc,
					                           divFunc: rfToken.divFunc,
					                           brFunc : rfToken.brFunc ,
					                           ldFunc : rfToken.ldFunc ,
					                           stFunc : rfToken.stFunc ,
					                           // Op
					                           arg1   : arg1           ,
					                           arg2   : arg2           ,
					                           imm    : rfToken.imm    ,
					                           dst    : rfToken.dst    });

				end

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
				method Addr         firstPC();
					return ?;
				endmethod
				method Bool         notEmpty();
					return ?;
				endmethod

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

	`ifdef DEBUG_STATS
	method FetchStat getStat();
		return FetchStat { hit  : l1I.getNumHit() ,
		                   miss : l1I.getNumMiss(),
		                   empty: numEmpty        };
	endmethod
	`endif

endmodule