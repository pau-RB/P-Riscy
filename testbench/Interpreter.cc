#include"Interpreter.h"

Interpreter::Interpreter(isa_parser_t *isa) {
	disasm = new disassembler_t(isa);
}

Interpreter::~Interpreter() {
	delete disasm;
}

void Interpreter::print_TST_dut(const TestRes tst) {

    std::string phrase;

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

    phrase = "               TST     | type :                 | len  :                 | str  :                 |";
    overwrite(phrase, print_testType(tst.testtyp), 33, 14 );
    overwrite(phrase, std::to_string(tst.testlen), 58, 14 );
    overwrite(phrase, std::to_string(tst.teststr), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "                       | lat  :                 | delTX:                 | delRX:                 |";
    overwrite(phrase, std::to_string(tst.latency), 33, 14 );
    overwrite(phrase, std::to_string(tst.delayTX), 58, 14 );
    overwrite(phrase, std::to_string(tst.delayRX), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "---------------------------------------------------------------------------------------------------";
    printf("%s \n", phrase.c_str());

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

    L1IStat l1I = msr.l1IStat;
    L1DStat l1D = msr.l1DStat;
    WMCStat l2S = msr.l2SStat;

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

    phrase = "               L1I     | tRD   :                | hRD   :                | mRD   :                |";
    overwrite(phrase, std::to_string(l1I.hRD+l1I.mRD), 33, 14 );
    overwrite(phrase, std::to_string(l1I.hRD        ), 58, 14 );
    overwrite(phrase, std::to_string(l1I.mRD        ), 83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               L1D     | tLd   :                | hLd   :                | mLd   :                |";
    overwrite(phrase, std::to_string(l1D.hLd+l1D.mLd),  33, 14 );
    overwrite(phrase, std::to_string(l1D.hLd        ),  58, 14 );
    overwrite(phrase, std::to_string(l1D.mLd        ),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | tSt   :                | hSt   :                | mSt   :                |";
    overwrite(phrase, std::to_string(l1D.hSt+l1D.mSt),  33, 14 );
    overwrite(phrase, std::to_string(l1D.hSt        ),  58, 14 );
    overwrite(phrase, std::to_string(l1D.mSt        ),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | tJoin :                | hJoin :                | mJoin :                |";
    overwrite(phrase, std::to_string(l1D.hJoin+l1D.mJoin),  33, 14 );
    overwrite(phrase, std::to_string(l1D.hJoin          ),  58, 14 );
    overwrite(phrase, std::to_string(l1D.mJoin          ),  83, 14 );
    printf("%s \n", phrase.c_str());


    phrase = "                       |------------------------|------------------------|------------------------|";
    printf("%s \n", phrase.c_str());

    phrase = "               L2S     | tRD   :                | hRD   :                | mRD   :                |";
    overwrite(phrase, std::to_string(l2S.hRD +l2S.mRD),  33, 14 );
    overwrite(phrase, std::to_string(l2S.hRD         ),  58, 14 );
    overwrite(phrase, std::to_string(l2S.mRD         ),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | tWR   :                | hWR   :                | mWR   :                |";
    overwrite(phrase, std::to_string(l2S.hWR +l2S.mWR),  33, 14 );
    overwrite(phrase, std::to_string(l2S.hWR         ),  58, 14 );
    overwrite(phrase, std::to_string(l2S.mWR         ),  83, 14 );
    printf("%s \n", phrase.c_str());

    phrase = "                       | tWB   :                |                        |                        |";
    overwrite(phrase, std::to_string(l2S.tWB          ),  33, 14 );
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

std::string Interpreter::print_testType(const TestType tType) {
    switch (tType) {
        case RDLAT:
            return "RDLAT";
        case MXLAT:
            return "MXLAT";
        case RDTHP:
            return "RDTHP";
        case WRTHP:
            return "WRTHP";
        case MXTHP:
            return "MXTHP";
        case TTEND:
            return "TTEND";
        default:
            return "???";
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