import Types::*;
import ProcTypes::*;
import Config::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

typedef struct {
	FrontID frontID; // FE id from  parent
	VerifID verifID; // FE id for evicted cont
	Addr    nextpc;  // next expected pc
	Bool    evict;   // evict/fork
} NTTXreq deriving(Bits);

interface FifoDeq#(type t);
	method Bool notEmpty;
	method Action deq;
	method t first;
endinterface

interface NTTX;

	// Requests from BE
	method Action putFork(NTTXreq req);

	// Requests to FE
	method ActionValue#(FrontID)  getReadRF();
	method Action                 putLineRF(CacheLine lo, CacheLine hi);
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// Completed req
	method Action    deq();
	method ContToken first();

endinterface

module mkNTTX (NTTX ifc);

	//////////// QUEUES ////////////

	FIFOF#(NTTXreq) eforkQ <- mkFIFOF();

	FIFOF#(FrontID)   rfreqQ   <- mkFIFOF();
	FIFOF#(NTTXreq)   rfreqidQ <- mkFIFOF();
	FIFOF#(CacheLine) rfresloQ <- mkFIFOF();
	FIFOF#(CacheLine) rfreshiQ <- mkFIFOF();
	Vector#(FrontWidth, FIFOF#(Redirect)) redirectQ <- replicateM(mkFIFOF());

	FIFOF#(ContToken) contQ <- mkSizedBypassFIFOF(valueOf(CTQ_LEN));

	//////////// RULES ////////////

	rule do_req;
		NTTXreq req = eforkQ.first(); eforkQ.deq();
		rfreqQ.enq(req.frontID); rfreqidQ.enq(req);
	endrule

	rule do_res;
		NTTXreq req = rfreqidQ.first(); rfreqidQ.deq();
		rfresloQ.deq(); rfreshiQ.deq();
		contQ.enq(ContToken{ verifID: req.verifID,
		                     pc     : req.nextpc,
		                     rfL    : rfresloQ.first,
		                     rfH    : rfreshiQ.first });
		if(req.evict) // If evict, dry ghost
			redirectQ[req.frontID].enq(Redirect{ lock    : False,
			                                     dry     : True,
			                                     kill    : False,
			                                     redirect: False,
			                                     epoch   : ?    ,
			                                     nextPc  : ?    });
		else // If fork, unlock thd
			redirectQ[req.frontID].enq(Redirect{ lock    : False,
			                                     dry     : False,
			                                     kill    : False,
			                                     redirect: False,
			                                     epoch   : ?    ,
			                                     nextPc  : ?    });
	endrule

	//////////// INTERFACE ////////////

	Vector#(FrontWidth, FifoDeq#(Redirect)) deqRedirectIfc = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deqRedirectIfc[i] =
			(interface FifoDeq#(Redirect);
				method notEmpty = redirectQ[i].notEmpty;
				method deq      = redirectQ[i].deq;
				method first    = redirectQ[i].first;
			endinterface);
	end

	// Requests from BE
	method Action putFork(NTTXreq req);
		eforkQ.enq(req);
	endmethod

	// Requests to FE
	method ActionValue#(FrontID) getReadRF();
		rfreqQ.deq(); return rfreqQ.first();
	endmethod
	method Action putLineRF(CacheLine lo, CacheLine hi);
		rfresloQ.enq(lo);
		rfreshiQ.enq(hi);
	endmethod
	interface deqRedirect = deqRedirectIfc;

	// Completed req
	method Action    deq()   = contQ.deq();
	method ContToken first() = contQ.first();

endmodule