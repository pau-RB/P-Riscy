import Ifc::*;
import Core::*; 
import Types::*;
import MemTypes::*;
import Memory::*;
import MemUtil::*;
import SimMem::*;
import Fifo::*;
import ClientServer::*;
import GetPut::*;

interface ConnectalWrapper;
   interface FromHost connectProc;
   interface ConnectalMemoryInitialization initProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   let debug = True;
   
   Reg#(Bool) memDone <- mkReg(False);  

   Fifo#(2, DDR3_Req)  ddr3ReqFifo <- mkCFFifo();
   Fifo#(2, DDR3_Resp) ddr3RespFifo <- mkCFFifo();

   DDR3_Client ddrclient = toGPClient( ddr3ReqFifo, ddr3RespFifo );
   mkSimMem(ddrclient);

   Core dut <- mkCore6S(ddr3ReqFifo,ddr3RespFifo);

   rule relayMessage;
	     CommitReport cmr <- dut.getCMR();
        ind.print(cmr.pc);
   endrule

   interface FromHost connectProc;

      method Action startPC(Bit#(32) startpc) if (memDone);
        $display("Received software req to start pc\n");
        $fflush(stdout);
        dut.start(startpc);
      endmethod

   endinterface

   interface ConnectalMemoryInitialization initProc;

      method Action done();
         $display("Done memory initialization");
         memDone <= True;
      endmethod

   endinterface

endmodule
