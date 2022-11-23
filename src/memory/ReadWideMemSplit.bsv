import Types::*;
import Fifo::*;
import Vector::*;

module mkSplitReadWideMem(  Bool initDone, ReadWideMem mem,
                        Vector#(n, ReadWideMem) ifc );

    Vector#(n, Fifo#(2, ReadWideMemReq)) reqFifos <- replicateM(mkCFFifo);
    Fifo#(TAdd#(n,1), Bit#(TLog#(n))) reqSource <- mkCFFifo;
    Vector#(n, Fifo#(2, ReadWideMemResp)) respFifos <- replicateM(mkCFFifo);

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
            reqSource.enq( fromMaybe(?,req_index) );
        end
    endrule

    rule doWideMemResp(initDone);
        let resp <- mem.resp;

        let source = reqSource.first;
        reqSource.deq;

        respFifos[source].enq( resp );
    endrule

    Vector#(n, ReadWideMem) wideMemIfcs = newVector;
    for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
        wideMemIfcs[i] =
            (interface ReadWideMem;
                method Action req( ReadWideMemReq x );
                    reqFifos[i].enq(x);
                endmethod
                method ActionValue#(ReadWideMemResp) resp;
                    let x = respFifos[i].first;
                    respFifos[i].deq;
                    return x;
                endmethod
            endinterface);
    end
    return wideMemIfcs;
endmodule