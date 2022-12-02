import Ehr::*;
import Vector::*;
import GetPut::*;
import FShow::*;

//////////////////
// MFifo interface
interface MFifoEnqPort#(type t);
    method Bool notFull;
    method Action enq(t x);
endinterface

interface MFifo#(numeric type n, numeric type e, type t);
    interface Vector#(e, MFifoEnqPort#(t)) port;
    method Bool notEmpty;
    method Action deq;
    method t first;
    method Action clear;
endinterface

//////////////////
// Pipeline MFifo 
module mkPipelineMFifo( MFifo#(n, e, t) ) provisos (Bits#(t,tSz), FShow#(t));
    // n is size of fifo
    // t is data type of fifo
    Vector#(n, Ehr#(e,t))            data     <- replicateM(mkEhrU());
    Ehr#(TAdd#(e,1), Bit#(TLog#(n))) enqP     <- mkEhr(0);
    Ehr#(TAdd#(e,1), Bit#(TLog#(n))) ovfP     <- mkEhr(fromInteger(valueOf(e)));
    Ehr#(2         , Bit#(TLog#(n))) deqP     <- mkEhr(0);
    Ehr#(TAdd#(e,2), Bool)           empty    <- mkEhr(True);
    Ehr#(TAdd#(e,2), Bool)           full     <- mkEhr(False);
    Bit#(TLog#(n))                   max_index = fromInteger(valueOf(n)-1);

    Vector#(e, MFifoEnqPort#(t)) eIfcs = newVector;

    for(Integer i = 0; i < valueOf(e); i=i+1) begin
         eIfcs[i] =
            (interface MFifoEnqPort#(t);

                method Bool notFull = !full[1];

                method Action enq(t x) if( !full[1] );
                    data [enqP[i]][i] <= x;
                    empty[i+1]        <= False;
                    enqP [i]          <= (enqP[i] == max_index) ? 0 : enqP[i] + 1;
                    ovfP [i]          <= (ovfP[i] == max_index) ? 0 : ovfP[i] + 1;
                    if( ovfP[i] == deqP[1] ) begin
                        full[i+1] <= True;
                    end
                endmethod

            endinterface);
    end

    interface port = eIfcs;

    method Bool notEmpty = !empty[0];

    method Action deq if( !empty[0] );
        deqP[0] <= (deqP[0] == max_index) ? 0 : deqP[0] + 1;
        if( ovfP[0] == deqP[1] ) begin
            full[0] <= False;
        end
        if( deqP[1] == enqP[0] ) begin
            empty[0] <= True;
        end
    endmethod

    method t first if( !empty[0] );
        return data[deqP[0]][0];
    endmethod

    method Action clear;
        enqP [valueOf(e)] <= 0;
        deqP [1]          <= 0;
        empty[valueOf(e)+1] <= True;
        full [valueOf(e)+1] <= False;
    endmethod

endmodule