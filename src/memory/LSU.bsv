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

	method Action req(DataCacheReq r);

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

		return (valid[index] && (tags[index] == tag));

	endmethod

	method Action req(DataCacheReq r) if(!bramWBReq.notEmpty());

		Addr                 addr     = r.addr;
		CacheTag             tag      = truncateLSB(addr);
		CacheIndex           index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) write_en = writeEnDCR(r);
		CacheLine            write_ln = embedDCR(r);

		bramReq.enq(BramReq{ op  : r.op,
							 addr: r.addr});

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

	endmethod

    method ActionValue#(DataCacheResp) resp;

    	MemOp op   = bramReq.first().op;
    	Addr  addr = bramReq.first().addr;
		bramReq.deq();

		CacheWordSelect wordSelect = truncate(addr >> 2);

		CacheLine line = bram.a.read;
		return tagged Valid line[wordSelect];

    endmethod

    method Action put(DataCacheWB wb) if(!bramReq.notEmpty());

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
	Fifo#(1,Bool)        dataCacheHit <- mkStageFifo();

	Fifo#(1,LSUReq#(transIdType)) reqQ  <- mkBypassFifo();
	Fifo#(4,LSUReq#(transIdType)) mshr  <- mkPipelineFifo();
	Fifo#(1,Addr)                 outQ  <- mkPipelineFifo();

	Ehr#(2,Bool) flushMSHR <- mkEhr(False);

	rule do_RETRY if(flushMSHR[0]);

		if(mshr.notEmpty()) begin

			let r = mshr.first(); mshr.deq();

			dataCache.req(DataCacheReq{ op:   r.op,
			                            func: r.func,
			                            addr: r.addr,
			                            data: r.data });
			dataCacheReq.enq(r.transId);
			dataCacheOld.enq(True);
			dataCacheHit.enq(True);

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

	rule do_MEMRESP if(!flushMSHR[0]);

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

			dataCache.req(DataCacheReq{ op:   r.op,
			                            func: r.func,
			                            addr: r.addr,
			                            data: r.data });
			dataCacheReq.enq(r.transId);
			dataCacheOld.enq(False);
			dataCacheHit.enq(True);
			reqQ.deq();

		end else begin

			if(!mshr.notEmpty()) begin

				dataCacheReq.enq(r.transId);
				dataCacheOld.enq(False);
				dataCacheHit.enq(False);
				reqQ.deq();

				mshr.enq(r);
				outQ.enq(r.addr);
				mem.req(WideMemReq{ write_en: '0,
									addr    : r.addr,
									data    : ? });

			end else if(cacheLineNumReq(mshr.first())==cacheLineNumReq(r)) begin

				dataCacheReq.enq(r.transId);
				dataCacheOld.enq(False);
				dataCacheHit.enq(False);
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
		dataCacheHit.deq();

		if(dataCacheHit.first()) begin
			let r <- dataCache.resp();
			return LSUResp{ valid: True,
			                data: fromMaybe(?,r),
			                transId: dataCacheReq.first() };
		end else begin
			return LSUResp{ valid: False,
			                data: ?,
			                transId: dataCacheReq.first() };
		end

    endmethod

    method ActionValue#(LSUOldResp#(transIdType)) oldResp if(dataCacheOld.first()==True);

   		dataCacheReq.deq();
		dataCacheOld.deq();
		dataCacheHit.deq();

		let r <- dataCache.resp();
		return LSUOldResp{ data: fromMaybe(?,r),
		                   transId: dataCacheReq.first() };

    endmethod

endmodule