//////////// TL OPCODES ////////////

typedef enum {
    PutFullData     = 0,
    PutPartialData  = 1,
    ArithmeticData  = 2,
    LogicalData     = 3,
    Get             = 4,
    Intent          = 5,
    Acquire         = 6,
    Illegal7        = 7
} TLopcodeA deriving(Bits, Eq, FShow);

typedef enum {
    PutFullData     = 0,
    PutPartialData  = 1,
    ArithmeticData  = 2,
    LogicalData     = 3,
    Get             = 4,
    Intent          = 5,
    Probe           = 6,
    Illegal7        = 7
} TLopcodeB deriving(Bits, Eq, FShow);

typedef enum {
    AccessAck       = 0,
    AccessAckData   = 1,
    HintAck         = 2,
    Illegal3        = 3,
    ProbeAck        = 4,
    ProbeAckData    = 5,
    Release         = 6,
    ReleaseData     = 7
} TLopcodeC deriving(Bits, Eq, FShow);

typedef enum {
    AccessAck       = 0,
    AccessAckData   = 1,
    HintAck         = 2,
    Illegal3        = 3,
    Grant           = 4,
    GrantData       = 5,
    ReleaseAck      = 6,
    Illegal7        = 7
} TLopcodeD deriving(Bits, Eq, FShow);

// TLopcodeE = GrantAck

//////////// TL STRUCTS UNPACKED ////////////

typedef struct {
    TLopcodeA           bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(64)            bits_mask   ;
    Bit#(512)           bits_data   ;
} TLreqA deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeB           bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(64)            bits_mask   ;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt;
} TLreqB deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeC           bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(32)            bits_address;
    Bit#(512)           bits_data   ;
} TLreqC deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeD           bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(2)             bits_sink   ;
    Bit#(1)             bits_denied ;
    Bit#(512)           bits_data   ;
    Bit#(1)             bits_corrupt;
} TLreqD deriving(Eq,Bits,FShow);

typedef struct {
    Bit#(2)             bits_sink   ;
} TLreqE deriving(Eq,Bits,FShow);

//////////// TL STRUCTS PACKED ////////////

typedef Bit#(SizeOf#(TLreqA)) TLreqApacked;
typedef Bit#(SizeOf#(TLreqB)) TLreqBpacked;
typedef Bit#(SizeOf#(TLreqC)) TLreqCpacked;
typedef Bit#(SizeOf#(TLreqD)) TLreqDpacked;
typedef Bit#(SizeOf#(TLreqE)) TLreqEpacked;