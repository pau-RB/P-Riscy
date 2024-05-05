//////////// TL OPCODES ////////////

typedef enum {
    PutFullData     = 0,
    PutPartialData  = 1,
    ArithmeticData  = 2,
    LogicalData     = 3,
    Get             = 4,
    Hint            = 5,
    AcquireBlock    = 6,
    AcquirePerm     = 7
} TLopcodeA deriving(Bits, Eq, FShow);

typedef enum {
    PutFullData     = 0,
    PutPartialData  = 1,
    ArithmeticData  = 2,
    LogicalData     = 3,
    Get             = 4,
    Hint            = 5,
    ProbeBlock      = 6,
    ProbePerm       = 7
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

//////////// TL Permissions Transitions ////////////

typedef enum {
    NtoB            = 0,
    NtoT            = 1,
    BtoT            = 2,
    Illegal3        = 3,
    Illegal4        = 4,
    Illegal5        = 5,
    Illegal6        = 6,
    Illegal7        = 7
} TLparamA deriving(Bits, Eq, FShow);

typedef enum {
    ToT             = 0,
    ToB             = 1,
    ToN             = 2,
    Illegal3        = 3
} TLparamB deriving(Bits, Eq, FShow);

typedef enum {
    TtoB            = 0,
    TtoN            = 1,
    BtoN            = 2,
    TtoT            = 3,
    BtoB            = 4,
    NtoN            = 5,
    Illegal6        = 6,
    Illegal7        = 7
} TLparamC deriving(Bits, Eq, FShow);

typedef enum {
    ToT             = 0,
    ToB             = 1,
    ToN             = 2,
    Illegal3        = 3
} TLparamD deriving(Bits, Eq, FShow);

//////////// TL STRUCTS UNPACKED ////////////

typedef struct {
    TLopcodeA           opcode ;
    TLparamA            param  ;
    Bit#(4)             size   ;
    Bit#(2)             source ;
    Bit#(32)            address;
    Bit#(64)            mask   ;
    Bit#(512)           data   ;
} TLreqA deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeB           opcode ;
    TLparamB            param  ;
    Bit#(4)             size   ;
    Bit#(2)             source ;
    Bit#(32)            address;
    Bit#(64)            mask   ;
    Bit#(512)           data   ;
    Bit#(1)             corrupt;
} TLreqB deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeC           opcode ;
    TLparamC            param  ;
    Bit#(4)             size   ;
    Bit#(2)             source ;
    Bit#(32)            address;
    Bit#(512)           data   ;
} TLreqC deriving(Eq,Bits,FShow);

typedef struct {
    TLopcodeD           opcode ;
    TLparamD            param  ;
    Bit#(4)             size   ;
    Bit#(2)             source ;
    Bit#(2)             sink   ;
    Bit#(1)             denied ;
    Bit#(512)           data   ;
    Bit#(1)             corrupt;
} TLreqD deriving(Eq,Bits,FShow);

typedef struct {
    Bit#(2)             sink   ;
} TLreqE deriving(Eq,Bits,FShow);

//////////// TL STRUCTS PACKED ////////////

typedef Bit#(SizeOf#(TLreqA)) TLreqApacked;
typedef Bit#(SizeOf#(TLreqB)) TLreqBpacked;
typedef Bit#(SizeOf#(TLreqC)) TLreqCpacked;
typedef Bit#(SizeOf#(TLreqD)) TLreqDpacked;
typedef Bit#(SizeOf#(TLreqE)) TLreqEpacked;