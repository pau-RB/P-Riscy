import Types::*;
import ProcTypes::*;
import Config::*;
import BRAM::*;
import FIFO::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

import FShow::*;

typedef enum {EVICT, FORK, JOIN, STALL, MKRD} NTTXtype deriving(Bits, FShow, Eq);

typedef struct {
	FrontID  frontID; // FE id from parent
	HartID   hartID;  // HT id from parent
	VerifID  verifID; // VF id for evicted cont
	Addr     nextpc;  // next expected pc
	NTTXtype reqtype; // Evict, Fork or Join
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

	// Hart table
	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 1,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };
	BRAM2Port#(HartID, ContToken) hartTable <- mkBRAM2Server(cfg);
	FIFOF#(HartID)                hartAvail <- mkSizedFIFOF(valueOf(NumHart)+1);
	FIFOF#(HartID)                hartReady <- mkSizedFIFOF(valueOf(NumHart)+1);
	Reg#(Maybe#(HartID))          initAvail <- mkReg(tagged Valid '0);

	//////////// RULES ////////////

	rule do_initAvail if(initAvail matches tagged Valid .hartID);

		hartAvail.enq(hartID);

		if(hartID != lastHartID)
			initAvail <= tagged Valid (hartID+1);
		else
			initAvail <= tagged Invalid;

	endrule

	rule do_fork_req;

		NTTXreq req = eforkQ.first(); eforkQ.deq();
		rfreqQ.enq(req.frontID); rfreqidQ.enq(req);

	endrule

	rule do_fork_res;

		NTTXreq req = rfreqidQ.first(); rfreqidQ.deq();
		rfresloQ.deq(); rfreshiQ.deq();

		case(req.reqtype)
			EVICT: begin
				// Dry ghost
				redirectQ[req.frontID].enq(Redirect{ lock    : False,
				                                     dry     : True ,
				                                     kill    : False,
				                                     redirect: False,
				                                     epoch   : ?    ,
				                                     nextPc  : ?    });
				// Update hart table token and mark as ready
				hartTable.portA.request.put( BRAMRequest{ write          : True      ,
				                                          responseOnWrite: False     ,
				                                          address        : req.hartID,
				                                          datain         : ContToken{ verifID: req.verifID   ,
				                                                                      hartID : req.hartID    ,
				                                                                      pc     : req.nextpc    ,
				                                                                      rfL    : rfresloQ.first,
				                                                                      rfH    : rfreshiQ.first} } );
				hartReady.enq(req.hartID);
			end
			FORK: begin
				// Unlock stream
				redirectQ[req.frontID].enq(Redirect{ lock    : False,
				                                     dry     : False,
				                                     kill    : False,
				                                     redirect: False,
				                                     epoch   : ?    ,
				                                     nextPc  : ?    });
				if(hartAvail.notEmpty) begin
					// If a slot is available, add new stream to hart table
					hartTable.portA.request.put( BRAMRequest{ write          : True           ,
					                                          responseOnWrite: False          ,
					                                          address        : hartAvail.first,
					                                          datain         : ContToken{ verifID: req.verifID    ,
					                                                                      hartID : hartAvail.first,
					                                                                      pc     : req.nextpc     ,
					                                                                      rfL    : rfresloQ.first ,
					                                                                      rfH    : rfreshiQ.first } } );
					hartReady.enq(hartAvail.first);
					hartAvail.deq();
				end else begin
					// Otherwise, offload to MTQ
					mtqtx.enq(ContToken{ verifID: req.verifID    ,
					                     hartID : ?              ,
					                     pc     : req.nextpc     ,
					                     rfL    : rfresloQ.first ,
					                     rfH    : rfreshiQ.first });
				end
			end
			JOIN: begin
				hartAvail.enq(req.hartID);
			end
			STALL: begin
				// Unlock stream
				redirectQ[req.frontID].enq(Redirect{ lock    : False,
				                                     dry     : False,
				                                     kill    : False,
				                                     redirect: False,
				                                     epoch   : ?    ,
				                                     nextPc  : ?    });
				// Update hart table token and mark as ready
				hartTable.portA.request.put( BRAMRequest{ write          : True      ,
				                                          responseOnWrite: False     ,
				                                          address        : req.hartID,
				                                          datain         : ContToken{ verifID: req.verifID   ,
				                                                                      hartID : req.hartID    ,
				                                                                      pc     : req.nextpc    ,
				                                                                      rfL    : rfresloQ.first,
				                                                                      rfH    : rfreshiQ.first} } );
			end
			MKRD: begin
				hartReady.enq(req.hartID);
			end
		endcase

	endrule

	rule do_forward_mtq;

		// If a slot is available, add new stream to hart table
		hartTable.portA.request.put( BRAMRequest{ write          : True           ,
		                                          responseOnWrite: False          ,
		                                          address        : hartAvail.first,
		                                          datain         : ContToken{ verifID: mtqrx.first.verifID,
		                                                                      hartID : hartAvail.first    ,
		                                                                      pc     : mtqrx.first.pc     ,
		                                                                      rfL    : mtqrx.first.rfL    ,
		                                                                      rfH    : mtqrx.first.rfH    } } );
		hartReady.enq(hartAvail.first);
		hartAvail.deq();
		mtqrx.deq();

	endrule

	rule do_forward_readytx_req;
		hartTable.portB.request.put( BRAMRequest{ write          : False          ,
		                                          responseOnWrite: False          ,
		                                          address        : hartReady.first,
		                                          datain         : ?              });
		hartReady.deq();
	endrule

	rule do_forward_readytx_res;
		ContToken latest <- hartTable.portB.response.get();
		readytx.enq(latest);
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