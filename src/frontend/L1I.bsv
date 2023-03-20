import Config::*;
import Types::*;
import WideMemTypes::*;
import FIFOF::*;
import SpecialFIFOs::*;
import GetPut::*;
import BRAM::*;
import Vector::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(cacheRows))) CacheTag  #(numeric type cacheRows);
typedef Bit#(TLog#(cacheRows))                                              CacheIndex#(numeric type cacheRows);
typedef Bit#(TLog#(CacheLineWords))                                         CacheOffset;

typedef struct{
    CacheTag#(cacheRows) tag;
    CacheLine            line;
} CacheEntry#(numeric type cacheRows) deriving(Eq, Bits, FShow);

typedef struct{
    transIdType  transID;
    CacheLineNum num;
} BramReq#(type transIdType) deriving(Eq, Bits, FShow);

interface L1I#(numeric type numHart, numeric type cacheRows);
    interface Vector#(numHart, WideMem) port;
    method Data getNumHit();
    method Data getNumMiss();
endinterface

module mkDirectL1I(WideMem mem, L1I#(numHart, cacheRows) ifc) provisos(Add#(a__, TLog#(cacheRows), CacheLineNumSz),
                                                                       Alias#(cacheTag, CacheTag#(cacheRows)),
                                                                       Alias#(cacheIdx, CacheIndex#(cacheRows)),
                                                                       Alias#(cacheEnt, CacheEntry#(cacheRows)),
                                                                       Alias#(hartId  , Bit#(TLog#(numHart))),
                                                                       Alias#(bramReq , BramReq#(hartId))  );

    //////////// UTILITIES ////////////

    function cacheTag tagOf(CacheLineNum num);
        return truncateLSB(num);
    endfunction

    function cacheIdx indexOf(CacheLineNum num);
        return truncate(num);
    endfunction

    //////////// BRAM ////////////

    BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
                                          latency                 : 1,
                                          outFIFODepth            : 2,
                                          loadFormat              : None,
                                          allowWriteResponseBypass: False };

    BRAM1Port#(cacheIdx, CacheLine) dataArray <- mkBRAM1Server(cfg);
    BRAM1Port#(cacheIdx, cacheTag ) tagsArray <- mkBRAM1Server(cfg);
    BRAM1Port#(cacheIdx, Bool     ) metaArray <- mkBRAM1Server(cfg);

    //////////// QUEUES ////////////

    FIFOF#(bramReq) reqQ <- mkBypassFIFOF();
    FIFOF#(bramReq) brmQ <- mkFIFOF();
    FIFOF#(bramReq) memQ <- mkSizedFIFOF(valueOf(TAdd#(numHart,1)));

    Vector#(numHart, FIFOF#(WideMemResp)) resQ <- replicateM(mkPipelineFIFOF());

    Reg#(Maybe#(cacheIdx))   invIndex <- mkReg(tagged Valid 0); // Invalidate entries

    //////////// STATS ////////////

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

    //////////// RULES ////////////

    rule do_invalidate if (invIndex matches tagged Valid .index);

        metaArray.portA.request.put( BRAMRequest  { write          : True,
                                                    responseOnWrite: False,
                                                    address        : index,
                                                    datain         : False } );

        if(index < fromInteger(valueOf(TSub#(cacheRows,1)))) begin
            invIndex <= tagged Valid (index+1);
        end else begin
            invIndex <= tagged Invalid;
        end

    endrule

    rule do_REQ if (!isValid(invIndex));

        bramReq req = reqQ.first(); reqQ.deq();
        cacheIdx index = indexOf(req.num);

        brmQ.enq(req);

        dataArray.portA.request.put( BRAMRequest{ write          : False,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : ? } );
        tagsArray.portA.request.put( BRAMRequest{ write          : False,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : ? } );
        metaArray.portA.request.put( BRAMRequest{ write          : False,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : ? } );

    endrule

    rule do_BRAMRESP;

        bramReq req = brmQ.first(); brmQ.deq();

        CacheLine line <- dataArray.portA.response.get;
        cacheTag  tag  <- tagsArray.portA.response.get;
        Bool      meta <- metaArray.portA.response.get;

        cacheIdx index = indexOf(req.num);

        if (meta && (tag == tagOf(req.num))) begin // read hit

            resQ[req.transID].enq(line);

        end else begin // read miss

            mem.request.put(WideMemReq{ write: False,
                                        num  : req.num,
                                        line : ? });
            memQ.enq(req);

        end

        if (mem_ext_DEBUG) begin
            if (meta && (tag == tagOf(req.num))) begin // read hit
                numHit <= numHit+1;
            end else begin // read miss
                numMiss <= numMiss+1;
            end
        end

    endrule

    rule do_MEMRESP;

        bramReq req = memQ.first(); memQ.deq();

        cacheIdx  index = indexOf(req.num);
        CacheLine line <- mem.response.get();

        resQ[req.transID].enq(line);

        dataArray.portA.request.put( BRAMRequest{ write          : True,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : line } );
        tagsArray.portA.request.put( BRAMRequest{ write          : True,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : tagOf(req.num) } );
        metaArray.portA.request.put( BRAMRequest{ write          : True,
                                                  responseOnWrite: False,
                                                  address        : index,
                                                  datain         : True } );

    endrule

    Vector#(numHart, WideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(numHart); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMem;
                interface request = (interface Put#(WideMemReq);
                    method Action put(WideMemReq r);
                        reqQ.enq(BramReq{ transID: fromInteger(i),
                                          num    : r.num });
                    endmethod
                endinterface);
                interface response = (interface Get#(WidememResp);
                    method ActionValue#(CacheLine) get();
                        resQ[fromInteger(i)].deq();
                        return resQ[fromInteger(i)].first();
                    endmethod
                endinterface);
            endinterface);
    end

    interface port = wideMemIfcs;

    method Data getNumHit();
        return numHit;
    endmethod

    method Data getNumMiss();
        return numMiss;
    endmethod

endmodule