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

   WideMem    mem     <- mkWideMemBRAM;
   Core       dut     <- mkCore6S(mem);
   Reg#(Bool) memInit <- mkReg(False);

   rule relayCMR;
	     CommitReport cmr <- dut.getCMR();
        Data iType = zeroExtend(pack(cmr.iType));
        Data wbDst = zeroExtend(pack(cmr.wbDst));
        ind.printCMR(cmr.cycle, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
   endrule

   rule relayMSG;
        Data msg <- dut.getMSG();
        ind.printMSG(msg);
   endrule

   interface FromHost connectProc;

      method Action setMem (Bit#(32) addr, Bit#(32) word);
         mem.req(toWideMemReq(MemReq{
                     op:   St,
                     addr: addr,
                     data: word,
                     func: SW
                  }));
         if(addr == 'h3fffc) begin
            memInit <= True;
         end
      endmethod

      method Action startPC(Bit#(32) startpc) if(memInit);
        dut.start(startpc);
      endmethod

   endinterface

endmodule
