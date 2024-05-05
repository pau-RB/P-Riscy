// Platform types
import Types::*;
import WideMemTypes::*;

// TL types
import TileLinkTypes::*;
import TileLinkIfc::*;

interface TL2WMBridgeIfc;

    interface WideMemClient#(Bit#(3)) wm_client;

    interface TileLinkSlaveCached tl_slave;

endinterface : TL2WMBridgeIfc
