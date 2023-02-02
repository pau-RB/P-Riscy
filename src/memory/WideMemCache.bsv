import Config::*;
import Types::*;

import BRAM::*;
import FIFOF::*;
import Vector::*;
import Ehr::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(L2CacheRows))) CacheTag;
typedef Bit#(TLog#(L2CacheRows))                                              CacheIndex;

function CacheTag tagOf(CacheLineNum num);
	return truncateLSB(num);
endfunction

function CacheIndex indexOf(CacheLineNum num);
	return truncate(num);
endfunction

typedef struct{
	Bool     valid;
	Bool     dirty;
} CacheMeta deriving(Eq, Bits, FShow);

module mkWideMemCache(WideMem mem, WideMem ifc);

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM2Port#(CacheIndex, CacheLine) dataArray <- mkBRAM2Server(cfg);
	BRAM2Port#(CacheIndex, CacheTag ) tagsArray <- mkBRAM2Server(cfg);
	BRAM2Port#(CacheIndex, CacheMeta) metaArray <- mkBRAM2Server(cfg);

	FIFOF#(WideMemReq)  reqQ     <- mkFIFOF();
	FIFOF#(WideMemReq)  bramReqQ <- mkFIFOF();

	FIFOF#(Bool)        resQ     <- mkFIFOF();
	FIFOF#(WideMemResp) hitQ     <- mkFIFOF();
	FIFOF#(WideMemResp) misQ     <- mkFIFOF();

	FIFOF#(WideMemReq)  wbQ      <- mkFIFOF();

	Ehr#(3,Maybe#(CacheIndex)) writePortIndex <- mkEhr(tagged Invalid); // Prevent conflicts
	Reg#(Maybe#(CacheIndex))   invIndex       <- mkReg(tagged Valid 0); // Invalidate entries

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
		if(index < fromInteger(valueOf(TSub#(L2CacheRows,1)))) begin
			invIndex <= tagged Valid (index+1);
		end else begin
			invIndex <= tagged Invalid;
		end

	endrule

	rule do_REQ if(!wbQ.notEmpty() && !isValid(invIndex) && (!isValid(writePortIndex[1]) || fromMaybe(?,writePortIndex[1]) != indexOf(reqQ.first.num)));

		WideMemReq req   = reqQ.first(); reqQ.deq();
		CacheIndex index = indexOf(req.num);

		bramReqQ.enq(req);
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

		WideMemReq req = bramReqQ.first(); bramReqQ.deq();

		CacheLine  line <- dataArray.portA.response.get;
		CacheTag   tag  <- tagsArray.portA.response.get;
		CacheMeta  meta <- metaArray.portA.response.get;

		CacheIndex index = indexOf(req.num);

		if (req.write) begin // write

			if(meta.valid && meta.dirty) begin // old line is dirty
				wbQ.enq(WideMemReq { write: True,
				                     num  : {tag,index},
				                     line : line });
			end

			CacheMeta newMeta = CacheMeta { valid: True,
			                                dirty: True };

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

			resQ.enq(False);
			mem.req(req);

		end

	endrule

	rule do_MEMRESP;

		WideMemResp res <- mem.resp();
		misQ.enq(res);

	endrule

	rule do_WB;

		WideMemReq wb = wbQ.first(); wbQ.deq();

		mem.req(wb);

	endrule

	method Action req(WideMemReq r);
		reqQ.enq(r);
	endmethod

	method ActionValue#(WideMemResp) resp;
		if(resQ.first) begin // hit
			WideMemResp res = hitQ.first(); hitQ.deq(); resQ.deq();
			return res;
		end else begin
			WideMemResp res = misQ.first(); misQ.deq(); resQ.deq();
			return res;
		end
	endmethod

endmodule