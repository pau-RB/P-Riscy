import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import CMRTypes::*;
import BRAM::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;
import Ehr::*;

typedef CacheLineNum              CacheTag     #(numeric type cacheRows   );
typedef Bit#(TLog#(cacheRows))    CacheRowIndex#(numeric type cacheRows   );
typedef Bit#(TLog#(cacheHash))    CacheRowHash #(numeric type cacheHash   );
typedef Bit#(TLog#(cacheColumns)) CacheColIndex#(numeric type cacheColumns);

typedef struct{
	Bool valid;
	Bool dirty;
} CacheMeta deriving(Eq, Bits);

typedef enum{
	PUT, // Add this entry to the cache (WB if existing is dirty)
	INV, // If hit, invalidate this entry
	WR , // If hit, write this entry (WB if existing is miss)
	RD   // If hit, read this entry
} CacheOp deriving(Eq, Bits);

typedef struct{
	tagT          tag         ;
	CacheOp       op          ;
	Bool          dirty       ;
	CacheLineNum  addr        ;
	CacheLine     data        ;
	CacheLineMask byte_enable ;
} WMCReq#(type tagT) deriving(Eq, Bits);

interface WideMemCache#(numeric type cacheRows, numeric type cacheColumns, numeric type cacheHash, type tagT);
	interface WideMemClient#(tagT) mem;
	interface WideMemServer#(tagT) portA;
	`ifdef DEBUG_STATS
	method WMCStat getStat();
	`endif
endinterface

module mkWideMemCache(WideMemCache#(cacheRows, cacheColumns, cacheHash, tagT) ifc) provisos(Log#(cacheRows, b__),
                                                                                            Add#(c__, TLog#(cacheRows), CacheLineNumSz),
                                                                                            Log#(cacheColumns, d__),
                                                                                            Log#(cacheHash, e__),
                                                                                            Add#(f__, TLog#(cacheHash), TLog#(cacheRows)),
                                                                                            Add#(g__, TLog#(cacheHash), CacheLineNumSz),
                                                                                            Bits#(tagT, t__),
                                                                                            NumAlias#(numT, TExp#(SizeOf#(tagT))),
                                                                                            Alias#(cacheTag ,    CacheTag#(cacheRows)),
                                                                                            Alias#(cacheRowIdx,  CacheRowIndex#(cacheRows)),
                                                                                            Alias#(cacheRowHash, CacheRowHash#(cacheHash)),
                                                                                            Alias#(cacheColIdx,  CacheColIndex#(cacheColumns)));

	//////////// UTILITIES ////////////

	function cacheTag tagOf(CacheLineNum num);
		return truncateLSB(num);
	endfunction

	function cacheRowIdx indexOf(Integer offset, CacheLineNum num);
		cacheRowIdx idx = '0;
		for (Integer i = 0; i < valueOf(TLog#(cacheRows)); i=i+1)
			for (Integer j = i; j < valueOf(CacheLineNumSz); j=j+valueOf(TLog#(cacheRows)))
				idx[i] = idx[i]^num[(j+offset)%valueOf(CacheLineNumSz)];
		return idx;
	endfunction

	function cacheRowHash hashOf(Integer offset, CacheLineNum num);
		return truncate(indexOf(offset, num));
	endfunction

	//////////// BRAM ////////////

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	Vector#(cacheColumns, BRAM2PortBE#(cacheRowIdx, CacheLine, CacheLineBytes)) dataArray <- replicateM(mkBRAM2ServerBE(cfg));
	Vector#(cacheColumns, BRAM2Port  #(cacheRowIdx, cacheTag ))                 tagsArray <- replicateM(mkBRAM2Server  (cfg));
	Vector#(cacheColumns, BRAM2Port  #(cacheRowIdx, CacheMeta))                 metaArray <- replicateM(mkBRAM2Server  (cfg));

	Vector#(cacheColumns, Ehr#(3,Maybe#(cacheRowHash))) writePortHash <- replicateM(mkEhr(tagged Invalid)); // Prevent conflicts

	Reg#(cacheColIdx) replaceIndex <- mkReg(0);

	Vector#(numT,Reg#(CacheLineNum)) mshrArray <- replicateM(mkReg('0));

	//////////// QUEUES ////////////

	Vector#(cacheColumns, FIFOF#(WMCReq#(void)    )) colReqQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(WMCReq#(void)    )) colBRMQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(Maybe#(CacheLine))) colResQ <- replicateM(mkPipelineFIFOF());
	Vector#(cacheColumns, FIFOF#(WideMemReq#(tagT))) colWBQ  <- replicateM(mkPipelineFIFOF());

	FIFOF#(WMCReq#(tagT))      reqQ   <- mkFIFOF();
	FIFOF#(WMCReq#(tagT))      brmQ   <- mkSizedFIFOF(5);
	FIFOF#(WideMemReq#(tagT))  memreq <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(tagT))  memres <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(tagT))  resQ   <- mkFIFOF();

	Reg#(Maybe#(cacheRowIdx)) invIndex <- mkReg(tagged Valid 0); // Invalidate entries

	//////////// STATS ////////////

	`ifdef DEBUG_STATS
	Ehr#(2,PerfCnt) hWR <- mkEhr(0); // Total hits on write
	Ehr#(2,PerfCnt) mWR <- mkEhr(0); // Total miss on write
	Ehr#(2,PerfCnt) hRD <- mkEhr(0); // Total hits on read
	Ehr#(2,PerfCnt) mRD <- mkEhr(0); // Total miss on read
	Ehr#(3,PerfCnt) tWB <- mkEhr(0); // Total writebacks
	`endif

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

		WMCReq#(tagT) req = reqQ.first(); reqQ.deq();

		if(req.op == PUT) begin // We only put to one column
			colReqQ[replaceIndex].enq(WMCReq{ tag        : ?               ,
			                                  op         : req.op          ,
			                                  dirty      : req.dirty       ,
			                                  addr       : req.addr        ,
			                                  data       : req.data        ,
			                                  byte_enable: req.byte_enable });
			replaceIndex <= replaceIndex+1;
		end else begin // We try to read/inv/write from all of them
			for (Integer i = 0; i < valueOf(cacheColumns); i=i+1)
				colReqQ[i].enq(WMCReq{ tag        : ?               ,
				                       op         : req.op          ,
				                       dirty      : req.dirty       ,
				                       addr       : req.addr        ,
				                       data       : req.data        ,
				                       byte_enable: req.byte_enable });
			if(req.op == RD || req.op == WR)
				brmQ.enq(req);
		end

	endrule

	//////////// COLUMNS DO REQUEST ////////////

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_WPI;
			writePortHash[i][2] <= tagged Invalid;
		endrule

	end


	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_COLREQ if(!isValid(invIndex) && !colWBQ[i].notEmpty() && (!isValid(writePortHash[i][1]) || fromMaybe(?,writePortHash[i][1]) != hashOf(i,colReqQ[i].first.addr)));

			WMCReq#(void) req = colReqQ[i].first(); colReqQ[i].deq();
			cacheRowIdx index = indexOf(i,req.addr);

			colBRMQ[i].enq(req);

			dataArray[i].portA.request.put( BRAMRequestBE{ writeen        : '0   ,
			                                               responseOnWrite: False,
			                                               address        : index,
			                                               datain         : ?    });
			tagsArray[i].portA.request.put( BRAMRequest  { write          : False,
			                                               responseOnWrite: False,
			                                               address        : index,
			                                               datain         : ?    });
			metaArray[i].portA.request.put( BRAMRequest  { write          : False,
			                                               responseOnWrite: False,
			                                               address        : index,
			                                               datain         : ?    });

		endrule

	end

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_COLRESP;

			WMCReq#(void) req = colBRMQ[i].first(); colBRMQ[i].deq();

			CacheLine data <- dataArray[i].portA.response.get;
			cacheTag  tag  <- tagsArray[i].portA.response.get;
			CacheMeta meta <- metaArray[i].portA.response.get;

			cacheRowIdx index = indexOf(i,req.addr);


			case (req.op)
			PUT: begin

				if(meta.valid && meta.dirty) begin // old line is dirty
					colWBQ[i].enq(WideMemReq { tag        : ?    ,
					                           write      : True ,
					                           addr       : tag  ,
					                           data       : data ,
					                           byte_enable: '1   });
				end

				CacheMeta newMeta = CacheMeta { valid: True,
				                                dirty: req.dirty };

				dataArray[i].portB.request.put( BRAMRequestBE{ writeen        : req.byte_enable,
				                                               responseOnWrite: False          ,
				                                               address        : index          ,
				                                               datain         : req.data       });
				tagsArray[i].portB.request.put( BRAMRequest  { write          : True           ,
				                                               responseOnWrite: False          ,
				                                               address        : index          ,
				                                               datain         : tagOf(req.addr)});
				metaArray[i].portB.request.put( BRAMRequest  { write          : True           ,
				                                               responseOnWrite: False          ,
				                                               address        : index          ,
				                                               datain         : newMeta        });

				writePortHash[i][0] <= tagged Valid (hashOf(i,req.addr));

			end
			INV: begin

				if (meta.valid && (tag == tagOf(req.addr))) begin // hit
					CacheMeta newMeta = CacheMeta { valid: False,
					                                dirty: False };
					metaArray[i].portB.request.put( BRAMRequest{ write          : True,
					                                             responseOnWrite: False,
					                                             address        : index,
					                                             datain         : newMeta } );
				end

				writePortHash[i][0] <= tagged Valid (hashOf(i,req.addr));
				end

			WR : begin

				if (meta.valid && (tag == tagOf(req.addr))) begin // write hit local

					CacheMeta newMeta = CacheMeta { valid: True,
					                                dirty: req.dirty };

					dataArray[i].portB.request.put( BRAMRequestBE{ writeen        : req.byte_enable,
					                                               responseOnWrite: False          ,
					                                               address        : index          ,
					                                               datain         : req.data       });
					tagsArray[i].portB.request.put( BRAMRequest  { write          : True           ,
					                                               responseOnWrite: False          ,
					                                               address        : index          ,
					                                               datain         : tagOf(req.addr)});
					metaArray[i].portB.request.put( BRAMRequest  { write          : True           ,
					                                               responseOnWrite: False          ,
					                                               address        : index          ,
					                                               datain         : newMeta        });

					writePortHash[i][0] <= tagged Valid (hashOf(i,req.addr));

					colResQ[i].enq(tagged Valid (?));

				end else if(req.dirty) begin // write miss and new line is dirty

					colResQ[i].enq(tagged Invalid);

				end

			end
			RD : begin

				if (meta.valid && (tag == tagOf(req.addr))) begin // read hit local

					colResQ[i].enq(tagged Valid data);

				end else begin // read miss local

					colResQ[i].enq(tagged Invalid);

				end

			end
			endcase

		endrule

	end

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin

		rule do_WB;

			WideMemReq#(tagT) req = colWBQ[i].first(); colWBQ[i].deq();
			memreq.enq(req);

			`ifdef DEBUG_STATS
			tWB[1] <= tWB[1]+1;
			`endif

		endrule

	end

	//////////// COLLECT RES ////////////

	rule do_RESP;

		WMCReq#(tagT) req = brmQ.first(); brmQ.deq();

		CacheLine data = unpack('0);
		Bool      val  = False;

		for(Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
			colResQ[i].deq();
			data = unpack(pack(data)|pack(fromMaybe(unpack('0),colResQ[i].first)));
			val = val||isValid(colResQ[i].first);
		end

		if(req.op == WR) begin
			if(!val) begin // if no hit, we must WB
				memreq.enq(WideMemReq { tag        : ?               ,
				                        write      : True            ,
				                        addr       : req.addr        ,
				                        data       : req.data        ,
				                        byte_enable: req.byte_enable });
			end
		end else if(req.op == RD) begin
			if(val) begin // hit
				resQ.enq(WideMemRes{ tag: req.tag, data: data });
			end else begin // miss
				mshrArray[pack(req.tag)] <= req.addr;
				memreq.enq(WideMemReq { tag        : req.tag  ,
				                        write      : False    ,
				                        addr       : req.addr ,
				                        data       : req.data ,
				                        byte_enable: '0       });
			end
		end

		`ifdef DEBUG_STATS
		if(req.op == WR) begin
			if (val) begin
				hWR[0] <= hWR[0]+1;
			end else begin
				mWR[0] <= mWR[0]+1;
				tWB[0] <= tWB[0]+1;
			end
		end else if(req.op == RD) begin
			if (val) begin
				hRD[0] <= hRD[0]+1;
			end else begin
				mRD[0] <= mRD[0]+1;
			end
		end
		`endif

	endrule

	rule do_MEMRESP;

		WideMemRes#(tagT) res  = memres.first(); memres.deq();
		CacheLineNum      addr = mshrArray[pack(res.tag)];

		reqQ.enq( WMCReq { tag        : ?       ,
		                   op         : PUT     ,
		                   dirty      : False   ,
		                   addr       : addr    ,
		                   data       : res.data,
		                   byte_enable: '1      });

		resQ.enq(res);

	endrule

	//////////// INTERFACE ////////////

	interface WideMemClient mem;
        interface request = (interface Get#(WideMemReq#(tagT));
            method ActionValue#(WideMemReq#(tagT)) get();
                memreq.deq();
                return memreq.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememResp);
            method Action put(WideMemRes#(tagT) r);
                memres.enq(r);
            endmethod
        endinterface);
    endinterface

	interface WideMemServer portA;
		interface request = (interface Put#(WideMemReq#(tagT));
			method Action put(WideMemReq#(tagT) r);
				reqQ.enq( WMCReq{tag        : r.tag         ,
				                 op         :(r.write?WR:RD),
				                 dirty      : r.write       ,
				                 addr       : r.addr        ,
				                 data       : r.data        ,
				                 byte_enable: r.byte_enable });
			endmethod
		endinterface);
		interface response = (interface Get#(WidememResp);
			method ActionValue#(WideMemRes#(tagT)) get();
				resQ.deq(); return resQ.first(); 
			endmethod
		endinterface);
	endinterface

	`ifdef DEBUG_STATS
	method WMCStat getStat();
		return WMCStat{ hWR: hWR[1],
		                mWR: mWR[1],
		                hRD: hRD[1],
		                mRD: mRD[1],
		                tWB: tWB[2]};
	endmethod
	`endif

endmodule