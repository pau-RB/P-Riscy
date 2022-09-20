import Ifc::*;
import Core::*; 
import Types::*;
import MemTypes::*;
import Memory::*;
import MemUtil::*;
import Fifo::*;

interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   Core dut <- mkCore6S(?);

   rule relayMessage;
	     CommitReport cmr <- dut.getCMR();
        ind.print(cmr.pc);
   endrule

   interface FromHost connectProc;

      method Action startPC(Bit#(32) startpc);
        $display("Received software req to start pc\n");
        $fflush(stdout);
        dut.start(startpc);
      endmethod

   endinterface

endmodule
