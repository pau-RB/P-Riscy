// General BSV utilities
import FShow::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Connectable::*;
import ClientServer::*;
import GetPut::*;
import BRAMFIFO::*;
import Ehr::*;

// Platform types
import Types::*;
import ProcTypes::*;
import WideMemTypes::*;
import CMRTypes::*;

// TL types
import TileLinkTypes::*;
import TileLinkIfc::*;

// Rocket types
import RocketTileBcastTypes::*;
import PackedRocketTileIfc::*;
import PackedRocketTile::*;
import WMRocketTileIfc::*;
import RocketConfig::*;


// Bridge
import TL2WMBridgeIfc::*;
import TL2WMBridge::*;


(*synthesize*)
module mkWMRocketTile(WMRocketTileIfc ifc);

    //////////// ROCKET INSTANCE ////////////

    PackedRocketTileIfc rocket_tile <- mkPackedRocketTile;

    //////////// BRIDGE ////////////

    TL2WMBridgeIfc bridge <- mkTL2WMBridge;
    Reg#(Bool) bridgeStarted <- mkReg(False);

    //////////// "bootROM" ////////////

    FIFOF#(TLreqApacked) to_bootROM <- mkPipelineFIFOF();

    //////////// CMR relay ////////////

    Ehr#(2,PerfCnt) latest_insns_cycle  <- mkEhr('0);
    Ehr#(2,PerfCnt) latest_insns_commit <- mkEhr('0);

    `ifdef DEBUG_RCKT_CMR
    FIFOF#(CommitReport) commitReportQ <- mkSizedBRAMFIFOF(valueOf(CMRTHQ_LEN));
    `endif

    //////////// MMIO ////////////

    FIFOF#(TLreqApacked) to_MMIO <- mkPipelineFIFOF();

    `ifdef RCKT_MMIO
    FIFOF#(StatReq) mmio_MSGQ <- mkFIFOF();
    FIFOF#(StatReq) mmio_HEXQ <- mkFIFOF();
    FIFOF#(StatReq) mmio_MSRQ <- mkFIFOF();
    FIFOF#(StatReq) mmio_CTRQ <- mkFIFOF();
    `endif

    //////////// TL2Bridge ////////////

    rule do_put_reqA if(bridgeStarted);

        TLreqApacked beat_packed = rocket_tile.tlc_link.getA();
        TLreqA beat = unpack(beat_packed);

        if(beat.address == 32'h00010040) begin

            to_bootROM.enq(beat_packed);

            rocket_tile.tlc_link.readyA();

        end else if (beat.address[31:28] == 4'h6) begin

            to_MMIO.enq(beat_packed);

            rocket_tile.tlc_link.readyA();

        end else begin

            bridge.tl_slave.putA(beat_packed);
            if(bridge.tl_slave.readyA())
                rocket_tile.tlc_link.readyA();

        end

        `ifdef DEBUG_RCKT_TL
        $display("get channel A = ", fshow(beat));
        $display("bridge.tl_slave.readyA() = ", fshow(bridge.tl_slave.readyA()));
        `endif

    endrule

    rule do_get_reqB;

        TLreqBpacked beat_packed = bridge.tl_slave.getB();
        rocket_tile.tlc_link.putB(beat_packed);
        if(rocket_tile.tlc_link.readyB())
            bridge.tl_slave.readyB();

        `ifdef DEBUG_RCKT_TL
        TLreqB beat = unpack(beat_packed);
        $display("put channel B = ", fshow(beat));
        $display("rocket_tile.tlc_link.readyB() = ", fshow(rocket_tile.tlc_link.readyB()));
        `endif

    endrule

    rule do_put_reqC;

        TLreqCpacked beat_packed = rocket_tile.tlc_link.getC();
        bridge.tl_slave.putC(beat_packed);
        if(bridge.tl_slave.readyC())
            rocket_tile.tlc_link.readyC();

        `ifdef DEBUG_RCKT_TL
        TLreqC beat = unpack(beat_packed);
        $display("get channel C = ", fshow(beat));
        $display("(bridge.tl_slave.readyC() = ", fshow(bridge.tl_slave.readyC()));
        `endif

    endrule

    rule do_get_reqD;

        TLreqDpacked beat_packed = bridge.tl_slave.getD();
        rocket_tile.tlc_link.putD(beat_packed);
        if(rocket_tile.tlc_link.readyD())
            bridge.tl_slave.readyD();

        `ifdef DEBUG_RCKT_TL
        TLreqD beat = unpack(beat_packed);
        $display("put channel D = ", fshow(beat));
        $display("rocket_tile.tlc_link.readyD() = ", fshow(rocket_tile.tlc_link.readyD()));
        `endif

    endrule

    rule do_put_reqE;

        TLreqEpacked beat_packed = rocket_tile.tlc_link.getE();
        bridge.tl_slave.putE(beat_packed);
        if(bridge.tl_slave.readyE())
            rocket_tile.tlc_link.readyE();

        `ifdef DEBUG_RCKT_TL
        TLreqE beat = unpack(beat_packed);
        $display("get channel E = ", fshow(beat));
        $display("bridge.tl_slave.readyE() = ", fshow(bridge.tl_slave.readyE()));
        `endif

    endrule

    //////////// TL-WM conversion "bootROM" ////////////

    rule do_bootROM;

        TLreqApacked beat_packed = to_bootROM.first();
        to_bootROM.deq();
        TLreqA beat = unpack(beat_packed);

        // "BootROM"
        // 0x30001073 CSRW mstatus, x0
        // 0x800000b7 lui x1, -524288
        // 0x00008067 jalr x0, 0(x1) 
        // Just jump to 0x80000000

        TLreqD reqD = TLreqD { opcode : TileLinkTypes::AccessAckData                    ,
                               param  : TileLinkTypes::ToT                              ,
                               size   : 6                                               ,
                               source : beat.source                                     ,
                               sink   : 0                                               ,
                               denied : 0                                               ,
                               data   : {'0, 32'h00008067, 32'h800000b7, 32'h30001073}  ,
                               corrupt: 0                                               };

        rocket_tile.tlc_link.putD(pack(reqD));

        `ifdef DEBUG_RCKT_TL
        $display("put channel D = ", fshow(reqD));
        `endif

    endrule

    //////////// TL-WM conversion MMIO ////////////

    rule do_latest_insns;

        RocketBcastPacked bcastPacked = rocket_tile.get_rocket_bcast();
        RocketBcast bcast = unpack(bcastPacked);

        latest_insns_cycle [1] <= bcast.bits_time;
        latest_insns_commit[1] <= latest_insns_commit[1]+1;

    endrule

    rule do_MMIO;

        // get reqA
        TLreqApacked beat_packed = to_MMIO.first();
        to_MMIO.deq();
        TLreqA beat = unpack(beat_packed);

        // Check params
        if(beat.opcode != TileLinkTypes::PutFullData) $error("WMRocketTile MMIO - Only expected PutFullData!"   );
        if(beat.size   != 2                         ) $error("WMRocketTile MMIO - Only expected 8-bit requests!");

        // Send reqD response
        TLreqD reqD = TLreqD { opcode : TileLinkTypes::AccessAck,
                               param  : TileLinkTypes::ToT      ,
                               size   : 2                       ,
                               source : beat.source             ,
                               sink   : 0                       ,
                               denied : 0                       ,
                               data   : '0                      ,
                               corrupt: 0                       };

        rocket_tile.tlc_link.putD(pack(reqD));

        `ifdef RCKT_MMIO

        Bit#(6) offset = beat.address[5:0];
        StatReq stat_req = StatReq { verifID: '0                             ,
                                     cycle  : latest_insns_cycle [0]         ,
                                     commit : latest_insns_commit[0]         ,
                                     data   : beat.data[offset*8+31:offset*8]};

             if(RocketConfig::msg_ext_DEBUG && beat.address ==  msg_ADDR) mmio_MSGQ.enq(stat_req);
        else if(RocketConfig::hex_ext_DEBUG && beat.address ==  hex_ADDR) mmio_HEXQ.enq(stat_req);
        else if(RocketConfig::msr_ext_DEBUG && beat.address ==  msr_ADDR) mmio_MSRQ.enq(stat_req);
        else if(RocketConfig::ctr_ext_DEBUG && beat.address ==  ctr_ADDR) mmio_CTRQ.enq(stat_req);
        else $error("WMRocketTile MMIO - MMIO dropped due to unknown address!");

        `endif

    endrule

    //////////// DEBUG MONITORS ////////////

    `ifdef DEBUG_RCKT_WFI

    rule do_DEBUG_RCKT_CYC_WFI;

        if(rocket_tile.get_auto_wfi_out_0 == 1'b1)
           $error("WFI is set!");

    endrule

    `endif

    `ifdef DEBUG_RCKT_TRACE

    rule do_DEBUG_RCKT_TRACE;

        RocketBcastPacked bcastPacked = rocket_tile.get_rocket_bcast();
        RocketBcast bcast = unpack(bcastPacked);

        $display("WMRocketTile bcast = ", fshow(bcast));

    endrule

    `endif

    `ifdef DEBUG_RCKT_CMR
    rule do_DEBUG_RCKT_CMR;

        RocketBcastPacked bcastPacked = rocket_tile.get_rocket_bcast();
        RocketBcast bcast = unpack(bcastPacked);

        if(bcast.bits_insns_0_iaddr[31:16] != 16'h0001) begin
            // Skip the tiny bootROM
            commitReportQ.enq(CommitReport {cycle  : bcast.bits_time            ,
                                            verifID: '0                         ,
                                            pc     : bcast.bits_insns_0_iaddr   ,
                                            rawInst: bcast.bits_insns_0_insn    ,
                                            iType  : Unsupported                ,
                                            wbDst  : '0                         ,
                                            wbRes  : '0                         ,
                                            addr   : '0                         });
        end

    endrule
    `endif

    //////////// INTERFACE ////////////

    interface WideMemClient wm_client = bridge.wm_client;

    method Action startBridge();
        bridgeStarted <= True;
    endmethod

    // CMR
    `ifdef DEBUG_RCKT_CMR
    method ActionValue#(CommitReport) getCMR();
        let latest = commitReportQ.first(); commitReportQ.deq();
        return latest;
    endmethod
    `endif

    // MMIO
    `ifdef RCKT_MMIO

    method ActionValue#(StatReq) getMSG();
        mmio_MSGQ.deq();
        return mmio_MSGQ.first();
    endmethod

    method ActionValue#(StatReq) getHEX();
        mmio_HEXQ.deq();
        return mmio_HEXQ.first();
    endmethod

    method ActionValue#(StatReq) getMSR();
        mmio_MSRQ.deq();
        return mmio_MSRQ.first();
    endmethod

    method ActionValue#(StatReq) getCTR();
        mmio_CTRQ.deq();
        return mmio_CTRQ.first();
    endmethod

    `endif

endmodule