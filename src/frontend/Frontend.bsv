import FShow::*;
import Config::*;

// types
import Types::*;
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

	// Function
	interface Vector#(FrontWidth, Hart) hart;

	// Debug
	interface Vector#(FrontWidth, FetchDebug)    fetch;
	interface Vector#(FrontWidth, DecodeDebug)   decode;
	interface Vector#(FrontWidth, RegFetchDebug) regfetch;

	// Stats
	method FetchStat getStat();

endinterface

module mkFrontend (WideMem                             mem        ,
	               Vector#(FrontWidth, RFile)          regFile    ,
	               Vector#(FrontWidth, Scoreboard#(8)) scoreboard ,
	               Vector#(FrontWidth, Ehr#(2,Epoch))  wbEpoch    ,
	               Bool                                coreStarted,
	               Frontend ifc);

	// Data cache
	L1I#(FrontWidth, L1ICacheRows) l1I <- mkDirectL1I(mem);

	// Stages
	Vector#(FrontWidth, FIFOF#(RFToken)  ) regfetchQ  <- replicateM(mkPipelineFIFOF() );
	Vector#(FrontWidth, FIFOF#(ExecToken)) arbiterQ   <- replicateM(mkBypassFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect) ) redirectQ  <- replicateM(mkBypassFIFOF());

	// Stats
	Reg#(Data) numEmpty <- mkReg(0);

	//////////// FETCH ////////////

    Vector#(FrontWidth, Stream) stream;

    for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
        stream[i] <- mkStream(l1I.port[i]);
    end

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

	Vector#(FrontWidth, Reg#(Bool)) regfetchLock <- replicateM(mkReg(False));

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_regfetch;

			if (redirectQ[i].notEmpty) begin

				Redirect red = redirectQ[i].first(); redirectQ[i].deq();
				regfetchLock[i] <= red.lock;
				if(red.dry || red.kill || red.redirect) begin
					regfetchQ [i].deq();
					scoreboard[i].clear();
					stream    [i].redirect(red);
				end

			end else if (regfetchQ[i].first().epoch != wbEpoch[i][1]) begin

				regfetchQ[i].deq();

			end else if(!regfetchLock[i] && !scoreboard[i].search1(regfetchQ[i].first().inst.src1)
			                             && !scoreboard[i].search2(regfetchQ[i].first().inst.src2)) begin

				let rfToken = regfetchQ[i].first(); regfetchQ[i].deq();

				let arg1    = regFile[i].rd1(fromMaybe(?, rfToken.inst.src1));
				let arg2    = regFile[i].rd2(fromMaybe(?, rfToken.inst.src2));
				let eToken  = ExecToken{ inst   : rfToken.inst,
				                         arg1   : arg1,
				                         arg2   : arg2,
				                         pc     : rfToken.pc,
				                         feID   : fromInteger(i),
				                         epoch  : rfToken.epoch,
				                         rawInst: rfToken.rawInst};

				scoreboard[i].insert(rfToken.inst.dst);

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

	interface hart     = hartIfc;
	interface fetch    = fetchIfc;
	interface decode   = decodeIfc;
	interface regfetch = regfetchIfc;

	method FetchStat getStat();
		return FetchStat { hit:   l1I.getNumHit(),
                           miss:  l1I.getNumMiss(),
                           empty: numEmpty };
	endmethod

endmodule
