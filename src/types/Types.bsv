import Vector::*;

typedef 32 AddrSz;
typedef Bit#(AddrSz) Addr;

typedef 32 DataSz;
typedef Bit#(DataSz) Data;

typedef 32 InstSz;
typedef Bit#(InstSz) Instruction;

typedef 16                                        CacheLineWords;
typedef TMul#(CacheLineWords, 4)                  CacheLineBytes;
typedef Bit#( TLog#(CacheLineBytes) )             CacheByteSelect;
typedef Bit#( TLog#(CacheLineWords) )             CacheWordSelect;
typedef Bit#(TSub#(AddrSz,TLog#(CacheLineBytes))) CacheLineNum;
typedef Vector#(CacheLineWords, Data)             CacheLine;

typedef enum{Ld, St, Join} MemOp deriving(Eq, Bits, FShow);
typedef enum {SB, SH, SW} StoreFunc deriving(Bits, Eq, FShow);

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