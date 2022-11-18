import Types::*;

// Connectal (FPGA)
Bool wb_ext_DEBUG  = False;
Bool msg_ext_DEBUG = True;

// Verilog (SIM)
Bool msg_DEBUG     = False;
Bool perf_DEBUG    = False;

// MSG relay
typedef	80 THQ_LEN;
Addr	msg_ADDR  = 'h0fff0;
Addr	max_ADDR  = 'h3fffc;

// Round Robin
Bool 	roundRobin = True;
typedef	100 RR_INT;

// Main Token Queue
typedef 16 MTQ_LEN;

// Core width
typedef 4 FrontWidth;
typedef Bit#(TLog#(FrontWidth)) FrontID;
FrontID lastFrontID = fromInteger(valueOf(FrontWidth)-1);

// LSU
typedef 8 LSUCacheRows;    // Must be power of 2
typedef 4 LSUCacheColumns; // Must be power of 2
Bool lsuAssociative = True;

// Verification
typedef Bit#(32) VerifID;

// Main Mem
typedef 15 RAMLatency;