import Ifc::*;
import Core::*; 
import VerifMaster::*;
import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Memory::*;
import WideMemBRAM::*;
import MemUtil::*;
import CacheTypes::*;
import Fifo::*;
import Config::*;
import Vector::*;


interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   WideMem                   mem        <- mkWideMemBRAM;
   VerifMaster               verif      <- mkVerifMaster;
   Core                      dut        <- mkCore6S(mem, verif);
   Reg#(Bool)                memInit    <- mkReg(False);
   Fifo#(MTQ_LEN, ContToken) mainTokenQ <- mkBypassFifo();

   rule relayCMR;

	     CommitReport cmr <- dut.getCMR();
        Bit#(8) iType = zeroExtend(pack(cmr.iType));
        Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
        ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);

   endrule

   rule relayMSG;

        Message msg <- dut.getMSG();
        ind.reportMSG(msg.verifID, msg.data);

   endrule

   rule doEvict if((dut.getNumCommit()%100) == 80);

      for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
         dut.evict(fromInteger(i));
      end

   endrule

   rule getContToken;

      let t <- dut.getContToken();
      mainTokenQ.enq(t);

   endrule

   rule putContToken;

      FrontID hart = 0;

      for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
         if(!dut.available(hart)) begin
            hart = hart+1;
         end
      end

      let t = mainTokenQ.first(); mainTokenQ.deq();
      dut.start(hart,t);

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

      method Action startPC(Bit#(32) startpc) if(memInit);

         VerifID verifID <- verif.newVerifID();

         mainTokenQ.enq(ContToken{
                           verifID: verifID,
                           pc     : startpc,
                           rfL    : replicate('0),
                           rfH    : replicate('0)  });

      endmethod

   endinterface

endmodule
