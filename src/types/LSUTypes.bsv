import Types::*;
import CMRTypes::*;
import Vector::*;

//////////// BARE DATA CACHE ////////////

typedef struct{
    MemOp		op;
    LoadFunc	ldFunc;
    StoreFunc   stFunc;
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
    LoadFunc    ldFunc;
    StoreFunc   stFunc;
    Addr		addr;
    Data		data;
    transIdType	transId;
} LSUReq#(type transIdType) deriving(Eq, Bits, FShow);

typedef struct{
	Bool		valid;
    Data		data;
    transIdType	transId;
} LSUResp#(type transIdType) deriving(Eq, Bits, FShow);

interface LSU#(type transIdType);
    method Action req(LSUReq#(transIdType) r);
    method ActionValue#(LSUResp#(transIdType)) resp();
    method ActionValue#(LSUResp#(transIdType)) oldResp();
    method LSUStat getStat();
endinterface