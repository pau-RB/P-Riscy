import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemDelay#(numeric type delayLatency, type tagT);
	interface WideMemClient#(tagT) mem;
	interface WideMemServer#(tagT) portA;
endinterface

module mkWideMemDelay(WideMemDelay#(delayLatency, tagT) ifc) provisos(Bits#(tagT, t__));

	Vector#(delayLatency, FIFOF#(WideMemReq#(tagT))) forward <- replicateM(mkFIFOF());
	FIFOF#(WideMemReq#(tagT)) inQ  = forward[0];
	FIFOF#(WideMemReq#(tagT)) outQ = forward[valueof(delayLatency)-1];
	FIFOF#(WideMemReq#(tagT)) memreq <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(tagT)) memres <- mkBypassFIFOF();

	for (Integer i = 0; i < valueOf(delayLatency)-1; i=i+1) begin
		rule do_FORWARD;
			forward[fromInteger(i)+1].enq(forward[fromInteger(i)].first());
			forward[fromInteger(i)].deq();
		endrule
	end

	rule do_SEND;
		memreq.enq(outQ.first()); outQ.deq();
	endrule

	interface WideMemClient mem;
		interface request = (interface Get#(WideMemReq#(tagT));
			method ActionValue#(WideMemReq#(tagT)) get();
				memreq.deq();
				return memreq.first();
			endmethod
		endinterface);
		interface response = (interface Put#(WideMemRes#(tagT));
			method Action put(WideMemRes#(tagT) r);
				memres.enq(r);
			endmethod
		endinterface);
	endinterface

	interface WideMemServer portA;
		interface request = (interface Put#(WideMemReq#(tagT));
			method Action put(WideMemReq#(tagT) r);
				inQ.enq(r);
			endmethod
		endinterface);
		interface response = (interface Get#(WideMemRes#(tagT));
			method ActionValue#(WideMemRes#(tagT)) get();
				memres.deq();
				return memres.first();
			endmethod
		endinterface);
	endinterface

endmodule
