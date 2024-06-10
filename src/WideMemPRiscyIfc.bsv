import FShow::*;
import FIFOF::*;
import FIFO::*;
import BRAMFIFO::*;

import Types::*;
import Config::*;
import CMRTypes::*;
import WideMemTypes::*;

interface WideMemPRiscy;

    // WMI
    interface WideMemClient#(Tuple2#(Bit#(TLog#(2)),FrontID)) wm_client;

    // Stream load
    interface FIFOF#(ContToken) toMTQ;

    // CMR
    `ifdef DEBUG_CMR
    method ActionValue#(CommitReport) getCMR();
    `endif

    // MMIO
    `ifdef MMIO
    method ActionValue#(StatReq) getMSG();
    method ActionValue#(StatReq) getHEX();
    method ActionValue#(StatReq) getMSR();
    method ActionValue#(StatReq) getCTR();
    `endif

    // STAT
    `ifdef DEBUG_STATS
    method L1IStat     getL1IStat();
    method L1DStat     getL1DStat();
    method CoreStat    getCoreStat();
    `endif

endinterface
