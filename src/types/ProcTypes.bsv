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


//////////// STAGES ////////////

typedef struct {
    IType            iType;
    MulFunc          mulFunc;
    LoadFunc         ldFunc;
    StoreFunc        stFunc;
    Maybe#(RIndx)    dst;
    Data             data;
    Addr             addr;
    Bool             brTaken;
} ExecInst deriving(Bits, Eq, FShow);


// DECODE

typedef struct {
	Maybe#(Data)inst;
	Addr        pc;
	Epoch       epoch;
} DecToken deriving(Bits, Eq);

typedef struct {
	// iType
    IType         iType  ;
    AluFunc       aluFunc;
    MulFunc       mulFunc;
    BrFunc        brFunc ;
    LoadFunc      ldFunc ;
    StoreFunc     stFunc ;
    // Op
    Maybe#(RIndx) dst    ;
    Maybe#(RIndx) src1   ;
    Maybe#(RIndx) src2   ;
    Maybe#(Data)  imm    ;
} DecodedInst deriving(Bits, Eq, FShow);

// REGFETCH

typedef struct {
	Addr          pc     ;
	Epoch         epoch  ;
	Data          rawInst;
	// iType
	IType         iType  ;
	AluFunc       aluFunc;
	MulFunc       mulFunc;
	BrFunc        brFunc ;
	LoadFunc      ldFunc ;
	StoreFunc     stFunc ;
	// Op
	Maybe#(RIndx) dst    ;
	Maybe#(RIndx) src1   ;
	Maybe#(RIndx) src2   ;
	Maybe#(Data)  imm    ;
} RFToken deriving (Bits, Eq, FShow);

// EXECUTE

typedef struct {
	FrontID       feID   ;
	Addr          pc     ;
	Epoch         epoch  ;
	Data          rawInst;
	// iType
	IType         iType  ;
	AluFunc       aluFunc;
	MulFunc       mulFunc;
	BrFunc        brFunc ;
	LoadFunc      ldFunc ;
	StoreFunc     stFunc ;
	// Op
	Data          arg1   ;
	Data          arg2   ;
	Maybe#(Data)  imm    ;
	Maybe#(RIndx) dst    ;
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

//////////// SPECULATION INDICATIONS ////////////

function Bool isMemInst(ExecToken inst);
	return (inst.iType == Ld          || inst.iType == St    ||
	        inst.iType == Fork        || inst.iType == Forkr ||
	        inst.iType == Join        || inst.iType == Ghost );
endfunction

function Bool isArithInst(ExecToken inst);
	return (inst.iType == Unsupported || inst.iType == Alu   ||
	        inst.iType == Mul         || inst.iType == J     ||
	        inst.iType == Jr          || inst.iType == Br    ||
	        inst.iType == Auipc );
endfunction

function Bool isSpecInst(ExecToken inst);
	return (inst.iType == J           || inst.iType == Jr    ||
	        inst.iType == Fork        || inst.iType == Forkr ||
	        inst.iType == Br          || inst.iType == Ld    ||
	        inst.iType == St          || inst.iType == Join  );
endfunction

function Bool isFlowInst(ExecToken inst);
	return (inst.iType == J           || inst.iType == Jr    ||
	        inst.iType == Br);
endfunction