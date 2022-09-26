import Types::*;
import MemTypes::*;
import MemUtil::*;
import FIFO::*;
import Fifo::*;
import BRAMCore::*;

module mkZeroCache(WideMem mem, Cache ifc);

	FIFO#(Addr) pendingReq <- mkFIFO;

	method Action req(MemReq r);
		pendingReq.enq(r.addr);
	endmethod

	method ActionValue#(MemResp) resp;
		pendingReq.deq();
		return 0;
	endmethod

endmodule

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

typedef struct {
	MemReq             r;
	Maybe#(CacheEntry) e;
} PendingReqEntry deriving(Eq, Bits);

module mkReadCache(WideMem mem, Cache ifc);

	BRAM_DUAL_PORT#(CacheIndex, Maybe#(CacheEntry)) bram       <- mkBRAMCore2(valueOf(CacheRows), False);
	Fifo#(1,MemReq)                                 bramReq    <- mkStageFifo();
	Fifo#(4,PendingReqEntry)                        pendingReq <- mkBypassFifo();

	rule do_read_BRAM;

		let e = bram.b.read;
		let r = bramReq.first(); bramReq.deq();
		pendingReq.enq(PendingReqEntry{r: r, e: e});
		if(!isValid(e) || fromMaybe(?,e).tag != truncateLSB(r.addr)) begin
			mem.req(toWideMemReq(r));
		end

	endrule

	method Action req(MemReq r);

		bramReq.enq(r);
		bram.b.put(False, truncate(r.addr >> valueOf(TLog#(CacheLineBytes))), tagged Invalid);

	endmethod

	method ActionValue#(MemResp) resp;

		let e = pendingReq.first().e;
		let r = pendingReq.first().r;
		pendingReq.deq();

		if(isValid(e) && fromMaybe(?,e).tag == truncateLSB(r.addr)) begin
			
			CacheLine       line       = fromMaybe(?,e).data;
			Addr            addr       = r.addr;
			CacheWordSelect wordSelect = truncate(addr >> 2);
			return line[wordSelect];

		end else begin
			
			CacheLine       line <- mem.resp();

			CacheTag        tag  = truncateLSB(r.addr);
			CacheEntry      ne   = CacheEntry{tag: tag, data: line};
			Addr            addr = r.addr;

			bram.a.put(True, truncate(addr >> valueOf(TLog#(CacheLineBytes))), tagged Valid ne);
			
			CacheWordSelect wordSelect =  truncate(addr >> 2);
			return line[wordSelect];

		end

	endmethod

endmodule