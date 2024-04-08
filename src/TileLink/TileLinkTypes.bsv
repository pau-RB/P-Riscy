typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(a)             bits_address;
    Bit#(w)             bits_mask   ;
    Bit#(TMul#(w, 8))   bits_data   ;
    Bit#(1)             bits_corrupt;
} TLreqA#(numeric type w, numeric type a) deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(a)             bits_address;
    Bit#(w)             bits_mask   ;
    Bit#(TMul#(w, 8))   bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqB#(numeric type w, numeric type a) deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(3)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(a)             bits_address;
    Bit#(TMul#(w, 8))   bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqC#(numeric type w, numeric type a)deriving(Eq,Bits);

typedef struct {
    Bit#(3)             bits_opcode ;
    Bit#(2)             bits_param  ;
    Bit#(4)             bits_size   ;
    Bit#(2)             bits_source ;
    Bit#(2)             bits_sink   ;
    Bit#(1)             bits_denied ;
    Bit#(TMul#(w, 8))   bits_data   ;
    Bit#(1)             bits_corrupt; 
} TLreqD#(numeric type w) deriving(Eq,Bits);

typedef struct {
    Bit#(2)             bits_sink   ;
} TLreqE deriving(Eq,Bits);