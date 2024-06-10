import Types::*;

// CMR buffer for verif (8M instructions)
typedef	8388608 CMRTHQ_LEN;

// MMIO
typedef	16 MTHQ_LEN;

`ifdef RCKT_MMIO
	Bool msg_ext_DEBUG = True;
	Bool hex_ext_DEBUG = True;
	Bool msr_ext_DEBUG = True;
	Bool ctr_ext_DEBUG = True;
	Addr msg_ADDR      = 32'h60000000;
	Addr hex_ADDR      = 32'h60000004;
	Addr msr_ADDR      = 32'h60000008;
	Addr ctr_ADDR      = 32'h6000000c;
`endif
