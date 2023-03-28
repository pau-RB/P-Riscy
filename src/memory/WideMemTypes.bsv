import Types::*;
import ClientServer::*;

typedef struct {
	tagT         tag;
	Bool         write;
	CacheLineNum num;
	CacheLine    line;
} WideMemReq#(type tagT) deriving(Eq,Bits);

typedef struct {
	tagT         tag;
	CacheLine    line;
} WideMemRes#(type tagT) deriving(Eq,Bits);

typedef Server#(WideMemReq#(tagT), WideMemRes#(tagT)) WideMemServer#(type tagT);

typedef Client#(WideMemReq#(tagT), WideMemRes#(tagT)) WideMemClient#(type tagT);