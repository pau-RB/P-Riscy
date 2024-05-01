//////////// RocketTile STRUCTS UNPACKED ////////////

typedef struct {
    Bit#(1)  bits_insns_0_valid    ;
    Bit#(32) bits_insns_0_iaddr    ;
    Bit#(32) bits_insns_0_insn     ; 
    Bit#(3)  bits_insns_0_priv     ; 
    Bit#(1)  bits_insns_0_exception;
    Bit#(1)  bits_insns_0_interrupt;
    Bit#(32) bits_insns_0_cause    ;
    Bit#(32) bits_insns_0_tval     ;
    Bit#(64) bits_time             ;
} RocketBcast deriving(Eq,Bits,FShow);

//////////// RocketTile STRUCTS PACKED ////////////

typedef Bit#(SizeOf#(RocketBcast)) RocketBcastPacked;