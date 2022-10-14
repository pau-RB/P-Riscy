import Ifc::*;
import Core::*; 
import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Memory::*;
import WideMemBRAM::*;
import MemUtil::*;
import Fifo::*;
import Config::*;

interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   WideMem    mem     <- mkWideMemBRAM;
   Core       dut     <- mkCore6S(mem);
   Reg#(Bool) memInit <- mkReg(False);

   rule relayCMR;

	     CommitReport cmr <- dut.getCMR();
        Bit#(8) feID  = zeroExtend(pack(cmr.feID));
        Bit#(8) iType = zeroExtend(pack(cmr.iType));
        Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
        ind.reportCMR(cmr.cycle, feID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);

   endrule

   rule relayMSG;

        Data msg <- dut.getMSG();
        ind.reportMSG(msg);

   endrule

   interface FromHost connectProc;

      method Action setMem (Bit#(32) addr, Bit#(32) word);

         mem.req(toWideMemReq(MemReq{
                     op:   St,
                     addr: addr,
                     data: word,
                     func: SW
                  }));

         if(addr == max_ADDR) begin
            memInit <= True;
         end

      endmethod

      method Action startPC(Bit#(8) feID, Bit#(32) startpc) if(memInit);

         dut.start(truncate(feID), startpc);

      endmethod

   endinterface

endmodule
