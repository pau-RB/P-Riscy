import Types::*;

// Connectal (FPGA)
Bool cmr_ext_DEBUG = False;
Bool msg_ext_DEBUG = True;
Bool mem_ext_DEBUG = True;

// Verilog (SIM)
Bool perf_DEBUG    = False;

// MSG relay
typedef	512 MTHQ_LEN;
typedef	8   CTHQ_LEN;
Addr	msg_ADDR  = 'h3fff0;
Addr	lsu_ADDR  = 'h3fff4;
Addr	max_ADDR  = 'h3fffc;

// Round Robin
Bool 	roundRobin = True;
typedef	1000 RR_INT;

// Main Token Queue
typedef 512 MTQ_LEN;
typedef 4   CTQ_LEN;

// Core width
typedef 4 FrontWidth;
typedef Bit#(TLog#(FrontWidth)) FrontID;
FrontID lastFrontID = fromInteger(valueOf(FrontWidth)-1);

typedef 2 BackWidth;

// L1I
typedef 32 L1ICacheRows;   // Must be power of 2

// LSU
typedef 8 LSUCacheRows;    // Must be power of 2
typedef 4 LSUCacheColumns; // Must be power of 2
Bool lsuAssociative = True;
typedef FrontWidth LSUmshrW;
typedef FrontWidth LSUmshrD;

// Verification
typedef Bit#(32) VerifID;

// Main Mem
typedef 15 RAMLatency;