import Types::*;
import MemTypes::*;
import CacheTypes::*;
import MemUtil::*;
import FIFO::*;

module mkNullCache(WideMem mem, Cache ifc);

	FIFO#(Addr) pendingReq <- mkFIFO;

	method Action req(MemReq r);
		pendingReq.enq(r.addr);
		mem.req(toWideMemReq(r));
	endmethod

	method ActionValue#(MemResp) resp;
		CacheLine       line       <- mem.resp();
		Addr            addr       =  pendingReq.first(); pendingReq.deq();
		CacheWordSelect wordSelect =  truncate(addr >> 2);
		return line[wordSelect];
	endmethod

endmodule