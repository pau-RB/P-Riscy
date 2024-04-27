
`include "TileLinkTypes"
`include "RocketTileBcastTypes"

module PackedRocketTile (

  input  logic                  clock_i                             ,
  input  logic                  reset_ni                            ,
  input  logic                  auto_hartid_in_i                    ,
  
  input  logic                  auto_buffer_out_a_ready_i           ,
  output logic                  auto_buffer_out_a_valid_o           ,
  output TLreqApacked_t         auto_buffer_out_a_beat_o            ,

  output logic                  auto_buffer_out_b_ready_o           ,
  input  logic                  auto_buffer_out_b_valid_i           ,
  input  TLreqBpacked_t         auto_buffer_out_b_beat_i            ,

  input  logic                  auto_buffer_out_c_ready_i           ,
  output logic                  auto_buffer_out_c_valid_o           ,
  output TLreqCpacked_t         auto_buffer_out_c_beat_o            ,

  output logic                  auto_buffer_out_d_ready_o           ,
  input  logic                  auto_buffer_out_d_valid_i           ,
  input  TLreqDpacked_t         auto_buffer_out_d_beat_i            ,

  input  logic                  auto_buffer_out_e_ready_i           ,
  output logic                  auto_buffer_out_e_valid_o           ,
  output TLreqEpacked_t         auto_buffer_out_e_beat_o            ,

  output logic                  auto_broadcast_out_valid_o          ,
  output rocket_bcast_packed_t  auto_broadcast_out_packet_o         ,

  input  logic                  auto_int_local_in_2_0_i             ,
  input  logic                  auto_int_local_in_1_0_i             ,
  input  logic                  auto_int_local_in_1_1_i             ,
  input  logic                  auto_int_local_in_0_0_i             ,

  output logic                  auto_wfi_out_0_o

);

  //////////// raw RocketTile port interconect ////////////

  logic         rckt_clock                                ;
  logic         rckt_reset                                ;
  logic         rckt_auto_buffer_out_a_ready              ;
  logic         rckt_auto_buffer_out_b_valid              ;
  logic [2:0]   rckt_auto_buffer_out_b_bits_opcode        ;
  logic [1:0]   rckt_auto_buffer_out_b_bits_param         ;
  logic [3:0]   rckt_auto_buffer_out_b_bits_size          ;
  logic [1:0]   rckt_auto_buffer_out_b_bits_source        ;
  logic [31:0]  rckt_auto_buffer_out_b_bits_address       ;
  logic [63:0]  rckt_auto_buffer_out_b_bits_mask          ;
  logic [511:0] rckt_auto_buffer_out_b_bits_data          ;
  logic         rckt_auto_buffer_out_b_bits_corrupt       ;
  logic         rckt_auto_buffer_out_c_ready              ;
  logic         rckt_auto_buffer_out_d_valid              ;
  logic [2:0]   rckt_auto_buffer_out_d_bits_opcode        ;
  logic [1:0]   rckt_auto_buffer_out_d_bits_param         ;
  logic [3:0]   rckt_auto_buffer_out_d_bits_size          ;
  logic [1:0]   rckt_auto_buffer_out_d_bits_source        ;
  logic [1:0]   rckt_auto_buffer_out_d_bits_sink          ;
  logic         rckt_auto_buffer_out_d_bits_denied        ;
  logic [511:0] rckt_auto_buffer_out_d_bits_data          ;
  logic         rckt_auto_buffer_out_d_bits_corrupt       ;
  logic         rckt_auto_buffer_out_e_ready              ;
  logic         rckt_auto_int_local_in_2_0                ;
  logic         rckt_auto_int_local_in_1_0                ;
  logic         rckt_auto_int_local_in_1_1                ;
  logic         rckt_auto_int_local_in_0_0                ;
  logic         rckt_auto_hartid_in                       ;
  logic         rckt_auto_buffer_out_a_valid              ;
  logic [2:0]   rckt_auto_buffer_out_a_bits_opcode        ;
  logic [2:0]   rckt_auto_buffer_out_a_bits_param         ;
  logic [3:0]   rckt_auto_buffer_out_a_bits_size          ;
  logic [1:0]   rckt_auto_buffer_out_a_bits_source        ;
  logic [31:0]  rckt_auto_buffer_out_a_bits_address       ;
  logic [63:0]  rckt_auto_buffer_out_a_bits_mask          ;
  logic [511:0] rckt_auto_buffer_out_a_bits_data          ;
  logic         rckt_auto_buffer_out_b_ready              ;
  logic         rckt_auto_buffer_out_c_valid              ;
  logic [2:0]   rckt_auto_buffer_out_c_bits_opcode        ;
  logic [2:0]   rckt_auto_buffer_out_c_bits_param         ;
  logic [3:0]   rckt_auto_buffer_out_c_bits_size          ;
  logic [1:0]   rckt_auto_buffer_out_c_bits_source        ;
  logic [31:0]  rckt_auto_buffer_out_c_bits_address       ;
  logic [511:0] rckt_auto_buffer_out_c_bits_data          ;
  logic         rckt_auto_buffer_out_d_ready              ;
  logic         rckt_auto_buffer_out_e_valid              ;
  logic [1:0]   rckt_auto_buffer_out_e_bits_sink          ;
  logic         rckt_auto_broadcast_out_insns_0_valid     ;
  logic [31:0]  rckt_auto_broadcast_out_insns_0_iaddr     ;
  logic [31:0]  rckt_auto_broadcast_out_insns_0_insn      ;
  logic [2:0]   rckt_auto_broadcast_out_insns_0_priv      ;
  logic         rckt_auto_broadcast_out_insns_0_exception ;
  logic         rckt_auto_broadcast_out_insns_0_interrupt ;
  logic [31:0]  rckt_auto_broadcast_out_insns_0_cause     ;
  logic [31:0]  rckt_auto_broadcast_out_insns_0_tval      ;
  logic [63:0]  rckt_auto_broadcast_out_time              ;
  logic         rckt_auto_wfi_out_0                       ;

  //////////// raw RocketTile instance ////////////

  RocketTile rocket_tile_i (

    .clock                                 ( rckt_clock                                ),
    .reset                                 ( rckt_reset                                ),
    .auto_buffer_out_a_ready               ( rckt_auto_buffer_out_a_ready              ),
    .auto_buffer_out_b_valid               ( rckt_auto_buffer_out_b_valid              ),
    .auto_buffer_out_b_bits_opcode         ( rckt_auto_buffer_out_b_bits_opcode        ),
    .auto_buffer_out_b_bits_param          ( rckt_auto_buffer_out_b_bits_param         ),
    .auto_buffer_out_b_bits_size           ( rckt_auto_buffer_out_b_bits_size          ),
    .auto_buffer_out_b_bits_source         ( rckt_auto_buffer_out_b_bits_source        ),
    .auto_buffer_out_b_bits_address        ( rckt_auto_buffer_out_b_bits_address       ),
    .auto_buffer_out_b_bits_mask           ( rckt_auto_buffer_out_b_bits_mask          ),
    .auto_buffer_out_b_bits_data           ( rckt_auto_buffer_out_b_bits_data          ),
    .auto_buffer_out_b_bits_corrupt        ( rckt_auto_buffer_out_b_bits_corrupt       ),
    .auto_buffer_out_c_ready               ( rckt_auto_buffer_out_c_ready              ),
    .auto_buffer_out_d_valid               ( rckt_auto_buffer_out_d_valid              ),
    .auto_buffer_out_d_bits_opcode         ( rckt_auto_buffer_out_d_bits_opcode        ),
    .auto_buffer_out_d_bits_param          ( rckt_auto_buffer_out_d_bits_param         ),
    .auto_buffer_out_d_bits_size           ( rckt_auto_buffer_out_d_bits_size          ),
    .auto_buffer_out_d_bits_source         ( rckt_auto_buffer_out_d_bits_source        ),
    .auto_buffer_out_d_bits_sink           ( rckt_auto_buffer_out_d_bits_sink          ),
    .auto_buffer_out_d_bits_denied         ( rckt_auto_buffer_out_d_bits_denied        ),
    .auto_buffer_out_d_bits_data           ( rckt_auto_buffer_out_d_bits_data          ),
    .auto_buffer_out_d_bits_corrupt        ( rckt_auto_buffer_out_d_bits_corrupt       ),
    .auto_buffer_out_e_ready               ( rckt_auto_buffer_out_e_ready              ),
    .auto_int_local_in_2_0                 ( rckt_auto_int_local_in_2_0                ),
    .auto_int_local_in_1_0                 ( rckt_auto_int_local_in_1_0                ),
    .auto_int_local_in_1_1                 ( rckt_auto_int_local_in_1_1                ),
    .auto_int_local_in_0_0                 ( rckt_auto_int_local_in_0_0                ),
    .auto_hartid_in                        ( rckt_auto_hartid_in                       ),
    .auto_buffer_out_a_valid               ( rckt_auto_buffer_out_a_valid              ),
    .auto_buffer_out_a_bits_opcode         ( rckt_auto_buffer_out_a_bits_opcode        ),
    .auto_buffer_out_a_bits_param          ( rckt_auto_buffer_out_a_bits_param         ),
    .auto_buffer_out_a_bits_size           ( rckt_auto_buffer_out_a_bits_size          ),
    .auto_buffer_out_a_bits_source         ( rckt_auto_buffer_out_a_bits_source        ),
    .auto_buffer_out_a_bits_address        ( rckt_auto_buffer_out_a_bits_address       ),
    .auto_buffer_out_a_bits_mask           ( rckt_auto_buffer_out_a_bits_mask          ),
    .auto_buffer_out_a_bits_data           ( rckt_auto_buffer_out_a_bits_data          ),
    .auto_buffer_out_b_ready               ( rckt_auto_buffer_out_b_ready              ),
    .auto_buffer_out_c_valid               ( rckt_auto_buffer_out_c_valid              ),
    .auto_buffer_out_c_bits_opcode         ( rckt_auto_buffer_out_c_bits_opcode        ),
    .auto_buffer_out_c_bits_param          ( rckt_auto_buffer_out_c_bits_param         ),
    .auto_buffer_out_c_bits_size           ( rckt_auto_buffer_out_c_bits_size          ),
    .auto_buffer_out_c_bits_source         ( rckt_auto_buffer_out_c_bits_source        ),
    .auto_buffer_out_c_bits_address        ( rckt_auto_buffer_out_c_bits_address       ),
    .auto_buffer_out_c_bits_data           ( rckt_auto_buffer_out_c_bits_data          ),
    .auto_buffer_out_d_ready               ( rckt_auto_buffer_out_d_ready              ),
    .auto_buffer_out_e_valid               ( rckt_auto_buffer_out_e_valid              ),
    .auto_buffer_out_e_bits_sink           ( rckt_auto_buffer_out_e_bits_sink          ),
    .auto_broadcast_out_insns_0_valid      ( rckt_auto_broadcast_out_insns_0_valid     ),
    .auto_broadcast_out_insns_0_iaddr      ( rckt_auto_broadcast_out_insns_0_iaddr     ),
    .auto_broadcast_out_insns_0_insn       ( rckt_auto_broadcast_out_insns_0_insn      ),
    .auto_broadcast_out_insns_0_priv       ( rckt_auto_broadcast_out_insns_0_priv      ),
    .auto_broadcast_out_insns_0_exception  ( rckt_auto_broadcast_out_insns_0_exception ),
    .auto_broadcast_out_insns_0_interrupt  ( rckt_auto_broadcast_out_insns_0_interrupt ),
    .auto_broadcast_out_insns_0_cause      ( rckt_auto_broadcast_out_insns_0_cause     ),
    .auto_broadcast_out_insns_0_tval       ( rckt_auto_broadcast_out_insns_0_tval      ),
    .auto_broadcast_out_time               ( rckt_auto_broadcast_out_time              ),
    .auto_wfi_out_0                        ( rckt_auto_wfi_out_0                       )

  );

  //////////// pack-unpack port assignment ////////////

  TLreqA_t        rckt_reqA;
  TLreqB_t        rckt_reqB;
  TLreqC_t        rckt_reqC;
  TLreqD_t        rckt_reqD;
  TLreqE_t        rckt_reqE;
  rocket_bcast_t  rckt_bcast;

  assign rckt_reqA  = { rckt_auto_buffer_out_a_bits_opcode        ,
                        rckt_auto_buffer_out_a_bits_param         ,
                        rckt_auto_buffer_out_a_bits_size          ,
                        rckt_auto_buffer_out_a_bits_source        ,
                        rckt_auto_buffer_out_a_bits_address       ,
                        rckt_auto_buffer_out_a_bits_mask          ,
                        rckt_auto_buffer_out_a_bits_data          };

  assign rckt_auto_buffer_out_b_bits_opcode  = rckt_reqB.bits_opcode ;
  assign rckt_auto_buffer_out_b_bits_param   = rckt_reqB.bits_param  ;
  assign rckt_auto_buffer_out_b_bits_size    = rckt_reqB.bits_size   ;
  assign rckt_auto_buffer_out_b_bits_source  = rckt_reqB.bits_source ;
  assign rckt_auto_buffer_out_b_bits_address = rckt_reqB.bits_address;
  assign rckt_auto_buffer_out_b_bits_mask    = rckt_reqB.bits_mask   ;
  assign rckt_auto_buffer_out_b_bits_data    = rckt_reqB.bits_data   ;
  assign rckt_auto_buffer_out_b_bits_corrupt = rckt_reqB.bits_corrupt;

  assign rckt_reqC  = { rckt_auto_buffer_out_c_bits_opcode        ,
                        rckt_auto_buffer_out_c_bits_param         ,
                        rckt_auto_buffer_out_c_bits_size          ,
                        rckt_auto_buffer_out_c_bits_source        ,
                        rckt_auto_buffer_out_c_bits_address       ,
                        rckt_auto_buffer_out_c_bits_data          };

  assign rckt_auto_buffer_out_d_bits_opcode  = rckt_reqD.bits_opcode ;
  assign rckt_auto_buffer_out_d_bits_param   = rckt_reqD.bits_param  ;
  assign rckt_auto_buffer_out_d_bits_size    = rckt_reqD.bits_size   ;
  assign rckt_auto_buffer_out_d_bits_source  = rckt_reqD.bits_source ;
  assign rckt_auto_buffer_out_d_bits_sink    = rckt_reqD.bits_sink   ;
  assign rckt_auto_buffer_out_d_bits_denied  = rckt_reqD.bits_denied ;
  assign rckt_auto_buffer_out_d_bits_data    = rckt_reqD.bits_data   ;
  assign rckt_auto_buffer_out_d_bits_corrupt = rckt_reqD.bits_corrupt;

  assign rckt_reqE  = { rckt_auto_buffer_out_e_bits_sink          };

  assign rckt_bcast = { rckt_auto_broadcast_out_insns_0_iaddr     ,
                        rckt_auto_broadcast_out_insns_0_insn      ,
                        rckt_auto_broadcast_out_insns_0_priv      ,
                        rckt_auto_broadcast_out_insns_0_exception ,
                        rckt_auto_broadcast_out_insns_0_interrupt ,
                        rckt_auto_broadcast_out_insns_0_cause     ,
                        rckt_auto_broadcast_out_insns_0_tval      ,
                        rckt_auto_broadcast_out_time              };

  //////////// raw RocketTile port assignment ////////////

  assign rckt_clock                   = clock_i                               ;
  assign rckt_reset                   = !reset_ni                             ;
  assign rckt_auto_hartid_in          = auto_hartid_in_i                      ;

  assign rckt_auto_buffer_out_a_ready = auto_buffer_out_a_ready_i             ;
  assign auto_buffer_out_a_valid_o    = rckt_auto_buffer_out_a_valid          ;
  assign auto_buffer_out_a_beat_o     = rckt_reqA                             ;

  assign auto_buffer_out_b_ready_o    = rckt_auto_buffer_out_b_ready          ;
  assign rckt_auto_buffer_out_b_valid = auto_buffer_out_b_valid_i             ;
  assign rckt_reqB                    = auto_buffer_out_b_beat_i              ;

  assign rckt_auto_buffer_out_c_ready = auto_buffer_out_c_ready_i             ;
  assign auto_buffer_out_c_valid_o    = rckt_auto_buffer_out_c_valid          ;
  assign auto_buffer_out_c_beat_o     = rckt_reqC                             ;

  assign auto_buffer_out_d_ready_o    = rckt_auto_buffer_out_d_ready          ;
  assign rckt_auto_buffer_out_d_valid = auto_buffer_out_d_valid_i             ;
  assign rckt_reqD                    = auto_buffer_out_d_beat_i              ;

  assign rckt_auto_buffer_out_e_ready = auto_buffer_out_e_ready_i             ;
  assign auto_buffer_out_e_valid_o    = rckt_auto_buffer_out_e_valid          ;
  assign auto_buffer_out_e_beat_o     = rckt_reqE                             ;

  assign auto_broadcast_out_valid_o   = rckt_auto_broadcast_out_insns_0_valid ;
  assign auto_broadcast_out_packet_o  = rckt_bcast                            ;

  assign rckt_auto_int_local_in_2_0   = auto_int_local_in_2_0_i               ;
  assign rckt_auto_int_local_in_1_0   = auto_int_local_in_1_0_i               ;
  assign rckt_auto_int_local_in_1_1   = auto_int_local_in_1_1_i               ;
  assign rckt_auto_int_local_in_0_0   = auto_int_local_in_0_0_i               ;

  assign auto_wfi_out_0_o             = rckt_auto_wfi_out_0                   ;

endmodule : PackedRocketTile