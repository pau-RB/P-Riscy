#include"Interpreter.h"

Interpreter::Interpreter(isa_parser_t *isa) {
	disasm = new disassembler_t(isa);
}

Interpreter::~Interpreter() {
	delete disasm;
}

void Interpreter::print_CMR_spk(const CommitReport cmr) {

    std::string phrase = " [id:     ] cycle:          | pc: 0x          | iType:       | res: 0x        ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.verifID ),  6, 3 );
    overwrite(phrase, std::to_string(cmr.cycle   ), 19, 8 );
    overwrite(phrase,    uint_to_hex(cmr.pc      ), 36, 8 );
    overwrite(phrase,    print_itype(cmr.iType   ), 54, 8 );
    overwrite(phrase,                res          , 70, 8 );

    printf("\033[1;33m");
    printf("%s | %s\n", phrase.c_str(), print_disasm(cmr.rawInst).c_str());
    fflush(stdout);
    printf("\033[0m");

}

void Interpreter::print_CMR_dut(const CommitReport cmr) {

    std::string phrase = "            cycle:          | pc: 0x          | iType:       | res: 0x        ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.cycle), 19, 8 );
    overwrite(phrase,    uint_to_hex(cmr.pc   ), 36, 8 );
    overwrite(phrase,    print_itype(cmr.iType), 54, 8 );
    overwrite(phrase,                res       , 70, 8 );

    printf("%s | %s\n", phrase.c_str(), print_disasm(cmr.rawInst).c_str());
    fflush(stdout);

}

void Interpreter::print_MSG_dut(const VerifID verifID, const uint8_t msg) {

	std::string phrase = " [id:     ] MSG:";
	overwrite(phrase, std::to_string(verifID),  6, 3 );
    printf("%s %c\n\n", phrase.c_str(), (char)msg);
    fflush(stdout);

}

void Interpreter::print_stats(const std::map<VerifID, uint32_t> commit_thread) {

	uint32_t total = 0;

	printf("\033[1;33m");
	printf("\n\n----------- STATS -----------\n\n");
	for(auto p: commit_thread) {

        std::string phrase = " [id:     ] commits:         ";
		overwrite(phrase, std::to_string(p.first ),  6, 3 );
	    overwrite(phrase, std::to_string(p.second), 21, 8 );
	    printf("%s\n", phrase.c_str());

	    total+=p.second;

    }

    std::string phrase = "\n      total commits:         \n";
	overwrite(phrase, std::to_string(total), 21, 8 );
	printf("%s\n", phrase.c_str());

	printf("-----------------------------\n\n");
	fflush(stdout);
	printf("\033[0m");

}

std::string Interpreter::uint_to_hex(uint32_t w) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(8,'0');
    for (size_t i=0, j=(8-1)*4 ; i<8; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}


std::string Interpreter::int_to_hex(int32_t w) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(8,'0');
    for (size_t i=0, j=(8-1)*4 ; i<8; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

void Interpreter::overwrite (std::string &base, const std::string &text, int position, int max) {
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

std::string Interpreter::print_itype(const IType iType) {
    switch (iType) {
        case iTypeUnsup:
            return "Unsup";
        case iTypeAlu  :
            return "Alu";
        case iTypeMul  :
            return "Mul";
        case iTypeLd   :
            return "Ld";
        case iTypeSt   :
            return "St";
        case iTypeFork :
            return "Fork";
        case iTypeJoin :
            return "Join";
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

std::string Interpreter::print_disasm(const Data uinst) {

	return disasm->disassemble((insn_t)uinst);

}