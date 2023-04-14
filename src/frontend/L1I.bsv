import Types::*;
import WideMemTypes::*;
import BareInstCache::*;
import FIFOF::*;
import SpecialFIFOs::*;
import GetPut::*;
import ClientServer::*;
import Vector::*;

interface L1I#(numeric type numHart, numeric type cacheRows, numeric type cacheColumns);
    interface WideMemClient#(Bit#(TLog#(numHart))) mem;
    interface Vector#(numHart, WideMemServer#(void)) port;
    `ifdef DEBUG_STATS
    method PerfCnt getNumHit();
    method PerfCnt getNumMiss();
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
    FIFOF#(WideMemReq#(hartID)) memreq <- mkBypassFIFOF();
    FIFOF#(WideMemRes#(hartID)) memres <- mkBypassFIFOF();

    Vector#(numHart, FIFOF#(WideMemRes#(void))) resQ <- replicateM(mkFIFOF());

    //////////// STATS ////////////

    `ifdef DEBUG_STATS
    Reg#(PerfCnt) numHit  <- mkReg(0);
    Reg#(PerfCnt) numMiss <- mkReg(0);
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

        if(res matches tagged Valid .line) // read hit
            resQ[req.transID].enq(WideMemRes{tag: ?, line: line});
        else begin // read miss
            memreq.enq(WideMemReq{ tag  : req.transID,
                                   write: False,
                                   num  : req.num,
                                   line : ? });
            mshrLine[req.transID] <= req.num;
        end

        `ifdef DEBUG_STATS
        if (res matches tagged Valid .line) begin // read hit
            numHit <= numHit+1;
        end else begin // read miss
            numMiss <= numMiss+1;
        end
        `endif

    endrule

    rule do_MEMRESP;

        WideMemRes#(hartID) res = memres.first(); memres.deq();
        CacheLineNum        num = mshrLine[res.tag];

        resQ[res.tag].enq(WideMemRes{tag: ?, line: res.line});

        instCache.req(InstCacheReq{ write: True,
                                    num  : num,
                                    line : res.line });

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
                                          num    : r.num });
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
    method PerfCnt getNumHit();
        return numHit;
    endmethod
    method PerfCnt getNumMiss();
        return numMiss;
    endmethod
    `endif

endmodule