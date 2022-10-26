#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <pthread.h>

// Testbench
#include "TestbenchTypes.h"
#include "Interpreter.h"
#include "LoadTracer.h"
#include "StoreTracer.h"
#include "CustomSpike.h"
#include "Tandem.h"

// Spike
#include "config.h"
#include "simif.h"
#include "mmu.h"
#include "processor.h"

CustomSpike::~CustomSpike() {
    free(mem);
}

CustomSpike::CustomSpike(const std::string elf_file, size_t memory_sz):
	isa("RV32I", "m"),
	sout_(nullptr),
    lt(),
    st()
{

	sout_.rdbuf(std::cerr.rdbuf()); // debug output goes to stderr by default

	mem_sz = memory_sz;
    mem    = (char*) calloc(memory_sz, 1);

    this->load_vmh(elf_file);

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


CommitReport CustomSpike::step(VerifID verifID) {

    if(!proc.count(verifID)) {
        this->add_proc(verifID);
        tandem_warning("New thread added to spike!");
    }

	CommitReport cmr;

	// What instruction will I execute next?
	cmr.cycle   = this->cycleCnt;
    cmr.verifID = verifID;
	cmr.pc      = this->proc[verifID]->get_state()->pc;
	try {
		cmr.rawInst = (uint32_t) proc[verifID]->get_mmu()->access_icache(cmr.pc)->data.insn.bits();
    } catch(...) {
        std::cout << "[ERROR] access_icache(0x" << std::hex << cmr.pc <<  ") failed even though there was no interrupt or exception for the current verification packet." << std::endl;
    }
    cmr.iType = getIType(cmr.rawInst);

    // Execute it
    proc[verifID]->step(1); cycleCnt++;

    // What is the result ?
    cmr.wbDst = (cmr.rawInst >> 7) & 0x1F;
    cmr.wbRes = this->proc[verifID]->get_state()->XPR[cmr.wbDst & 0x1F];

    if(cmr.iType == iTypeLd)
        cmr.addr = this->lt.get_last_access();
    else if(cmr.iType == iTypeSt)
        cmr.addr = this->st.get_last_access();
    else if(cmr.iType == iTypeJoin)
        cmr.addr = this->st.get_last_access();
    else if(cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
        cmr.addr = this->proc[verifID]->get_state()->pc;
    else
        cmr.addr = 0;
    
    return cmr;

}

void CustomSpike::fork(VerifID verifID, VerifID childverifID, Addr childpc) {

    if(!proc.count(verifID)) {
        this->add_proc(verifID);
        tandem_warning("New thread added to spike!");
    }

    if(proc.count(childverifID)) {
        tandem_warning("New childverifID already exists in spike!");
    }

    this->add_proc(childverifID);

    this->proc[childverifID]->get_state()->pc = childpc;
    for (RIndx xi = 0; xi < 32; ++xi) {
        Data value = this->proc[verifID     ]->get_state()->XPR[xi & 0x1F];
                     this->proc[childverifID]->get_state()->XPR.write(xi & 0x1F, value);
    }

    return;

}

void CustomSpike::join(VerifID verifID, Data res) {

    if(res == 0) {
        this->remove_proc(verifID);
    }

}

void CustomSpike::load_vmh(std::string path) {

    std::ifstream srcfile; srcfile.open(path,std::fstream::in|std::fstream::out|std::fstream::app);
	std::string aux; srcfile >> aux;

	uint32_t word;
    for (uint32_t addr = 0; addr < MEM_MAX_ADDR; addr=addr+4) {
        srcfile >> std::hex >> word;
        memcpy(((char*) mem) + addr, &word, 4);
    }

}

void CustomSpike::add_proc(VerifID verifID) {

    processor_t *new_proc = new processor_t(&isa, DEFAULT_VARCH, this, 0, false, NULL, sout_);
                            // processor_t(isa, varch, sim, id, halt_on_reset, log_file, sout_);

    new_proc->set_mmu_capability(IMPL_MMU_SBARE);
    new_proc->get_state()->pc = StartPC;
    new_proc->get_mmu()->register_memtracer(&(this->lt));
    new_proc->get_mmu()->register_memtracer(&(this->st));

    proc.insert ( std::pair<VerifID,processor_t*>(verifID, new_proc) );

}

void CustomSpike::remove_proc(VerifID verifID) {

    if(proc.count(verifID)) {

        processor_t *old_proc = proc[verifID];
        delete old_proc;
        proc.erase ( verifID );

    }

}