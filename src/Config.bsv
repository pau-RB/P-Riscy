import Types::*;

// Connectal (FPGA)
Bool cmr_ext_DEBUG = False;
Bool msg_ext_DEBUG = True;
Bool hex_ext_DEBUG = True;
Bool mem_ext_DEBUG = True;

// Verilog (SIM)
Bool perf_DEBUG    = False;

// MSG relay
typedef	512 MTHQ_LEN;
typedef	8   CTHQ_LEN;
Addr	msg_ADDR  = 'h3fff0;
Addr	hex_ADDR  = 'h3fff4;
Addr	msr_ADDR  = 'h3fff8;
Addr	max_ADDR  = 'h3fffc;

// Round Robin
Bool 	roundRobin = True;
typedef	1000 RR_INT;

// Main Token Queue
typedef 512 MTQ_LEN;
typedef 4   CTQ_LEN;

// Core width
typedef 8 FrontWidth;
typedef Bit#(TLog#(FrontWidth)) FrontID;
FrontID lastFrontID = fromInteger(valueOf(FrontWidth)-1);

typedef 3 BackWidth;

// L1I
typedef 32 L1ICacheRows;   // Must be power of 2

// LSU
typedef 32 LSUCacheRows;   // Must be power of 2
typedef 4 LSUCacheColumns; // Must be power of 2
Bool lsuAssociative = False;
typedef FrontWidth LSUmshrW;
typedef FrontWidth LSUmshrD;

// L2
typedef 64 L2CacheRows;       // Must be power of 2
typedef 4  L2CacheColumns;    // Must be power of 2
typedef 16 L2CacheHashBlocks; // Must be power of 2

// Verification
typedef Bit#(32) VerifID;

// Main Mem
typedef 15 RAMLatency;
