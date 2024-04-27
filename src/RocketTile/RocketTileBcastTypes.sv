//////////// RocketTile STRUCTS UNPACKED ////////////

typedef struct packed {
	logic[31:0]  bits_insns_0_iaddr    	;
	logic[31:0]  bits_insns_0_insn     	;
	logic[2:0]   bits_insns_0_priv     	;
	logic        bits_insns_0_exception	;
	logic        bits_insns_0_interrupt	;
	logic[31:0]  bits_insns_0_cause    	;
	logic[31:0]  bits_insns_0_tval     	;
	logic[63:0]  bits_time 				;
} rocket_bcast_t;

//////////// RocketTile STRUCTS PACKED ////////////

typedef logic[$bits(rocket_bcast_t)-1:0] rocket_bcast_packed_t;