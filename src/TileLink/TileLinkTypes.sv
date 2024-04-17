//////////// TL STRUCTS UNPACKED ////////////

typedef struct {
    logic [2:0]   bits_opcode   ,
    logic [2:0]   bits_param    ,
    logic [3:0]   bits_size     ,
    logic [1:0]   bits_source   ,
    logic [31:0]  bits_address  , 
    logic [63:0]  bits_mask     ,
    logic [511:0] bits_data
} TLreqA;

typedef struct {
    logic [2:0]   bits_opcode   ,
    logic [1:0]   bits_param    ,
    logic [3:0]   bits_size     ,
    logic [1:0]   bits_source   ,
    logic [31:0]  bits_address  ,
    logic [63:0]  bits_mask     ,
    logic [511:0] bits_data     ,
    logic         bits_corrupt
} TLreqB;

typedef struct {
    logic         ready         ,
    logic         valid         ,
    logic [2:0]   bits_opcode   ,
    logic [2:0]   bits_param    ,
    logic [3:0]   bits_size     ,
    logic [1:0]   bits_source   ,
    logic [31:0]  bits_address  ,
    logic [511:0] bits_data
} TLreqC;

typedef struct {
    logic [2:0]   bits_opcode   ,
    logic [1:0]   bits_param    ,
    logic [3:0]   bits_size     ,
    logic [1:0]   bits_source   ,
    logic [1:0]   bits_sink     ,
    logic         bits_denied   ,
    logic [511:0] bits_data     ,
    logic         bits_corrupt
} TLreqD;

typedef struct {
    logic [1:0]   bits_sink
} TLreqE;

//////////// TL STRUCTS PACKED ////////////

typedef logic[$bits(TLreqA)-1] TLreqApacked;
typedef logic[$bits(TLreqB)-1] TLreqBpacked;
typedef logic[$bits(TLreqC)-1] TLreqCpacked;
typedef logic[$bits(TLreqD)-1] TLreqDpacked;
typedef logic[$bits(TLreqE)-1] TLreqEpacked;