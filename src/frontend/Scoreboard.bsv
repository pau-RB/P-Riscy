import SFifo::*;
import ProcTypes::*;

interface Scoreboard#(numeric type size);
    method Action insert(Maybe#(RIndx) d, Bool s);
    method Action remove;
    method Bool hasDest1(Maybe#(RIndx) r);
    method Bool hasDest2(Maybe#(RIndx) r);
    method Bool hasSpec();
    method Action clear;
endinterface

function Bool isFound(Maybe#(RIndx) x, Maybe#(RIndx) k);

    if(x matches tagged Valid .xv &&& k matches tagged Valid .kv &&& kv == xv &&& kv != '0) begin
        return True;
    end else begin
        return False;
    end
    
endfunction

function Bool isSpec(Bool x, void k);

    return x;
    
endfunction


// remove < search < insert < clear
module mkPipelineScoreboard(Scoreboard#(size));

    SFifo#(size, Maybe#(RIndx), Maybe#(RIndx)) dest <- mkPipelineSFifo(isFound);
    SFifo#(size, Bool         , void         ) spec <- mkPipelineSFifo(isSpec);

    method Action insert(Maybe#(RIndx) d, Bool s);
        dest.enq(d);
        spec.enq(s);
    endmethod

    method Action remove();
        dest.deq();
        spec.deq();
    endmethod

    method hasDest1 = dest.search;
    method hasDest2 = dest.search;

    method Bool hasSpec;
        return spec.search(?);
    endmethod

    method Action clear;
        dest.clear();
        spec.clear();
    endmethod

endmodule