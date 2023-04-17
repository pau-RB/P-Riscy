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
	Div,
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
	Mulhu
} MulFunc deriving(Bits, Eq, FShow);

typedef enum {
	Div,
	Divu,
	Rem,
	Remu
} DivFunc deriving(Bits, Eq, FShow);


//////////// STAGES ////////////

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
    DivFunc       divFunc;
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
	`ifdef DEBUG_RAW_INST
	Data          rawInst;
	`endif
	// iType
	IType         iType  ;
	AluFunc       aluFunc;
	MulFunc       mulFunc;
	DivFunc       divFunc;
	BrFunc        brFunc ;
	LoadFunc      ldFunc ;
	StoreFunc     stFunc ;
	// Op
	Maybe#(RIndx) dst    ;
	Maybe#(RIndx) src1   ;
	Maybe#(RIndx) src2   ;
	Maybe#(Data)  imm    ;
} RFToken deriving (Bits, Eq, FShow);

// EXECUTE 1

typedef struct {
	FrontID       feID   ;
	Addr          pc     ;
	Epoch         epoch  ;
	`ifdef DEBUG_RAW_INST
	Data          rawInst;
	`endif
	// iType
	IType         iType  ;
	AluFunc       aluFunc;
	MulFunc       mulFunc;
	DivFunc       divFunc;
	BrFunc        brFunc ;
	LoadFunc      ldFunc ;
	StoreFunc     stFunc ;
	// Op
	Data          arg1   ;
	Data          arg2   ;
	Maybe#(Data)  imm    ;
	Maybe#(RIndx) dst    ;
} ExecToken deriving (Bits, Eq, FShow);

// EXECUTE 2

typedef struct {
	FrontID       feID   ;
	Epoch         epoch  ;
	`ifdef DEBUG_RAW_INST
	Addr          pc     ;
	Data          rawInst;
	`endif
	// iType
	IType         iType  ;
	MulFunc       mulFunc;
	DivFunc       divFunc;
	LoadFunc      ldFunc ;
	StoreFunc     stFunc ;
	// Op
	Data          res    ;
	Addr          addr   ;
	Addr          nextpc ;
	Bool          brTaken;
	Maybe#(RIndx) dst    ;
} MemToken deriving (Bits, Eq, FShow);

// COMMIT

typedef struct {
	FrontID       feID   ;
	Epoch         epoch  ;
	`ifdef DEBUG_RAW_INST
	Addr          pc     ;
	Data          rawInst;
	`endif
	// iType
	IType         iType  ;
	MulFunc       mulFunc;
	DivFunc       divFunc;
	// Op
	Data          res    ;
	Data          addr   ;
	Addr          nextpc ;
	Bool          brTaken;
	Maybe#(RIndx) dst    ;
} ComToken deriving (Bits, Eq, FShow);

// OLD COMMIT

typedef struct {
	`ifdef DEBUG_CYC
	FrontID       feID   ;
	`endif
	`ifdef DEBUG_CMR
	Addr          pc     ;
	`endif
	`ifdef  DEBUG_RAW_INST
	Data          rawInst;
	`endif
	// iType
	IType         iType  ;
	// Op
	`ifdef DEBUG_CMR
	Data          addr   ;
	`endif
	RIndx         dst    ;
} OldToken deriving (Bits, Eq, FShow);

// REDIRECT

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
	Bool        rmv;
	Bool        clr;
} RFwb deriving (Bits, Eq, FShow);

//////////// SPECULATION INDICATIONS ////////////

// Must be executed by an arithmetic lane
function Bool isMemInst(IType inst);
	return (inst == Ld          || inst == St    ||
	        inst == Fork        || inst == Forkr ||
	        inst == Join        || inst == Ghost );
endfunction

// Must be executed by a memory lane
function Bool isArithInst(IType inst);
	return (inst == Unsupported || inst == Alu   ||
	        inst == Mul         || inst == Div   ||
	        inst == J           || inst == Jr    ||
	        inst == Br          || inst == Auipc );
endfunction

// May cause a redirect
function Bool isSpecInst(IType inst);
	return (inst == J           || inst == Jr    ||
	        inst == Fork        || inst == Forkr ||
	        inst == Br          || inst == Ld    ||
	        inst == St          || inst == Join  );
endfunction

// Will likely cause a redirect
function Bool isFlowInst(IType inst);
	return (inst == J           || inst == Jr    ||
	        inst == Br);
endfunction