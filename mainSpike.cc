#include <iostream>
#include <string>

#include "TestbenchTypes.h"
#include "Interpreter.h"
#include "CustomSpike.h"

using namespace std;

int main () {

	CustomSpike* c = new CustomSpike("./vmh/addi.riscv.vmh",MEM_MAX_ADDR);

	for (int i = 0; i < 50; ++i)
		printCMRSpike(c->step());
	
}