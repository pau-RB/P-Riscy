import TileLinkIfc::*;
import RocketTileBcastIfc::*;


//////////// Raw imported interface for RocketTile ////////////

interface RawRocketTileIfc;

    interface TileLinkMasterCached tlc_link;

    interface RocketTileBcastIfc bcast_link;

    method Action put_auto_int_local_in_2_0();
    method Action put_auto_int_local_in_1_0();
    method Action put_auto_int_local_in_1_1();
    method Action put_auto_int_local_in_0_0();

    method Bit#(1) get_auto_wfi_out_0();

endinterface : RawRocketTileIfc