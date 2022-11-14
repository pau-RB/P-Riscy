import Types::*;
import LSUTypes::*;
import Fifo::*;
import Ehr::*;
import Vector::*;
import BRAMCore::*;

typedef 8 CacheRows;
typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(CacheRows))) CacheTag;
typedef Bit#(TLog#(CacheRows)) CacheIndex;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

module mkNullDataCache (BareDataCache ifc);

	method ActionValue#(Bool) req(DataCacheReq r);
		return False;
	endmethod

    method ActionValue#(DataCacheResp) resp;
    	return tagged Invalid;
    endmethod

    method Action put(DataCacheWB wb);
    endmethod

    method ActionValue#(DataCacheWB) get() if(False);
    	return DataCacheWB { num: '0,
    						line: replicate(0) };
    endmethod

endmodule

module mkDirectDataCache (BareDataCache ifc);

	Vector#(CacheRows,Reg#(Bool))     valid <- replicateM(mkReg(False));
	Vector#(CacheRows,Reg#(Bool))     dirty <- replicateM(mkReg(False));
	Vector#(CacheRows,Reg#(CacheTag)) tags  <- replicateM(mkReg(0));

	BRAM_DUAL_PORT_BE#(CacheIndex, CacheLine, CacheLineBytes) bram  <- mkBRAMCore2BE(valueOf(CacheRows), False);
	Fifo#(1,BramReq) bramReq <- mkStageFifo();
	Fifo#(1,CacheLineNum) bramWBReq <- mkStageFifo();
	// Use port a for R and port b for W, important in Join (both operations)

	method Bool isHit(DataCacheReq r) if(!bramWBReq.notEmpty());

		Addr                 addr     = r.addr;
		CacheTag             tag      = truncateLSB(addr);
		CacheIndex           index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) write_en = writeEnDCR(r);
		CacheLine            write_ln = embedDCR(r);

		if(valid[index] && (tags[index] == tag)) begin
			return True;
		end else begin
			return False;
		end

	endmethod

	method ActionValue#(Bool) req(DataCacheReq r) if(!bramWBReq.notEmpty());

		Addr                 addr     = r.addr;
		CacheTag             tag      = truncateLSB(addr);
		CacheIndex           index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) write_en = writeEnDCR(r);
		CacheLine            write_ln = embedDCR(r);

		if(valid[index] && (tags[index] == tag)) begin // hit

			bramReq.enq(BramReq{ op  : r.op,
								 addr: r.addr,
								 hit : True });

			if(r.op == Ld) begin
				bram.a.put('0, index, ?);
			end else if (r.op == St) begin
				bram.b.put(write_en, index, write_ln);
				dirty[index] <= True;
			end else if(r.op == Join) begin
				bram.a.put('0, index, ?);
				bram.b.put(write_en, index, write_ln);
				dirty[index] <= True;
			end

			return True;

		end else begin // miss
			bramReq.enq(BramReq{ op  : r.op,
								 addr: r.addr,
								 hit : False });
			return False;

		end

	endmethod

    method ActionValue#(DataCacheResp) resp;

    	MemOp op   = bramReq.first().op;
    	Addr  addr = bramReq.first().addr;
		Bool  hit  = bramReq.first().hit;
		bramReq.deq();

		CacheWordSelect wordSelect = truncate(addr >> 2);

		if(hit) begin
			CacheLine line = bram.a.read;
			return tagged Valid line[wordSelect];
		end else begin
			return tagged Invalid;
		end

    endmethod

    method Action put(DataCacheWB wb);

    	CacheLineNum num = wb.num;
    	CacheLine line = wb.line;

    	CacheTag   tag   = truncateLSB(num);
		CacheIndex index = truncate(num);

		bram.a.put('0, index, ?   );
		bram.b.put('1, index, line);
		valid[index] <= True;
		dirty[index] <= False;
		tags [index] <= tag;

		if(valid[index] && dirty[index]) begin
			bramWBReq.enq({tags[index],index});
		end

    endmethod

    method ActionValue#(DataCacheWB) get();
    	bramWBReq.deq();
    	return DataCacheWB { num: bramWBReq.first(),
    						line: bram.a.read };
    endmethod

endmodule

module mkLSU (WideMem mem, BareDataCache dataCache, LSU#(transIdType) ifc) provisos(Bits#(transIdType,transIdTypeSz),FShow#(transIdType));

	Fifo#(1,transIdType) dataCacheReq <- mkStageFifo();
	Fifo#(1,Bool)        dataCacheOld <- mkStageFifo();

	Fifo#(1,LSUReq#(transIdType)) reqQ  <- mkBypassFifo();
	Fifo#(4,LSUReq#(transIdType)) mshr  <- mkPipelineFifo();
	Fifo#(1,Addr)                 outQ  <- mkPipelineFifo();

	Ehr#(2,Bool) flushMSHR <- mkEhr(False);

	rule do_RETRY if(flushMSHR[0]);

		if(mshr.notEmpty()) begin

			let r = mshr.first(); mshr.deq();

			let hit <- dataCache.req(DataCacheReq{ op:   r.op,
			                                       func: r.func,
			                                       addr: r.addr,
			                                       data: r.data });
			dataCacheReq.enq(r.transId);
			dataCacheOld.enq(True);

		end else begin

			flushMSHR[0] <= False;

		end

	endrule

	rule do_WB;

		let r <- dataCache.get();

		mem.req(WideMemReq{ write_en: '1,
		                    addr    : {r.num,0},
		                    data    : r.line });

	endrule

	rule do_MEMRESP;

		let num  = cacheLineNumAddr(outQ.first()); outQ.deq();
		let line <- mem.resp();
		dataCache.put(DataCacheWB{ num:  num,
		                           line: line });
		flushMSHR[0] <= True;

	endrule

	rule do_INREQ if(!flushMSHR[1]);

		let r = reqQ.first();

		let hit = dataCache.isHit(DataCacheReq{ op:   r.op,
		                                        func: r.func,
		                                        addr: r.addr,
		                                        data: r.data });

		if(hit) begin

			let hit <- dataCache.req(DataCacheReq{ op:   r.op,
		                                           func: r.func,
		                                           addr: r.addr,
		                                           data: r.data });
			dataCacheReq.enq(r.transId);
			dataCacheOld.enq(False);
			reqQ.deq();

		end else begin

			if(!mshr.notEmpty()) begin

				let hit <- dataCache.req(DataCacheReq{ op:   r.op,
				                                       func: r.func,
				                                       addr: r.addr,
				                                       data: r.data });
				dataCacheReq.enq(r.transId);
				dataCacheOld.enq(False);
				reqQ.deq();
				mshr.enq(r);
				outQ.enq(r.addr);
				mem.req(WideMemReq{ write_en: '0,
									addr    : r.addr,
									data    : ? });

			end else if(cacheLineNumReq(mshr.first())==cacheLineNumReq(r)) begin

				let hit <- dataCache.req(DataCacheReq{ op:   r.op,
				                                       func: r.func,
				                                       addr: r.addr,
				                                       data: r.data });
				dataCacheReq.enq(r.transId);
				dataCacheOld.enq(False);
				reqQ.deq();
				mshr.enq(r);

			end

		end

	endrule

	method Action req(LSUReq#(transIdType) r);

		reqQ.enq(r);

	endmethod

    method ActionValue#(LSUResp#(transIdType)) resp if(dataCacheOld.first()==False);

		dataCacheReq.deq();
		dataCacheOld.deq();
		let r <- dataCache.resp();
		return LSUResp{ valid: isValid(r),
		                data: fromMaybe(?,r),
		                transId: dataCacheReq.first() };

    endmethod

    method ActionValue#(LSUOldResp#(transIdType)) oldResp if(dataCacheOld.first()==True);

   		dataCacheReq.deq();
   		dataCacheOld.deq();
		let r <- dataCache.resp();
		return LSUOldResp{ data: fromMaybe(?,r),
		                   transId: dataCacheReq.first() };

    endmethod

endmodule