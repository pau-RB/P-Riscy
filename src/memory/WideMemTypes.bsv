import Types::*;
import ClientServer::*;

typedef struct{
    Bool         write;
    CacheLineNum num;
    CacheLine    line;
} WideMemReq deriving(Eq,Bits);

typedef CacheLine    WideMemResp;

typedef Server#(WideMemReq, WideMemResp) WideMem;