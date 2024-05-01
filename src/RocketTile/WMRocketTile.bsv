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

(*synthesize*)
module mkWMRocketTile(WMRocketTileIfc ifc);

	//////////// ROCKET INSTANCE ////////////

	PackedRocketTileIfc rocket_tile <- mkPackedRocketTile;

	//////////// BRIDGE FIFOS ////////////

	FIFOF#(WideMemReq#(Bit#(2))) wm_mem_req <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(Bit#(2))) wm_mem_res <- mkBypassFIFOF();

	FIFOF#(TLreqA) tl_reqA <- mkBypassFIFOF();
	FIFOF#(TLreqB) tl_reqB <- mkBypassFIFOF();
	FIFOF#(TLreqC) tl_reqC <- mkBypassFIFOF();
	FIFOF#(TLreqD) tl_reqD <- mkBypassFIFOF();
	FIFOF#(TLreqE) tl_reqE <- mkBypassFIFOF();

	//////////// TL2FF ////////////

	rule do_get_reqA;

		TLreqApacked reqApacked <- rocket_tile.tlc_link.getA();
		TLreqA reqA = unpack(reqApacked);
		tl_reqA.enq(reqA);

		`ifdef DEBUG_RCKT
		$display("get channel A = ", fshow(reqA));
		`endif

	endrule

	rule do_put_reqB;

		TLreqB reqB = tl_reqB.first(); tl_reqB.deq();
		TLreqBpacked reqBpacked = pack(reqB);
		rocket_tile.tlc_link.putB(reqBpacked);

		`ifdef DEBUG_RCKT
		$display("put channel B = ", fshow(reqB));
		`endif

	endrule

	rule do_get_reqC;

		TLreqCpacked reqCpacked <- rocket_tile.tlc_link.getC();
		TLreqC reqC = unpack(reqCpacked);
		tl_reqC.enq(reqC);

		`ifdef DEBUG_RCKT
		$display("get channel C = ", fshow(reqC));
		`endif

	endrule

	rule do_put_reqD;

		TLreqD reqD = tl_reqD.first(); tl_reqD.deq();
		TLreqDpacked reqDpacked = pack(reqD);
		rocket_tile.tlc_link.putD(reqDpacked);

		`ifdef DEBUG_RCKT
		$display("put channel D = ", fshow(reqD));
		`endif

	endrule

	rule do_get_reqE;

		TLreqEpacked reqEpacked <- rocket_tile.tlc_link.getE();
		TLreqE reqE = unpack(reqEpacked);
		tl_reqE.enq(reqE);

		`ifdef DEBUG_RCKT
		$display("get channel E = ", fshow(reqE));
		`endif

	endrule

	//////////// TL-WM conversion ////////////

	// TODO: TL-WM conversion logic





	//////////// DEBUG MONITORS ////////////

	`ifdef DEBUG_RCKT

	rule do_DEBUG_RCKT_CYC_WFI;

		$display("WFI : %b",rocket_tile.get_auto_wfi_out_0);

		$write("----------------------------------------------------------------------------------------------------------------------------------------\n");

	endrule

	rule do_DEBUG_RCKT_CYC_INSNS;

		RocketBcastPacked bcastPacked = rocket_tile.get_rocket_bcast();
		RocketBcast bcast = unpack(bcastPacked);

		$display("bcast = ", fshow(bcast));

	endrule

	`endif

	//////////// INTERFACE ////////////

	interface WideMemClient uniMem;
        interface request = (interface Get#(WideMemReq#(Bit#(2)));
            method ActionValue#(WideMemReq#(Bit#(2))) get();
                wm_mem_req.deq();
                return wm_mem_req.first();
            endmethod
        endinterface);
        interface response = (interface Put#(WidememRes#(Tuple2#(srcT,tagT)));
            method Action put(WideMemRes#(Bit#(2)) resp);
                wm_mem_res.enq(resp);
            endmethod
        endinterface);
    endinterface

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