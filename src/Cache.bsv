import Types::*;
import MemTypes::*;
import MemUtil::*;
import FIFO::*;
import Fifo::*;
import BRAMCore::*;
import Vector::*;

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

typedef enum {Ready, Request, Load, Retry} CacheStatus deriving (Eq, Bits);

module mkDirectCache(WideMem mem, Cache ifc);

	Reg#(CacheStatus) status <- mkReg(Ready);

	Vector#(CacheRows,Reg#(Maybe#(CacheTag))) tags  <- replicateM(mkReg(tagged Invalid));
	Vector#(CacheRows,Reg#(Bool))             dirty <- replicateM(mkReg(False));
	BRAM_PORT_BE#(CacheIndex, CacheLine, CacheLineBytes) bram <- mkBRAMCore1BE(valueOf(CacheRows), False);

	Fifo#(1,MemReq) bramReq  <- mkStageFifo();
	Fifo#(1,MemReq) memReq   <- mkStageFifo();
	Fifo#(1,Data)   memResp  <- mkStageFifo();
	Fifo#(1,Data)   response <- mkBypassFifo();

	rule do_read_BRAM if(bramReq.notEmpty());

		CacheLine line = bram.read;
		MemReq    r    = bramReq.first(); bramReq.deq();
		Addr      addr = r.addr;

		CacheWordSelect wordSelect = truncate(addr >> 2);
		if(r.op == Ld) begin
			response.enq(line[wordSelect]);
		end

	endrule

	rule do_REQUEST if(status == Request);

		Addr       addr      = memReq.first().addr;
		CacheIndex index     = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		CacheLine  flushLine = bram.read;
		Addr       flushAddr = {fromMaybe(?,tags[index]), index, '0};

		if(dirty[index]) begin

			mem.req(WideMemReq {
           			    write_en: '1,
           			    addr: flushAddr,
           			    data: flushLine
           			});
			dirty[index] <= False;

			status <= Request;

		end else begin

			mem.req(WideMemReq {
                write_en: '0,
                addr: addr,
                data: ?
            });

			status <= Load;

		end

	endrule

	rule do_LOAD if(status == Load);

		CacheLine line <- mem.resp();
		MemReq    r    = memReq.first();
		Addr      addr = r.addr;

		// Update BRAM
		CacheTag   tag   = truncateLSB(addr);
		CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		bram.put('1, index, line);
		tags [index] <= tagged Valid tag;
		dirty[index] <= False;

		status <= Retry;

	endrule

	rule do_RETRY if(status == Retry);

		MemReq               r        = memReq.first();
		Addr                 addr     = r.addr;
		CacheTag             tag      = truncateLSB(addr);
		CacheIndex           index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) write_en = writeEnReq(r);
		CacheLine            write_ln = embedReq(r);

		bramReq.enq(r);
		bram.put(write_en, index, write_ln);
		if(r.op == St) begin
			dirty[index] <= True;
		end

		memReq.deq();
		status <= Ready;

	endrule

	method Action req(MemReq r) if(status == Ready);

		Addr                 addr     = r.addr;
		CacheTag             tag      = truncateLSB(addr);
		CacheIndex           index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) write_en = writeEnReq(r);
		CacheLine            write_ln = embedReq(r);

		if(isValid(tags[index]) && fromMaybe(?,tags[index]) == tag) begin // hit

			bramReq.enq(r);
			bram.put(write_en, index, write_ln);
			if(r.op == St) begin
				dirty[index] <= True;
			end

			status <= Ready;

		end else begin // miss

			memReq.enq(r);
			bram.put('0, index, ?);
			status <= Request;

		end

	endmethod

	method ActionValue#(MemResp) resp if(status == Ready);

		let r = response.first(); response.deq();
		return r;

	endmethod

endmodule