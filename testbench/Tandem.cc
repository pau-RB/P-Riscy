#include "Tandem.h"

void tandem_report(std::string msg) {
	printf("\033[1;31m");
	printf("------------------------ ");
    printf("%s", msg.c_str());
	printf(" ------------------------\n");
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
		return tandem_mm::rawInst;
	}

	if(dut.iType == iTypeUnsup) { 
		tandem_report("Unsupported instruction!");
		return tandem_mm::unsup;
	}

	// Instruction WB
	if(dut.iType == iTypeAlu || dut.iType == iTypeLd) {
		// wb expected
		if(dut.wbDst != spike.wbDst) {
			tandem_report("Destination register mismatch!");
			return tandem_mm::wbDst;
		}
		if(dut.wbRes != spike.wbRes && dut.wbDst != 0) {
			tandem_report("Result mismatch!");
			return tandem_mm::wbRes;
		}
	} else {
		// wb not expected
		if(dut.wbDst != 0) {
			tandem_report("Unexpected register write!");
			return tandem_mm::wbUnexp;
		}
	}

	// Load/Store
	if(dut.iType == iTypeLd || dut.iType == iTypeSt) {
		if(dut.addr != spike.addr) {
			tandem_report("Ld/St addr mismatch!");
			return tandem_mm::addr;
		}
	}

	return tandem_mm::correct;

}