import Types::*;
import WideMemTypes::*;
import BareInstCache::*;
import FIFOF::*;
import SpecialFIFOs::*;
import GetPut::*;
import ClientServer::*;
import Vector::*;
import CMRTypes::*;

interface L1I#(numeric type numHart, numeric type cacheRows, numeric type cacheColumns);
    interface WideMemClient#(Bit#(TLog#(numHart))) mem;
    interface Vector#(numHart, WideMemServer#(void)) port;
    `ifdef DEBUG_STATS
    method L1IStat getStat();
    `endif
endinterface

typedef struct{
    transIdType  transID;
    CacheLineNum num;
} BramReq#(type transIdType) deriving(Eq, Bits, FShow);

module mkL1I(L1I#(numHart, cacheRows, cacheColumns) ifc) provisos(Add#(a__, TLog#(cacheRows), CacheLineNumSz),
                                                                  Alias#(hartID  , Bit#(TLog#(numHart))),
                                                                  Alias#(bramReq , BramReq#(hartID))  );

    BareInstCache#(cacheRows,cacheColumns) instCache <- ((valueOf(cacheColumns)==1)?mkDirectInstCache():mkAssociativeInstCache());
    Vector#(numHart, Reg#(CacheLineNum)) mshrLine <- replicateM(mkReg(?));

    FIFOF#(bramReq            ) reqQ   <- mkBypassFIFOF();
    FIFOF#(bramReq            ) brmQ   <- mkSizedFIFOF(3);
    FIFOF#(WideMemReq#(hartID)) memreq <- mkFIFOF();
    FIFOF#(WideMemRes#(hartID)) memres <- mkFIFOF();

    Vector#(numHart, FIFOF#(WideMemRes#(void))) resQ <- replicateM(mkFIFOF());

    //////////// STATS ////////////

    `ifdef DEBUG_STATS
    Reg#(PerfCnt) hRD <- mkReg(0);
    Reg#(PerfCnt) mRD <- mkReg(0);
    `endif

    //////////// RULES ////////////

    rule do_REQ;

        bramReq req = reqQ.first(); reqQ.deq();

        instCache.req(InstCacheReq{ write: False  ,
                                    num  : req.num,
                                    line : ?      });

        brmQ.enq(req);

    endrule

    rule do_BRAMRES;

        bramReq      req =  brmQ.first(); brmQ.deq();
        InstCacheRes res <- instCache.resp();

        if(res matches tagged Valid .data) // read hit
            resQ[req.transID].enq(WideMemRes{tag: ?, data: data});
        else begin // read miss
            memreq.enq(WideMemReq{ tag        : req.transID,
                                   write      : False      ,
                                   addr       : req.num    ,
                                   data       : ?          ,
                                   byte_enable: '0         });
            mshrLine[req.transID] <= req.num;
        end

        `ifdef DEBUG_STATS
        if (res matches tagged Valid .data)
            hRD <= hRD+1;
        else
            mRD <= mRD+1;
        `endif

    endrule

    rule do_MEMRESP;

        WideMemRes#(hartID) res = memres.first(); memres.deq();
        CacheLineNum        num = mshrLine[res.tag];

        resQ[res.tag].enq(WideMemRes{tag: ?, data: res.data});

        instCache.req(InstCacheReq{ write: True,
                                    num  : num,
                                    line : res.data });

    endrule

    //////////// INTERFACE ////////////

    // IPORTS
    Vector#(numHart, WideMemServer#(void)) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(numHart); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMemServer;
                interface request = (interface Put#(WideMemReq#(void));
                    method Action put(WideMemReq#(void) r);
                        reqQ.enq(BramReq{ transID: fromInteger(i),
                                          num    : r.addr });
                    endmethod
                endinterface);
                interface response = (interface Get#(WidememRes#(void));
                    method ActionValue#(WideMemRes#(void)) get();
                        resQ[fromInteger(i)].deq();
                        return resQ[fromInteger(i)].first();
                    endmethod
                endinterface);
            endinterface);
    end

    // IMEM
    interface WideMemClient mem;
        interface request = (interface Get#(WideMemReq#(hartID));
            method ActionValue#(WideMemReq#(hartID)) get();
                memreq.deq();
                return memreq.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememRes#(hartID));
            method Action put(WideMemRes#(hartID) r);
                memres.enq(r);
            endmethod
        endinterface);
    endinterface

    interface port = wideMemIfcs;

    `ifdef DEBUG_STATS
    method L1IStat getStat();
        return L1IStat{ hRD: hRD,
                        mRD: mRD};
    endmethod
    `endif

endmodule