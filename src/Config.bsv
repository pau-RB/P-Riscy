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
Addr	msg_ADDR  = 32'h7ffff000;
Addr	hex_ADDR  = 32'h7ffff004;
Addr	msr_ADDR  = 32'h7ffff008;
Addr	max_ADDR  = 32'h80000000;

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
typedef 64 L1ICacheRows;    // Must be power of 2
typedef 2  L1ICacheColumns; // Must be power of 2
Bool l1IAssociative = False;

// LSU
typedef 64 LSUCacheRows;    // Must be power of 2
typedef 2  LSUCacheColumns; // Must be power of 2
Bool lsuAssociative = False;
typedef FrontWidth LSUmshrW;
typedef FrontWidth LSUmshrD;

// L2
typedef 256 L2CacheRows;       // Must be power of 2
typedef 4   L2CacheColumns;    // Must be power of 2
typedef 16  L2CacheHashBlocks; // Must be power of 2

// Verification
typedef Bit#(32) VerifID;

// Main Mem
typedef 15 RAMLatency;
