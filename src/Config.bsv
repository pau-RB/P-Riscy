import Types::*;

// MMIO
typedef	16 MTHQ_LEN;

`ifdef MMIO
	Bool msg_ext_DEBUG = True;
	Bool hex_ext_DEBUG = True;
	Bool msr_ext_DEBUG = True;
	Addr msg_ADDR      = 32'h7ffff000;
	Addr hex_ADDR      = 32'h7ffff004;
	Addr msr_ADDR      = 32'h7ffff008;
`endif

Addr max_ADDR  = 32'h80000000;

// Main Token Queue
typedef 512 MTQ_LEN;

// Core width
typedef 8 FrontWidth;
typedef Bit#(TLog#(FrontWidth)) FrontID;
FrontID lastFrontID = fromInteger(valueOf(FrontWidth)-1);

typedef 3 BackWidth;

// L1I
typedef 256 L1ICacheRows;       // Must be power of 2
typedef 1   L1ICacheColumns;    // Must be power of 2

// L1D
typedef 512 L1DCacheRows;       // Must be power of 2
typedef 1   L1DCacheColumns;    // Must be power of 2
typedef 256 L1DCacheHashBlocks; // Must be power of 2

// L2
`ifdef L2SC
typedef 512  L2CacheRows;       // Must be power of 2
typedef 4    L2CacheColumns;    // Must be power of 2
typedef 16   L2CacheHashBlocks; // Must be power of 2
`endif

// Main Mem
typedef 100 SimDDRLatency;
typedef 100 VCUDDRLatency;
