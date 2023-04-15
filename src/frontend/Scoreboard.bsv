import SFifo::*;
import ProcTypes::*;

interface Scoreboard#(numeric type size);
    method Action insert(Maybe#(RIndx) d);
    method Action remove;
    method Bool hasDest1(Maybe#(RIndx) r);
    method Bool hasDest2(Maybe#(RIndx) r);
    method Action clear;
endinterface

function Bool isFound(Maybe#(RIndx) x, Maybe#(RIndx) k);

    if(x matches tagged Valid .xv &&& k matches tagged Valid .kv &&& kv == xv &&& kv != '0) begin
        return True;
    end else begin
        return False;
    end
    
endfunction

// remove < search < insert < clear
module mkPipelineScoreboard(Scoreboard#(size));

    SFifo#(size, Maybe#(RIndx), Maybe#(RIndx)) dest <- mkPipelineSFifo(isFound);

    method Action insert(Maybe#(RIndx) d);
        dest.enq(d);
    endmethod

    method Action remove();
        dest.deq();
    endmethod

    method hasDest1 = dest.search;
    method hasDest2 = dest.search;

    method Action clear;
        dest.clear();
    endmethod

endmodule