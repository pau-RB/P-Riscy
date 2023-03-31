import Config::*;
import Types::*;
import WideMemTypes::*;
import CMRTypes::*;
import CFFifo::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Ehr::*;
import Vector::*;
import BRAM::*;

typedef CacheLineNum                CacheTag;
typedef Bit#(TLog#(LSUCacheRows))   CacheIndex;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

typedef Bit#(TLog#(LSUCacheColumns)) CacheLane;

//////////// UTILITIES ////////////

function DataCacheOp cacheOpOf(MemOp op, LoadFunc ldFunc, StoreFunc stFunc);
	case(op)
		Ld: case(ldFunc)
				LB : return LB ;
				LH : return LH ;
				LW : return LW ;
				LBU: return LBU;
				LHU: return LHU;
			endcase
		St: case(stFunc)
				SB: return SB;
				SH: return SH;
				SW: return SW;
			endcase
		Join: return JOIN;
	endcase
endfunction


function CacheTag tagOf(Addr addr);
	return truncateLSB(addr);
endfunction

function CacheIndex indexOf(Addr addr);
	CacheIndex   idx = '0;
	CacheLineNum num = truncateLSB(addr);
	for (Integer i = 0; i < valueOf(TLog#(LSUCacheRows)); i=i+1)
		for (Integer j = i; j < valueOf(CacheLineNumSz); j=j+valueOf(TLog#(LSUCacheRows)))
			idx[i] = idx[i]^num[j];
	return idx;
endfunction

function CacheOffset offsetOf(Addr addr);
	return truncate(addr >> 2);
endfunction

function CacheLineNum lineNumOf(Addr addr);
    CacheLineNum num = truncateLSB(addr);
    return num;
endfunction

function CacheWordSelect wordSelectOf(Addr addr);
    CacheWordSelect wordSelect = truncate(addr >> 2);
    return wordSelect;
endfunction


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

//////////// BARE DATA CACHE TYPES ////////////

typedef enum{PUT,LB,LH,LW,LBU,LHU,SB,SH,SW,JOIN} DataCacheOp deriving(Bits, Eq, FShow);

typedef struct{
	DataCacheOp op;
	Addr        addr;
	Data        data;
	CacheLine   line;
} DataCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(Data) DataCacheResp;

interface BareDataCache;
	method Action invalidate();
	method Action req(DataCacheReq r);
	method ActionValue#(DataCacheResp) resp();
	method ActionValue#(WideMemReq#(void)) getWB();
endinterface

//////////// LSU TYPES ////////////

typedef struct{
	MemOp       op;
	LoadFunc    ldFunc;
	StoreFunc   stFunc;
	Addr        addr;
	Data        data;
	transIdType	transId;
} LSUReq#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Bool        valid;
	Data        data;
	transIdType transId;
} LSUResp#(type transIdType) deriving(Eq, Bits, FShow);

interface LSU#(numeric type numHart);
	interface WideMemClient#(Bit#(TLog#(numHart))) mem;
	method Action req(LSUReq#(Bit#(TLog#(numHart))) r);
	method ActionValue#(LSUResp#(Bit#(TLog#(numHart)))) resp();
	method ActionValue#(LSUResp#(Bit#(TLog#(numHart)))) oldResp();
	method LSUStat getStat();
endinterface

//////////// BARE DATA CACHE ////////////

typedef struct{
	Bool     valid;
	Bool     dirty;
} CacheMeta deriving(Eq, Bits, FShow);

module mkDirectDataCache (BareDataCache ifc);

	Reg#(Maybe#(CacheIndex)) invIndex <- mkReg(tagged Valid 0);

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 1,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM2PortBE#(CacheIndex, CacheLine, CacheLineBytes) dataArray <- mkBRAM2ServerBE(cfg);
	BRAM2Port  #(CacheIndex, CacheTag                 ) tagsArray <- mkBRAM2Server  (cfg);
	BRAM2Port  #(CacheIndex, CacheMeta                ) metaArray <- mkBRAM2Server  (cfg);

	FIFOF#(DataCacheReq)      reqQ    <- mkBypassFIFOF();
	FIFOF#(DataCacheReq)      bramReq <- mkPipelineFIFOF();
	FIFOF#(DataCacheResp)     resQ    <- mkBypassFIFOF();
	FIFOF#(WideMemReq#(void)) wbQ     <- mkBypassFIFOF();

	Ehr#(3,Maybe#(CacheIndex)) writePortIndex <- mkEhr(tagged Invalid); // Prevent conflicts

	rule do_invalidate if (invIndex matches tagged Valid .index);

		CacheMeta newMeta = CacheMeta { valid: False,
		                                dirty: False };
		metaArray.portA.request.put( BRAMRequest  { write          : True,
		                                            responseOnWrite: False,
		                                            address        : index,
		                                            datain         : newMeta } );
		if(index < fromInteger(valueOf(TSub#(LSUCacheRows,1)))) begin
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
		CacheIndex index = indexOf(req.addr);

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
		CacheTag   tag  <- tagsArray.portA.response.get;
		CacheMeta  meta <- metaArray.portA.response.get;

		CacheIndex           index      = indexOf     (req.addr);
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

module mkAssociativeDataCache (BareDataCache ifc);

	Vector#(LSUCacheColumns,BareDataCache) lane <- replicateM(mkDirectDataCache());
	Reg#(CacheLane) replaceIndex <- mkReg(0);
	FIFOF#(WideMemReq#(void)) wbFifo <- mkBypassFIFOF();

	for (Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1) begin
		rule do_COLLECT_WB;
			let wb <- lane[i].getWB();
			wbFifo.enq(wb);
		endrule
	end

	method Action invalidate();
		for (Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1)
			lane[i].invalidate();
	endmethod

	method Action req(DataCacheReq r) if(!wbFifo.notEmpty());
		if(r.op==PUT) begin
			lane[replaceIndex].req(r);
			replaceIndex <= replaceIndex+1;
		end else begin
			for(Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1)
				lane[fromInteger(i)].req(r);
		end
	endmethod

	method ActionValue#(DataCacheResp) resp();
		Data res = '0;
		Bool val = False;

		for(Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1) begin
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

//////////// LSU  ////////////

typedef struct{
	LSUReq#(transIdType) req;
	Bool                 isOld;
} DataCacheToken#(type transIdType) deriving(Eq, Bits, FShow);


interface MSHR#(numeric type numHart);
	method Bool isMatch(Addr addr);
	method Action enq(LSUReq#(Bit#(TLog#(numHart))) req);
	method Action deq();
	method LSUReq#(Bit#(TLog#(numHart))) first();
	method Bool isEmpty();
	method Bool isLast();
	method CacheLineNum cacheLineNum();
endinterface

module mkMSHR (MSHR#(numHart)) provisos(Add#(a__, 1, TLog#(numHart)), Alias#(hartID, Bit#(TLog#(numHart))));

	Fifo#(numHart,LSUReq#(hartID)) requests <- mkCFFifo();
	Reg #(CacheLineNum) linenum  <- mkReg(?);
	Reg #(hartID) numreq <- mkReg('0);

	method Bool isMatch(Addr addr);
		return (numreq != '0 && linenum == lineNumOf(addr));
	endmethod

	method Action enq(LSUReq#(hartID) r);
		linenum <= lineNumOf(r.addr);
		requests.enq(r);
		numreq <= numreq+1;
	endmethod

	method Action deq();
		requests.deq();
		numreq <= numreq-1;
	endmethod

	method LSUReq#(hartID) first();
		return requests.first();
	endmethod

	method Bool isEmpty();
		return !requests.notEmpty();
	endmethod

	method Bool isLast();
		return (numreq == 'd1);
	endmethod

	method CacheLineNum cacheLineNum();
		return linenum;
	endmethod

endmodule

module mkLSU (LSU#(numHart) ifc) provisos(Add#(a__, 1, TLog#(numHart)), Alias#(hartID, Bit#(TLog#(numHart))));

	BareDataCache                    dataCache <- (lsuAssociative ? mkAssociativeDataCache() : mkDirectDataCache());
	Vector#(numHart, MSHR#(numHart)) mshrArray <- replicateM(mkMSHR());
	Ehr#(2,Maybe#(hartID))           retryMSHR <- mkEhr(tagged Invalid);

	FIFOF#(LSUReq        #(hartID)) inReqQ   <- mkBypassFIFOF();
	FIFOF#(DataCacheToken#(hartID)) dcReqQ   <- mkPipelineFIFOF();
	FIFOF#(WideMemReq    #(hartID)) memreq   <- mkBypassFIFOF();
	FIFOF#(WideMemRes    #(hartID)) memres   <- mkBypassFIFOF();
	FIFOF#(LSUResp       #(hartID)) respQ    <- mkBypassFIFOF();
	FIFOF#(LSUResp       #(hartID)) oldRespQ <- mkBypassFIFOF();

	Ehr#(2,Data) hLd   <- mkEhr(0);
	Ehr#(2,Data) hSt   <- mkEhr(0);
	Ehr#(2,Data) hJoin <- mkEhr(0);
	Ehr#(2,Data) mLd   <- mkEhr(0);
	Ehr#(2,Data) mSt   <- mkEhr(0);
	Ehr#(2,Data) mJoin <- mkEhr(0);
	Ehr#(2,Data) dLd   <- mkEhr(0);
	Ehr#(2,Data) dSt   <- mkEhr(0);
	Ehr#(2,Data) dJoin <- mkEhr(0);

	rule do_INREQ if(!isValid(retryMSHR[1]));

		LSUReq#(hartID) req = inReqQ.first(); inReqQ.deq();

		dataCache.req(DataCacheReq{ op  : cacheOpOf(req.op, req.ldFunc, req.stFunc),
		                            addr: req.addr,
		                            data: req.data,
		                            line: ? });
		dcReqQ.enq(DataCacheToken{ req  : req,
		                           isOld: False });

	endrule

	rule do_RESP if(respQ.notFull() && oldRespQ.notFull() || !cmr_ext_DEBUG);
	// If cmr_ext_DEBUG (verification), we must preserve the order

		LSUReq#(hartID) req = dcReqQ.first().req; dcReqQ.deq();
		DataCacheResp d <- dataCache.resp();

		// Try matching an older mshr in case of miss
		Bool   isMatch = False;
		hartID idMatch = '0;

		for (Integer i = 0; i < valueOf(numHart); i = i+1) begin
			Bool mmMatch = mshrArray[fromInteger(i)].isMatch(req.addr);
			isMatch = isMatch || mmMatch;
			idMatch = idMatch  | signExtend(pack(mmMatch))&fromInteger(i);
		end

		if(isValid(d)) begin // Hit

			if(dcReqQ.first().isOld) begin // Old hit
				oldRespQ.enq(LSUResp{ valid  : True,
				                      data   : fromMaybe(?,d),
				                      transId: req.transId });
			end else begin // Young hit
				respQ.enq(LSUResp{ valid  : True,
				                   data   : fromMaybe(?,d),
				                   transId: req.transId });
			end

		end else begin // Young miss

			respQ.enq(LSUResp{ valid  : False,
			                   data   : ?,
			                   transId: req.transId });

			if(isMatch) begin
				mshrArray[idMatch].enq(req);
			end else begin
				mshrArray[req.transId].enq(req);
				memreq.enq(WideMemReq{ tag  : req.transId,
				                       write: False,
				                       num  : lineNumOf(req.addr),
				                       line : ? });
			end

		end

		if(mem_ext_DEBUG) begin
			if(!dcReqQ.first().isOld) begin
				if (isValid(d)) begin // hit
					case (req.op)
						Ld:   hLd  [0] <= hLd  [0]+1;
						St:   hSt  [0] <= hSt  [0]+1;
						Join: hJoin[0] <= hJoin[0]+1;
					endcase
				end else begin
					case (req.op)
						Ld:   mLd  [0] <= mLd  [0]+1;
						St:   mSt  [0] <= mSt  [0]+1;
						Join: mJoin[0] <= mJoin[0]+1;
					endcase
				end
			end
		end

	endrule

	rule do_MEMRESP if(!isValid(retryMSHR[0]));

		WideMemRes#(hartID) res = memres.first(); memres.deq();
		dataCache.req(DataCacheReq{ op  : PUT,
		                            addr: {mshrArray[res.tag].cacheLineNum,'0},
		                            data: ?,
		                            line: res.line });

		hartID mshrId = res.tag;
		if(!mshrArray[mshrId].isEmpty && mshrArray[mshrId].first.op == Ld) begin
			let  req = mshrArray[mshrId].first(); mshrArray[mshrId].deq();
			Data dat = extendLoad( res.line[wordSelectOf(req.addr)],
			                       req.addr,
			                       cacheOpOf(req.op, req.ldFunc, req.stFunc));
			oldRespQ.enq(LSUResp{ valid  : True,
			                      data   : dat,
			                      transId: mshrId });
			if(!mshrArray[mshrId].isLast())
				retryMSHR[0] <= tagged Valid res.tag;
		end else begin
			retryMSHR[0] <= tagged Valid res.tag;
		end

	endrule

	rule do_RETRY if(retryMSHR[0] matches tagged Valid .mshrId);

		let req = mshrArray[mshrId].first(); mshrArray[mshrId].deq();
		dataCache.req(DataCacheReq{ op  : cacheOpOf(req.op, req.ldFunc, req.stFunc),
		                            addr: req.addr,
		                            data: req.data,
		                            line: ? });
		dcReqQ.enq(DataCacheToken{ req  : req,
		                           isOld: True});

		if(mshrArray[mshrId].isLast())
			retryMSHR[0] <= tagged Invalid;

	endrule

	rule do_WB;

		let req <- dataCache.getWB();

		memreq.enq(WideMemReq{ tag  : ?,
		                       write: True,
		                       num  : req.num,
		                       line : req.line });

	endrule

	//////////// INTERFACE ////////////

	interface WideMemClient mem;
        interface request = (interface Get#(WideMemReq);
            method ActionValue#(WideMemReq#(hartID)) get();
                memreq.deq();
                return memreq.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememRes);
            method Action put(WideMemRes#(hartID) r);
                memres.enq(r);
            endmethod
        endinterface);
    endinterface

	method Action req(LSUReq#(hartID) r);
		inReqQ.enq(r);
	endmethod

	method ActionValue#(LSUResp#(hartID)) resp;
		respQ.deq();
		return respQ.first();
	endmethod

	method ActionValue#(LSUResp#(hartID)) oldResp;
		oldRespQ.deq();
		return oldRespQ.first();
	endmethod

	method LSUStat getStat();
		return LSUStat{ hLd      : hLd  [1],
		                hSt      : hSt  [1],
		                hJoin    : hJoin[1],
		                mLd      : mLd  [1],
		                mSt      : mSt  [1],
		                mJoin    : mJoin[1],
		                dLd      : dLd  [1],
		                dSt      : dSt  [1],
		                dJoin    : dJoin[1] };
	endmethod

endmodule