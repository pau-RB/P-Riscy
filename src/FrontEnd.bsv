import FShow::*;
import Config::*;

// types
import Types::*;
import ProcTypes::*;
import CMRTypes::*;

// include
import Fifo::*;
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
	method Action backendDry();

	// Performance Debug
	method StreamStatus currentState();
	method Addr         currentPC();
	method Addr         firstPC();
	method Bool         notEmpty();
	method Bool         isl0Ihit();

endinterface

interface FrontEnd;

	interface Vector#(FrontWidth, Hart) hart;

	method FetchStat getStat();

endinterface

module mkFrontEnd (WideMem mem, Vector#(FrontWidth, RFile) regFile, Vector#(FrontWidth, Scoreboard#(8)) scoreboard,
	                      Vector#(FrontWidth, Epoch) wbEpoch, Bool coreStarted, FrontEnd ifc);

	L1I#(FrontWidth) l1I <- mkDirectL1I(mem);

	Vector#(FrontWidth, Fifo#(1,RFToken)  ) regfetchQ  <- replicateM(mkStageFifo() );
	Vector#(FrontWidth, Fifo#(1,ExecToken)) arbiterQ   <- replicateM(mkBypassFifo());
	Vector#(FrontWidth, Fifo#(1,Redirect) ) redirectQ  <- replicateM(mkBypassFifo());

	Vector#(FrontWidth, Ehr#(2,Bool)      ) rfLock     <- replicateM(mkEhr(False));

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

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin

		rule do_regfetch;

			if (regfetchQ[i].first().epoch != wbEpoch[i]) begin

				regfetchQ[i].deq();

			end else if(!rfLock[i][1] && !scoreboard[i].search1(regfetchQ[i].first().inst.src1)
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

				if(rfToken.inst.iType == Br || rfToken.inst.iType == J || rfToken.inst.iType == Jr) begin
					rfLock[i][1] <= True;
				end

				arbiterQ[i].enq(eToken);

			end

		endrule

	end

	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
		rule do_rfLock;
			Redirect r = redirectQ[i].first(); redirectQ[i].deq();
			rfLock[i][0] <= r.lock;
			if(r.redirect || r.kill) begin
				stream[i].redirect(r);
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
				method Action backendDry()         = stream[i].backendDry();

				// Performance Debug
				method StreamStatus currentState() = stream[i].currentState(); 
				method Addr         currentPC()    = stream[i].currentPC(); 
				method Addr         firstPC()      = stream[i].firstPC(); 
				method Bool         notEmpty()     = stream[i].notEmpty(); 
				method Bool         isl0Ihit()     = stream[i].isl0Ihit(); 

			endinterface);
	end

	interface hart = hartIfc;
	method FetchStat getStat();
		return FetchStat { hit:   l1I.getNumHit(),
                           miss:  l1I.getNumMiss(),
                           empty: numEmpty };
	endmethod

endmodule
