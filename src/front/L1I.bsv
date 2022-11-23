import Config::*;
import Types::*;
import Fifo::*;
import Vector::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(L1ICacheRows))) CacheTag;
typedef Bit#(TLog#(L1ICacheRows)) CacheIndex;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;
typedef Bit#(TLog#(L1ICacheColumns)) CacheBank;

module mkDirectL1I(WideMem mem, ReadWideMem ifc);

    method Action req(ReadWideMemReq r);
        mem.req(WideMemReq{write_en: '0,
                           addr    : r,
                           data    : ? });
    endmethod

    method ActionValue#(ReadWideMemResp) resp;
        let r <- mem.resp();
        return r;
    endmethod

endmodule