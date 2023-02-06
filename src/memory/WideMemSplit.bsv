import Types::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemSplit#(numeric type n, numeric type m);
    interface Vector#(n, WideMem) port;
endinterface

module mkSplitWideMem(  WideMem mem, WideMemSplit#(n, m) ifc );

    Vector#(n, FIFOF#(WideMemReq))  reqFifos  <- replicateM(mkFIFOF);
    Vector#(n, FIFOF#(WideMemResp)) respFifos <- replicateM(mkFIFOF);

    FIFOF#(Bit#(TLog#(n))) reqSource <- mkSizedFIFOF(valueOf(m));

    rule doWideMemReq;
        Maybe#(Bit#(TLog#(n))) req_index = tagged Invalid;
        for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
            if( !isValid(req_index) && reqFifos[i].notEmpty ) begin
                req_index = tagged Valid (fromInteger(i));
            end
        end

        if( isValid(req_index) ) begin
            let req = reqFifos[ fromMaybe(?,req_index) ].first;
            reqFifos[ fromMaybe(?,req_index) ].deq();

            mem.req(req);
            if(!req.write) begin
                // req is a load, so keep track of the source
                reqSource.enq( fromMaybe(?,req_index) );
            end
        end
    endrule

    rule doWideMemResp;
        let resp <- mem.resp;

        let source = reqSource.first;
        reqSource.deq;

        respFifos[source].enq( resp );
    endrule

    Vector#(n, WideMem) wideMemIfcs = newVector;
    for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMem;
                method Action req( WideMemReq x );
                    reqFifos[i].enq(x);
                endmethod
                method ActionValue#(WideMemResp) resp;
                    let x = respFifos[i].first;
                    respFifos[i].deq;
                    return x;
                endmethod
            endinterface);
    end

    interface port = wideMemIfcs;

endmodule