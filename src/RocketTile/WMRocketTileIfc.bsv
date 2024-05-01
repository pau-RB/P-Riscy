import Types::*;
import WideMemTypes::*;
import TileLinkIfc::*;
import RocketTileBcastTypes::*;

//////////// Interface adpated to WM ////////////

interface WMRocketTileIfc;

	// Bit#(2) WM tags to match TL 2-bit source ID
	interface WideMemClient#(Bit#(2)) uniMem;
/*
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
*/
endinterface : WMRocketTileIfc
