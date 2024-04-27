import TileLinkIfc::*;
import TileLinkTypes::*;
import PackedRocketTileIfc::*;
import RocketTileBcastTypes::*;

import "BVI" PackedRocketTile =

module mkPackedRocketTile (PackedRocketTileIfc);

    Bit#(1) instance_hartid = 0;

    default_clock clk(clock_i, (*unused*) clk_gate);
    default_reset rst(reset_ni);

    interface TileLinkMasterCached tlc_link;

        //// Master to Slave
        method auto_buffer_out_a_beat_o getA enable(auto_buffer_out_a_ready_i) ready (auto_buffer_out_a_valid_o);
        method auto_buffer_out_c_beat_o getC enable(auto_buffer_out_c_ready_i) ready (auto_buffer_out_c_valid_o);
        method auto_buffer_out_e_beat_o getE enable(auto_buffer_out_e_ready_i) ready (auto_buffer_out_e_valid_o);

        // Slave to master
        method putB(auto_buffer_out_b_beat_i) enable(auto_buffer_out_b_valid_i) ready (auto_buffer_out_b_ready_o);
        method putD(auto_buffer_out_d_beat_i) enable(auto_buffer_out_d_valid_i) ready (auto_buffer_out_d_ready_o);

    endinterface : tlc_link

    method auto_broadcast_out_packet_o get_rocket_bcast ready(auto_broadcast_out_valid_o);

    method put_auto_int_local_in_2_0() enable(auto_int_local_in_2_0_i);
    method put_auto_int_local_in_1_0() enable(auto_int_local_in_1_0_i);
    method put_auto_int_local_in_1_1() enable(auto_int_local_in_1_1_i);
    method put_auto_int_local_in_0_0() enable(auto_int_local_in_0_0_i);

    method auto_wfi_out_0_o get_auto_wfi_out_0();

    port auto_hartid_in_i = instance_hartid;

endmodule : mkPackedRocketTile