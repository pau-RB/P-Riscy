import Types::*;

// Connectal (FPGA)
Bool wb_ext_DEBUG  = True;
Bool msg_ext_DEBUG = True;

// Verilog (SIM)
Bool wb_DEBUG      = False;
Bool msg_DEBUG     = False;
Bool perf_DEBUG    = False;

// MSG relay
typedef  80 THQ_LEN;
Addr     msg_ADDR  = 'h10000;
Addr     max_ADDR  = 'h3fffc;

// Main Token Queue
typedef 10 MTQ_LEN;

// Core width
typedef 4 FrontWidth;
typedef Bit#(TLog#(FrontWidth)) FrontID;

// Verification
typedef Bit#(32) VerifID;