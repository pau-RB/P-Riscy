import Types::*;
import Vector::*;

//////////// BARE DATA CACHE ////////////

typedef struct{
    MemOp	op;
    Addr	addr;
    Bool	hit;
} BramReq deriving(Eq, Bits, FShow);

typedef struct{
    MemOp		op;
    StoreFunc	func;
    Addr		addr;
    Data		data;
} DataCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(Data) DataCacheResp;

typedef struct {
	CacheLineNum num;
	CacheLine 	 line;
} DataCacheWB deriving(Eq, Bits, FShow);

interface BareDataCache;
	method ActionValue#(Bool) req(DataCacheReq r);
    method ActionValue#(DataCacheResp) resp;
    method Action put(DataCacheWB wb);
    method ActionValue#(DataCacheWB) get();
endinterface

//////////// LSU ////////////

typedef struct{
    MemOp		op;
    StoreFunc	func;
    Addr		addr;
    Data		data;
    transIdType	transId;
} LSUReq#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Bool		valid;
    Data		data;
    transIdType	transId;
} LSUResp#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
    Data		data;
    transIdType	transId;
} LSUOldResp#(type transIdType) deriving(Eq, Bits, FShow);

interface MSHR#(numeric type length, type transIdType);
    method Bool notEmpty();
    method Bool notFull();
    method Bool addrMatch(LSUReq#(transIdType) r);
    method Action enq(LSUReq#(transIdType) r);
    method Action deq();
    method LSUReq#(transIdType) first();
endinterface

interface LSU#(type transIdType);
    method Action req(LSUReq#(transIdType) r);
    method ActionValue#(LSUResp#(transIdType)) resp;
    method ActionValue#(LSUOldResp#(transIdType)) oldResp;
endinterface

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
        case(req.func)
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
        case(req.func)
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