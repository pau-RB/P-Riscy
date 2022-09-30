import Types::*;
import MemTypes::*;
import MemUtil::*;
import Fifo::*;
import Vector::*;

module mkSplitWideMem(  Bool initDone, WideMem mem,
                        Vector#(n, WideMem) ifc );

    Vector#(n, Fifo#(2, WideMemReq)) reqFifos <- replicateM(mkCFFifo);
    Fifo#(TAdd#(n,1), Bit#(TLog#(n))) reqSource <- mkCFFifo;
    Vector#(n, Fifo#(2, WideMemResp)) respFifos <- replicateM(mkCFFifo);

    rule doWideMemReq(initDone);
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
            if( req.write_en == 0 ) begin
                // req is a load, so keep track of the source
                reqSource.enq( fromMaybe(?,req_index) );
            end
        end
    endrule

    rule doWideMemResp(initDone);
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
    return wideMemIfcs;
endmodule