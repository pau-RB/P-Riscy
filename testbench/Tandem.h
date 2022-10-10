#ifndef _TANDEM_H
#define _TANDEM_H

#include <string>
#include "TestbenchTypes.h"
#include "Interpreter.h"
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

void tandem_report(std::string msg);

tandem_mm tandem_compare(CommitReport spike, CommitReport dut);

#endif