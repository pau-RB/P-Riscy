import Config::*;
import Types::*;
import FIFOF::*;
import SpecialFIFOs::*;
import BRAM::*;
import Vector::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(L1ICacheRows))) CacheTag;
typedef Bit#(TLog#(L1ICacheRows))                                              CacheIndex;
typedef Bit#(TLog#(CacheLineWords))                                            CacheOffset;

typedef struct{
    CacheTag  tag;
    CacheLine line;
} CacheEntry deriving(Eq, Bits, FShow);

typedef struct{
    transIdType  transID;
    CacheLineNum num;
} BramReq#(type transIdType) deriving(Eq, Bits, FShow);

interface L1I#(numeric type n);
    interface Vector#(n, ReadWideMem) port;
    method Data getNumHit();
    method Data getNumMiss();
endinterface

module mkDirectL1I(WideMem mem, L1I#(n) ifc);

    BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
                                          latency                 : 1,
                                          outFIFODepth            : 2,
                                          loadFormat              : None,
                                          allowWriteResponseBypass: False };

    BRAM1Port#(CacheIndex, CacheEntry)  cache   <- mkBRAM1Server(cfg);
    Vector#(L1ICacheRows, Reg#(Bool))   valid   <- replicateM(mkReg(False));

    FIFOF#(BramReq#(Bit#(TLog#(n))))    icReqQ  <- mkFIFOF();
    FIFOF#(BramReq#(Bit#(TLog#(n))))    memReqQ <- mkSizedFIFOF(valueOf(TAdd#(n,1)));
    Vector#(n, FIFOF#(ReadWideMemResp)) respQ   <- replicateM(mkPipelineFIFOF());

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

    rule do_BRAMRESP;

        BramReq#(Bit#(TLog#(n))) req    = icReqQ.first(); icReqQ.deq();
        CacheIndex               index  = truncate   (req.num);
        CacheTag                 tag    = truncateLSB(req.num);
        CacheEntry               entry <- cache.portA.response.get();

        if (valid[index] && (entry.tag == tag)) begin // hit

            respQ[req.transID].enq(entry.line);
            if(mem_ext_DEBUG == True)
                numHit <= numHit+1;

        end else begin // miss

            mem.req(WideMemReq{ write: False,
                                num  : req.num,
                                line : ? });
            memReqQ.enq(BramReq{ transID: req.transID,
                                 num    : req.num });
            if(mem_ext_DEBUG == True)
                numMiss <= numMiss+1;

        end

    endrule

    rule do_MEMRESP;

        BramReq#(Bit#(TLog#(n))) req   = memReqQ.first(); memReqQ.deq();
        CacheIndex               index = truncate   (req.num);
        CacheTag                 tag   = truncateLSB(req.num);
        CacheLine                line <- mem.resp();

        respQ[req.transID].enq(line);

        cache.portA.request.put( BRAMRequest { write          : True,
                                               responseOnWrite: False,
                                               address        : index,
                                               datain         : CacheEntry{tag: tag, line: line }});

        valid[index] <= True;

    endrule

    Vector#(n, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(n); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;

                method Action req(ReadWideMemReq num);
                    cache.portA.request.put( BRAMRequest { write          : False,
                                                           responseOnWrite: False,
                                                           address        : truncate(num),
                                                           datain         : ? });
                    icReqQ.enq(BramReq{ transID: fromInteger(i),
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