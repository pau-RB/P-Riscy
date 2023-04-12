import Types::*;
import WideMemTypes::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Ehr::*;
import Vector::*;
import BRAM::*;

typedef CacheLineNum              CacheTag     #(numeric type cacheRows   );
typedef Bit#(TLog#(cacheRows))    CacheRowIndex#(numeric type cacheRows   );
typedef Bit#(TLog#(cacheColumns)) CacheColIndex#(numeric type cacheColumns);

typedef enum{PUT,LB,LH,LW,LBU,LHU,SB,SH,SW,JOIN} DataCacheOp deriving(Bits, Eq, FShow);

typedef struct{
	DataCacheOp op;
	Addr        addr;
	Data        data;
	CacheLine   line;
} DataCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(Data) DataCacheResp;

interface BareDataCache#(numeric type cacheRows, numeric type cacheColumns);
	method Action invalidate();
	method Action req(DataCacheReq r);
	method ActionValue#(DataCacheResp) resp();
	method ActionValue#(WideMemReq#(void)) getWB();
endinterface

function CacheWordSelect wordSelectOf(Addr addr);
    CacheWordSelect wordSelect = truncate(addr >> 2);
    return wordSelect;
endfunction

function Data extendLoad( Data value, Addr addr, DataCacheOp op);

    Bit#(32) wordValue = value;
    
    Bit#(5)  halfsel   = {(addr[1:0] & 2'b10),3'b000};
    Bit#(16) halfValue = truncate(value>>halfsel);

    Bit#(5)  bytesel   = {(addr[1:0] & 2'b11),3'b000};
    Bit#(8)  byteValue = truncate(value>>bytesel);

    case(op)
        LB : return signExtend(byteValue);
        LH : return signExtend(halfValue);
        LW : return signExtend(wordValue);
        LBU: return zeroExtend(byteValue);
        LHU: return zeroExtend(halfValue);
        default: return value;
    endcase

endfunction

typedef struct{
	Bool     valid;
	Bool     dirty;
} CacheMeta deriving(Eq, Bits, FShow);

module mkDirectDataCache (BareDataCache#(cacheRows, cacheColumns) ifc) provisos(Alias#(cacheTag   ,  CacheTag#(cacheRows)),
                                                                                Alias#(cacheRowIdx,  CacheRowIndex#(cacheRows)));

	function Bit#(CacheLineBytes) writeEnOf (Addr addr, DataCacheOp op);

	    CacheByteSelect wordsel = truncate(addr & 32'hfffffffc );
	    CacheByteSelect halfsel = truncate(addr & 32'hfffffffe );
	    CacheByteSelect bytesel = truncate(addr & 32'hffffffff );

	    case(op)
	        SB  : return 'b1    << bytesel;
	        SH  : return 'b11   << halfsel;
	        SW  : return 'b1111 << wordsel;
	        JOIN: return 'b1111 << wordsel;
	        default: return '0;
	    endcase

	endfunction

	function CacheLine writeLnOf (Addr addr, DataCacheOp op, Data data);

	    case(op)
	        SB     : return replicate({data[ 7:0],data[ 7:0],data[ 7:0],data[ 7:0]});
	        SH     : return replicate({data[15:0],data[15:0]});
	        SW     : return replicate({data});
	        JOIN   : return replicate({32'd1});
	        default: return replicate('0);
	    endcase

	endfunction

	function cacheTag tagOf(Addr addr);
		return truncateLSB(addr);
	endfunction

	function cacheRowIdx indexOf(Addr addr);
		cacheRowIdx  idx = '0;
		CacheLineNum num = truncateLSB(addr);
		for (Integer i = 0; i < valueOf(TLog#(cacheRows)); i=i+1)
			for (Integer j = i; j < valueOf(CacheLineNumSz); j=j+valueOf(TLog#(cacheRows)))
				idx[i] = idx[i]^num[j];
		return idx;
	endfunction

	Reg#(Maybe#(cacheRowIdx)) invIndex <- mkReg(tagged Valid 0);

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 1,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM2PortBE#(cacheRowIdx, CacheLine, CacheLineBytes) dataArray <- mkBRAM2ServerBE(cfg);
	BRAM2Port  #(cacheRowIdx, cacheTag                 ) tagsArray <- mkBRAM2Server  (cfg);
	BRAM2Port  #(cacheRowIdx, CacheMeta                ) metaArray <- mkBRAM2Server  (cfg);

	FIFOF#(DataCacheReq)      reqQ    <- mkBypassFIFOF();
	FIFOF#(DataCacheReq)      bramReq <- mkPipelineFIFOF();
	FIFOF#(DataCacheResp)     resQ    <- mkBypassFIFOF();
	FIFOF#(WideMemReq#(void)) wbQ     <- mkBypassFIFOF();

	Ehr#(3,Maybe#(cacheRowIdx)) writePortIndex <- mkEhr(tagged Invalid); // Prevent conflicts

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

	rule do_WPI;
		writePortIndex[2] <= tagged Invalid;
	endrule

	rule do_REQ if(!wbQ.notEmpty() && !isValid(invIndex) && (!isValid(writePortIndex[1]) || fromMaybe(?,writePortIndex[1]) != indexOf(reqQ.first.addr)));

		DataCacheReq req = reqQ.first(); reqQ.deq();
		cacheRowIdx index = indexOf(req.addr);

		bramReq.enq(req);
		dataArray.portA.request.put( BRAMRequestBE{ writeen        : '0,
		                                            responseOnWrite: False,
		                                            address        : index,
		                                            datain         : ? } );
		tagsArray.portA.request.put( BRAMRequest  { write          : False,
		                                            responseOnWrite: False,
		                                            address        : index,
		                                            datain         : ? } );
		metaArray.portA.request.put( BRAMRequest  { write          : False,
		                                            responseOnWrite: False,
		                                            address        : index,
		                                            datain         : ? } );
	endrule

	rule do_RESP;

		DataCacheReq req = bramReq.first(); bramReq.deq();

		CacheLine  data <- dataArray.portA.response.get;
		cacheTag   tag  <- tagsArray.portA.response.get;
		CacheMeta  meta <- metaArray.portA.response.get;

		cacheRowIdx          index      = indexOf     (req.addr);
		CacheWordSelect      wordSelect = wordSelectOf(req.addr);
		Bit#(CacheLineBytes) writeEn    = writeEnOf   (req.addr, req.op);
		CacheLine            writeLn    = writeLnOf   (req.addr, req.op, req.data);

		if(req.op == PUT || req.op == SB ||req.op == SH ||req.op == SW || req.op == JOIN) begin
			writePortIndex[0] <= tagged Valid (index);
		end

		if(req.op == PUT) begin

			if(meta.valid && meta.dirty) begin // old line is dirty
				wbQ.enq(WideMemReq { tag  : ?,
				                     write: True,
				                     num  : tag, //{tag,index},
				                     line : data });
			end

			CacheMeta newMeta = CacheMeta { valid: True,
			                                dirty: False };

			dataArray.portB.request.put( BRAMRequestBE{ writeen        : '1,
			                                            responseOnWrite: False,
			                                            address        : index,
			                                            datain         : req.line } );
			tagsArray.portB.request.put( BRAMRequest  { write          : True,
			                                            responseOnWrite: False,
			                                            address        : index,
			                                            datain         : tagOf(req.addr)} );
			metaArray.portB.request.put( BRAMRequest  { write          : True,
			                                            responseOnWrite: False,
			                                            address        : index,
			                                            datain         : newMeta } );

		end else if (meta.valid && (tag == tagOf(req.addr))) begin // request hit

			if(req.op == SB ||req.op == SH ||req.op == SW || req.op == JOIN) begin
				CacheMeta newMeta = CacheMeta { valid: True,
				                                dirty: True };

				dataArray.portB.request.put( BRAMRequestBE{ writeen        : writeEn,
				                                            responseOnWrite: False,
				                                            address        : index,
				                                            datain         : writeLn } );
				metaArray.portB.request.put( BRAMRequest  { write          : True,
				                                            responseOnWrite: False,
				                                            address        : index,
				                                            datain         : newMeta } );
			end

			resQ.enq(tagged Valid extendLoad(data[wordSelect], req.addr, req.op));

		end else begin // request miss

			resQ.enq(tagged Invalid);

		end

	endrule

	method Action invalidate();
		invIndex <= tagged Valid 0;
	endmethod

	method Action req(DataCacheReq r);
		reqQ.enq(r);
	endmethod

	method ActionValue#(DataCacheResp) resp();
		resQ.deq();
		return resQ.first();
	endmethod

	method ActionValue#(WideMemReq#(void)) getWB();
		wbQ.deq();
		return wbQ.first();
	endmethod

endmodule

module mkAssociativeDataCache (BareDataCache#(cacheRows, cacheColumns) ifc) provisos(Alias#(cacheColIdx,  CacheColIndex#(cacheColumns)));

	Vector#(cacheColumns,BareDataCache#(cacheRows,cacheColumns)) lane <- replicateM(mkDirectDataCache());
	Reg#(cacheColIdx) replaceIndex <- mkReg(0);
	FIFOF#(WideMemReq#(void)) wbFifo <- mkBypassFIFOF();

	for (Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
		rule do_COLLECT_WB;
			let wb <- lane[i].getWB();
			wbFifo.enq(wb);
		endrule
	end

	method Action invalidate();
		for (Integer i = 0; i < valueOf(cacheColumns); i=i+1)
			lane[i].invalidate();
	endmethod

	method Action req(DataCacheReq r) if(!wbFifo.notEmpty());
		if(r.op==PUT) begin
			lane[replaceIndex].req(r);
			replaceIndex <= replaceIndex+1;
		end else begin
			for(Integer i = 0; i < valueOf(cacheColumns); i=i+1)
				lane[fromInteger(i)].req(r);
		end
	endmethod

	method ActionValue#(DataCacheResp) resp();
		Data res = '0;
		Bool val = False;

		for(Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
			let partial <- lane[fromInteger(i)].resp();
			res = res|fromMaybe('0,partial);
			val = val||isValid(partial);
		end

		return (val ? tagged Valid res : tagged Invalid);

	endmethod

	method ActionValue#(WideMemReq#(void)) getWB();
		wbFifo.deq();
		return wbFifo.first();
	endmethod

endmodule
