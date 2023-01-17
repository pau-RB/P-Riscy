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
	return truncate(addr >> valueOf(TLog#(CacheLineBytes)));
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


typedef struct{
	DataCacheReq req;
	Bool         hit;
} BRAMmeta deriving(Eq, Bits, FShow);

module mkDirectDataCache (BareDataCache ifc);

	BRAM_Configure cfg = defaultValue;
	cfg.memorySize   = 0;
	cfg.latency      = 1;
	cfg.outFIFODepth = 2;

	BRAM1PortBE#(CacheIndex, CacheLine, CacheLineBytes) bram <- mkBRAM1ServerBE(cfg);
	Fifo#(1,BRAMmeta) bramMeta <- mkStageFifo();

	Vector#(LSUCacheRows,Reg#(Bool))     valid <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(Bool))     dirty <- replicateM(mkReg(False));
	Vector#(LSUCacheRows,Reg#(CacheTag)) tags  <- replicateM(mkReg(0));

	Fifo#(1,DataCacheReq) inReqQ <- mkBypassFifo();

	rule do_REQ;

		DataCacheReq req = inReqQ.first();
		CacheIndex index = indexOf(req.addr);

		if(req.op == PUT) begin

			if(valid[index] && dirty[index]) begin // put new line and old is dirty
				valid[index] <= False;
				dirty[index] <= False;
				bramMeta.enq(BRAMmeta { req : DataCacheReq { op  : WB,
				                                             addr: {{tags[index],index},'0},
				                                             data: ?,
				                                             line: ? },
				                        hit : True });
				bram.portA.request.put( BRAMRequestBE{ writeen        : '0,
				                                       responseOnWrite: False,
				                                       address        : index,
				                                       datain         : ? });
			end else begin // put new line and old is clean
				valid[index] <= True;
				dirty[index] <= False;
				tags [index] <= tagOf(req.addr);
				bram.portA.request.put( BRAMRequestBE{ writeen        : '1,
				                                       responseOnWrite: False,
				                                       address        : index,
				                                       datain         : req.line });
				inReqQ.deq();
			end

		end else begin
			if (valid[index] && (tags[index] == tagOf(req.addr))) begin // request hit
				if(req.op == SB ||req.op == SH ||req.op == SW || req.op == JOIN) begin
					dirty[index] <= True;
				end

				bramMeta.enq(BRAMmeta{ req : req,
				                       hit : True });

				bram.portA.request.put( BRAMRequestBE{ writeen        : '0,
				                                       responseOnWrite: False,
				                                       address        : index,
				                                       datain         : ? });
				inReqQ.deq();
			end else begin // request miss
				bramMeta.enq(BRAMmeta{ req: req,
				                       hit: False });
				bram.portA.request.put( BRAMRequestBE{ writeen        : '0,
				                                       responseOnWrite: False,
				                                       address        : index,
				                                       datain         : ? });
				inReqQ.deq();
			end

		end

	endrule

	method Action req(DataCacheReq r);

		inReqQ.enq(r);

	endmethod

    method ActionValue#(DataCacheResp) resp() if(bramMeta.first().req.op!=WB);

    	CacheLine    line <- bram.portA.response.get;
    	DataCacheReq req   = bramMeta.first.req;
    	Bool         hit   = bramMeta.first.hit;
    	bramMeta.deq();

		CacheIndex           index      = indexOf(req.addr);
		CacheWordSelect      wordSelect = wordSelectOf(req.addr);
		Bit#(CacheLineBytes) writeEn    = writeEnOf(req.addr, req.op);
		CacheLine            writeLn    = writeLnOf(req.addr, req.op, req.data);

		if(bramMeta.first.hit) begin
			if(req.op==SB || req.op==SH || req.op==SW || req.op==JOIN) begin
				bram.portA.request.put( BRAMRequestBE{ writeen        : writeEn,
				                                       responseOnWrite: False,
				                                       address        : index,
				                                       datain         : writeLn });
			end
			return tagged Valid extendLoad(line[wordSelect], req.addr, req.op);
		end else begin
			return tagged Invalid;
		end

    endmethod

    method ActionValue#(DataCacheWB) getWB() if(bramMeta.first().req.op==WB);

    	CacheLineNum num   = truncateLSB(bramMeta.first().req.addr);
    	CacheLine    line  <- bram.portA.response.get; bramMeta.deq();

    	return DataCacheWB { num:  num,
    	                     line: line};

    endmethod

endmodule
/*
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
*/
typedef Bit#(TLog#(LSUmshrW)) LSUmshrId;

typedef struct{
	LSUReq#(transIdType) req;
	Bool                 isOld;
} DataCacheToken#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Addr        addr;
	LSUmshrId   mshr;
} MemReqToken deriving(Eq, Bits, FShow);

module mkLSU (WideMem mem, BareDataCache dataCache, LSU#(transIdType) ifc) provisos(Bits#(transIdType,transIdTypeSz),FShow#(transIdType));

	Vector#(LSUmshrW, Fifo#(LSUmshrD,LSUReq#(transIdType))) mshr      <- replicateM(mkCFFifo());
	Ehr#(2,Maybe#(LSUmshrId))                               retryMSHR <- mkEhr(tagged Invalid);

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

	rule do_INREQ if(!isValid(retryMSHR[1]));

		LSUReq#(transIdType) req = inReqQ.first(); inReqQ.deq();

		dataCache.req(DataCacheReq{ op  : cacheOpOf(req.op, req.ldFunc, req.stFunc),
		                            addr: req.addr,
		                            data: req.data,
		                            line: ? });
		dcReqQ.enq(DataCacheToken{ req  : req,
		                           isOld: False });

	endrule

	rule do_RESP if(respQ.notFull() && oldRespQ.notFull() || !cmr_ext_DEBUG);
	// If cmr_ext_DEBUG (verification), we must preserve the order

		LSUReq#(transIdType) req = dcReqQ.first().req; dcReqQ.deq();
		DataCacheResp d <- dataCache.resp();

		// Try matching an older mshr in case of miss
		Maybe#(LSUmshrId) isMatch = tagged Invalid;
		for (Integer i = 0; i < valueOf(LSUmshrW); i = i+1) begin
			if(mshr[fromInteger(i)].notEmpty() && lineNumOf(mshr[fromInteger(i)].first().addr) == lineNumOf(req.addr)) begin
				isMatch = tagged Valid fromInteger(i);
			end
		end

		// Try to allocate a new mshr in case of miss
		Maybe#(LSUmshrId) isEmpty = tagged Invalid;
		for (Integer i = 0; i < valueOf(LSUmshrW); i = i+1) begin
			if(!mshr[fromInteger(i)].notEmpty()) begin
				isEmpty = tagged Valid fromInteger(i);
			end
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

			if(isValid(isMatch)) begin

				mshr[fromMaybe(?,isMatch)].enq(req);

			end else if(isValid(isEmpty)) begin

				mshr[fromMaybe(?,isEmpty)].enq(req);

				memReqQ.enq(MemReqToken{ addr: req.addr,
				                         mshr: fromMaybe(?,isEmpty) });
				mem.req(WideMemReq{ write_en: '0,
									addr    : req.addr,
									data    : ? });

			end

		end

		if(mem_ext_DEBUG) begin
			if (isValid(d)) begin // hit
				case (req.op)
					Ld:   hLd   <= hLd+1;
					St:   hSt   <= hSt+1;
					Join: hJoin <= hJoin+1;
				endcase
			end else if(isValid(isMatch) || isValid(isEmpty)) begin
				case (req.op)
					Ld:   mLd   <= mLd+1;
					St:   mSt   <= mSt+1;
					Join: mJoin <= mJoin+1;
				endcase
			end else begin
				case (req.op)
					Ld:   dLd   <= dLd+1;
					St:   dSt   <= dSt+1;
					Join: dJoin <= dJoin+1;
				endcase
			end
		end

	endrule

	rule do_MEMRESP if(!isValid(retryMSHR[0]));

		let line <- mem.resp(); memReqQ.deq();
		dataCache.req(DataCacheReq{ op  : PUT,
		                            addr: memReqQ.first().addr,
		                            data: ?,
		                            line: line });
		retryMSHR[0] <= tagged Valid memReqQ.first().mshr;

	endrule

	rule do_RETRY if(isValid(retryMSHR[0]));

		LSUmshrId mshrId = fromMaybe(?,retryMSHR[0]);

		if(mshr[mshrId].notEmpty()) begin

			let req = mshr[mshrId].first(); mshr[mshrId].deq();
			dataCache.req(DataCacheReq{ op  : cacheOpOf(req.op, req.ldFunc, req.stFunc),
			                            addr: req.addr,
			                            data: req.data,
			                            line: ? });
			dcReqQ.enq(DataCacheToken{ req  : req,
			                           isOld: True});

		end else begin

			retryMSHR[0] <= tagged Invalid;

		end

	endrule

	rule do_WB;

		let r <- dataCache.getWB();

		mem.req(WideMemReq{ write_en: '1,
		                    addr    : {r.num,0},
		                    data    : r.line });

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