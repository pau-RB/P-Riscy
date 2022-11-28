import Config::*;
import Types::*;
import Fifo::*;
import BRAMCore::*;
import Vector::*;

typedef Bit#(TSub#(TSub#(AddrSz, TLog#(CacheLineBytes)), TLog#(L1ICacheRows))) CacheTag;
typedef Bit#(TLog#(L1ICacheRows)) CacheIndex;
typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

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

    BRAM_PORT#(CacheIndex, CacheEntry) bram <- mkBRAMCore1(valueOf(L1ICacheRows), False);
    Vector#(L1ICacheRows, Reg#(Bool)) valid <- replicateM(mkReg(False));


    Fifo#(1         , BramReq#(Bit#(TLog#(n)))) bramReq <- mkStageFifo();
    Fifo#(TAdd#(n,1), BramReq#(Bit#(TLog#(n)))) memReqQ <- mkPipelineFifo();

    Vector#(n, Fifo#(1,ReadWideMemResp)) respQ <- replicateM(mkPipelineFifo());
    Vector#(n, Reg#(Bool)) busy <- replicateM(mkReg(False));

    Reg#(Data) numHit  <- mkReg(0);
    Reg#(Data) numMiss <- mkReg(0);

    rule do_BRAMRESP;

        BramReq#(Bit#(TLog#(n))) req      = bramReq.first(); bramReq.deq();
        Bit#(TLog#(n))           transID  = req.transID;
        Addr                     addr     = req.addr;
        CacheTag                 tag      = truncateLSB(addr);
        CacheIndex               index    = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
        CacheEntry               entry    = bram.read();

        if (valid[index] && (entry.tag == tag)) begin // hit
            respQ[transID].enq(entry.line);

            if(mem_ext_DEBUG == True) begin
                numHit <= numHit+1;    
            end
        end else begin // miss
            mem.req(WideMemReq{ write_en: '0,
                                addr    : addr,
                                data    : ? });
            memReqQ.enq(BramReq{ transID: transID,
                                 addr   : addr });

            if(mem_ext_DEBUG == True) begin
                numMiss <= numMiss+1;    
            end
        end

    endrule

    rule do_MEMRESP;

        BramReq#(Bit#(TLog#(n))) req      = memReqQ.first(); memReqQ.deq();
        Bit#(TLog#(n))           transID  = req.transID;
        Addr                     addr     = req.addr;
        CacheLine                line     <- mem.resp();
        respQ[transID].enq(line);

        CacheTag   tag   = truncateLSB(addr);
        CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
        bram.put(True, index, CacheEntry{ tag  : tag,
                                          line : line });
        valid[index] <= True;

    endrule

    Vector#(n, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0; i < valueOf(n); i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;

                method Action req(ReadWideMemReq addr) if(!busy[fromInteger(i)]);
                    CacheIndex index = truncate(addr >> valueOf(TLog#(CacheLineBytes)));
                    bram.put(False, index, ?);
                    bramReq.enq(BramReq{ transID: fromInteger(i),
                                         addr   : addr });
                    busy[fromInteger(i)] <= True;
                endmethod

                method ActionValue#(ReadWideMemResp) resp;
                    respQ[fromInteger(i)].deq();
                    busy[fromInteger(i)] <= False;
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