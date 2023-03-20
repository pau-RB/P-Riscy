import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
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

            mem.request.put(req);
            if(!req.write) begin
                // req is a load, so keep track of the source
                reqSource.enq( fromMaybe(?,req_index) );
            end
        end
    endrule

    rule doWideMemResp;
        let resp <- mem.response.get();

        let source = reqSource.first;
        reqSource.deq;

        respFifos[source].enq( resp );
    endrule

    Vector#(n, WideMem) wideMemIfcs = newVector;
    for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMem;
                interface request = (interface Put#(WideMemReq);
                    method Action put(WideMemReq r);
                        reqFifos[i].enq(r);
                    endmethod
                endinterface);
                interface response = (interface Get#(WidememResp);
                    method ActionValue#(CacheLine) get();
                        let r = respFifos[i].first;
                        respFifos[i].deq;
                        return r;
                    endmethod
                endinterface);
            endinterface);
    end

    interface port = wideMemIfcs;

endmodule