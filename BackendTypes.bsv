import Types::*;
import ProcTypes::*;

typedef struct {
	Instruction inst;
	Addr        pc;
	Bool        epoch;
} DecToken deriving(Bits, Eq);

typedef struct {
	DecodedInst inst;
	Data        arg1;
	Data        arg2;
	Addr        pc;
	Bool        epoch;
} ExecToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
	Bool        epoch;
} MemToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
	Bool        epoch;
} WBToken deriving (Bits, Eq);

typedef struct {
	Addr        redirect;
	Bool        epoch;
} ContToken deriving (Bits, Eq);
