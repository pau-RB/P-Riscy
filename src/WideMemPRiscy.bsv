import FShow::*;
import FIFOF::*;
import FIFO::*;
import BRAMFIFO::*;
import Connectable::*;

import Types::*;
import Config::*;
import CMRTypes::*;
import WideMemTypes::*;

import WideMemPRiscyIfc::*;
import Core::*;
import WideMemSplit::*;

module mkWideMemPRiscy(WideMemPRiscy ifc);

    Core core <- mkCore7SS();

    WideMemSplit#(2,TMul#(2,FrontWidth), FrontID) memArb <- mkSplitWideMem();

    FIFOF#(ContToken) mainTokenQ <- mkSizedBRAMFIFOF(valueOf(MTQ_LEN));

    `ifdef DEBUG_CMR
    FIFOF#(CommitReport) mainCMRQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
    `endif

    //////////// Main arbiter ////////////

    mkConnection(core.instMem, memArb.port[0]);
    mkConnection(core.dataMem, memArb.port[1]);

    //////////// Large queues ////////////

    rule do_core_to_MTQ;
      mainTokenQ.enq(core.toMTQ.first()); core.toMTQ.deq();
    endrule

    rule do_MTQ_to_core;
      core.toMTQ.enq(mainTokenQ.first()); mainTokenQ.deq();
    endrule

    `ifdef DEBUG_CMR
    rule do_core_to_CMRQ;
      let latest <- core.getCMR();
      mainCMRQ.enq(latest);
    endrule
    `endif

    //////////// Interface ////////////

    // WMI
    interface WideMemClient wm_client = memArb.mem;

    // Stream load
    interface FIFOF toMTQ = mainTokenQ;

    // CMR
    `ifdef DEBUG_CMR
    method ActionValue#(CommitReport) getCMR();
        CommitReport cmr = mainCMRQ.first(); mainCMRQ.deq();
        return cmr;
    endmethod
    `endif

    // MMIO
    `ifdef MMIO
    method ActionValue#(StatReq) getMSG() = core.getMSG();
    method ActionValue#(StatReq) getHEX() = core.getHEX();
    method ActionValue#(StatReq) getMSR() = core.getMSR();
    method ActionValue#(StatReq) getCTR() = core.getCTR();
    `endif

    // STAT
    `ifdef DEBUG_STATS
    method L1IStat  getL1IStat  = core.getL1IStat;
    method L1DStat  getL1DStat  = core.getL1DStat;
    method CoreStat getCoreStat = core.getCoreStat;
    `endif

endmodule