#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <pthread.h>

// Testbench
#include "TestbenchTypes.h"
#include "LoadTracer.h"
#include "StoreTracer.h"
#include "CustomSpike.h"

// Spike
#include "config.h"
#include "memif.h"
#include "simif.h"
#include "mmu.h"
#include "processor.h"

CustomSpike::~CustomSpike() {
    free(mem);
    for(auto p: active_thread) {
        delete p.second;
    }
}

CustomSpike::CustomSpike(isa_parser_t *isa, const std::string elf_file, uint32_t min_addr_mem, uint32_t max_addr_mem):
	sout_(nullptr),
    lt(),
    st()
{

	sout_.rdbuf(std::cerr.rdbuf()); // debug output goes to stderr by default

    this->isa          = isa;
    this->min_addr_mem = min_addr_mem;
    this->max_addr_mem = max_addr_mem;
    this->mmio_void    = 0;
    this->mem          = (char*) calloc(max_addr_mem-min_addr_mem, 1);

    this->load_obj(elf_file);

    this->cycleCnt = 0;

}

// For a Ld/St, the mmu will call addr_to_mem to get the host addr for the actual
// memory map (calloc). If it returns an addr, it will proceed with the access
// If it return NULL, it will be considered as an MMIO region and will call
// mmio_load/mmio_store to request the operaton to the sim.

char* CustomSpike::addr_to_mem(reg_t addr) {
    if(addr >= min_addr_mem && addr < max_addr_mem )
        return ((char*)mem) + (addr - min_addr_mem);
    else
        return ((char*)(&mmio_void));

}

bool CustomSpike::mmio_load(reg_t addr, size_t len, uint8_t* bytes) { return true; }

bool CustomSpike::mmio_store(reg_t addr, size_t len, const uint8_t* bytes) { return true; }

const char* CustomSpike::get_symbol(uint64_t addr) { return ""; }


CommitReport CustomSpike::step(VerifID verifID) {

    if(!active_thread.count(verifID)) {
        this->add_proc(verifID);
    }

    commit_thread[verifID] = commit_thread[verifID]+1;

	CommitReport cmr;

	// What instruction will I execute next?
	cmr.cycle   = this->cycleCnt;
    cmr.verifID = verifID;
	cmr.pc      = this->active_thread[verifID]->get_state()->pc;	
    cmr.rawInst = (uint32_t) active_thread[verifID]->get_mmu()->access_icache(cmr.pc)->data.insn.bits();
    cmr.iType   = getIType(cmr.rawInst);

    // Execute it
    active_thread[verifID]->step(1); cycleCnt++;
    active_thread[verifID]->get_mmu()->flush_tlb();

    // What is the result ?
    cmr.wbDst = (cmr.rawInst >> 7) & 0x1F;
    cmr.wbRes = this->active_thread[verifID]->get_state()->XPR[cmr.wbDst & 0x1F];

    if(this->active_thread[verifID]->get_state()->pc == 0)
        cmr.iType = iTypeUnsup;

    if(cmr.iType == iTypeLd)
        cmr.addr = this->lt.get_last_access();
    else if(cmr.iType == iTypeSt)
        cmr.addr = this->st.get_last_access();
    else if(cmr.iType == iTypeJoin)
        cmr.addr = this->st.get_last_access();
    else if(cmr.iType == iTypeBr || cmr.iType == iTypeJ || cmr.iType == iTypeJr)
        cmr.addr = this->active_thread[verifID]->get_state()->pc;
    else
        cmr.addr = 0;

    if(cmr.iType == iTypeUnsup) {
        this->active_thread[verifID]->get_state()->pc = cmr.pc+4;
    }
    
    return cmr;

}

bool CustomSpike::active(VerifID verifID) {
    return this->active_thread.count(verifID);
}

bool CustomSpike::dead(VerifID verifID) {
    return this->dead_thread.count(verifID);
}

void CustomSpike::fork(VerifID verifID, VerifID childverifID, Addr childpc) {

    this->add_proc(childverifID);

    this->active_thread[childverifID]->get_state()->pc = childpc;
    for (RIndx xi = 0; xi < 32; ++xi) {
        reg_t value = this->active_thread[verifID     ]->get_state()->XPR[xi & 0x1F];
                      this->active_thread[childverifID]->get_state()->XPR.write(xi & 0x1F, value);
    }

    return;

}

void CustomSpike::join(VerifID verifID, Data res) {

    if(res == 0) {
        this->remove_proc(verifID);
    }

}

std::map<VerifID, PerfCnt> CustomSpike::get_stats() {
    return commit_thread;
}

IType CustomSpike::getIType(const Data uinst) {

    uint32_t opcode = (uinst&0x0000007f);
    uint32_t rd     = (uinst&0x00000f80)>>7;

    switch (opcode) {
        case opOpImm:
            return iTypeAlu;
        case opOp:
            return iTypeAlu; 
        case opLui:
            return iTypeAlu;
        case opAuipc:
            return iTypeAuipc;
        case opFork:
            return (rd == 0 ? iTypeFork : (rd == 1 ? iTypeForkr : iTypeJoin));
        case opJal:
            return iTypeJ;
        case opJalr:
            return iTypeJr;
        case opBranch:
            return iTypeBr;
        case opLoad:
            return iTypeLd;
        case opStore:
            return iTypeSt;
        default:
            return iTypeUnsup;
    }

}

void CustomSpike::load_obj(std::string path) {

    std::ifstream input( path, std::ios::binary );

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    for (uint32_t addr = 0; addr < max_addr_mem-min_addr_mem; addr=addr+4) {

        uint32_t byte0 = (addr+0<(uint32_t)buffer.size()) ? buffer[addr+0] : 0;
        uint32_t byte1 = (addr+1<(uint32_t)buffer.size()) ? buffer[addr+1] : 0;
        uint32_t byte2 = (addr+2<(uint32_t)buffer.size()) ? buffer[addr+2] : 0;
        uint32_t byte3 = (addr+3<(uint32_t)buffer.size()) ? buffer[addr+3] : 0;
        Data word = byte3<<24|byte2<<16|byte1<<8|byte0;

        memcpy(((char*) mem) + addr, &word, 4);

    }

}

void CustomSpike::add_proc(VerifID verifID) {

    processor_t *new_proc = new processor_t(isa, DEFAULT_VARCH, this, 0, false, memif_endianness_little, NULL, sout_);
                            // processor_t(isa, varch, sim, id, halt_on_reset, endianess, log_file, sout_);

    new_proc->set_mmu_capability(IMPL_MMU_SBARE);
    new_proc->get_state()->pc = StartPC;
    new_proc->get_mmu()->register_memtracer(&(this->lt));
    new_proc->get_mmu()->register_memtracer(&(this->st));

    active_thread.insert ( std::pair<VerifID,processor_t*>(verifID, new_proc) );
    commit_thread.insert ( std::pair<VerifID,PerfCnt>(verifID, 0) );

}

void CustomSpike::remove_proc(VerifID verifID) {

    if(active_thread.count(verifID)) {

        processor_t *old_proc = active_thread[verifID];
        delete old_proc;
        active_thread.erase( verifID );
        dead_thread.insert(verifID);

    }

}