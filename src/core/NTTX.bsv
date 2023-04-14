import Types::*;
import ProcTypes::*;
import Config::*;
import FIFO::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

import FShow::*;


typedef struct {
	FrontID frontID; // FE id from  parent
	VerifID verifID; // FE id for evicted cont
	Addr    nextpc;  // next expected pc
	Bool    evict;   // evict/fork
} NTTXreq deriving(Bits, FShow);

interface FifoDeq#(type t);
	method Bool notEmpty;
	method Action deq;
	method t first;
endinterface

interface NTTX;

	// Requests from BE
	method Action putFork(NTTXreq req);

	// Requests to FE
	method ActionValue#(FrontID) getReadRF();
	method Action putLineRF(CacheLine lo, CacheLine hi);
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// ready tokens
	interface FifoDeq#(ContToken) ready;

	// Stream control
	interface FIFO#(ContToken) toMTQ;

endinterface

module mkNTTX (NTTX ifc);

	//////////// QUEUES ////////////

	// Fork requests
	FIFOF#(NTTXreq)   eforkQ   <- mkFIFOF();
	FIFOF#(FrontID)   rfreqQ   <- mkFIFOF();
	FIFOF#(NTTXreq)   rfreqidQ <- mkFIFOF();
	FIFOF#(CacheLine) rfresloQ <- mkFIFOF();
	FIFOF#(CacheLine) rfreshiQ <- mkFIFOF();

	// Send redirects
	Vector#(FrontWidth, FIFOF#(Redirect)) redirectQ <- replicateM(mkFIFOF());

	// Completed tokens
	FIFOF#(ContToken) readytx <- mkFIFOF();

	// MTQ ifc
	FIFOF#(ContToken) mtqtx <- mkFIFOF();
	FIFOF#(ContToken) mtqrx <- mkFIFOF();

	//////////// RULES ////////////

	rule do_fork_req;

		NTTXreq req = eforkQ.first(); eforkQ.deq();
		rfreqQ.enq(req.frontID); rfreqidQ.enq(req);

	endrule

	rule do_fork_res;

		NTTXreq req = rfreqidQ.first(); rfreqidQ.deq();
		rfresloQ.deq(); rfreshiQ.deq();

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

		if(readytx.notFull)
			readytx.enq(ContToken{ verifID: req.verifID,
			                       pc     : req.nextpc,
			                       rfL    : rfresloQ.first,
			                       rfH    : rfreshiQ.first });
		else
			mtqtx.enq(ContToken{ verifID: req.verifID,
			                     pc     : req.nextpc,
			                     rfL    : rfresloQ.first,
			                     rfH    : rfreshiQ.first });

	endrule

	rule do_forward_mtq;
		readytx.enq(mtqrx.first()); mtqrx.deq();
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

	// ready tokens
	interface FifoDeq ready;
		method Bool      notEmpty = readytx.notEmpty;
		method Action    deq      = readytx.deq;
		method ContToken first    = readytx.first;
	endinterface

	// Stream control
	interface FIFO toMTQ;
		method Action    enq(ContToken x) = mtqrx.enq(x);
		method Action    deq              = mtqtx.deq();
		method ContToken first            = mtqtx.first();
		method Action    clear            = mtqtx.clear();
	endinterface

endmodule