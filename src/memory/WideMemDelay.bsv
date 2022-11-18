import Config::*;
import Types::*;
import Fifo::*;
import Vector::*;

typedef TSub#(RAMLatency,2) DelayLatency;

module mkWideMemDelay(WideMem mem, WideMem ifc);

	Vector#(DelayLatency, Fifo#(1,CacheLine)) forward <- replicateM(mkStageFifo());
	let inQ = forward[0];
	let outQ = forward[valueof(DelayLatency)-1];

	for (Integer i = 0; i < valueOf(DelayLatency)-1; i=i+1) begin
		rule do_FORWARD;
			forward[fromInteger(i)+1].enq(forward[fromInteger(i)].first());
			forward[fromInteger(i)].deq();
		endrule
	end

	rule do_RECEIVE;
		let d <- mem.resp();
		inQ.enq(d);
	endrule

	method Action req(WideMemReq r);
		mem.req(r);
	endmethod

	method ActionValue#(CacheLine) resp;
		outQ.deq();
		return outQ.first();
    endmethod

endmodule