import Types::*;
import Vector::*;
import ProcTypes::*;


//////////// LOCAL DATA-BASED MEMORY ////////////

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