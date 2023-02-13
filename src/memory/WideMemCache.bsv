import Types::*;
import Config::*;
import CMRTypes::*;
import BRAM::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;
import Ehr::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(cacheRows))) CacheTag     #(numeric type cacheRows   );
typedef Bit#(TLog#(cacheRows))                                              CacheRowIndex#(numeric type cacheRows   );
typedef Bit#(TLog#(cacheHash))                                              CacheRowHash #(numeric type cacheHash   );
typedef Bit#(TLog#(cacheColumns))                                           CacheColIndex#(numeric type cacheColumns);

typedef struct{
	Bool valid;
	Bool dirty;
} CacheMeta deriving(Eq, Bits, FShow);

typedef struct{
	Bool         inv  ; // Invalidate that entry if hit
	Bool         write; // Write that entry
	Bool         dirty; // If write, is it dirty?
	CacheLineNum num  ;
	CacheLine    line ;
} WMCReq deriving(Eq, Bits, FShow);

interface WideMemCache#(numeric type cacheRows, numeric type cacheColumns, numeric type cacheHash, numeric type numReq);
	interface WideMem cache;
	method WMCStat getStat();
endinterface

module mkWideMemCache(WideMem mem, WideMemCache#(cacheRows, cacheColumns, cacheHash, numReq) ifc) provisos(Log#(cacheRows, b__),
                                                                                                           Add#(c__, TLog#(cacheRows), CacheLineNumSz),
                                                                                                           Log#(cacheColumns, d__),
                                                                                                           Log#(cacheHash, e__),
                                                                                                           Add#(f__, TLog#(cacheHash), TLog#(cacheRows)),
                                                                                                           Add#(g__, TLog#(cacheHash), CacheLineNumSz),
                                                                                                           Alias#(cacheTag ,    CacheTag#(cacheRows)),
                                                                                                           Alias#(cacheRowIdx,  CacheRowIndex#(cacheRows)),
                                                                                                           Alias#(cacheRowHash, CacheRowHash#(cacheHash)),
                                                                                                           Alias#(cacheColIdx,  CacheColIndex#(cacheColumns)));

	//////////// UTILITIES ////////////

	function cacheTag tagOf(CacheLineNum num);
		return truncateLSB(num);
	endfunction

	function cacheRowIdx indexOf(CacheLineNum num);
		return truncate(num);
	endfunction

	function cacheRowHash hashOf(CacheLineNum num);
		return truncate(num);
	endfunction

	//////////// BRAM ////////////

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	Vector#(cacheColumns, BRAM2Port#(cacheRowIdx, CacheLine)) dataArray <- replicateM(mkBRAM2Server(cfg));
	Vector#(cacheColumns, BRAM2Port#(cacheRowIdx, cacheTag )) tagsArray <- replicateM(mkBRAM2Server(cfg));
	Vector#(cacheColumns, BRAM2Port#(cacheRowIdx, CacheMeta)) metaArray <- replicateM(mkBRAM2Server(cfg));

	Vector#(cacheColumns, Ehr#(3,Maybe#(cacheRowHash))) writePortHash <- replicateM(mkEhr(tagged Invalid)); // Prevent conflicts

	Reg#(cacheColIdx) replaceIndex <- mkReg(0);

	//////////// QUEUES ////////////

	Vector#(cacheColumns, FIFOF#(WMCReq             )) colReqQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(WMCReq             )) colBRMQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(Maybe#(WideMemResp))) colResQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(WideMemReq         )) colWBQ  <- replicateM(mkPipelineFIFOF());

	FIFOF#(WMCReq)       reqQ <- mkSizedFIFOF(valueOf(numReq));
	FIFOF#(WMCReq)       brmQ <- mkSizedFIFOF(5);
	FIFOF#(CacheLineNum) memQ <- mkSizedFIFOF(valueOf(numReq));

	FIFOF#(Bool)         resQ <- mkFIFOF();
	FIFOF#(WideMemResp)  hitQ <- mkFIFOF();
	FIFOF#(WideMemResp)  misQ <- mkFIFOF();

	Reg#(Maybe#(cacheRowIdx)) invIndex <- mkReg(tagged Valid 0); // Invalidate entries

	//////////// STATS ////////////

	Ehr#(2,Data) tWR <- mkEhr(0); // Total writes
	Ehr#(2,Data) tWB <- mkEhr(0); // Total writebacks
	Ehr#(2,Data) hRD <- mkEhr(0); // Total hits on read
	Ehr#(2,Data) mRD <- mkEhr(0); // Total miss on read

	//////////// INVALIDATE ON START ////////////

	rule do_invalidate if (invIndex matches tagged Valid .index);

		CacheMeta newMeta = CacheMeta { valid: False,
		                                dirty: False };

		for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
			metaArray[i].portA.request.put( BRAMRequest  { write          : True,
			                                               responseOnWrite: False,
			                                               address        : index,
			                                               datain         : newMeta } );
		end

		if(index < fromInteger(valueOf(TSub#(cacheRows,1)))) begin
			invIndex <= tagged Valid (index+1);
		end else begin
			invIndex <= tagged Invalid;
		end

	endrule

	//////////// ISSUE TO COLUMNS ////////////

	rule do_ISSUEREQ;

		WMCReq req = reqQ.first(); reqQ.deq();

		if(req.write) begin // We only write on one columns
			for (Integer i = 0; i < valueOf(cacheColumns); i=i+1)
				if(fromInteger(i) == replaceIndex) begin
					colReqQ[i].enq(WMCReq { inv  : False,
					                        write: True,
					                        dirty: req.dirty,
					                        num  : req.num,
					                        line : req.line });
				end else begin
					colReqQ[i].enq(WMCReq { inv  : True,
					                        write: False,
					                        dirty: req.dirty,
					                        num  : req.num,
					                        line : req.line });
				end
			replaceIndex <= replaceIndex+1;
		end else begin // We try to read from al of them
			brmQ.enq(req);
			for (Integer i = 0; i < valueOf(cacheColumns); i=i+1)
				colReqQ[i].enq(req);
		end

	endrule

	//////////// COLUMNS DO REQUEST ////////////

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_WPI;
			writePortHash[i][2] <= tagged Invalid;
		endrule

	end


	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_COLREQ if(!isValid(invIndex) && !colWBQ[i].notEmpty() && (!isValid(writePortHash[i][1]) || fromMaybe(?,writePortHash[i][1]) != hashOf(colReqQ[i].first.num)));

			WMCReq req = colReqQ[i].first(); colReqQ[i].deq();
			cacheRowIdx index = indexOf(req.num);

			colBRMQ[i].enq(req);

			dataArray[i].portA.request.put( BRAMRequest{ write          : False,
			                                             responseOnWrite: False,
			                                             address        : index,
			                                             datain         : ? } );
			tagsArray[i].portA.request.put( BRAMRequest{ write          : False,
			                                             responseOnWrite: False,
			                                             address        : index,
			                                             datain         : ? } );
			metaArray[i].portA.request.put( BRAMRequest{ write          : False,
			                                             responseOnWrite: False,
			                                             address        : index,
			                                             datain         : ? } );

		endrule

	end

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_COLRESP;

			WMCReq req = colBRMQ[i].first(); colBRMQ[i].deq();

			CacheLine line <- dataArray[i].portA.response.get;
			cacheTag  tag  <- tagsArray[i].portA.response.get;
			CacheMeta meta <- metaArray[i].portA.response.get;

			cacheRowIdx index = indexOf(req.num);

			if (req.inv) begin // invalidate

				if (meta.valid && (tag == tagOf(req.num))) begin // hit
					CacheMeta newMeta = CacheMeta { valid: False,
					                                dirty: False };
					metaArray[i].portB.request.put( BRAMRequest{ write          : True,
					                                             responseOnWrite: False,
					                                             address        : index,
					                                             datain         : newMeta } );
				end

				writePortHash[i][0] <= tagged Valid (hashOf(req.num));

			end else if (req.write) begin // write

				if(meta.valid && meta.dirty) begin // old line is dirty
					colWBQ[i].enq(WideMemReq { write: True,
					                           num  : {tag,index},
					                           line : line });
				end

				CacheMeta newMeta = CacheMeta { valid: True,
				                                dirty: req.dirty };

				dataArray[i].portB.request.put( BRAMRequest{ write          : True,
				                                             responseOnWrite: False,
				                                             address        : index,
				                                             datain         : req.line } );
				tagsArray[i].portB.request.put( BRAMRequest{ write          : True,
				                                             responseOnWrite: False,
				                                             address        : index,
				                                             datain         : tagOf(req.num) } );
				metaArray[i].portB.request.put( BRAMRequest{ write          : True,
				                                             responseOnWrite: False,
				                                             address        : index,
				                                             datain         : newMeta } );

				writePortHash[i][0] <= tagged Valid (hashOf(req.num));

			end else begin // read

				if (meta.valid && (tag == tagOf(req.num))) begin // read hit local

					colResQ[i].enq(tagged Valid line);

				end else begin // read miss local

					colResQ[i].enq(tagged Invalid);

				end

			end

			if (mem_ext_DEBUG)
				if (req.write && meta.valid && meta.dirty)  // old line is dirty
						tWB[0] <= tWB[0]+1;
				
		endrule

	end

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_WB;

			WideMemReq req = colWBQ[i].first(); colWBQ[i].deq();
			mem.req(req);

		endrule

	end

	//////////// COLLECT RES ////////////

	rule do_RESP;

		WMCReq req = brmQ.first(); brmQ.deq();

		WideMemResp res = unpack('0);
		Bool        val = False;

		for(Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
			colResQ[i].deq();
			res = unpack(pack(res)|pack(fromMaybe(unpack('0),colResQ[i].first)));
			val = val||isValid(colResQ[i].first);
		end

		if(val) begin // hit
			resQ.enq(True);
			hitQ.enq(res);
		end else begin // miss
			resQ.enq(False);
			memQ.enq(req.num);
			mem.req( WideMemReq { write: False,
			                      num  : req.num,
			                      line : req.line } );
		end

		if (mem_ext_DEBUG) begin
			if (val) begin
				// read hit
				hRD[0] <= hRD[0]+1;
			end else begin
				// read miss
				mRD[0] <= mRD[0]+1;
			end
		end

	endrule

	rule do_MEMRESP;

		WideMemResp  line <- mem.resp();
		CacheLineNum num  = memQ.first(); memQ.deq();

		reqQ.enq( WMCReq { inv  : False,
		                   write: True,
		                   dirty: False,
		                   num  : num,
		                   line : line } );

		misQ.enq(line);

	endrule

	//////////// INTERFACE ////////////

	interface WideMem cache;

		method Action req(WideMemReq r);

			reqQ.enq( WMCReq { inv  : False,
			                   write: r.write,
			                   dirty: r.write,
			                   num  : r.num,
			                   line : r.line } );

			if (mem_ext_DEBUG)
				if (r.write)
					tWR[0] <= tWR[0]+1;

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