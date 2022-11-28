import Types::*;
import CMRTypes::*;
import Config::*;
import Stream::*;
import L1I::*;
import ReadWideMemSplit::*;
import Vector::*;

interface Fetch#(numeric type n);
    interface Vector#(n, Stream) stream;
    method FetchStat getStat();
endinterface


module mkFetch(WideMem mem, Bool coreStarted, Fetch#(FrontWidth) ifc );

    L1I#(FrontWidth) l1I <- mkDirectL1I(mem);
    Vector#(FrontWidth, Stream) streamInst;

    for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
        streamInst[i] <- mkStream(l1I.port[i]);
    end

    Reg#(Data) numEmpty <- mkReg(0);

    rule do_EMPTYCNT if(mem_ext_DEBUG == True && coreStarted);

        Bool empty = True;
        for (Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
            if(streamInst[i].currentState() != Empty && streamInst[i].isl0Ihit()) begin
                empty = False;
            end
        end
        if (empty) begin
            numEmpty <= numEmpty+1;
        end

    endrule

    interface stream = streamInst;

    method FetchStat getStat();
        return FetchStat { hit:   l1I.getNumHit(),
                           miss:  l1I.getNumMiss(),
                           empty: numEmpty };
    endmethod

endmodule