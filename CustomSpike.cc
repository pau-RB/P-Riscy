#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <pthread.h>

// Testbench
#include "TestbenchTypes.h"
#include "Interpreter.h"
#include "CustomSpike.h"

// Spike
#include "config.h"
#include "simif.h"
#include "mmu.h"
#include "processor.h"

CustomSpike::~CustomSpike() {
    free(mem);
}

CustomSpike::CustomSpike(const char* isa_string, const char* elf_file, size_t memory_sz):
	isa("RV32I", "m"),
	sout_(nullptr),
	proc(&isa, DEFAULT_VARCH, this, 0, false, NULL, sout_)
			// processor_t(isa, varch, sim, id, halt_on_reset, log_file, sout_);
{

	sout_.rdbuf(std::cerr.rdbuf()); // debug output goes to stderr by default

	mem_sz = memory_sz;
    mem    = (char*) calloc(memory_sz, 1);

    this->loadVMH("./vmh/addi.riscv.vmh");
    this->proc.set_mmu_capability(IMPL_MMU_SBARE);
    this->proc.get_state()->pc = StartPC;
    this->cycleCnt = 0;

}

// For a Ld/St, the mmu will call addr_to_mem to get the host addr for the actual
// memory map (calloc). If it returns an addr, it will proceed with the access
// If it return NULL, it will be considered as an MMIO region and will call
// mmio_load/mmio_store to request the operaton to the sim.

char* CustomSpike::addr_to_mem(reg_t addr) { return ((char*) mem) + addr; }

bool CustomSpike::mmio_load(reg_t addr, size_t len, uint8_t* bytes) { return true; }

bool CustomSpike::mmio_store(reg_t addr, size_t len, const uint8_t* bytes) { return true; }

const char* CustomSpike::get_symbol(uint64_t addr) { return ""; }


CommitReport CustomSpike::step() {

	CommitReport cmr;

	cmr.cycle = this->cycleCnt;
	cmr.pc    = this->proc.get_state()->pc;

	try {
        cmr.rawInst = (uint32_t) proc.get_mmu()->access_icache(cmr.pc)->data.insn.bits();
    } catch(...) {
        std::cout << "[ERROR] access_icache(0x" << std::hex << cmr.pc <<  ") failed even though there was no interrupt or exception for the current verification packet." << std::endl;
    }

    proc.step(1); cycleCnt++;

    cmr.wbDst = (cmr.rawInst >> 7) & 0x1F;
    cmr.wbRes = this->proc.get_state()->XPR[cmr.wbDst & 0x1F];
    cmr.addr  = this->proc.get_state()->pc;
    
    return cmr;

}

void CustomSpike::loadVMH(std::string path) {

    std::ifstream srcfile; srcfile.open(path,std::fstream::in|std::fstream::out|std::fstream::app);
	std::string aux; srcfile >> aux;

	uint32_t word;
    for (uint32_t addr = 0; addr < MEM_MAX_ADDR; addr=addr+4) {
        srcfile >> std::hex >> word;
        memcpy(((char*) mem) + addr, &word, 4);
    }

}