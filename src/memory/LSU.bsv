import Config::*;
import Types::*;
import LSUTypes::*;
import Fifo::*;
import Ehr::*;
import Vector::*;
import BRAMCore::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(LSUCacheRows))) CacheTag;
typedef Bit#(TLog#(LSUCacheRows)) CacheIndex;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;
typedef Bit#(TLog#(LSUCacheColumns)) CacheBank;

//////////// UTILITIES ////////////

function CacheLineNum cacheLineNumReq(LSUReq#(transIdType) r) provisos(Bits#(LSUReq#(transIdType),reqSz));
    Addr a = r.addr;
    CacheLineNum num = truncateLSB(a);
    return num;
endfunction

function CacheLineNum cacheLineNumAddr(Addr a);
    CacheLineNum num = truncateLSB(a);
    return num;
endfunction

function Bit#(CacheLineBytes) writeEnDCR (DataCacheReq req);
    
    Bit#(CacheLineBytes) write_en = 0;

    CacheByteSelect wordsel = truncate( req.addr & 32'hfffffffc );
    CacheByteSelect halfsel = truncate( req.addr & 32'hfffffffe );
    CacheByteSelect bytesel = truncate( req.addr & 32'hffffffff );

    if( req.op == St ) begin
        case(req.stFunc)
            SB:  write_en = 'b1    << bytesel;
            SH:  write_en = 'b11   << halfsel;
            SW:  write_en = 'b1111 << wordsel;
        endcase
    end else if ( req.op == Join ) begin
        write_en = 'b1111 << wordsel;
    end

    return write_en;

endfunction

function CacheLine embedDCR (DataCacheReq req);

    Data word = '0;

    if( req.op == St ) begin
        case(req.stFunc)
            SB:  word = {req.data[ 7:0],req.data[ 7:0],req.data[ 7:0],req.data[ 7:0]};
            SH:  word = {req.data[15:0],req.data[15:0]};
            SW:  word = {req.data};
        endcase
    end else if ( req.op == Join ) begin
        word = {req.data};
    end

    CacheLine line = replicate(word);

    return line;

endfunction

function Data extendLoad( Data value, Addr addr, LoadFunc func );

    Bit#(32) wordValue = value;
    
    Bit#(5)  halfsel   = {(addr[1:0] & 2'b10),3'b000};
    Bit#(16) halfValue = truncate(value>>halfsel);

    Bit#(5)  bytesel   = {(addr[1:0] & 2'b11),3'b000};
    Bit#(8)  byteValue = truncate(value>>bytesel);

    case(func)
        LB:  return signExtend(byteValue);
        LH:  return signExtend(halfValue);
        LW:  return signExtend(wordValue);
        LBU: return zeroExtend(byteValue);
        LHU: return zeroExtend(halfValue);
        default: return value;
    endcase

endfunction

module mkNullDataCache (BareDataCache ifc);

	method ActionValue#(Bool) req(DataCacheReq r);
		return True;
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

typedef struct{
	Bool     req;
    MemOp    op;
    LoadFunc ldFunc;
    Addr     addr;
} BramReq deriving(Eq, Bits, FShow);

module mkDirectDataCache (BareDataCache ifc);

	Vector#(LSUCacheRows,Reg#(Bool))     valid <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(Bool))     dirty <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(CacheTag)) tags  <- replicateM(mkReg(0));

	BRAM_DUAL_PORT_BE#(CacheIndex, CacheLine, CacheLineBytes) bram  <- mkBRAMCore2BE(valueOf(LSUCacheRows), False);
	Fifo#(1,BramReq) bramReq <- mkStageFifo();
	// Use port a for R and port b for W, important in Join (both operations)

	method ActionValue#(Bool) req(DataCacheReq r);

		Addr                 addr    = r.addr;
		CacheTag             tag     = truncateLSB(addr);
		CacheIndex           index   = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
		Bit#(CacheLineBytes) writeEn = writeEnDCR(r);
		CacheLine            writeLn = embedDCR(r);

		if (valid[index] && (tags[index] == tag)) begin // hit

			bramReq.enq(BramReq{ req   : True,
			                     op    : r.op,
			                     ldFunc: r.ldFunc,
								 addr  : r.addr});

			if(r.op == Ld) begin
				bram.a.put('0, index, ?);
			end else if (r.op == St) begin
				bram.b.put(writeEn, index, writeLn);
				dirty[index] <= True;
			end else if(r.op == Join) begin
				bram.a.put('0, index, ?);
				bram.b.put(writeEn, index, writeLn);
				dirty[index] <= True;
			end

			return True;

		end else begin // miss

			return False;

		end

	endmethod

    method ActionValue#(DataCacheResp) resp() if(bramReq.first().req);

    	MemOp           op         = bramReq.first().op;
    	LoadFunc        ldFunc     = bramReq.first().ldFunc;
    	Addr            addr       = bramReq.first().addr;
		CacheWordSelect wordSelect = truncate(addr >> 2);

		CacheLine line = bram.a.read; bramReq.deq();

		Data word = line[wordSelect];

		if(op==Ld) begin
			word = extendLoad(word, addr, ldFunc);
		end

		return tagged Valid word;

    endmethod

    method Action put(DataCacheWB wb);

    	CacheLineNum num   = wb.num;
    	CacheLine    line  = wb.line;
    	CacheTag     tag   = truncateLSB(num);
		CacheIndex   index = truncate(num);

		valid[index] <= True;
		dirty[index] <= False;
		tags [index] <= tag;

		bram.b.put('1, index, line);

		if(valid[index] && dirty[index]) begin
			bramReq.enq(BramReq{ req    : False,
			                     op     : ?,
			                     ldFunc : ?,
			                     addr   : {{tags[index],index},'0}});
			bram.a.put('0, index, ? );
		end

    endmethod

    method ActionValue#(DataCacheWB) get() if(!bramReq.first().req);

    	CacheLineNum num   = truncateLSB(bramReq.first().addr);
    	CacheLine    line  = bram.a.read; bramReq.deq();

    	return DataCacheWB { num:  num,
    	                     line: line};

    endmethod

endmodule

module mkAssociativeDataCache (BareDataCache ifc);

	Vector#(LSUCacheColumns,BareDataCache) bank <- replicateM(mkDirectDataCache());
	Fifo#(1,CacheBank) bankHit <- mkStageFifo();
	Reg#(CacheBank) bankPut <- mkReg(0);
	Fifo#(1,DataCacheWB) wbFifo <- mkBypassFifo();

	for (Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1) begin
		rule do_COLLECT_WB;
			let wb <- bank[i].get();
			wbFifo.enq(wb);
		endrule
	end

	method ActionValue#(Bool) req(DataCacheReq r) if(!wbFifo.notEmpty());
		Bool      hit      = False;
		CacheBank whichHit = ?;
		for(Integer i = 0; i < valueOf(LSUCacheColumns); i=i+1) begin
			let hitBank <- bank[fromInteger(i)].req(r);
			if(hitBank) begin
				whichHit = fromInteger(i);
				hit = True;
			end
		end
		if(hit) begin
			bankHit.enq(whichHit);
		end
		return hit;
	endmethod

	method ActionValue#(DataCacheResp) resp();
		bankHit.deq();
		let r <- bank[bankHit.first()].resp();
		return r;
	endmethod

	method Action put(DataCacheWB wb);
		bank[bankPut].put(wb);
		bankPut <= bankPut+1;
	endmethod

	method ActionValue#(DataCacheWB) get();
		wbFifo.deq();
		return wbFifo.first();
	endmethod

endmodule

typedef struct{
	transIdType transId;
	Bool        isOld;
	Bool        isHit;
} DataCacheToken#(type transIdType) deriving(Eq, Bits, FShow);

module mkLSU (WideMem mem, BareDataCache dataCache, LSU#(transIdType) ifc) provisos(Bits#(transIdType,transIdTypeSz),FShow#(transIdType));

	Fifo#(4,LSUReq#(transIdType))         mshr    <- mkPipelineFifo();

	Fifo#(1,LSUReq#(transIdType))         inReqQ  <- mkBypassFifo();
	Fifo#(1,DataCacheToken#(transIdType)) dcReqQ  <- mkStageFifo();
	Fifo#(1,Addr)                         memReqQ <- mkPipelineFifo();
	Fifo#(1,LSUResp#(transIdType))        respQ   <- mkBypassFifo();

	Ehr#(2,Bool) flushMSHR <- mkEhr(False);

	rule do_RETRY if(flushMSHR[0]);

		if(mshr.notEmpty()) begin

			let r = mshr.first(); mshr.deq();
			let hit <- dataCache.req(DataCacheReq{ op    : r.op,
			                                       ldFunc: r.ldFunc,
			                                       stFunc: r.stFunc,
			                                       addr  : r.addr,
			                                       data  : r.data });
			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : True,
			                           isHit  : True });

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

		let num  = cacheLineNumAddr(memReqQ.first()); memReqQ.deq();
		let line <- mem.resp();
		dataCache.put(DataCacheWB{ num:  num,
		                           line: line });
		flushMSHR[0] <= True;

	endrule

	rule do_INREQ if(!flushMSHR[1]);

		let r = inReqQ.first();

		let hit <- dataCache.req(DataCacheReq{ op    : r.op,
		                                       ldFunc: r.ldFunc,
		                                       stFunc: r.stFunc,
		                                       addr  : r.addr,
		                                       data  : r.data });

		if(hit) begin
			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : False,
			                           isHit  : True });
			inReqQ.deq();

		end else begin

			if(!mshr.notEmpty()) begin

				dcReqQ.enq(DataCacheToken{ transId: r.transId,
				                           isOld  : False,
				                           isHit  : False });
				inReqQ.deq();

				mshr.enq(r);
				memReqQ.enq(r.addr);
				mem.req(WideMemReq{ write_en: '0,
									addr    : r.addr,
									data    : ? });

			end else if(cacheLineNumReq(mshr.first())==cacheLineNumReq(r)) begin

				dcReqQ.enq(DataCacheToken{ transId: r.transId,
				                           isOld  : False,
				                           isHit  : False });
				inReqQ.deq();

				mshr.enq(r);

			end

		end

	endrule

	rule do_RESP;

		let r = dcReqQ.first(); dcReqQ.deq();

		if(r.isOld) begin

			let d <- dataCache.resp();
			respQ.enq(LSUResp{ valid  : True,
			                   isOld  : True,
			                   data   : fromMaybe(?,d),
			                   transId: r.transId });

		end else if(r.isHit) begin

			let d <- dataCache.resp();
			respQ.enq(LSUResp{ valid  : True,
			                   isOld  : False,
			                   data   : fromMaybe(?,d),
			                   transId: r.transId });

		end else begin

			respQ.enq(LSUResp{ valid  : False,
			                   isOld  : False,
			                   data   : ?,
			                   transId: r.transId });

		end

	endrule

	method Action req(LSUReq#(transIdType) r);
		inReqQ.enq(r);
	endmethod

    method ActionValue#(LSUResp#(transIdType)) resp if(respQ.first().isOld==False);
    	respQ.deq();
    	return respQ.first();
    endmethod

    method ActionValue#(LSUResp#(transIdType)) oldResp if(respQ.first().isOld==True);
    	respQ.deq();
    	return respQ.first();
    endmethod

endmodule