import Config::*;
import Types::*;
import CMRTypes::*;
import LSUTypes::*;
import Fifo::*;
import Ehr::*;
import Vector::*;
import BRAM::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(LSUCacheRows))) CacheTag;
typedef Bit#(TLog#(LSUCacheRows))                                              CacheIndex;
typedef Bit#(TLog#(CacheLineWords))                                            CacheOffset;

typedef Bit#(TLog#(LSUCacheColumns))                                           CacheBank;

//////////// UTILITIES ////////////

function CacheTag tagOf(Addr addr);
	return truncateLSB(addr);
endfunction

function CacheIndex indexOf(Addr addr);
	return truncate(addr >> valueOf(TLog#(CacheLineBytes)));
endfunction

function CacheOffset offsetOf(Addr addr);
	return truncate(addr >> 2);
endfunction


function Bit#(4) writeEnDCR (DataCacheReq req);

    Bit#(4) write_en = 0;

    Bit#(2) bytesel = truncate(req.addr) & 2'b11;
    Bit#(2) halfsel = truncate(req.addr) & 2'b10;
    Bit#(2) wordsel = truncate(req.addr) & 2'b00;

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

function Data embedDCR (DataCacheReq req);

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

    return word;

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


function CacheLineNum cacheLineNumReq(LSUReq#(transIdType) r) provisos(Bits#(LSUReq#(transIdType),reqSz));
    Addr a = r.addr;
    CacheLineNum num = truncateLSB(a);
    return num;
endfunction

function CacheLineNum cacheLineNumAddr(Addr a);
    CacheLineNum num = truncateLSB(a);
    return num;
endfunction


module mkNullDataCache (BareDataCache ifc);

	method ActionValue#(Bool) req(DataCacheReq r);
		return True;
	endmethod

    method ActionValue#(DataCacheResp) resp;
    	return (?);
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
    LoadFunc ldFunc;
    Addr     addr;
} BRAMmeta deriving(Eq, Bits, FShow);

module mkDirectDataCache (BareDataCache ifc);

	BRAM_Configure cfg = defaultValue;
	cfg.memorySize   = 0;
	cfg.latency      = 1;
	cfg.outFIFODepth = 1;

	// Use port A for R and port B for W, important in Join (both operations)
	Vector#(CacheLineWords, BRAM2PortBE#(CacheIndex, Data, 4)) bram <- replicateM(mkBRAM2ServerBE(cfg));
	Fifo#(1,BRAMmeta) bramMeta <- mkStageFifo();

	Vector#(LSUCacheRows,Reg#(Bool))     valid <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(Bool))     dirty <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(CacheTag)) tags  <- replicateM(mkReg(0));

	method ActionValue#(Bool) req(DataCacheReq r);

		if (valid[indexOf(r.addr)] && (tags[indexOf(r.addr)] == tagOf(r.addr))) begin // hit

			if(r.op == St || r.op == Join)
				dirty[indexOf(r.addr)] <= True;

			bramMeta.enq(BRAMmeta{ req   : True,
			                       ldFunc: (r.op == Join) ? LW : r.ldFunc,
			                       addr  : r.addr});

			bram[offsetOf(r.addr)].portA.request.put( BRAMRequestBE{ writeen        : '0,
			                                                         responseOnWrite: True,
			                                                         address        : indexOf(r.addr),
			                                                         datain         : ? });
			bram[offsetOf(r.addr)].portB.request.put( BRAMRequestBE{ writeen        : writeEnDCR(r),
			                                                         responseOnWrite: True,
			                                                         address        : indexOf(r.addr),
			                                                         datain         : embedDCR(r) });
			return True;

		end else begin // miss

			return False;

		end

	endmethod

    method ActionValue#(DataCacheResp) resp() if(bramMeta.first().req);

    	LoadFunc        ldFunc     = bramMeta.first.ldFunc;
    	Addr            addr       = bramMeta.first.addr;

		bramMeta.deq();

		Data word <- bram[offsetOf(addr)].portA.response.get;
		             bram[offsetOf(addr)].portB.response.get;

		return extendLoad(word, addr, ldFunc);

    endmethod

    method Action put(DataCacheWB wb);

		CacheTag     tag   = truncateLSB(wb.num);
		CacheIndex   index = truncate(wb.num);

		valid[index] <= True;
		dirty[index] <= False;
		tags [index] <= tag;

		for (Integer i = 0; i < valueOf(CacheLineWords); i=i+1) begin
			bram[i].portB.request.put( BRAMRequestBE{ writeen        : '1,
			                                          responseOnWrite: False,
			                                          address        : index,
			                                          datain         : wb.line[i] });
		end

		if(valid[index] && dirty[index]) begin
			bramMeta.enq(BRAMmeta{ req    : False,
			                       ldFunc : ?,
			                       addr   : {{tags[index],index},'0}});
			for (Integer i = 0; i < valueOf(CacheLineWords); i=i+1) begin
				bram[i].portA.request.put( BRAMRequestBE{ writeen        : '0,
				                                          responseOnWrite: False,
				                                          address        : index,
				                                          datain         : ? });
			end
		end

	endmethod

	method ActionValue#(DataCacheWB) get() if(!bramMeta.first().req);

		CacheLineNum num  = truncateLSB(bramMeta.first().addr); bramMeta.deq();
		CacheLine    line = replicate('0);

		for (Integer i = 0; i < valueOf(CacheLineWords); i=i+1) begin
			line[i] <- bram[i].portA.response.get;
		end

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

typedef Bit#(TLog#(LSUmshrW)) LSUmshrId;

typedef struct{
	transIdType transId;
	Bool        isOld;
	Bool        isHit;
} DataCacheToken#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Addr        addr;
	LSUmshrId   mshr;
} MemReqToken deriving(Eq, Bits, FShow);

module mkLSU (WideMem mem, BareDataCache dataCache, LSU#(transIdType) ifc) provisos(Bits#(transIdType,transIdTypeSz),FShow#(transIdType));

	Vector#(LSUmshrW, Fifo#(LSUmshrD,LSUReq#(transIdType))) mshr      <- replicateM(mkPipelineFifo());
	Ehr#(2,Maybe#(LSUmshrId))                               flushMSHR <- mkEhr(tagged Invalid);

	Fifo#(1, LSUReq#(transIdType))         inReqQ   <- mkBypassFifo();
	Fifo#(1, DataCacheToken#(transIdType)) dcReqQ   <- mkStageFifo();
	Fifo#(LSUmshrW, MemReqToken)           memReqQ  <- mkPipelineFifo();
	Fifo#(1, LSUResp#(transIdType))        respQ    <- mkBypassFifo();
	Fifo#(1, LSUResp#(transIdType))        oldRespQ <- mkBypassFifo();

    Reg#(Data) hLd   <- mkReg(0);
    Reg#(Data) hSt   <- mkReg(0);
    Reg#(Data) hJoin <- mkReg(0);
    Reg#(Data) mLd   <- mkReg(0);
    Reg#(Data) mSt   <- mkReg(0);
    Reg#(Data) mJoin <- mkReg(0);
    Reg#(Data) dLd   <- mkReg(0);
    Reg#(Data) dSt   <- mkReg(0);
    Reg#(Data) dJoin <- mkReg(0);

	rule do_RETRY if(isValid(flushMSHR[0]));

		LSUmshrId mshrId = fromMaybe(?,flushMSHR[0]);

		if(mshr[mshrId].notEmpty()) begin

			let r = mshr[mshrId].first(); mshr[mshrId].deq();
			let hit <- dataCache.req(DataCacheReq{ op    : r.op,
			                                       ldFunc: r.ldFunc,
			                                       stFunc: r.stFunc,
			                                       addr  : r.addr,
			                                       data  : r.data });
			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : True,
			                           isHit  : True });

		end else begin

			flushMSHR[0] <= tagged Invalid;

		end

	endrule

	rule do_WB;

		let r <- dataCache.get();

		mem.req(WideMemReq{ write_en: '1,
		                    addr    : {r.num,0},
		                    data    : r.line });

	endrule

	rule do_MEMRESP if(!isValid(flushMSHR[0]));

		let num  = cacheLineNumAddr(memReqQ.first().addr); memReqQ.deq();
		let line <- mem.resp();
		dataCache.put(DataCacheWB{ num:  num,
		                           line: line });
		flushMSHR[0] <= tagged Valid memReqQ.first().mshr;

	endrule

	rule do_INREQ if(!isValid(flushMSHR[1]));

		LSUReq#(transIdType) r = inReqQ.first();

		// Try data cache
		Bool hit <- dataCache.req(DataCacheReq{ op    : r.op,
		                                        ldFunc: r.ldFunc,
		                                        stFunc: r.stFunc,
		                                        addr  : r.addr,
		                                        data  : r.data });

		// Try matching an older mshr
		Maybe#(LSUmshrId) isMatch = tagged Invalid;
		for (Integer i = 0; i < valueOf(LSUmshrW); i = i+1) begin
			if(mshr[fromInteger(i)].notEmpty() && cacheLineNumReq(mshr[fromInteger(i)].first()) == cacheLineNumReq(r)) begin
				isMatch = tagged Valid fromInteger(i);
			end
		end

		// Try to allocate a new mshr
		Maybe#(LSUmshrId) isEmpty = tagged Invalid;
		for (Integer i = 0; i < valueOf(LSUmshrW); i = i+1) begin
			if(!mshr[fromInteger(i)].notEmpty()) begin
				isEmpty = tagged Valid fromInteger(i);
			end
		end

		if(hit) begin
			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : False,
			                           isHit  : True });
			inReqQ.deq();

		end else if(isValid(isMatch)) begin

			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : False,
			                           isHit  : False });
			inReqQ.deq();

			mshr[fromMaybe(?,isMatch)].enq(r);

		end else if(isValid(isEmpty)) begin

			dcReqQ.enq(DataCacheToken{ transId: r.transId,
			                           isOld  : False,
			                           isHit  : False });
			inReqQ.deq();

			mshr[fromMaybe(?,isEmpty)].enq(r);

			memReqQ.enq(MemReqToken{ addr: r.addr,
			                         mshr: fromMaybe(?,isEmpty) });
			mem.req(WideMemReq{ write_en: '0,
								addr    : r.addr,
								data    : ? });

		end

		if(mem_ext_DEBUG) begin
			if (hit) begin
				case (r.op)
					Ld:   hLd   <= hLd+1;
					St:   hSt   <= hSt+1;
					Join: hJoin <= hJoin+1;
				endcase
			end else if(isValid(isMatch) || isValid(isEmpty)) begin
				case (r.op)
					Ld:   mLd   <= mLd+1;
					St:   mSt   <= mSt+1;
					Join: mJoin <= mJoin+1;
				endcase
			end else begin
				case (r.op)
					Ld:   dLd   <= dLd+1;
					St:   dSt   <= dSt+1;
					Join: dJoin <= dJoin+1;
				endcase
			end
		end

	endrule

	rule do_RESP if(respQ.notFull() && oldRespQ.notFull() || !cmr_ext_DEBUG);
	// If cmr_ext_DEBUG (verification), we must preserve the order

		let r = dcReqQ.first(); dcReqQ.deq();

		if(r.isOld) begin

			let d <- dataCache.resp();
			oldRespQ.enq(LSUResp{ valid  : True,
			                      data   : d,
			                      transId: r.transId });

		end else if(r.isHit) begin

			let d <- dataCache.resp();
			respQ.enq(LSUResp{ valid  : True,
			                   data   : d,
			                   transId: r.transId });

		end else begin

			respQ.enq(LSUResp{ valid  : False,
			                   data   : ?,
			                   transId: r.transId });

		end

	endrule

	method Action req(LSUReq#(transIdType) r);
		inReqQ.enq(r);
	endmethod

	method ActionValue#(LSUResp#(transIdType)) resp;
		respQ.deq();
		return respQ.first();
	endmethod

	method ActionValue#(LSUResp#(transIdType)) oldResp;
		oldRespQ.deq();
		return oldRespQ.first();
	endmethod

	method LSUStat getStat();
		return LSUStat{ hLd      : hLd,
		                hSt      : hSt,
		                hJoin    : hJoin,
		                mLd      : mLd,
		                mSt      : mSt,
		                mJoin    : mJoin,
		                dLd      : dLd,
		                dSt      : dSt,
		                dJoin    : dJoin };
	endmethod

endmodule