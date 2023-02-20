import Types::*;
import Config::*;

//////////// FRONTEND ////////////

typedef enum {
	Full,
	Evict,
	Ghost,
	Dry,
	Empty
} StreamStatus deriving(Bits, Eq, FShow);

typedef Bit#(5) RIndx;

typedef enum {
	Unsupported, 
	Alu, 
	Mul,
	Ld, 
	St, 
	Fork,
	Forkr,
	Join,
	J,  
	Jr, 
	Br, 
	Auipc,
	Ghost
} IType deriving(Bits, Eq, FShow);

typedef enum {
	Eq, 
	Neq, 
	Lt, 
	Ltu, 
	Ge, 
	Geu, 
	AT, 
	NT
} BrFunc deriving(Bits, Eq, FShow);

typedef enum {
	Add, 
	Sub, 
	And, 
	Or, 
	Xor, 
	Slt, 
	Sltu, 
	Sll, 
	Sra, 
	Srl
} AluFunc deriving(Bits, Eq, FShow);

typedef enum {
	Mul,
	Mulh,
	Mulhsu,
	Mulhu,
	Div,
	Divu,
	Rem,
	Remu
} MulFunc deriving(Bits, Eq, FShow);

typedef struct {
    IType            iType;
    AluFunc          aluFunc;
    MulFunc          mulFunc;
    BrFunc           brFunc;
    LoadFunc         ldFunc;
    StoreFunc        stFunc;
    Maybe#(RIndx)    dst;
    Maybe#(RIndx)    src1;
    Maybe#(RIndx)    src2;
    Maybe#(Data)     imm;
} DecodedInst deriving(Bits, Eq, FShow);

//////////// BACKEND ////////////

typedef struct {
    IType            iType;
    MulFunc          mulFunc;
    LoadFunc         ldFunc;
    StoreFunc        stFunc;
    Maybe#(RIndx)    dst;
    Data             data;
    Addr             addr;
    Bool             mispredict;
    Bool             brTaken;
} ExecInst deriving(Bits, Eq, FShow);

typedef struct {
	Maybe#(Data)inst;
	Addr        pc;
	Epoch       epoch;
} DecToken deriving(Bits, Eq);

typedef struct {
	DecodedInst inst;
	Addr        pc;
	Epoch       epoch;
	Data        rawInst;
} RFToken deriving (Bits, Eq, FShow);

typedef struct {
	DecodedInst inst;
	Data        arg1;
	Data        arg2;
	Addr        pc;
	FrontID     feID;
	Epoch       epoch;
	Data        rawInst;
} ExecToken deriving (Bits, Eq, FShow);

typedef struct {
	ExecInst    inst;
	Addr        pc;
	FrontID     feID;
	Epoch       epoch;
	Data        rawInst;
} MemToken deriving (Bits, Eq, FShow);

typedef struct {
	ExecInst    inst;
	Addr        pc;
	FrontID     feID;
	Epoch       epoch;
	Data        rawInst;
} WBToken deriving (Bits, Eq, FShow);

typedef struct {
	Bool        lock;
	Bool        dry;
	Bool        kill;
	Bool        redirect;
	Epoch       epoch;
	Addr        nextPc;
} Redirect deriving (Bits, Eq, FShow);

typedef struct {
	RIndx       dst;
	Data        res;
} RFwb deriving (Bits, Eq, FShow);

typedef struct {
	VerifID   verifID;
	Addr      pc;
	CacheLine rfL;
	CacheLine rfH;
} ContToken deriving(Bits, Eq);