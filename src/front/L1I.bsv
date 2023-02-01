import Config::*;
import Types::*;
import Ehr::*;
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

    BRAM1Port#(CacheIndex, CacheEntry) bram <- mkBRAM1Server(cfg);
    Vector#(L1ICacheRows, Reg#(Bool)) valid <- replicateM(mkReg(False));

    FIFOF#(BramReq#(Bit#(TLog#(n)))) bramReq <- mkPipelineFIFOF();
    FIFOF#(BramReq#(Bit#(TLog#(n)))) memReqQ <- mkSizedFIFOF(valueOf(TAdd#(n,1)));

    Vector#(n, FIFOF#(ReadWideMemResp)) respQ <- replicateM(mkPipelineFIFOF());
    Vector#(n, Ehr#(2,Bool)) busy <- replicateM(mkEhr(False));

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

    rule do_BRAMRESP;

        BramReq#(Bit#(TLog#(n))) req      = bramReq.first(); bramReq.deq();
        Bit#(TLog#(n))           transID  = req.transID;
        CacheLineNum             num      = req.num;
        CacheIndex               index    = truncate(num);
        CacheTag                 tag      = truncateLSB(num);
        CacheEntry               entry   <- bram.portA.response.get();

        if (valid[index] && (entry.tag == tag)) begin // hit
            respQ[transID].enq(entry.line);
            if(mem_ext_DEBUG == True) begin
                numHit <= numHit+1;    
            end
        end else begin // miss
            mem.req(WideMemReq{ write: False,
                                num  : num,
                                line : ? });
            memReqQ.enq(BramReq{ transID: transID,
                                 num    : num });

            if(mem_ext_DEBUG == True) begin
                numMiss <= numMiss+1;    
            end
        end

    endrule

    rule do_MEMRESP if(!bramReq.notEmpty());

        BramReq#(Bit#(TLog#(n))) req      = memReqQ.first(); memReqQ.deq();
        Bit#(TLog#(n))           transID  = req.transID;
        CacheLineNum             num      = req.num;
        CacheIndex               index    = truncate(num);
        CacheTag                 tag      = truncateLSB(num);
        CacheLine                line     <- mem.resp();
        respQ[transID].enq(line);

        bram.portA.request.put( BRAMRequest { write          : True,
                                              responseOnWrite: False,
                                              address        : index,
                                              datain         : CacheEntry{tag: tag, line: line }});

        valid[index] <= True;

    endrule

    Vector#(n, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(n); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;

                method Action req(ReadWideMemReq num) if(!busy[fromInteger(i)][1]);
                    bram.portA.request.put( BRAMRequest { write          : False,
                                                          responseOnWrite: False,
                                                          address        : truncate(num),
                                                          datain         : ? });
                    bramReq.enq(BramReq{ transID: fromInteger(i),
                                         num    : num });
                    busy[fromInteger(i)][1] <= True;
                endmethod

                method ActionValue#(ReadWideMemResp) resp;
                    respQ[fromInteger(i)].deq();
                    busy[fromInteger(i)][0] <= False;
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