import Ifc::*;
import Core::*; 
import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Memory::*;
import WideMemBRAM::*;
import MemUtil::*;
import Fifo::*;

interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   WideMem mem <- mkWideMemBRAM;
   Core    dut <- mkCore6S(mem);

   rule relayMessage;
	     CommitReport cmr <- dut.getCMR();
        Data iType = zeroExtend(pack(cmr.iType));
        ind.print(cmr.cycle, cmr.pc, iType, cmr.res);
   endrule

   interface FromHost connectProc;

      method Action startPC(Bit#(32) startpc);
        $display("Received software req to start pc\n");
        $fflush(stdout);
        dut.start(startpc);
      endmethod

   endinterface

endmodule
