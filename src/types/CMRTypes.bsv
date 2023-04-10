import Types::*;
import Encodings::*;
import ProcTypes::*;
import Config::*;

typedef struct {
	Data    cycle;
	VerifID verifID;
	Addr    pc;
	Data    rawInst;
	IType   iType;
	RIndx   wbDst;   // 0 if no wb
	Data    wbRes;   // ALU/Load result, childverifID for fork/forkr, memread for Join
	Addr    addr;    // nextpc for branch, addr for LSU, nextpc for fork/forkr
} CommitReport deriving (Bits, Eq, FShow);

typedef struct {
	VerifID verifID;
	Data    cycle;
	Data    commit;
	Data    data;
} Message deriving (Bits, Eq);

typedef struct{
	Data    hit;
	Data    miss;
	Data    empty;
} FetchStat deriving(Eq, Bits, FShow);

typedef struct{
	Data    memOvb;
	Data    arithOvb;
	Data    empty;
} ArbiterStat deriving(Eq, Bits, FShow);

typedef struct{
	Data    hLd;
	Data    hSt;
	Data    hJoin;
	Data    mLd;
	Data    mSt;
	Data    mJoin;
	Data    dLd;
	Data    dSt;
	Data    dJoin;
} LSUStat deriving(Eq, Bits, FShow);

typedef struct{
	Data hWR; // Total hits on read
	Data mWR; // Total miss on read
	Data hRD; // Total hits on read
	Data mRD; // Total miss on read
	Data tWB; // Total writebacks
} WMCStat deriving(Eq, Bits, FShow);

typedef struct{
	VerifID     verifID;
	Data        cycle;
	Data        commit;
	Data        data;
	FetchStat   fetch;
	ArbiterStat arbiter;
	LSUStat     lsu;
	WMCStat     l2s;
} MemStat deriving(Eq, Bits, FShow);

// Construct CMR
`ifdef DEBUG_CMR
function CommitReport generateCMR(Data numCycles, VerifID verifID, VerifID childVerifID, ComToken cToken, Data lsuRes, Data muldivRes);

	if(cToken.iType == J || cToken.iType == Jr || cToken.iType == Br) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : '0,
		                    wbRes  : '0,
		                    addr:    cToken.addr};

	end else if(cToken.iType == Fork || cToken.iType == Forkr) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : '0,
		                    wbRes  : childVerifID,
		                    addr   : cToken.addr};

	end else if(cToken.iType == Join) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : '0,
		                    wbRes  : lsuRes,
		                    addr   : cToken.addr};

	end else if(cToken.iType == Ld) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : fromMaybe('0,cToken.dst),
		                    wbRes  : lsuRes,
		                    addr   : cToken.addr};

	end else if(cToken.iType == St) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : '0,
		                    wbRes  : '0,
		                    addr   : cToken.addr};

	end else if(cToken.iType == Mul) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : fromMaybe('0,cToken.dst),
		                    wbRes  : muldivRes,
		                    addr   : '0};


	end else if(cToken.iType == Div) begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : fromMaybe('0,cToken.dst),
		                    wbRes  : muldivRes,
		                    addr   : '0};

	end else begin
		return CommitReport{cycle  : numCycles,
		                    verifID: verifID,
		                    pc     : cToken.pc,
		                    rawInst: cToken.rawInst,
		                    iType  : cToken.iType,
		                    wbDst  : fromMaybe('0,cToken.dst),
		                    wbRes  : cToken.res,
		                    addr   : '0};

	end

endfunction
`else
function CommitReport generateCMR(Data numCycles, VerifID verifID, VerifID childVerifID, ComToken cToken, Data lsuRes, Data muldivRes);
	return ?;
endfunction
`endif

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