import Types::*;
import Memory::*;
import Vector::*;
import ProcTypes::*;



//////////// LOCAL DATA-BASED MEMORY ////////////

typedef enum{Ld, St}  MemOp  deriving(Eq, Bits, FShow);

typedef struct{
    MemOp     op;
    Addr      addr;
    Data      data;
    StoreFunc func;
} MemReq deriving(Eq, Bits, FShow);

typedef Data MemResp;

interface Cache;
    method Action req(MemReq r);
    method ActionValue#(MemResp) resp;
endinterface


//////////// CACHE WIDEMEM REQUESTS ////////////

typedef 16 CacheLineWords; // to match DDR3 width
typedef TMul#(CacheLineWords, 4) CacheLineBytes;
typedef 8 CacheRows; // small size to improve compile times

typedef Bit#( TSub#(TSub#(TSub#(AddrSz, 2), TLog#(CacheRows)), TLog#(CacheLineWords)) ) CacheTag;
typedef Bit#( TLog#(CacheRows) ) CacheIndex;
typedef Bit#( TLog#(CacheLineBytes) ) CacheByteSelect;
typedef Bit#( TLog#(CacheLineWords) ) CacheWordSelect;
typedef Vector#(CacheLineWords, Data) CacheLine;

typedef struct{
    CacheTag  tag;
    CacheLine data;
} CacheEntry deriving(Eq,Bits);

typedef struct{
    Bit#(CacheLineBytes) write_en;  // Byte write enable
    Addr                 addr;
    CacheLine            data;      // Vector#(CacheLineWords, Data)
} WideMemReq deriving(Eq,Bits);

typedef CacheLine WideMemResp;

interface WideMem;
    method Action req(WideMemReq r);
    method ActionValue#(CacheLine) resp;
endinterface


//////////// BRAM ////////////

typedef 12 WMBAddrSz;
typedef Bit#(WMBAddrSz) WMBAddr;