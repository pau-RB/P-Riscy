import Types::*;
import Config::*;
import Stream::*;
import WideMemSplit::*;
import Vector::*;

module mkFetch(WideMem mem, Vector#(FrontWidth, Stream) ifc );

    Vector#(FrontWidth, WideMem) instSplit <- mkSplitWideMem(True, mem);
    Vector#(FrontWidth, Stream) stream;

    for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
        stream[i] <- mkStream(instSplit[i]);
    end

    return stream;

endmodule