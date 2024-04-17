//////////// TL STRUCTS UNPACKED ////////////

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(64)            bits_mask   ;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt;
} TLreqA deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(64)            bits_mask   ;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqB deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqC deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(2)             bits_sink   ;
    Bit#(1)             bits_denied ;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqD deriving(Eq,Bits);

typedef struct {
    Bit#(2)             bits_sink   ;
} TLreqE deriving(Eq,Bits);

//////////// TL STRUCTS PACKED ////////////

typedef Bit#(SizeOf#(TLreqA)) TLreqApacked;
typedef Bit#(SizeOf#(TLreqB)) TLreqBpacked;
typedef Bit#(SizeOf#(TLreqC)) TLreqCpacked;
typedef Bit#(SizeOf#(TLreqD)) TLreqDpacked;
typedef Bit#(SizeOf#(TLreqE)) TLreqEpacked;