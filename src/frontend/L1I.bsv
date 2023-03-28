import Config::*;
import Types::*;
import WideMemTypes::*;
import FIFOF::*;
import SpecialFIFOs::*;
import GetPut::*;
import BRAM::*;
import Vector::*;

typedef CacheLineNum                CacheTag   ;
typedef Bit#(TLog#(L1ICacheRows))   CacheIndex ;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

//////////// UTILITIES ////////////

function CacheTag tagOf(CacheLineNum num);
    return truncateLSB(num);
endfunction

function CacheIndex indexOf(CacheLineNum num);
    CacheIndex   idx = '0;
    for (Integer i = 0; i < valueOf(TLog#(L1ICacheRows)); i=i+1)
        for (Integer j = i; j < valueOf(CacheLineNumSz); j=j+valueOf(TLog#(L1ICacheRows)))
            idx[i] = idx[i]^num[j];
    return idx;
endfunction

//////////// BARE DATA CACHE TYPES ////////////

typedef struct{
    Bool         write;
    CacheLineNum num;
    CacheLine    line;
} InstCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(CacheLine) InstCacheRes;

interface BareInstCache;
    method Action invalidate();
    method Action req(InstCacheReq r);
    method ActionValue#(InstCacheRes) resp();
endinterface

//////////// L1I TYPES ////////////

interface L1I#(numeric type numHart, numeric type cacheRows);
    interface WideMemClient#(Bit#(TLog#(numHart))) mem;
    interface Vector#(numHart, WideMemServer#(void)) port;
    method Data getNumHit();
    method Data getNumMiss();
endinterface

//////////// BARE INST CACHE ////////////

typedef struct{
    CacheTag  tag;
    CacheLine line;
} CacheEntry deriving(Eq, Bits, FShow);

module mkDirectInstCache (BareInstCache ifc);

    //////////// BRAM ////////////

    BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
                                          latency                 : 1,
                                          outFIFODepth            : 2,
                                          loadFormat              : None,
                                          allowWriteResponseBypass: False };

    BRAM1Port#(CacheIndex, CacheLine) dataArray <- mkBRAM1Server(cfg);
    BRAM1Port#(CacheIndex, CacheTag ) tagsArray <- mkBRAM1Server(cfg);
    BRAM1Port#(CacheIndex, Bool     ) metaArray <- mkBRAM1Server(cfg);

    //////////// QUEUES ////////////

    FIFOF#(InstCacheReq) reqQ <- mkBypassFIFOF();
    FIFOF#(InstCacheReq) brmQ <- mkFIFOF();
    FIFOF#(InstCacheRes) resQ <- mkBypassFIFOF();

    Reg#(Maybe#(CacheIndex)) invIndex <- mkReg(tagged Valid 0); // Invalidate entries

    //////////// RULES ////////////

    rule do_invalidate if (invIndex matches tagged Valid .index);

        metaArray.portA.request.put( BRAMRequest  { write          : True,
                                                    responseOnWrite: False,
                                                    address        : index,
                                                    datain         : False } );

        if(index < fromInteger(valueOf(TSub#(L1ICacheRows,1)))) begin
            invIndex <= tagged Valid (index+1);
        end else begin
            invIndex <= tagged Invalid;
        end

    endrule

    rule do_REQ if (!isValid(invIndex));

        InstCacheReq req   = reqQ.first(); reqQ.deq();

        if(!req.write)
            brmQ.enq(req);

        dataArray.portA.request.put( BRAMRequest{ write          : req.write,
                                                  responseOnWrite: False,
                                                  address        : indexOf(req.num),
                                                  datain         : req.line } );
        tagsArray.portA.request.put( BRAMRequest{ write          : req.write,
                                                  responseOnWrite: False,
                                                  address        : indexOf(req.num),
                                                  datain         : tagOf(req.num) } );
        metaArray.portA.request.put( BRAMRequest{ write          : req.write,
                                                  responseOnWrite: False,
                                                  address        : indexOf(req.num),
                                                  datain         : True } );

    endrule

    rule do_RES;

        InstCacheReq req = brmQ.first(); brmQ.deq();

        CacheLine line <- dataArray.portA.response.get;
        CacheTag  tag  <- tagsArray.portA.response.get;
        Bool      meta <- metaArray.portA.response.get;

        if (meta && (tag == tagOf(req.num)))
            // read hit
            resQ.enq(tagged Valid line);
        else
            // read miss
            resQ.enq(tagged Invalid);

    endrule

    //////////// INTERFACE ////////////

    method Action invalidate();
        invIndex <= tagged Valid 0;
    endmethod

    method Action req(InstCacheReq r);
        reqQ.enq(r);
    endmethod

    method ActionValue#(InstCacheRes) resp();
        resQ.deq();
        return resQ.first();
    endmethod

endmodule

typedef Bit#(TLog#(L1ICacheColumns)) CacheLane;

module mkAssociativeInstCache (BareInstCache ifc);

    Vector#(L1ICacheColumns,BareInstCache) lane <- replicateM(mkDirectInstCache());
    Reg#(CacheLane) replaceIndex <- mkReg(0);

    //////////// INTERFACE ////////////

    method Action invalidate();
        for (Integer i = 0; i < valueOf(L1ICacheColumns); i=i+1)
            lane[i].invalidate();
    endmethod

    method Action req(InstCacheReq r);
        if(r.write) begin
            lane[replaceIndex].req(r);
            replaceIndex <= replaceIndex+1;
        end else begin
            for(Integer i = 0; i < valueOf(L1ICacheColumns); i=i+1)
                lane[fromInteger(i)].req(r);
        end
    endmethod

    method ActionValue#(InstCacheRes) resp();
        CacheLine res = unpack('0);
        Bool val = False;
        for(Integer i = 0; i < valueOf(L1ICacheColumns); i=i+1) begin
            let partial <- lane[fromInteger(i)].resp();
            res = unpack(pack(res)|pack(fromMaybe(unpack('0),partial)));
            val = val||isValid(partial);
        end
        return (val ? tagged Valid res : tagged Invalid);
    endmethod

endmodule

//////////// L1I ////////////

typedef struct{
    transIdType  transID;
    CacheLineNum num;
} BramReq#(type transIdType) deriving(Eq, Bits, FShow);

module mkDirectL1I(L1I#(numHart, cacheRows) ifc) provisos(Add#(a__, TLog#(cacheRows), CacheLineNumSz),
                                                          Alias#(hartID  , Bit#(TLog#(numHart))),
                                                          Alias#(bramReq , BramReq#(hartID))  );

    BareInstCache instCache <- (l1IAssociative?mkAssociativeInstCache():mkDirectInstCache());

    FIFOF#(bramReq            ) reqQ   <- mkBypassFIFOF();
    FIFOF#(bramReq            ) brmQ   <- mkFIFOF();
    FIFOF#(CacheLineNum       ) memQ   <- mkSizedFIFOF(valueOf(TAdd#(numHart,1)));
    FIFOF#(WideMemReq#(hartID)) memreq <- mkBypassFIFOF();
    FIFOF#(WideMemRes#(hartID)) memres <- mkBypassFIFOF();

    Vector#(numHart, FIFOF#(WideMemRes#(void))) resQ <- replicateM(mkFIFOF());

    //////////// STATS ////////////

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

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
            memQ.enq(req.num);
        end

        if (mem_ext_DEBUG) begin
            if (res matches tagged Valid .line) begin // read hit
                numHit <= numHit+1;
            end else begin // read miss
                numMiss <= numMiss+1;
            end
        end

    endrule

    rule do_MEMRESP;

        CacheLineNum        num = memQ.first(); memQ.deq();
        WideMemRes#(hartID) res = memres.first(); memres.deq();

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

    method Data getNumHit();
        return numHit;
    endmethod

    method Data getNumMiss();
        return numMiss;
    endmethod

endmodule