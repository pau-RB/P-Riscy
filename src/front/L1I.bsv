import Config::*;
import Types::*;
import FIFOF::*;
import SpecialFIFOs::*;
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
    interface Vector#(numHart, ReadWideMem) port;
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

    //////////// QUEUES ////////////

    BRAM1Port#(cacheIdx, cacheEnt) cache <- mkBRAM1Server(cfg);
    Vector#(cacheRows, Reg#(Bool)) valid <- replicateM(mkReg(False));

    FIFOF#(bramReq) brmQ <- mkFIFOF();
    FIFOF#(bramReq) memQ <- mkSizedFIFOF(valueOf(TAdd#(numHart,1)));

    Vector#(numHart, FIFOF#(ReadWideMemResp)) respQ   <- replicateM(mkPipelineFIFOF());

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

    //////////// RULES ////////////

    rule do_BRAMRESP;

        bramReq  req    = brmQ.first(); brmQ.deq();
        cacheIdx index  = indexOf(req.num);
        cacheTag tag    = tagOf(req.num);
        cacheEnt entry <- cache.portA.response.get();

        if (valid[index] && (entry.tag == tag)) begin // hit

            respQ[req.transID].enq(entry.line);
            if(mem_ext_DEBUG == True)
                numHit <= numHit+1;

        end else begin // miss

            mem.req(WideMemReq{ write: False,
                                num  : req.num,
                                line : ? });
            memQ.enq(BramReq{ transID: req.transID,
                              num    : req.num });
            if(mem_ext_DEBUG == True)
                numMiss <= numMiss+1;

        end

    endrule

    rule do_MEMRESP;

        bramReq    req   = memQ.first(); memQ.deq();
        cacheIdx   index = indexOf(req.num);
        cacheTag   tag   = tagOf(req.num);
        CacheLine  line <- mem.resp();

        respQ[req.transID].enq(line);

        cache.portA.request.put( BRAMRequest { write          : True,
                                               responseOnWrite: False,
                                               address        : index,
                                               datain         : CacheEntry{tag: tag, line: line }});

        valid[index] <= True;

    endrule

    Vector#(numHart, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(numHart); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;

                method Action req(ReadWideMemReq num);
                    cache.portA.request.put( BRAMRequest { write          : False,
                                                           responseOnWrite: False,
                                                           address        : indexOf(num),
                                                           datain         : ? });
                    brmQ.enq(BramReq{ transID: fromInteger(i),
                                      num    : num });
                endmethod

                method ActionValue#(ReadWideMemResp) resp;
                    respQ[fromInteger(i)].deq();
                    return respQ[fromInteger(i)].first();
                endmethod

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