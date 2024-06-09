#include "Tandem.h"
#include "Interpreter.h"

void tandem_warning(std::string msg) {
	printf("------------------------ ");
    printf("%s", msg.c_str());
	printf(" ------------------------\n");
}

void tandem_report(std::string msg) {
	printf("\033[1;31m");
	printf("------------------------ ");
    printf("%s", msg.c_str());
	printf(" ------------------------\n");
    printf("\033[0m");
}

void tandem_data(std::string msg, uint32_t data) {
	printf("\033[1;31m");
	printf(" --> ");
    printf("%s: 0x%s\n", msg.c_str(), Interpreter::uint_to_hex(data).c_str());
    printf("\033[0m");
}

tandem_mm tandem_compare(CommitReport spike, CommitReport dut) {

	// Instrucion fetch and suport
	if(dut.pc != spike.pc) {
		tandem_report("PC mismatch!");
		return tandem_mm::pc;
	}

	if(dut.rawInst != spike.rawInst) {
		tandem_report("Raw instruction mismatch!");
		tandem_data("Spike inst", spike.rawInst);
		tandem_data("Dut inst  ", dut.rawInst);
		return tandem_mm::rawInst;
	}

	if(dut.iType == iTypeUnsup) { 
		tandem_report("Unsupported instruction!");
		return tandem_mm::unsup;
	}

	// Join
	if(dut.iType == iTypeJoin) {
		if(dut.addr != spike.addr) {
			tandem_report("Join addr mismatch!");
			tandem_data("Spike addr", spike.addr);
			tandem_data("Dut addr  ", dut.addr);
			return tandem_mm::addr;
		}
		if(dut.wbRes != spike.wbRes) {
			tandem_report("Join result mismatch!");
			tandem_data("Spike result", spike.wbRes);
			tandem_data("Dut result  ", dut.wbRes);
			return tandem_mm::wbRes;
		}
	}

	// Load/Store
	if(dut.iType == iTypeLd || dut.iType == iTypeSt) {
		if(dut.addr != spike.addr) {
			tandem_report("Ld/St addr mismatch!");
			tandem_data("Spike addr", spike.addr);
			tandem_data("Dut addr  ", dut.addr);
			return tandem_mm::addr;
		}
	}

	// Br/J/Jr
	if(dut.iType == iTypeBr || dut.iType == iTypeJ || dut.iType == iTypeJr) {
		if(dut.addr != spike.addr) {
			tandem_report("Br/J/Jr addr mismatch!");
			tandem_data("Spike addr", spike.addr);
			tandem_data("Dut addr  ", dut.addr);
			return tandem_mm::addr;
		}
	}

	// Instruction WB
	if(dut.iType == iTypeAlu || dut.iType == iTypeMul || dut.iType == iTypeDiv ||
		dut.iType == iTypeLd || dut.iType == iTypeAuipc) {
		// wb expected
		if(dut.wbDst != spike.wbDst) {
			tandem_report("Destination register mismatch!");
			tandem_data("Spike dest", spike.wbDst);
			tandem_data("Dut dest  ", dut.wbDst);
			return tandem_mm::wbDst;
		}
		if(dut.wbRes != spike.wbRes && dut.wbDst != 0) {
			tandem_report("Result mismatch!");
			tandem_data("Spike result", spike.wbRes);
			tandem_data("Dut result  ", dut.wbRes);
			if(dut.iType == iTypeLd || dut.iType == iTypeSt) {
				tandem_data("Spike addr", spike.addr);
				tandem_data("Dut addr  ", dut.addr);
			}
			return tandem_mm::wbRes;
		}
	} else {
		// wb not expected
		if(dut.wbDst != 0) {
			tandem_report("Unexpected register write!");
			return tandem_mm::wbUnexp;
		}
	}

	return tandem_mm::correct;

}

tandem_mm tandem_compare_trace(CommitReport spike, CommitReport dut) {

	// Instrucion fetch and suport
	if(dut.pc != spike.pc) {
		tandem_report("PC mismatch!");
		return tandem_mm::pc;
	}

	if(dut.rawInst != spike.rawInst) {
		tandem_report("Raw instruction mismatch!");
		tandem_data("Spike inst", spike.rawInst);
		tandem_data("Dut inst  ", dut.rawInst);
		return tandem_mm::rawInst;
	}

	return tandem_mm::correct;

}