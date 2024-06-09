#ifndef _TANDEM_H
#define _TANDEM_H

#include <string>
#include "TestbenchTypes.h"
#include <stdio.h> 

enum tandem_mm{
	correct,
	unsup  ,
	pc     ,
	rawInst,
	wbUnexp,
	wbDst  ,
	wbRes  ,
	addr
};

void tandem_warning(std::string msg);

void tandem_report(std::string msg);

void tandem_data(std::string msg, uint32_t data);

tandem_mm tandem_compare(CommitReport spike, CommitReport dut);

tandem_mm tandem_compare_trace(CommitReport spike, CommitReport dut);

#endif