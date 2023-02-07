import Types::*;
import Config::*;
import CMRTypes::*;
import BRAM::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;
import Ehr::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(cacheRows))) CacheTag  #(numeric type cacheRows);
typedef Bit#(TLog#(cacheRows))                                              CacheIndex#(numeric type cacheRows);

typedef struct{
	Bool valid;
	Bool dirty;
} CacheMeta deriving(Eq, Bits, FShow);

typedef struct{
    Bool         write;
    Bool         dirty;
    CacheLineNum num;
    CacheLine    line;
} WMCReq deriving(Eq, Bits, FShow);

interface WideMemCache#(numeric type cacheRows, numeric type numReq);
    interface WideMem cache;
    method WMCStat getStat();
endinterface

module mkWideMemCache(WideMem mem, WideMemCache#(cacheRows, numReq) ifc) provisos( Log#(cacheRows, b__),
                                                                                   Add#(c__, TLog#(cacheRows), CacheLineNumSz),
                                                                                   Alias#(cacheTag, CacheTag#(cacheRows)),
                                                                                   Alias#(cacheIdx, CacheIndex#(cacheRows)));

	//////////// UTILITIES ////////////

	function cacheTag tagOf(CacheLineNum num);
		return truncateLSB(num);
	endfunction

	function cacheIdx indexOf(CacheLineNum num);
		return truncate(num);
	endfunction

	//////////// BRAM ////////////

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM2Port#(cacheIdx, CacheLine) dataArray <- mkBRAM2Server(cfg);
	BRAM2Port#(cacheIdx, cacheTag ) tagsArray <- mkBRAM2Server(cfg);
	BRAM2Port#(cacheIdx, CacheMeta) metaArray <- mkBRAM2Server(cfg);

	//////////// Queues ////////////

	FIFOF#(WMCReq)       reqQ <- mkSizedFIFOF(valueOf(numReq));
	FIFOF#(WMCReq)       brmQ <- mkPipelineFIFOF();
	FIFOF#(CacheLineNum) memQ <- mkFIFOF();

	FIFOF#(Bool)         resQ <- mkFIFOF();
	FIFOF#(WideMemResp)  hitQ <- mkFIFOF();
	FIFOF#(WideMemResp)  misQ <- mkFIFOF();

	Ehr#(3,Maybe#(cacheIdx)) writePortIndex <- mkEhr(tagged Invalid); // Prevent conflicts
	Reg#(Maybe#(cacheIdx))   invIndex       <- mkReg(tagged Valid 0); // Invalidate entries

	//////////// STATS ////////////

	Ehr#(2,Data) tWR <- mkEhr(0); // Total writes
	Ehr#(2,Data) tWB <- mkEhr(0); // Total writebacks
	Ehr#(2,Data) hRD <- mkEhr(0); // Total hits on read
	Ehr#(2,Data) mRD <- mkEhr(0); // Total miss on read

	//////////// RULES ////////////

	rule do_WPI;
		writePortIndex[2] <= tagged Invalid;
	endrule

	rule do_invalidate if (invIndex matches tagged Valid .index);

		CacheMeta newMeta = CacheMeta { valid: False,
		                                dirty: False };
		metaArray.portA.request.put( BRAMRequest  { write          : True,
		                                            responseOnWrite: False,
		                                            address        : index,
		                                            datain         : newMeta } );
		if(index < fromInteger(valueOf(TSub#(cacheRows,1)))) begin
			invIndex <= tagged Valid (index+1);
		end else begin
			invIndex <= tagged Invalid;
		end

	endrule

	rule do_REQ if(!isValid(invIndex) && (!isValid(writePortIndex[1]) || fromMaybe(?,writePortIndex[1]) != indexOf(reqQ.first.num)));

		WMCReq req = reqQ.first(); reqQ.deq();
		cacheIdx index = indexOf(req.num);

		brmQ.enq(req);

		dataArray.portA.request.put( BRAMRequest{ write          : False,
		                                          responseOnWrite: False,
		                                          address        : index,
		                                          datain         : ? } );
		tagsArray.portA.request.put( BRAMRequest{ write          : False,
		                                          responseOnWrite: False,
		                                          address        : index,
		                                          datain         : ? } );
		metaArray.portA.request.put( BRAMRequest{ write          : False,
		                                          responseOnWrite: False,
		                                          address        : index,
		                                          datain         : ? } );

	endrule

	rule do_RESP;

		WMCReq req = brmQ.first(); brmQ.deq();

		CacheLine line <- dataArray.portA.response.get;
		cacheTag  tag  <- tagsArray.portA.response.get;
		CacheMeta meta <- metaArray.portA.response.get;

		cacheIdx index = indexOf(req.num);

		if (req.write) begin // write



			if(meta.valid && meta.dirty) begin // old line is dirty
				mem.req(WideMemReq { write: True,
				                     num  : {tag,index},
				                     line : line });
			end

			CacheMeta newMeta = CacheMeta { valid: True,
			                                dirty: req.dirty };

			dataArray.portB.request.put( BRAMRequest{ write          : True,
			                                          responseOnWrite: False,
			                                          address        : index,
			                                          datain         : req.line } );
			tagsArray.portB.request.put( BRAMRequest{ write          : True,
			                                          responseOnWrite: False,
			                                          address        : index,
			                                          datain         : tagOf(req.num) } );
			metaArray.portB.request.put( BRAMRequest{ write          : True,
			                                          responseOnWrite: False,
			                                          address        : index,
			                                          datain         : newMeta } );

			writePortIndex[0] <= tagged Valid (index);

		end else if (meta.valid && (tag == tagOf(req.num))) begin // read hit

			resQ.enq(True);
			hitQ.enq(line);

		end else begin // read miss

			mem.req( WideMemReq { write: req.write,
			                      num  : req.num,
			                      line : req.line } );

			resQ.enq(False);
			memQ.enq(req.num);

		end

		if (mem_ext_DEBUG) begin
			if (req.write) begin // write
				tWR[0] <= tWR[0]+1;
				if(meta.valid && meta.dirty)  // old line is dirty
					tWB[0] <= tWB[0]+1;
			end else if (meta.valid && (tag == tagOf(req.num))) begin // read hit
				hRD[0] <= hRD[0]+1;
			end else begin // read miss
				mRD[0] <= mRD[0]+1;
			end
		end

	endrule

	rule do_MEMRESP;

		WideMemResp  line <- mem.resp();
		CacheLineNum num  = memQ.first(); memQ.deq();

		reqQ.enq( WMCReq { write: True,
		                   dirty: False,
		                   num  : num,
		                   line : line } );

		misQ.enq(line);

	endrule

	interface WideMem cache;

		method Action req(WideMemReq r);

			reqQ.enq( WMCReq { write: r.write,
			                   dirty: True,
			                   num  : r.num,
			                   line : r.line } );

		endmethod

		method ActionValue#(WideMemResp) resp;

			if(resQ.first) begin // hit
				WideMemResp res = hitQ.first(); hitQ.deq(); resQ.deq();
				return res;
			end else begin // miss
				WideMemResp res = misQ.first(); misQ.deq(); resQ.deq();
				return res;
			end

		endmethod

	endinterface

	method WMCStat getStat();
		return WMCStat{ tWR: tWR[1],
		                tWB: tWB[1],
		                hRD: hRD[1],
		                mRD: mRD[1] };
	endmethod

endmodule