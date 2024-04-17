import TileLinkIfc::*;
import TileLinkTypes::*;
import RawRocketTileIfc::*;
import RocketTileBcastIfc::*;

import "BVI" RawRocketTile =

module mkRawRocketTile (RawRocketTileIfc);

    interface TileLinkMasterCached tlc_link;

        //// Master to Slave
        method auto_buffer_out_a_beat getA enable(auto_buffer_out_a_ready) ready (auto_buffer_out_a_valid);
        method auto_buffer_out_c_beat getC enable(auto_buffer_out_c_ready) ready (auto_buffer_out_c_valid);
        method auto_buffer_out_e_beat getE enable(auto_buffer_out_e_ready) ready (auto_buffer_out_e_valid);

        // Slave to master
        method putB( auto_buffer_out_b_bits_beat) enable(auto_buffer_out_b_valid) ready (auto_buffer_out_b_ready);
        method putD( auto_buffer_out_d_bits_beat) enable(auto_buffer_out_d_valid) ready (auto_buffer_out_d_ready);

    endinterface : tlc_link

    interface RocketTileBcastIfc bcast_link;

        method auto_broadcast_out_insns_0_valid     get_auto_broadcast_out_insns_0_valid     ready(always_ready);
        method auto_broadcast_out_insns_0_iaddr     get_auto_broadcast_out_insns_0_iaddr     ready(always_ready);
        method auto_broadcast_out_insns_0_insn      get_auto_broadcast_out_insns_0_insn      ready(always_ready); 
        method auto_broadcast_out_insns_0_priv      get_auto_broadcast_out_insns_0_priv      ready(always_ready); 
        method auto_broadcast_out_insns_0_exception get_auto_broadcast_out_insns_0_exception ready(always_ready);
        method auto_broadcast_out_insns_0_interrupt get_auto_broadcast_out_insns_0_interrupt ready(always_ready);
        method auto_broadcast_out_insns_0_cause     get_auto_broadcast_out_insns_0_cause     ready(always_ready);
        method auto_broadcast_out_insns_0_tval      get_auto_broadcast_out_insns_0_tval      ready(always_ready);
        method auto_broadcast_out_time              get_auto_broadcast_out_time              ready(always_ready);

    endinterface : bcast_link

    method put_auto_int_local_in_2_0() enable(auto_int_local_in_2_0) ready(always_ready);
    method put_auto_int_local_in_1_0() enable(auto_int_local_in_1_0) ready(always_ready);
    method put_auto_int_local_in_1_1() enable(auto_int_local_in_1_1) ready(always_ready);
    method put_auto_int_local_in_0_0() enable(auto_int_local_in_0_0) ready(always_ready);

    method auto_wfi_out_0 get_auto_wfi_out_0();

endmodule : mkRawRocketTile