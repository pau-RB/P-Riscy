import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemDelay#(numeric type delayLatency);
	interface WideMem delayed;
	interface WideMem direct;
endinterface

module mkWideMemDelay(WideMem mem, WideMemDelay#(delayLatency) ifc);

	Vector#(delayLatency, FIFOF#(WideMemReq)) forward <- replicateM(mkPipelineFIFOF());
	FIFOF#(WideMemReq) inQ  = forward[0];
	FIFOF#(WideMemReq) outQ = forward[valueof(delayLatency)-1];

	for (Integer i = 0; i < valueOf(delayLatency)-1; i=i+1) begin
		rule do_FORWARD;
			forward[fromInteger(i)+1].enq(forward[fromInteger(i)].first());
			forward[fromInteger(i)].deq();
		endrule
	end

	rule do_SEND;
		mem.request.put(outQ.first());
		outQ.deq();
	endrule

	interface WideMem delayed;
		interface request = (interface Put#(WideMemReq);
			method Action put(WideMemReq r);
				inQ.enq(r);
			endmethod
		endinterface);
		interface response = (interface Get#(WidememResp);
			method ActionValue#(CacheLine) get = mem.response.get;
		endinterface);
	endinterface

	interface WideMem direct;
		interface request  = mem.request;
		interface response = mem.response;
	endinterface

endmodule