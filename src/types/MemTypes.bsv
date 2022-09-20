import Types::*;
import Memory::*;
import Vector::*;


//////////// LOCAL DATA-BASED MEMORY ////////////

typedef enum{Ld, St} MemOp deriving(Eq, Bits, FShow);

typedef struct{
    MemOp op;
    Addr  addr;
    Data  data;
} MemReq deriving(Eq, Bits, FShow);

typedef Data MemResp;

//////////// CACHE WIDEMEM REQUESTS ////////////

typedef 16 CacheLineWords; // to match DDR3 width
typedef TMul#(CacheLineWords, 4) CacheLineBytes;
typedef 8 CacheRows; // small size to improve compile times

typedef Bit#( TSub#(TSub#(TSub#(AddrSz, 2), TLog#(CacheRows)), TLog#(CacheLineWords)) ) CacheTag;
typedef Bit#( TLog#(CacheRows) ) CacheIndex;
typedef Bit#( TLog#(CacheLineWords) ) CacheWordSelect;
typedef Vector#(CacheLineWords, Data) CacheLine;

// Wide memory interface
// This is defined here since it depends on the CacheLine type
typedef struct{
    Bit#(CacheLineWords) write_en;  // Word write enable
    Addr                 addr;
    CacheLine            data;      // Vector#(CacheLineWords, Data)
} WideMemReq deriving(Eq,Bits);

typedef CacheLine WideMemResp;
interface WideMem;
    method Action req(WideMemReq r);
    method ActionValue#(CacheLine) resp;
endinterface

// Interface just like FPGAMemory (except no MemInit)
interface Cache;
    method Action req(MemReq r);
    method ActionValue#(MemResp) resp;
endinterface

