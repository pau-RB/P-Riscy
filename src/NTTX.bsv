import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Config::*;
import Fifo::*;
import Ehr::*;

interface NTTX;

	method Action    evict(FrontID feID, Addr pc);
	method Action    deq;
    method ContToken first;

endinterface

module mkNTTX (NTTX ifc);

	Fifo#(2,ContToken) out <- mkBypassFifo();

	method Action evict(FrontID feID, Addr pc);
		out.enq(ContToken{feID: feID, pc:pc});
	endmethod

	method Action deq();
		out.deq();
	endmethod

	method ContToken first();
		return out.first();
	endmethod

endmodule