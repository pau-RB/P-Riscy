import Vector::*;

typedef 32 AddrSz;
typedef Bit#(AddrSz) Addr;

typedef 32 DataSz;
typedef Bit#(DataSz) Data;
typedef Bit#(TAdd#(DataSz,DataSz)) Long;

typedef 32 InstSz;
typedef Bit#(InstSz) Instruction;

typedef Bit#(2) Epoch;

typedef 16                                        CacheLineWords;
typedef TMul#(CacheLineWords, 4)                  CacheLineBytes;
typedef Bit#( TLog#(CacheLineBytes) )             CacheByteSelect;
typedef Bit#( TLog#(CacheLineWords) )             CacheWordSelect;

typedef TSub#(AddrSz,TLog#(CacheLineBytes))       CacheLineNumSz;
typedef Bit#(CacheLineNumSz)                      CacheLineNum;
typedef Vector#(CacheLineWords, Data)             CacheLine;

typedef enum{Ld, St, Join} MemOp deriving(Eq, Bits, FShow);
typedef enum{SB,SH,SW} StoreFunc deriving(Bits, Eq, FShow);
typedef enum{LB,LH,LW,LBU,LHU} LoadFunc deriving(Bits, Eq, FShow);

typedef struct{
    Bool         write;
    CacheLineNum num;
    CacheLine    line;
} WideMemReq deriving(Eq,Bits);

typedef CacheLine    WideMemResp;
typedef CacheLineNum ReadWideMemReq;
typedef CacheLine    ReadWideMemResp;

interface WideMem;
    method Action req(WideMemReq r);
    method ActionValue#(WideMemResp) resp;
endinterface

interface ReadWideMem;
    method Action req(ReadWideMemReq r);
    method ActionValue#(ReadWideMemResp) resp;
endinterface

//////////// BRAM ////////////

typedef 12 WMBAddrSz;
typedef Bit#(WMBAddrSz) WMBAddr;