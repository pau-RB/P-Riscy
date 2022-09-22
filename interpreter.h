#include <string>


// opcode
#define opLoad    0b0000011
#define opMiscMem 0b0001111
#define opOpImm   0b0010011
#define opAuipc   0b0010111
#define opStore   0b0100011
#define opAmo     0b0101111
#define opOp      0b0110011
#define opLui     0b0110111
#define opBranch  0b1100011
#define opJalr    0b1100111
#define opJal     0b1101111
#define opSystem  0b1110011

// function code
// ALU
#define fnADD  0b000
#define fnSLL  0b001
#define fnSLT  0b010
#define fnSLTU 0b011
#define fnXOR  0b100
#define fnSR   0b101
#define fnOR   0b110
#define fnAND  0b111
// Branch
#define fnBEQ  0b000
#define fnBNE  0b001
#define fnBLT  0b100
#define fnBGE  0b101
#define fnBLTU 0b110
#define fnBGEU 0b111
// Load
#define fnLW  0b010
#define fnLB  0b000
#define fnLH  0b001
#define fnLBU 0b100
#define fnLHU 0b101
// Store
#define fnSW 0b010
#define fnSB 0b000
#define fnSH 0b001
// Amo
#define fnLR 0b00010
#define fnSC 0b00011
//MiscMem
#define fnFENCE  0b000
#define fnFENCEI 0b001
// System
#define fnCSRRW   0b001
#define fnCSRRS   0b010
#define fnCSRRC   0b011
#define fnCSRRWI  0b101
#define fnCSRRSI  0b110
#define fnCSRRCI  0b111
#define fnPRIV    0b000
#define privSCALL 0x000


union Inst
{
	uint32_t u;
	 int32_t s;
};

std::string uint_to_hex(uint32_t w) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(8,'0');
    for (size_t i=0, j=(8-1)*4 ; i<8; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}


std::string int_to_hex(int32_t w) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(8,'0');
    for (size_t i=0, j=(8-1)*4 ; i<8; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

std::string interpreter(uint32_t uinst) {

	Inst inst;
	inst.u = uinst;

	std::string ret;

	uint32_t opcode = (inst.u&0x0000007f)>> 0;
	uint32_t rd     = (inst.u&0x00000f80)>> 7;
	uint32_t funct3 = (inst.u&0x00007000)>>12;
	uint32_t rs1    = (inst.u&0x000f8000)>>15;
	uint32_t rs2    = (inst.u&0x01f00000)>>20;
	//uint32_t funct7 = (inst.u&0xfe000000)>>25;
	uint32_t aluSel = (inst.u&0x40000000)>>30;


	int32_t immI    = (inst.s&0xfff00000)>>20;
	int32_t immS    = (((inst.s&0xfe000000)<<0)|((inst.s&0x00000f80)<<13))>>27;
	int32_t immB    = (((inst.s&0x80000000)<<0)|((inst.s&0x00000080)<<23)|((inst.s&0x7e000000)>>1)|((inst.s&0x00000f00)<<12))>>19;
	int32_t immU    = (inst.s&0xfffff000);
	int32_t immJ    = (((inst.s&0x80000000)<<0)|((inst.s&0x000ff000)<<11)|((inst.s&0x00100000)<<2)|((inst.s&0x7e000000)>>10)|((inst.s&0x01e00000)>>9))>>11;

	switch (opcode) {
		case opOpImm:

			switch (funct3) {
				case fnADD:  ret = "addi" ; break;
				case fnSLT:  ret = "slti" ; break;
				case fnSLTU: ret = "sltiu"; break;
				case fnAND:  ret = "andi" ; break;
				case fnOR:   ret = "ori"  ; break;
				case fnXOR:  ret = "xori" ; break;
				case fnSLL:  ret = "slli" ; break;
				case fnSR:   ret = (aluSel == 0 ? "srli" : "srai"); break;
				default:     ret = "unsupport "+uint_to_hex(inst.u);
			}
			ret = ret+" r"+std::to_string(rd)+" = r"+std::to_string(rs1)+" ";
			ret = ret+((funct3==fnSLL || funct3==fnSR) ? ("0x" + int_to_hex(immI&0x1f)) : ("0x" + int_to_hex(immI)));
			return ret;

		case opOp:
			
			switch (funct3) {
				case fnADD:  ret = (aluSel == 0 ? "add" : "sub"); break;
				case fnSLT:  ret = "slt"; break;
				case fnSLTU: ret = "sltu"; break;
				case fnAND:  ret = "and"; break;
				case fnOR:   ret = "or"; break;
				case fnXOR:  ret = "xor"; break;
				case fnSLL:  ret = "sll"; break;
				case fnSR:   ret = (aluSel == 0 ? "srl" : "sra"); break;
				default:     ret = "unsupport "+uint_to_hex(inst.u);
			}
			ret = ret+" r"+std::to_string(rd)+" = r"+std::to_string(rs1)+" r"+std::to_string(rs2);
			return ret;

		case opLui:
			return "lui r"+std::to_string(rd)+" 0x"+int_to_hex(immU);

		case opAuipc:
			return "auipc r"+std::to_string(rd)+" 0x"+int_to_hex(immU);

		case opJal:
			return "jal r"+std::to_string(rd)+" 0x"+int_to_hex(immJ);

		case opJalr:
			return "jalr r"+std::to_string(rd)+" [r"+std::to_string(rs1)+" 0x"+int_to_hex(immI)+"]";

		case opBranch:

			switch (funct3) {
				case fnBEQ:  ret = "beq"; break;
				case fnBNE:  ret = "bne"; break;
				case fnBLT:  ret = "blt"; break;
				case fnBLTU: ret = "bltu"; break;
				case fnBGE:  ret = "bge"; break;
				case fnBGEU: ret = "bgeu"; break;
				default:     ret = "unsupport branch 0x"+uint_to_hex(inst.u);
			}
			ret = ret+" r"+std::to_string(rs1)+" r"+std::to_string(rs2)+" 0x"+int_to_hex(immB);
			return ret;

		case opLoad:

			ret = (funct3==fnLW) ? "lw" : ("unsupport Load 0x"+uint_to_hex(inst.u));
			ret = ret+" r"+std::to_string(rd)+" = [r"+std::to_string(rs1)+" 0x"+int_to_hex(immI)+"]";
			return ret;

		case opStore:
			ret = (funct3==fnSW) ? "sw" : ("unsupport Store 0x"+uint_to_hex(inst.u));
			ret = ret+" [r"+std::to_string(rs1)+" 0x"+int_to_hex(immS)+"] = r"+std::to_string(rs2);
			return ret;

		case opMiscMem:
			return "unsupport MiscMem 0x"+uint_to_hex(inst.u);

		case opAmo:
			return "unsupport Amo 0x"+uint_to_hex(inst.u);

		/*
		case opSystem:
			case (funct3)
				fnCSRRW, fnCSRRS: begin //fnCSRRC, fnCSRRWI, fnCSRRSI, fnCSRRCI: begin
					ret = case(funct3)
						fnCSRRW: $format("csrrw");
						fnCSRRS: $format("csrrs");
					endcase;
					ret = ret + $format(" r%d csr0x%0x r%d", rd, immI[11:0], rs1);
				end

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
		*/

		default:
			return "unsupport "+uint_to_hex(inst.u);
	}

}