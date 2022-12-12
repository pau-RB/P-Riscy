/*

Copyright (C) 2012

Arvind <arvind@csail.mit.edu>
Muralidaran Vijayaraghavan <vmurali@csail.mit.edu>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/


import Types::*;
import Config::*;
import FShow::*;

// general purpose reg index
typedef Bit#(5) RIndx;

// opcode
typedef Bit#(7) Opcode;
Opcode opLoad    = 7'b0000011;
Opcode opFork    = 7'b0001011;
Opcode opMiscMem = 7'b0001111;
Opcode opOpImm   = 7'b0010011;
Opcode opAuipc   = 7'b0010111;
Opcode opStore   = 7'b0100011;
Opcode opAmo     = 7'b0101111;
Opcode opOp      = 7'b0110011;
Opcode opLui     = 7'b0110111;
Opcode opBranch  = 7'b1100011;
Opcode opJalr    = 7'b1100111;
Opcode opJal     = 7'b1101111;
Opcode opSystem  = 7'b1110011;

// SCALL, SBREAK not implemented

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

typedef void Exception;

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

typedef struct {
    IType            iType;
    LoadFunc         ldFunc;
    StoreFunc        stFunc;
    Maybe#(RIndx)    dst;
    Data             data;
    Addr             addr;
    Bool             mispredict;
    Bool             brTaken;
} ExecInst deriving(Bits, Eq, FShow);

typedef struct {
	Data             arg1;
	Data             arg2;
	Long             partial;
	MulFunc          mulFunc;
} MultInst deriving(Bits, Eq, FShow);

// function code
// ALU
Bit#(3) fnADD   = 3'b000;
Bit#(3) fnSLL   = 3'b001;
Bit#(3) fnSLT   = 3'b010;
Bit#(3) fnSLTU  = 3'b011;
Bit#(3) fnXOR   = 3'b100;
Bit#(3) fnSR    = 3'b101;
Bit#(3) fnOR    = 3'b110;
Bit#(3) fnAND   = 3'b111;
// FORK/JOIN
Bit#(5) fnFork  = 5'b00000;
Bit#(5) fnForkr = 5'b00001;
Bit#(5) fnJoin  = 5'b00010;
// M
Bit#(3) fnMUL   = 3'b000;
Bit#(3) fnMULH  = 3'b001;
Bit#(3) fnMULHSU= 3'b010;
Bit#(3) fnMULHU = 3'b011;
Bit#(3) fnDIV   = 3'b100;
Bit#(3) fnDIVU  = 3'b101;
Bit#(3) fnREM   = 3'b110;
Bit#(3) fnREMU  = 3'b111;
// Branch
Bit#(3) fnBEQ   = 3'b000;
Bit#(3) fnBNE   = 3'b001;
Bit#(3) fnBLT   = 3'b100;
Bit#(3) fnBGE   = 3'b101;
Bit#(3) fnBLTU  = 3'b110;
Bit#(3) fnBGEU  = 3'b111;
// Load
Bit#(3) fnLW    = 3'b010;
Bit#(3) fnLB    = 3'b000;
Bit#(3) fnLH    = 3'b001;
Bit#(3) fnLBU   = 3'b100;
Bit#(3) fnLHU   = 3'b101;
// Store
Bit#(3) fnSW    = 3'b010;
Bit#(3) fnSB    = 3'b000;
Bit#(3) fnSH    = 3'b001;
// Amo
Bit#(5) fnLR    = 5'b00010;
Bit#(5) fnSC    = 5'b00011;
//MiscMem
Bit#(3) fnFENCE  = 3'b000;
//Bit#(3) fnFENCEI = 3'b001;
// System
Bit#(3) fnPRIV   = 3'b000;
Bit#(12) privSCALL    = 12'h000;

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
	MultInst    mul;
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