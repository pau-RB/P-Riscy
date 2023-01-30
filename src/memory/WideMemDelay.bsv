import Types::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface DelayedWideMem#(numeric type delayLatency);
    interface WideMem delayed;
    interface WideMem direct;
endinterface

module mkWideMemDelay(WideMem mem, DelayedWideMem#(delayLatency) ifc);

	Vector#(delayLatency, FIFOF#(WideMemReq)) forward <- replicateM(mkPipelineFIFOF());
	let inQ = forward[0];
	let outQ = forward[valueof(delayLatency)-1];

	for (Integer i = 0; i < valueOf(delayLatency)-1; i=i+1) begin
		rule do_FORWARD;
			forward[fromInteger(i)+1].enq(forward[fromInteger(i)].first());
			forward[fromInteger(i)].deq();
		endrule
	end

	rule do_SEND;
		mem.req(outQ.first());
		outQ.deq();
	endrule

	interface WideMem delayed;

		method Action req(WideMemReq r);
			inQ.enq(r);
		endmethod

		method ActionValue#(CacheLine) resp = mem.resp();

	endinterface

	interface WideMem direct;

		method Action req(WideMemReq r) = mem.req(r);

		method ActionValue#(CacheLine) resp = mem.resp();

	endinterface

endmodule