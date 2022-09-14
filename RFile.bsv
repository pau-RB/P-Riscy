import Types::*;
import ProcTypes::*;
import Vector::*;
import Ehr::*;
import ConfigReg::*;

interface RFile;

    method Action wrSet( RegSet data );
    method Action wr( RIndx rindx, Data data );
    method RegSet rdSet();
    method Data rd1( RIndx rindx );
    method Data rd2( RIndx rindx );

endinterface

(* synthesize *)
module mkRFile( RFile );
    Vector#(RFSize, Reg#(Data)) rfile <- replicateM(mkReg(0));

    function Data read(RIndx rindx);
        return rfile[rindx];
    endfunction

    method Action wrSet ( RegSet data );
        for(Integer i=0; i < valueOf(RFSize); i=i+1) begin
            rfile[i] <= data[i];
        end
    endmethod

    method Action wr( RIndx rindx, Data data );
        if(rindx!=0) begin
            rfile[rindx] <= data;
        end
    endmethod

    method RegSet rdSet();
        RegSet data;
        for(Integer i=0; i < valueOf(RFSize); i=i+1) begin
            data[i] = rfile[i];
        end
        return data;
    endmethod

    method Data rd1( RIndx rindx ) = read(rindx);
    method Data rd2( RIndx rindx ) = read(rindx);
endmodule