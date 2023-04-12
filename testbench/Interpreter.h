#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <string>
#include <map>
#include <stdio.h>

#include "TestbenchTypes.h"
#include "isa_parser.h"
#include "disasm.h"

class Interpreter {

	public:

		Interpreter(isa_parser_t *isa);
		~Interpreter();

		static std::string uint_to_hex(uint32_t w);
		static std::string int_to_hex(int32_t w);

		void print_CMR_spk(const CommitReport cmr);
		void print_CMR_dut(const CommitReport cmr);
		void print_MSG_dut(const Message msg);
		void print_HEX_dut(const Message msg);
		void print_MSR_dut(const MemStat msr);
		void print_stats(const std::map<VerifID, PerfCnt> commit_thread);

	private:

		disassembler_t *disasm;

		static void overwrite(std::string &base, const std::string &text, int position, int max);

		std::string print_itype(const IType iType);
		std::string print_disasm(const Data uinst);

};

#endif