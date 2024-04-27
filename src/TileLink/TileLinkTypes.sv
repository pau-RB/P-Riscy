//////////// TL STRUCTS UNPACKED ////////////

typedef struct packed {
    logic [2:0]   bits_opcode   ;
    logic [2:0]   bits_param    ;
    logic [3:0]   bits_size     ;
    logic [1:0]   bits_source   ;
    logic [31:0]  bits_address  ;
    logic [63:0]  bits_mask     ;
    logic [511:0] bits_data     ;
} TLreqA_t;

typedef struct packed {
    logic [2:0]   bits_opcode   ;
    logic [1:0]   bits_param    ;
    logic [3:0]   bits_size     ;
    logic [1:0]   bits_source   ;
    logic [31:0]  bits_address  ;
    logic [63:0]  bits_mask     ;
    logic [511:0] bits_data     ;
    logic         bits_corrupt  ;
} TLreqB_t;

typedef struct packed {
    logic [2:0]   bits_opcode   ;
    logic [2:0]   bits_param    ;
    logic [3:0]   bits_size     ;
    logic [1:0]   bits_source   ;
    logic [31:0]  bits_address  ;
    logic [511:0] bits_data     ;
} TLreqC_t;

typedef struct packed {
    logic [2:0]   bits_opcode   ;
    logic [1:0]   bits_param    ;
    logic [3:0]   bits_size     ;
    logic [1:0]   bits_source   ;
    logic [1:0]   bits_sink     ;
    logic         bits_denied   ;
    logic [511:0] bits_data     ;
    logic         bits_corrupt  ;
} TLreqD_t;

typedef struct packed {
    logic [1:0]   bits_sink     ;
} TLreqE_t;

//////////// TL STRUCTS PACKED ////////////

typedef logic[$bits(TLreqA_t)-1:0] TLreqApacked_t;
typedef logic[$bits(TLreqB_t)-1:0] TLreqBpacked_t;
typedef logic[$bits(TLreqC_t)-1:0] TLreqCpacked_t;
typedef logic[$bits(TLreqD_t)-1:0] TLreqDpacked_t;
typedef logic[$bits(TLreqE_t)-1:0] TLreqEpacked_t;
