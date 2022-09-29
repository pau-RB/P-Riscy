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

module mkReadCache(WideMem mem, Cache ifc);

	BRAM_PORT#(CacheIndex, Maybe#(CacheEntry)) bram     <- mkBRAMCore1(valueOf(CacheRows), False);
	Fifo#(1,MemReq)                            bramReq  <- mkStageFifo();
	Fifo#(1,MemReq)                            memReq   <- mkStageFifo();
	Fifo#(1,Data)                              memResp  <- mkStageFifo();
	Fifo#(1,Data)                              response <- mkBypassFifo();


	rule do_read_BRAM if (bramReq.notEmpty());

		Maybe#(CacheEntry) e    = bram.read;
		CacheLine          line = fromMaybe(?,e).data;
		MemReq             r    = bramReq.first(); bramReq.deq();
		Addr               addr = r.addr;
		
		if(isValid(e) && fromMaybe(?,e).tag == truncateLSB(r.addr)) begin
			// hit
			CacheWordSelect wordSelect = truncate(addr >> 2);
			response.enq(line[wordSelect]);
		end else begin
			// miss
			memReq.enq(r);
			mem.req(toWideMemReadReq(r));
		end

	endrule

	rule do_read_MEM if (memReq.notEmpty());

		CacheLine          line       <- mem.resp();
		MemReq             r          = memReq.first(); memReq.deq();
		Addr               addr       = r.addr;
		
		// Update BRAM
		CacheTag   tag   = truncateLSB(addr);
		CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		bram.put(True, index, tagged Valid CacheEntry{tag: tag, data: line});

		// Fordward response
		CacheWordSelect wordSelect = truncate(addr >> 2);
		memResp.enq(line[wordSelect]);

	endrule

	rule do_forward_MEM if(memResp.notEmpty());

		response.enq(memResp.first()); memResp.deq();

	endrule

	method Action req(MemReq r);

		bramReq.enq(r);
		bram.put(False, truncate(r.addr >> valueOf(TLog#(CacheLineBytes))), tagged Invalid);

	endmethod

	method ActionValue#(MemResp) resp;

		let r = response.first(); response.deq();
		return r;

	endmethod

endmodule