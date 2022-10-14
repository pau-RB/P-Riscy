#include"Interpreter.h"

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

// Overwrite part of a base string
void overwrite (std::string &base, const std::string &text, int position, int max) {
    int base_size = base.size();
    int text_size = text.size();

    if(text_size < max) {
        position += (max-text_size)/2;
    }

    for (int i = 0; i < text_size && i < max; ++i) {
        if (position+i < base_size)
            base[position+i] = text[i];
        else
            base += text[i]; 
    }
}

// Prints the instruction type
std::string printIType (const IType iType) {
    switch (iType) {
        case iTypeUnsup:
            return "Unsup";
        case iTypeAlu  :
            return "Alu";
        case iTypeLd   :
            return "Ld";
        case iTypeSt   :
            return "St";
        case iTypeJ    :
            return "J";
        case iTypeJr   :
            return "Jr";
        case iTypeBr   :
            return "Br";
        case iTypeAuipc:
            return "Auipc";
        default:
            return "???";
    }
}

// Get IType
IType getIType(const Data uinst) {

	uint32_t opcode = (uinst&0x0000007f);

	switch (opcode) {
		case opOpImm:
			return iTypeAlu;
		case opOp:
			return iTypeAlu; 
		case opLui:
			return iTypeAlu;
		case opAuipc:
			return iTypeAuipc;
		case opJal:
			return iTypeJ;
		case opJalr:
			return iTypeJr;
		case opBranch:
			return iTypeBr;
		case opLoad:
			return iTypeLd;
		case opStore:
			return iTypeSt;
		default:
			return iTypeUnsup;
	}

}

// Pretty print of an instruction
std::string interpreter(const Data uinst) {

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


	int32_t immI    = inst.s>>20;
	int32_t immS    = ((int32_t)(((inst.s&0xfe000000)<<0)|((inst.s&0x00000f80)<<13)))>>27;
	int32_t immB    = ((int32_t)(((inst.s&0x80000000)<<0)|((inst.s&0x00000080)<<23)|((inst.s&0x7e000000)>>1)|((inst.s&0x00000f00)<<12)))>>19;
	int32_t immU    = (inst.s&0xfffff000);
	int32_t immJ    = ((int32_t)(((inst.s&0x80000000)<<0)|((inst.s&0x000ff000)<<11)|((inst.s&0x00100000)<<2)|((inst.s&0x7e000000)>>10)|((inst.s&0x01e00000)>>9)))>>11;

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
				default:     return "unsupport branch 0x"+uint_to_hex(inst.u);
			}
			ret = ret+" r"+std::to_string(rs1)+" r"+std::to_string(rs2)+" 0x"+int_to_hex(immB);
			return ret;

		case opLoad:

			switch (funct3) {
				case fnLW:  ret = "lw"; break;
				case fnLB:  ret = "lb"; break;
				case fnLH:  ret = "lh"; break;
				case fnLBU: ret = "lbu"; break;
				case fnLHU: ret = "lhu"; break;
				default:    return "unsupport Load 0x"+uint_to_hex(inst.u);
			}
			ret = ret+" r"+std::to_string(rd)+" = [r"+std::to_string(rs1)+" 0x"+int_to_hex(immI)+"]";
			return ret;

		case opStore:

			switch (funct3) {
				case fnSW:  ret = "sw"; break;
				case fnSB:  ret = "sb"; break;
				case fnSH:  ret = "sh"; break;
				default:    return "unsupport Store 0x"+uint_to_hex(inst.u);
			}
			ret = ret+" [r"+std::to_string(rs1)+" 0x"+int_to_hex(immS)+"] = r"+std::to_string(rs2);
			return ret;

		case opMiscMem:
			return "unsupport MiscMem 0x"+uint_to_hex(inst.u);

		case opAmo:
			return "unsupport Amo 0x"+uint_to_hex(inst.u);

		case opSystem:
			
			return "unsupport System 0x"+uint_to_hex(inst.u);

		default:
			return "unsupport "+uint_to_hex(inst.u);
	}

}

void printCMRSpike(const CommitReport cmr) {

    std::string phrase = " [id:     ] cycle:          | pc:          | iType:          | res:           ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.feID ),  6, 3 );
    overwrite(phrase, std::to_string(cmr.cycle), 19, 8 );
    overwrite(phrase,    uint_to_hex(cmr.pc   ), 34, 8 );
    overwrite(phrase,     printIType(cmr.iType), 52, 8 );
    overwrite(phrase,                res       , 68, 8 );

    printf("\033[1;33m");
    printf("%s | %s\n", phrase.c_str(), interpreter(cmr.rawInst).c_str());
    fflush(stdout);
    printf("\033[0m");

}

void printCMRDut(const CommitReport cmr) {

    std::string phrase = "            cycle:          | pc:          | iType:          | res:           ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.feID ),  6, 3 );
    overwrite(phrase, std::to_string(cmr.cycle), 19, 8 );
    overwrite(phrase,    uint_to_hex(cmr.pc   ), 34, 8 );
    overwrite(phrase,     printIType(cmr.iType), 52, 8 );
    overwrite(phrase,                res       , 68, 8 );

    printf("%s | %s\n", phrase.c_str(), interpreter(cmr.rawInst).c_str());
    fflush(stdout);

}