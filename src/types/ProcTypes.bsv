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
	LB,
	LH,
	LW,
	LBU,
	LHU
} LoadFunc deriving(Bits, Eq, FShow);

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
	Data        inst;
	Addr        pc;
	Bool        ghost;
	Bool        epoch;
} DecToken deriving(Bits, Eq);

typedef struct {
	DecodedInst inst;
	Addr        pc;
	Bool        epoch;
	Data        rawInst;
} RFToken deriving (Bits, Eq);

typedef struct {
	DecodedInst inst;
	Data        arg1;
	Data        arg2;
	Addr        pc;
	FrontID     feID;
	Bool        epoch;
	Data        rawInst;
} ExecToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
	Addr        pc;
	FrontID     feID;
	Bool        epoch;
	Data        rawInst;
} MemToken deriving (Bits, Eq);

typedef struct {
	ExecInst    inst;
	Addr        pc;
	FrontID     feID;
	Bool        epoch;
	Data        rawInst;
} WBToken deriving (Bits, Eq, FShow);

typedef struct {
    Addr  pc;
    Bool  epoch;
    Addr  nextPc;
    IType brType;
    Bool  taken;
    Bool  mispredict;
} Redirect deriving (Bits, Eq, FShow);

typedef struct {
	VerifID   verifID;
	Addr      pc;
	CacheLine rfL;
	CacheLine rfH;
} ContToken deriving(Bits, Eq);

typedef struct {
	Data    cycle;
	VerifID verifID;
	Addr    pc;
	Data  	rawInst;
	IType 	iType;
	RIndx 	wbDst;   // 0 if no wb
	Data  	wbRes;   // ALU/Load result, childverifID for fork/forkr, memread for Join
	Addr  	addr;    // nextpc for branch, addr for LSU, nextpc for fork/forkr
} CommitReport deriving (Bits, Eq);

typedef struct {
	VerifID verifID;
	Data    cycle;
	Data    commit;
	Data	data;
} Message deriving (Bits, Eq);

function Bool dataHazard(Maybe#(RIndx) src1, Maybe#(RIndx) src2, Maybe#(RIndx) dst);
    return (isValid(dst) && ((isValid(src1) && fromMaybe(?, dst)==fromMaybe(?, src1)) ||
                             (isValid(src2) && fromMaybe(?, dst)==fromMaybe(?, src2))));
endfunction

// pretty print instuction
function Fmt showInst(Instruction inst);
	Fmt ret = $format("");

	Opcode opcode = inst[  6 :  0 ];
	let rd     = inst[ 11 :  7 ];
	let funct3 = inst[ 14 : 12 ];
	let rs1    = inst[ 19 : 15 ];
	let rs2    = inst[ 24 : 20 ];
	let funct7 = inst[ 31 : 25 ];
	let aluSel = inst[30]; // select between Add/Sub, Srl/Sra

	Bit#(32) immI   = signExtend(inst[31:20]);
	Bit#(32) immS   = signExtend({ inst[31:25], inst[11:7] });
	Bit#(32) immB   = signExtend({ inst[31], inst[7], inst[30:25], inst[11:8], 1'b0});
	Bit#(32) immU   = { inst[31:12], 12'b0 };
	Bit#(32) immJ   = signExtend({ inst[31], inst[19:12], inst[20], inst[30:25], inst[24:21], 1'b0});

	case (opcode)
		opOpImm: begin
			ret = case (funct3)
				fnADD: $format("addi");
				fnSLT: $format("slti");
				fnSLTU: $format("sltiu");
				fnAND: $format("andi");
				fnOR: $format("ori");
				fnXOR: $format("xori");
				fnSLL: (( funct7          != '0) ? $format("unsupport OpImm 0x%0x", inst) : $format("slli"));
				fnSR:  (((funct7 & 7'h5F) != '0) ? $format("unsupport OpImm 0x%0x", inst) : (aluSel == 0 ? $format("srli") : $format("srai")));
				default: $format("unsupport OpImm 0x%0x", inst);
			endcase;
			ret = ret + $format(" r%d = r%d ", rd, rs1);
			ret = ret + (case (funct3)
				fnSLL, fnSR: $format("0x%0x", immI[4:0]); // only low 5 bits for shift
				default: $format("0x%0x", immI);
			endcase);
		end

		opOp: begin
			ret = case (funct7)
				7'h00: begin
					case (funct3)
						fnADD:  $format("add");
						fnSLT:  $format("slt");
						fnSLTU: $format("sltu");
						fnAND:  $format("and");
						fnOR:   $format("or");
						fnXOR:  $format("xor");
						fnSLL:  $format("sll");
						fnSR:   $format("srl");
						default: $format("unsupport Op 0x%0x", inst);
					endcase
				end
				7'h20: begin
					case (funct3)
						fnADD:  $format("sub");
						fnSR:   $format("sra");
						default: $format("unsupport Op 0x%0x", inst);
					endcase
				end
				7'h01: begin
					case (funct3)
						fnMUL:    $format("mul");
						fnMULH:   $format("mulh");
						fnMULHSU: $format("mulhsu");
						fnMULHU:  $format("mulhu");
						fnDIV:    $format("div");
						fnDIVU:   $format("divu");
						fnREM:    $format("rem");
						fnREMU:   $format("remu");
						default: $format("unsupport Op 0x%0x", inst);
					endcase
				end
				default: $format("unsupport Op 0x%0x", inst);
			endcase;
			ret = ret + $format(" r%d = r%d r%d", rd, rs1, rs2);
		end

		opLui: begin
			ret = $format("lui r%d 0x%0x", rd, immU);
		end

		opAuipc: begin
			ret = $format("auipc r%d 0x%0x", rd, immU);
		end

		opFork: begin
			ret = $format("fork 0x%0x", immJ);
		end

		opJal: begin
			ret = $format("jal r%d 0x%0x", rd, immJ);
		end

		opJalr: begin
			ret = $format("jalr r%d [r%d 0x%0x]", rd, rs1, immI);
		end

		opBranch: begin
			ret = case(funct3)
				fnBEQ: $format("beq");
				fnBNE: $format("bne");
				fnBLT: $format("blt");
				fnBLTU: $format("bltu");
				fnBGE: $format("bge");
				fnBGEU: $format("bgeu");
				default: $format("unsupport Branch 0x%0x", inst);
			endcase;
			ret = ret + $format(" r%d r%d 0x%0x", rs1, rs2, immB);
		end

		opLoad: begin
			ret = case(funct3)
				fnLW:  $format("lw");
				fnLB:  $format("lb");
				fnLH:  $format("lh");
				fnLBU: $format("lbu");
				fnLHU: $format("lhu");
				default: $format("unsupport Load 0x%0x", inst);
			endcase;
			ret = ret + $format(" r%d = [r%d 0x%0x]", rd, rs1, immI);
		end

		opStore: begin
			ret = case(funct3)
				fnSW: $format("sw");
				fnSB: $format("sb");
				fnSH: $format("sh");
				default: $format("unsupport Store 0x%0x", inst);
			endcase;
			ret = ret + $format(" [r%d 0x%0x] = r%d", rs1, immS, rs2);
		end

		opMiscMem: begin
			ret = case (funct3)
				//fnFENCE: $format("fence");
				//fnFENCEI: $format("fence.i");
				default: $format("unsupport MiscMem 0x%0x", inst);
			endcase;
		end

		opAmo: begin
			ret = $format("unsupport Amo 0x%0x", inst);
		end

		opSystem: begin
			case (funct3)
				fnPRIV: begin
					ret = case (truncate(immI))
						//privSCALL: $format("scall");
						default: $format("unsupport System PRIV 0x%0x", inst);
					endcase;
				end

				default: begin
					ret = $format("unsupport System 0x%0x", inst);
				end
			endcase
		end

		default: begin
			ret = $format("unsupport 0x%0x", inst);
		end
	endcase

  return ret;

endfunction

