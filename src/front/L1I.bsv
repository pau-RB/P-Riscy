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

function CacheLineNum lineNumOf(Addr addr);
    CacheLineNum num = truncateLSB(addr);
    return num;
endfunction

typedef struct{
    CacheTag  tag;
    CacheLine line;
} CacheEntry deriving(Eq, Bits, FShow);

typedef struct{
    transIdType transID;
    Addr        addr;
} BramReq#(type transIdType) deriving(Eq, Bits, FShow);

interface L1I#(numeric type n);
    interface Vector#(n, ReadWideMem) port;
    method Data getNumHit();
    method Data getNumMiss();
endinterface

module mkDirectL1I(WideMem mem, L1I#(n) ifc);

    BRAM_Configure cfg = defaultValue;
    cfg.memorySize = valueOf(L1ICacheRows);
    cfg.latency    = 1;

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
        Addr                     addr     = req.addr;
        CacheTag                 tag      = truncateLSB(addr);
        CacheIndex               index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
        CacheEntry               entry   <- bram.portA.response.get();

        if (valid[index] && (entry.tag == tag)) begin // hit
            respQ[transID].enq(entry.line);

            if(mem_ext_DEBUG == True) begin
                numHit <= numHit+1;    
            end
        end else begin // miss
            mem.req(WideMemReq{ write: False,
                                num  : lineNumOf(addr),
                                line : ? });
            memReqQ.enq(BramReq{ transID: transID,
                                 addr   : addr });

            if(mem_ext_DEBUG == True) begin
                numMiss <= numMiss+1;    
            end
        end

    endrule

    rule do_MEMRESP if(!bramReq.notEmpty());

        BramReq#(Bit#(TLog#(n))) req      = memReqQ.first(); memReqQ.deq();
        Bit#(TLog#(n))           transID  = req.transID;
        Addr                     addr     = req.addr;
        CacheLine                line     <- mem.resp();
        respQ[transID].enq(line);

        CacheTag   tag   = truncateLSB(addr);
        CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));

        bram.portA.request.put( BRAMRequest { write          : True,
                                              responseOnWrite: False,
                                              address        : index,
                                              datain         : CacheEntry{ tag  : tag, line : line } });

        valid[index] <= True;

    endrule

    Vector#(n, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(n); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;

                method Action req(ReadWideMemReq addr) if(!busy[fromInteger(i)][1]);
                    CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
                    bram.portA.request.put( BRAMRequest { write          : False,
                                                          responseOnWrite: False,
                                                          address        : index,
                                                          datain         : ? });

                    bramReq.enq(BramReq{ transID: fromInteger(i),
                                         addr   : addr });
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