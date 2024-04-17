//////////// RocketTile instruction reporting ifc ////////////

interface RocketTileBcastIfc;

  method Bit#(1)  get_auto_broadcast_out_insns_0_valid    ();
  method Bit#(32) get_auto_broadcast_out_insns_0_iaddr    ();
  method Bit#(32) get_auto_broadcast_out_insns_0_insn     (); 
  method Bit#(3)  get_auto_broadcast_out_insns_0_priv     (); 
  method Bit#(1)  get_auto_broadcast_out_insns_0_exception();
  method Bit#(1)  get_auto_broadcast_out_insns_0_interrupt();
  method Bit#(32) get_auto_broadcast_out_insns_0_cause    ();
  method Bit#(32) get_auto_broadcast_out_insns_0_tval     ();
  method Bit#(64) get_auto_broadcast_out_time             ();

endinterface : RocketTileBcastIfc
