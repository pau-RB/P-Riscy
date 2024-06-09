import Types::*;
import WideMemTypes::*;
import TileLinkIfc::*;
import RocketTileBcastTypes::*;
import CMRTypes::*;

//////////// Interface adpated to WM ////////////

interface WMRocketTileIfc;

	// Bit#(3) WM tags to match TL 2-bit source ID + 1 additional MSB
	interface WideMemClient#(Bit#(3)) wm_client;

	method Action startBridge();

	// CMR
	`ifdef DEBUG_RCKT_CMR
	method ActionValue#(CommitReport) getCMR();
	`endif
/*
	// MMIO
	`ifdef MMIO
	method ActionValue#(StatReq) getMSG();
	method ActionValue#(StatReq) getHEX();
	method ActionValue#(StatReq) getMSR();
	method ActionValue#(StatReq) getCTR();
	`endif
*/
endinterface : WMRocketTileIfc
