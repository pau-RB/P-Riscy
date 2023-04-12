#include"Interpreter.h"

Interpreter::Interpreter(isa_parser_t *isa) {
	disasm = new disassembler_t(isa);
}

Interpreter::~Interpreter() {
	delete disasm;
}

void Interpreter::print_CMR_spk(const CommitReport cmr) {

    std::string phrase = " [id:        ] cycle:                | pc: 0x         | iType:          | res: 0x        ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.verifID ),  6,  6 );
    overwrite(phrase, std::to_string(cmr.cycle   ), 22, 14 );
    overwrite(phrase,    uint_to_hex(cmr.pc      ), 45,  8 );
    overwrite(phrase,    print_itype(cmr.iType   ), 63,  8 );
    overwrite(phrase,                res          , 81,  8 );

    printf("\033[1;33m");
    printf("%s | %s\n", phrase.c_str(), print_disasm(cmr.rawInst).c_str());
    fflush(stdout);
    printf("\033[0m");

}

void Interpreter::print_CMR_dut(const CommitReport cmr) {

    std::string phrase = "               cycle:                | pc: 0x         | iType:          | res: 0x        ";
    std::string res;

    if (cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
    	res = uint_to_hex(cmr.addr);
    else
    	res = uint_to_hex(cmr.wbRes);

    overwrite(phrase, std::to_string(cmr.cycle), 22, 14 );
    overwrite(phrase,    uint_to_hex(cmr.pc   ), 45,  8 );
    overwrite(phrase,    print_itype(cmr.iType), 63,  8 );
    overwrite(phrase,                res       , 81,  8 );

    printf("%s | %s\n", phrase.c_str(), print_disasm(cmr.rawInst).c_str());
    fflush(stdout);

}

void Interpreter::print_MSG_dut(const Message msg) {

    std::string phrase;

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

	phrase = " [id:        ] MESSAGE | cycle :                | commit:                |                        |";
	overwrite(phrase, std::to_string(msg.verifID)  ,  6,  6 );
    overwrite(phrase, std::to_string(msg.cycle  )  , 33, 14 );
    overwrite(phrase, std::to_string(msg.commit )  , 58, 14 );
    overwrite(phrase, std::string(1,(char)msg.data), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    fflush(stdout);

}

void Interpreter::print_HEX_dut(const Message msg) {

    std::string phrase;

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    phrase = " [id:        ] MESSAGE | cycle :                | commit:                |                        |";
    overwrite(phrase, std::to_string(msg.verifID)        ,  6,  6 );
    overwrite(phrase, std::to_string(msg.cycle  )        , 33, 14 );
    overwrite(phrase, std::to_string(msg.commit )        , 58, 14 );
    overwrite(phrase, "0x"+int_to_hex((int32_t) msg.data), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    fflush(stdout);

}

void Interpreter::print_MSR_dut(const MemStat msr) {

    LSUStat     lsu     = msr.lsu;
    ArbiterStat arbiter = msr.arbiter;
    FetchStat   fetch   = msr.fetch;
    WMCStat     l2s     = msr.l2s;

    std::string phrase;

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    std::string data(1, (char)msr.data);

    phrase = " [id:        ] MSR     | cycle :                | commit:                | data  :                |";
    overwrite(phrase, std::to_string(msr.verifID   ),  6,  6 );
    overwrite(phrase, std::to_string(msr.cycle     ), 33, 14 );
    overwrite(phrase, std::to_string(msr.commit    ), 58, 14 );
    overwrite(phrase,                    data       , 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               Fetch   | hit   :                | miss  :                | empty :                |";
    overwrite(phrase, std::to_string(fetch.hit     ), 33, 14 );
    overwrite(phrase, std::to_string(fetch.miss    ), 58, 14 );
    overwrite(phrase, std::to_string(fetch.empty   ), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               Arbiter | memOvb:                | ariOvb:                | empty :                |";
    overwrite(phrase, std::to_string(arbiter.memOvb  ), 33, 14 );
    overwrite(phrase, std::to_string(arbiter.arithOvb), 58, 14 );
    overwrite(phrase, std::to_string(arbiter.empty   ), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               LSU     | tLd   :                | tSt   :                | tJoin :                |";
    overwrite(phrase, std::to_string(lsu.hLd  +lsu.mLd  +lsu.dLd  ),  33, 14 );
    overwrite(phrase, std::to_string(lsu.hSt  +lsu.mSt  +lsu.dSt  ),  58, 14 );
    overwrite(phrase, std::to_string(lsu.hJoin+lsu.mJoin+lsu.dJoin),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | hLd   :                | hSt   :                | hJoin :                |";
    overwrite(phrase, std::to_string(lsu.hLd  ),  33, 14 );
    overwrite(phrase, std::to_string(lsu.hSt  ),  58, 14 );
    overwrite(phrase, std::to_string(lsu.hJoin),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | mLd   :                | mSt   :                | mJoin :                |";
    overwrite(phrase, std::to_string(lsu.mLd  ),  33, 14 );
    overwrite(phrase, std::to_string(lsu.mSt  ),  58, 14 );
    overwrite(phrase, std::to_string(lsu.mJoin),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | dLd   :                | dSt   :                | dJoin :                |";
    overwrite(phrase, std::to_string(lsu.dLd  ),  33, 14 );
    overwrite(phrase, std::to_string(lsu.dSt  ),  58, 14 );
    overwrite(phrase, std::to_string(lsu.dJoin),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               L2S     | tRD   :                | tWR   :                | tWB   :                |";
    overwrite(phrase, std::to_string(l2s.hRD + l2s.mRD),  33, 14 );
    overwrite(phrase, std::to_string(l2s.hWR + l2s.mWR),  58, 14 );
    overwrite(phrase, std::to_string(l2s.tWB          ),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | hRD   :                | hWR   :                |                        |";
    overwrite(phrase, std::to_string(l2s.hRD          ),  33, 14 );
    overwrite(phrase, std::to_string(l2s.hWR          ),  58, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | mRD   :                | mWR   :                |                        |";
    overwrite(phrase, std::to_string(l2s.mRD          ),  33, 14 );
    overwrite(phrase, std::to_string(l2s.mWR          ),  58, 14 );
    printf("%s \n", phrase.c_str());


    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    fflush(stdout);

}

void Interpreter::print_stats(const std::map<VerifID, PerfCnt> commit_thread) {

	uint32_t total = 0;

	printf("\033[1;33m");
	printf("\n\n----------- STATS -----------\n\n");
	for(auto p: commit_thread) {

        std::string phrase = " [id:        ] commits:               ";
		overwrite(phrase, std::to_string(p.first ),  6, 6 );
	    overwrite(phrase, std::to_string(p.second), 24, 14 );
	    printf("%s\n", phrase.c_str());

	    total+=p.second;

    }

    std::string phrase = "\n         total commits:               \n";
	overwrite(phrase, std::to_string(total), 25, 14 );
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
    if(text_size > max) {
        if(position < text_size)
            base[position] = 'N';
    } else {
        for (int i = 0; i < text_size; ++i)
            if (position+max-text_size+i < base_size)
                base[position+max-text_size+i] = text[i];
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
        case iTypeDiv  :
            return "Div";
        case iTypeLd   :
            return "Ld";
        case iTypeSt   :
            return "St";
        case iTypeFork :
            return "Fork";
        case iTypeForkr :
            return "Forkr";
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