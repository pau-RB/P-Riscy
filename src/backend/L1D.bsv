import Types::*;
import WideMemTypes::*;
import CMRTypes::*;
import CFFifo::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Ehr::*;
import Vector::*;
import BRAM::*;
import BareDataCache::*;

typedef struct{
	MemOp       op;
	LoadFunc    ldFunc;
	StoreFunc   stFunc;
	Addr        addr;
	Data        data;
	transIdType	transId;
} L1DReq#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Bool        valid;
	Data        data;
	transIdType transId;
} L1DResp#(type transIdType) deriving(Eq, Bits, FShow);

interface L1D#(numeric type numHart, numeric type cacheRows, numeric type cacheColumns, numeric type cacheHash);
	interface WideMemClient#(Bit#(TLog#(numHart))) mem;
	method Action req(L1DReq#(Bit#(TLog#(numHart))) r);
	method Action confirm(Bool comm);
	method L1DResp#(Bit#(TLog#(numHart))) getres();
	method L1DResp#(Bit#(TLog#(numHart))) getoldres();
	method Action deqres();
	method Action deqoldres();
	`ifdef DEBUG_STATS
	method LSUStat getStat();
	`endif
endinterface

function CacheLineNum lineNumOf(Addr addr);
	CacheLineNum num = truncateLSB(addr);
	return num;
endfunction

typedef struct{
	L1DReq#(transIdType) req;
	Bool                 isOld;
} DataCacheToken#(type transIdType) deriving(Eq, Bits, FShow);

interface MSHR#(numeric type numHart);
	method Bool isMatch(Addr addr);
	method Action enq(L1DReq#(Bit#(TLog#(numHart))) req);
	method Action deq();
	method L1DReq#(Bit#(TLog#(numHart))) first();
	method Bool isEmpty();
	method Bool isLast();
	method CacheLineNum cacheLineNum();
endinterface

module mkMSHR (MSHR#(numHart)) provisos(Add#(a__, 1, TLog#(numHart)), Alias#(hartID, Bit#(TLog#(numHart))));

	Fifo#(numHart,L1DReq#(hartID)) requests <- mkCFFifo();
	Reg #(CacheLineNum) linenum  <- mkReg(?);
	Reg #(hartID) numreq <- mkReg('0);

	method Bool isMatch(Addr addr);
		return (numreq != '0 && linenum == lineNumOf(addr));
	endmethod

	method Action enq(L1DReq#(hartID) r);
		linenum <= lineNumOf(r.addr);
		requests.enq(r);
		numreq <= numreq+1;
	endmethod

	method Action deq();
		requests.deq();
		numreq <= numreq-1;
	endmethod

	method L1DReq#(hartID) first();
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

module mkL1D (L1D#(numHart, cacheRows, cacheColumns, cacheHash) ifc) provisos(Add#(a__, 1, TLog#(numHart)),
                                                                              Log#(cacheHash, e__),
                                                                              Add#(f__, TLog#(cacheHash), TLog#(cacheRows)),
                                                                              Add#(g__, TLog#(cacheHash), CacheLineNumSz),
                                                                              Alias#(hartID, Bit#(TLog#(numHart))));

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

	FIFOF#(WideMemReq#(hartID)) memreq <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(hartID)) memres <- mkBypassFIFOF();

	BareDataCache#(cacheRows,cacheColumns,cacheHash) dataCache <- mkDirectDataCache();
	Vector#(numHart, MSHR#(numHart))                 mshrArray <- replicateM(mkMSHR());
	Ehr#(2,Maybe#(hartID))                           retryMSHR <- mkEhr(tagged Invalid);

	FIFOF#(L1DReq        #(hartID)) inReqQ   <- mkBypassFIFOF();
	FIFOF#(Bool                   ) confirmQ <- mkFIFOF();
	FIFOF#(DataCacheToken#(hartID)) dcReqQ   <- mkSizedFIFOF(3);
	FIFOF#(WideMemReq#(hartID)    ) missQ    <- mkSizedBypassFIFOF(4);
	FIFOF#(L1DResp       #(hartID)) respQ    <- mkBypassFIFOF();
	FIFOF#(L1DResp       #(hartID)) oldRespQ <- mkFIFOF();

	`ifdef DEBUG_STATS
	Ehr#(2,PerfCnt) hLd   <- mkEhr(0);
	Ehr#(2,PerfCnt) hSt   <- mkEhr(0);
	Ehr#(2,PerfCnt) hJoin <- mkEhr(0);
	Ehr#(2,PerfCnt) mLd   <- mkEhr(0);
	Ehr#(2,PerfCnt) mSt   <- mkEhr(0);
	Ehr#(2,PerfCnt) mJoin <- mkEhr(0);
	Ehr#(2,PerfCnt) dLd   <- mkEhr(0);
	Ehr#(2,PerfCnt) dSt   <- mkEhr(0);
	Ehr#(2,PerfCnt) dJoin <- mkEhr(0);
	`endif

	rule do_INREQ if(!isValid(retryMSHR[0]));

		L1DReq#(hartID) req = inReqQ.first(); inReqQ.deq();

		dataCache.req(DataCacheReq{ op   : cacheOpOf(req.op, req.ldFunc, req.stFunc),
		                            addr : req.addr,
		                            data : req.data,
		                            line : ? ,
		                            isOld: False });
		dcReqQ.enq(DataCacheToken{ req  : req,
		                           isOld: False });

	endrule

	`ifdef CMR_EXT_DEBUG
	rule do_RESP if(respQ.notFull() && oldRespQ.notFull());
	// If cmr_ext_DEBUG (verification), we must preserve the order
	`else
	rule do_RESP;
	`endif

		L1DReq#(hartID) req = dcReqQ.first().req; dcReqQ.deq();
		DataCacheResp d <- dataCache.resp();

		// Try matching an older mshr in case of miss
		Bool   isMatch = False;
		hartID idMatch = '0;

		for (Integer i = 0; i < valueOf(numHart); i = i+1) begin
			Bool mmMatch = mshrArray[fromInteger(i)].isMatch(req.addr);
			isMatch = isMatch || mmMatch;
			idMatch = idMatch  | signExtend(pack(mmMatch))&fromInteger(i);
		end

		if(dcReqQ.first.isOld) begin // Old hit
			oldRespQ.enq(L1DResp{ valid  : True,
			                      data   : fromMaybe(?,d),
			                      transId: req.transId });
		end else begin
			Bool conf = confirmQ.first(); confirmQ.deq();
			if(conf) begin
				if(isValid(d)) begin // Young hit
					respQ.enq(L1DResp{ valid  : True,
					                   data   : fromMaybe(?,d),
					                   transId: req.transId });
				end else if(conf) begin // Young miss
					respQ.enq(L1DResp{ valid  : False,
					                   data   : ?,
					                   transId: req.transId });
					if(isMatch) begin
						mshrArray[idMatch].enq(req);
					end else begin
						mshrArray[req.transId].enq(req);
						missQ.enq(WideMemReq{ tag  : req.transId,
						                      write: False,
						                      num  : lineNumOf(req.addr),
						                      line : ? });
					end
				end
			end
		end

		`ifdef DEBUG_STATS
		if(!dcReqQ.first().isOld && confirmQ.first) begin
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
		`endif

	endrule

	rule do_MEMREQ;

		if(dataCache.hasWB()) begin
			let req = dataCache.getWB(); dataCache.deqWB();
			memreq.enq(WideMemReq{ tag  : ?,
			                       write: True,
			                       num  : req.num,
			                       line : req.line });
		end else if(missQ.notEmpty) begin
			let req = missQ.first(); missQ.deq();
			memreq.enq(req);
		end

	endrule

	rule do_MEMRESP if(!isValid(retryMSHR[1]));

		WideMemRes#(hartID) res = memres.first(); memres.deq();
		dataCache.req(DataCacheReq{ op   : PUT,
		                            addr : {mshrArray[res.tag].cacheLineNum,'0},
		                            data : ?,
		                            line : res.line,
		                            isOld: True});
		hartID mshrId = res.tag;
		if(!mshrArray[mshrId].isEmpty && mshrArray[mshrId].first.op == Ld) begin
			let  req = mshrArray[mshrId].first(); mshrArray[mshrId].deq();
			Data dat = extendLoad( res.line[wordSelectOf(req.addr)],
			                       req.addr,
			                       cacheOpOf(req.op, req.ldFunc, req.stFunc));
			oldRespQ.enq(L1DResp{ valid  : True,
			                      data   : dat,
			                      transId: mshrId });
			if(!mshrArray[mshrId].isLast())
				retryMSHR[1] <= tagged Valid res.tag;
		end else begin
			retryMSHR[1] <= tagged Valid res.tag;
		end

	endrule

	rule do_RETRY if(retryMSHR[1] matches tagged Valid .mshrId);

		let req = mshrArray[mshrId].first(); mshrArray[mshrId].deq();
		dataCache.req(DataCacheReq{ op   : cacheOpOf(req.op, req.ldFunc, req.stFunc),
		                            addr : req.addr,
		                            data : req.data,
		                            line : ?,
		                            isOld: True});
		dcReqQ.enq(DataCacheToken{ req  : req,
		                           isOld: True});

		if(mshrArray[mshrId].isLast())
			retryMSHR[1] <= tagged Invalid;

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

	method Action req(L1DReq#(hartID) r);
		inReqQ.enq(r);
	endmethod

	method Action confirm(Bool comm);
		dataCache.confirm(comm);
		confirmQ.enq(comm);
	endmethod

	method L1DResp#(Bit#(TLog#(numHart))) getres();
		return respQ.first();
	endmethod

	method L1DResp#(Bit#(TLog#(numHart))) getoldres();
		return oldRespQ.first();
	endmethod

	method Action deqres();
		respQ.deq();
	endmethod
	method Action deqoldres();
		oldRespQ.deq();
	endmethod

	`ifdef DEBUG_STATS
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
	`endif

endmodule