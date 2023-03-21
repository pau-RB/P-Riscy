import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemDelay#(numeric type delayLatency);
	interface WideMemClient mem;
	interface WideMemServer portA;
endinterface

module mkWideMemDelay(WideMemDelay#(delayLatency) ifc);

	Vector#(delayLatency, FIFOF#(WideMemReq)) forward <- replicateM(mkPipelineFIFOF());
	FIFOF#(WideMemReq)  inQ  = forward[0];
	FIFOF#(WideMemReq)  outQ = forward[valueof(delayLatency)-1];
	FIFOF#(WideMemReq ) memreq <- mkBypassFIFOF();
	FIFOF#(WideMemResp) memres <- mkBypassFIFOF();

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
		interface request = (interface Get#(WideMemReq);
			method ActionValue#(WideMemReq) get();
				memreq.deq();
				return memreq.first();
			endmethod
		endinterface);
		interface response = (interface Put#(WidememResp);
			method Action put(WideMemResp r);
				memres.enq(r);
			endmethod
		endinterface);
	endinterface

	interface WideMemServer portA;
		interface request = (interface Put#(WideMemReq);
			method Action put(WideMemReq r);
				inQ.enq(r);
			endmethod
		endinterface);
		interface response = (interface Get#(WidememResp);
			method ActionValue#(CacheLine) get();
				memres.deq();
				return memres.first();
			endmethod
		endinterface);
	endinterface

endmodule