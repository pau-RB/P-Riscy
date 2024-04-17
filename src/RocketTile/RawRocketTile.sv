import TileLinkTypes::*;

module RawRocketTile(
  input  logic        clock                     ,
  input  logic        reset_ni                  ,
  input  logic        auto_hartid_in            ,
  
  input  logic        auto_buffer_out_a_ready   ,
  output logic        auto_buffer_out_a_valid   ,
  output TLreqApacked auto_buffer_out_a_beat    ,

  output logic        auto_buffer_out_b_ready   ,
  input  logic        auto_buffer_out_b_valid   ,
  input  TLreqBpacked auto_buffer_out_b_beat    ,

  input  logic        auto_buffer_out_c_ready   ,
  output logic        auto_buffer_out_c_valid   ,
  output TLreqCpacked auto_buffer_out_c_beat    ,

  output logic        auto_buffer_out_d_ready   ,
  input  logic        auto_buffer_out_d_valid   ,
  input  TLreqDpacked auto_buffer_out_d_beat    ,

  input  logic        auto_buffer_out_e_ready   ,
  input  logic        auto_buffer_out_e_valid   ,
  output TLreqEpacked auto_buffer_out_e_beat    ,

  output logic        auto_broadcast_out_insns_0_valid    ,
  output logic[31:0]  auto_broadcast_out_insns_0_iaddr    ,
  output logic[31:0]  auto_broadcast_out_insns_0_insn     ,
  output logic[2:0]   auto_broadcast_out_insns_0_priv     ,
  output logic        auto_broadcast_out_insns_0_exception,
  output logic        auto_broadcast_out_insns_0_interrupt,
  output logic[31:0]  auto_broadcast_out_insns_0_cause    ,
  output logic[31:0]  auto_broadcast_out_insns_0_tval     ,
  output logic[63:0]  auto_broadcast_out_time             ,

  input  logic        auto_int_local_in_2_0     ,
  input  logic        auto_int_local_in_1_0     ,
  input  logic        auto_int_local_in_1_1     ,
  input  logic        auto_int_local_in_0_0     ,

  output logic        auto_wfi_out_0

);

endmodule : RawRocketTile