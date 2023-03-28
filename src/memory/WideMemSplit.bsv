import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Vector::*;

interface WideMemSplit#(numeric type n, numeric type m, type tagT);
    interface WideMemClient#(tagT) mem;
    interface Vector#(n, WideMemServer#(tagT)) port;
endinterface

module mkSplitWideMem(WideMemSplit#(n, m, tagT) ifc) provisos(Bits#(tagT, t__));

    FIFOF#(WideMemReq#(tagT))             memreq   <- mkBypassFIFOF();
    FIFOF#(WideMemRes#(tagT))             memres   <- mkBypassFIFOF();
    Vector#(n, FIFOF#(WideMemReq#(tagT))) reqFifos <- replicateM(mkFIFOF);
    Vector#(n, FIFOF#(WideMemRes#(tagT))) resFifos <- replicateM(mkFIFOF);

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

            memreq.enq(req);
            if(!req.write) begin
                // req is a load, so keep track of the source
                reqSource.enq( fromMaybe(?,req_index) );
            end
        end
    endrule

    rule doWideMemResp;
        let res = memres.first(); memres.deq();

        let source = reqSource.first;
        reqSource.deq;

        resFifos[source].enq( res );
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
        interface request = (interface Get#(WideMemReq#(tagT));
            method ActionValue#(WideMemReq#(tagT)) get();
                memreq.deq();
                return memreq.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememRes#(tagT));
            method Action put(WideMemRes#(tagT) r);
                memres.enq(r);
            endmethod
        endinterface);
    endinterface

    interface port = wideMemIfcs;

endmodule