// General BSV utilities
import FShow::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Connectable::*;
import ClientServer::*;
import GetPut::*;

// Platform types
import Types::*;
import WideMemTypes::*;

// TL types
import TileLinkTypes::*;
import TileLinkIfc::*;

// Rocket types
import RocketTileBcastTypes::*;
import PackedRocketTileIfc::*;
import PackedRocketTile::*;
import WMRocketTileIfc::*;

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

    //////////// TL2Bridge ////////////

    rule do_put_reqA if(bridgeStarted);

        TLreqApacked beat_packed <- rocket_tile.tlc_link.getA();
        TLreqA beat = unpack(beat_packed);

        if(beat.address == 32'h00010040) begin

            to_bootROM.enq(beat_packed);

        end else begin

            bridge.tl_slave.putA(beat_packed);

        end

        `ifdef DEBUG_RCKT
        $display("get channel A = ", fshow(beat));
        `endif

    endrule

    rule do_get_reqB;

        TLreqBpacked beat_packed <- bridge.tl_slave.getB();
        rocket_tile.tlc_link.putB(beat_packed);

        `ifdef DEBUG_RCKT
        TLreqB beat = unpack(beat_packed);
        $display("put channel B = ", fshow(beat));
        `endif

    endrule

    rule do_put_reqC;

        TLreqCpacked beat_packed <- rocket_tile.tlc_link.getC();
        bridge.tl_slave.putC(beat_packed);

        `ifdef DEBUG_RCKT
        TLreqC beat = unpack(beat_packed);
        $display("get channel C = ", fshow(beat));
        `endif

    endrule

    rule do_get_reqD;

        TLreqDpacked beat_packed <- bridge.tl_slave.getD();
        rocket_tile.tlc_link.putD(beat_packed);

        `ifdef DEBUG_RCKT
        TLreqD beat = unpack(beat_packed);
        $display("put channel D = ", fshow(beat));
        `endif

    endrule

    rule do_put_reqE;

        TLreqEpacked beat_packed <- rocket_tile.tlc_link.getE();
        bridge.tl_slave.putE(beat_packed);

        `ifdef DEBUG_RCKT
        TLreqE beat = unpack(beat_packed);
        $display("get channel E = ", fshow(beat));
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

        `ifdef DEBUG_RCKT
        $display("put channel D = ", fshow(reqD));
        `endif

    endrule

    //////////// DEBUG MONITORS ////////////

    `ifdef DEBUG_RCKT

    rule do_DEBUG_RCKT_CYC_WFI;

        if(rocket_tile.get_auto_wfi_out_0 == 1'b1)
           $error("WFI is set!");

    endrule

    `endif

    `ifdef DEBUG_RCKT_TRACE

    rule do_DEBUG_RCKT_CYC_INSNS;

        RocketBcastPacked bcastPacked = rocket_tile.get_rocket_bcast();
        RocketBcast bcast = unpack(bcastPacked);

        $display("WMRocketTile bcast = ", fshow(bcast));

    endrule

    `endif

    //////////// INTERFACE ////////////

    interface WideMemClient wm_client = bridge.wm_client;

    method Action startBridge();
        bridgeStarted <= True;
    endmethod

/*
    // CMR
    `ifdef DEBUG_CMR
    method ActionValue#(CommitReport) getCMR = backend.getCMR;
    `endif

    // MMIO
    `ifdef MMIO
    method ActionValue#(StatReq) getMSG() = backend.getMSG();
    method ActionValue#(StatReq) getHEX() = backend.getHEX();
    method ActionValue#(StatReq) getMSR() = backend.getMSR();
    method ActionValue#(StatReq) getCTR() = backend.getCTR();
    `endif

    */

endmodule