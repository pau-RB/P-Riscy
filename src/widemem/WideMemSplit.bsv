import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemSplit#(numeric type n, numeric type m, type tagT);
    interface WideMemClient#(Tuple2#(Bit#(TLog#(n)),tagT)) mem;
    interface Vector#(n, WideMemServer#(tagT)) port;
endinterface

module mkSplitWideMem(WideMemSplit#(n, m, tagT) ifc) provisos(Bits#(tagT, t__), Alias#(srcT,Bit#(TLog#(n))));

    FIFOF#(WideMemReq#(Tuple2#(srcT,tagT))) memreq   <- mkBypassFIFOF();
    FIFOF#(WideMemRes#(Tuple2#(srcT,tagT))) memres   <- mkBypassFIFOF();
    Vector#(n, FIFOF#(WideMemReq#(tagT)))   reqFifos <- replicateM(mkBypassFIFOF);
    Vector#(n, FIFOF#(WideMemRes#(tagT)))   resFifos <- replicateM(mkBypassFIFOF);

    rule doWideMemReq;
        Maybe#(Bit#(TLog#(n))) req_index = tagged Invalid;
        for( Integer i = 0 ; i < valueOf(n) ; i = i+1 )
            if( !isValid(req_index) && reqFifos[i].notEmpty )
                req_index = tagged Valid (fromInteger(i));
        if( req_index matches tagged Valid .src) begin
            let req = reqFifos[ fromMaybe(?,req_index) ].first;
            reqFifos[ fromMaybe(?,req_index) ].deq();
            memreq.enq(WideMemReq{ tag  : tuple2(src,req.tag),
                                   write: req.write    ,
                                   num  : req.num      ,
                                   line : req.line     });
        end
    endrule

    rule doWideMemResp;
        WideMemRes#(Tuple2#(srcT,tagT)) res = memres.first(); memres.deq();
        if(res.tag matches {.src, .tag})
            resFifos[src].enq(WideMemRes{ tag : tag     ,
                                          line: res.line});
    endrule

    Vector#(n, WideMemServer#(tagT)) wideMemIfcs = newVector;
    for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMemServer#(tagT);
                interface request = (interface Put#(WideMemReq#(tagT));
                    method Action put(WideMemReq#(tagT) r);
                        reqFifos[i].enq(r);
                    endmethod
                endinterface);
                interface response = (interface Get#(WidememRes#(tagT));
                    method ActionValue#(WideMemRes#(tagT)) get();
                        let r = resFifos[i].first;
                        resFifos[i].deq;
                        return r;
                    endmethod
                endinterface);
            endinterface);
    end

    interface WideMemClient mem;
        interface request = (interface Get#(WideMemReq#(Tuple2#(srcT,tagT)));
            method ActionValue#(WideMemReq#(Tuple2#(srcT,tagT))) get();
                memreq.deq();
                return memreq.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememRes#(Tuple2#(srcT,tagT)));
            method Action put(WideMemRes#(Tuple2#(srcT,tagT)) r);
                memres.enq(r);
            endmethod
        endinterface);
    endinterface

    interface port = wideMemIfcs;

endmodule