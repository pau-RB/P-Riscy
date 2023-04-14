import Types::*;
import FIFOF::*;
import SpecialFIFOs::*;
import BRAM::*;
import Vector::*;

typedef CacheLineNum              CacheTag     #(numeric type cacheRows   );
typedef Bit#(TLog#(cacheRows))    CacheRowIndex#(numeric type cacheRows   );
typedef Bit#(TLog#(cacheColumns)) CacheColIndex#(numeric type cacheColumns);

typedef struct{
    Bool         write;
    CacheLineNum num;
    CacheLine    line;
} InstCacheReq deriving(Eq, Bits, FShow);

typedef Maybe#(CacheLine) InstCacheRes;

interface BareInstCache#(numeric type cacheRows, numeric type cacheColumns);
    method Action invalidate();
    method Action req(InstCacheReq r);
    method ActionValue#(InstCacheRes) resp();
endinterface

module mkDirectInstCache (BareInstCache#(cacheRows, cacheColumns) ifc) provisos(Alias#(cacheTag   ,  CacheTag#(cacheRows)),
                                                                                Alias#(cacheRowIdx,  CacheRowIndex#(cacheRows)));

    function cacheTag tagOf(CacheLineNum num);
        return truncateLSB(num);
    endfunction

    function cacheRowIdx indexOf(CacheLineNum num);
        cacheRowIdx   idx = '0;
        for (Integer i = 0; i < valueOf(TLog#(cacheRows)); i=i+1)
            for (Integer j = i; j < valueOf(CacheLineNumSz); j=j+valueOf(TLog#(cacheRows)))
                idx[i] = idx[i]^num[j];
        return idx;
    endfunction

    //////////// BRAM ////////////

    BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
                                          latency                 : 1,
                                          outFIFODepth            : 2,
                                          loadFormat              : None,
                                          allowWriteResponseBypass: False };

    BRAM1Port#(cacheRowIdx, CacheLine) dataArray <- mkBRAM1Server(cfg);
    BRAM1Port#(cacheRowIdx, cacheTag ) tagsArray <- mkBRAM1Server(cfg);
    BRAM1Port#(cacheRowIdx, Bool     ) metaArray <- mkBRAM1Server(cfg);

    //////////// QUEUES ////////////

    FIFOF#(InstCacheReq) reqQ <- mkBypassFIFOF();
    FIFOF#(InstCacheReq) brmQ <- mkFIFOF();
    FIFOF#(InstCacheRes) resQ <- mkBypassFIFOF();

    Reg#(Maybe#(cacheRowIdx)) invIndex <- mkReg(tagged Valid 0); // Invalidate entries

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
        cacheTag  tag  <- tagsArray.portA.response.get;
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

module mkAssociativeInstCache (BareInstCache#(cacheRows, cacheColumns) ifc) provisos(Alias#(cacheColIdx,  CacheColIndex#(cacheColumns)));

    Vector#(cacheColumns,BareInstCache#(cacheRows,cacheColumns)) lane <- replicateM(mkDirectInstCache());
    Reg#(cacheColIdx) replaceIndex <- mkReg(0);

    //////////// INTERFACE ////////////

    method Action invalidate();
        for (Integer i = 0; i < valueOf(cacheColumns); i=i+1)
            lane[i].invalidate();
    endmethod

    method Action req(InstCacheReq r);
        if(r.write) begin
            lane[replaceIndex].req(r);
            replaceIndex <= replaceIndex+1;
        end else begin
            for(Integer i = 0; i < valueOf(cacheColumns); i=i+1)
                lane[fromInteger(i)].req(r);
        end
    endmethod

    method ActionValue#(InstCacheRes) resp();
        CacheLine res = unpack('0);
        Bool val = False;
        for(Integer i = 0; i < valueOf(cacheColumns); i=i+1) begin
            let partial <- lane[fromInteger(i)].resp();
            res = unpack(pack(res)|pack(fromMaybe(unpack('0),partial)));
            val = val||isValid(partial);
        end
        return (val ? tagged Valid res : tagged Invalid);
    endmethod

endmodule