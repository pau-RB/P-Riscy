#ifndef _CUSTOM_SPIKE_H
#define _CUSTOM_SPIKE_H

#include <vector>
#include <set>

#include "simif.h"
#include "isa_parser.h"
#include "processor.h"
#include "LoadTracer.h"
#include "StoreTracer.h"
#include "TestbenchTypes.h"

class CustomSpike : public simif_t {
    public:

    	// class
        CustomSpike(isa_parser_t *isa, const std::string elf_file, size_t memory_sz);
        ~CustomSpike();

        // simif_t
        char* addr_to_mem(reg_t addr);
        bool mmio_load(reg_t addr, size_t len, uint8_t* bytes);
        bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes);
        void proc_reset(unsigned id) { /* do nothing */ }
        const char* get_symbol(uint64_t addr);

        // custom
       	CommitReport step(VerifID verifID);
        bool active(VerifID verifID);
        bool dead(VerifID verifID);
        void fork(VerifID verifID, VerifID childverifID, Addr childpc);
        void join(VerifID verifID, Data res);
        std::map<VerifID, PerfCnt> get_stats();

    private:
        isa_parser_t *isa;
        std::ostream sout_;
        std::map<VerifID, processor_t*> active_thread;
        std::set<VerifID> dead_thread;
        std::map<VerifID, PerfCnt> commit_thread;

        char*        mem;
        size_t       mem_sz;

        Data         cycleCnt;
        loadTracer   lt;
        storeTracer  st;

        IType getIType(const Data uinst);
        void load_obj(std::string path);
        void add_proc(VerifID id);
        void remove_proc(VerifID id);

};

#endif