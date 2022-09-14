import Types::*;
import ProcTypes::*;

typedef struct {
	Instruction inst;
	Addr        pc;
} DecToken deriving(Bits, Eq);

typedef struct {
	DecodedInst inst;
	Data        arg1;
	Data        arg2;
	Addr        pc;
} ExecToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
} MemToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
} WBToken deriving (Bits, Eq);

typedef struct {
	Addr pc;	
} ContToken deriving (Bits, Eq);
