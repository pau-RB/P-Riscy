import Types::*;
import CMRTypes::*;
import Vector::*;

//////////// BARE DATA CACHE ////////////

typedef enum{PUT,LB,LH,LW,LBU,LHU,SB,SH,SW,JOIN} DataCacheOp deriving(Bits, Eq, FShow);

typedef struct{
    DataCacheOp op;
    Addr		addr;
    Data		data;
    CacheLine   line;
} DataCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(Data) DataCacheResp;

typedef struct {
	CacheLineNum num;
	CacheLine 	 line;
} DataCacheWB deriving(Eq, Bits, FShow);

interface BareDataCache;
    method Action invalidate();
	method Action req(DataCacheReq r);
    method ActionValue#(DataCacheResp) resp();
    method ActionValue#(DataCacheWB) getWB();
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