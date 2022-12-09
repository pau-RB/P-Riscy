import Ifc::*;
import Core::*; 
import VerifMaster::*;
import Types::*;
import ProcTypes::*;
import CMRTypes::*;
import Memory::*;
import WideMemBRAM::*;
import WideMemSplit::*;
import WideMemDelay::*;
import Fifo::*;
import Config::*;
import Vector::*;

function WideMemReq toWideMemReq(Addr addr, Data data);

    CacheByteSelect wordsel = truncate(addr & 32'hfffffffc);
    Bit#(CacheLineBytes) writeEn = 'b1111 << wordsel;
    CacheLine writeLn = replicate(data);

    return WideMemReq { write_en: writeEn,
                        addr: addr,
                        data: writeLn };

endfunction

interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);

   WideMem                                       mainBRAM     <- mkWideMemBRAM();
   DelayedWideMem#(TSub#(RAMLatency,2))          mainMem      <- mkWideMemDelay(mainBRAM);
   SplitWideMem#(FrontWidth,TMul#(2,FrontWidth)) mainSplit    <- mkSplitWideMem(True, mainMem.delayed);

   VerifMaster                                   verif        <- mkVerifMaster();
   Core                                          dut          <- mkCore6S(mainSplit.port[0], mainSplit.port[1], verif);

   Reg#(Bool)                                    memInit      <- mkReg(False);
   Fifo#(MTQ_LEN, ContToken)                     mainTokenQ   <- mkCFFifo();
   Reg#(Data)                                    commitTarget <- mkReg(80);
   Reg#(FrontID)                                 evictTarget  <- mkReg(0);

   rule relayCMR;

	     CommitReport cmr <- dut.getCMR();
        Bit#(8) iType = zeroExtend(pack(cmr.iType));
        Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
        ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);

   endrule

   rule relayMSG;

        Message msg <- dut.getMSG();
        ind.reportMSG(msg.verifID, msg.cycle, msg.commit, msg.data);

   endrule

   rule relayMSR;

         MemStat msr <- dut.getMSR();
         ind.reportMSR(msr.verifID, msr.cycle, msr.commit, msr.data,
                       msr.fetch.hit, msr.fetch.miss, msr.fetch.empty,
                       msr.lsu.hLd, msr.lsu.hSt, msr.lsu.hJoin,
                       msr.lsu.mLd, msr.lsu.mSt, msr.lsu.mJoin,
                       msr.lsu.dLd, msr.lsu.dSt, msr.lsu.dJoin);

   endrule

   rule doEvict if(roundRobin && dut.getNumCommit() == commitTarget);

      if(mainTokenQ.notEmpty) begin
         dut.evict(evictTarget);
         evictTarget  <=  (evictTarget == lastFrontID) ? '0 : evictTarget+1;
      end

      commitTarget <= commitTarget+fromInteger(valueOf(RR_INT));

   endrule

   rule getContToken;

      let t <- dut.getContToken();
      mainTokenQ.enq(t);

   endrule

   rule putContToken;

      FrontID hart = 0;

      if(valueOf(FrontWidth) != 1) begin
         for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
            if(!dut.available(hart)) begin
               hart = (hart == lastFrontID) ? '0 : hart+1;
            end
         end
      end

      let t = mainTokenQ.first(); mainTokenQ.deq();
      dut.start(hart,t);

   endrule

   interface FromHost connectProc;

      method Action setMem (Bit#(32) addr, Bit#(32) word);

         mainMem.direct.req(toWideMemReq(addr, word));

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
