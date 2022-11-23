import Types::*;
import Config::*;
import Stream::*;
import L1I::*;
import ReadWideMemSplit::*;
import Vector::*;

module mkFetch(WideMem mem, Vector#(FrontWidth, Stream) ifc );

    Vector#(FrontWidth, ReadWideMem) l1I <- mkDirectL1I(mem);
    Vector#(FrontWidth, Stream) stream;

    for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) begin
        stream[i] <- mkStream(l1I[i]);
    end

    return stream;

endmodule