#ifndef _CUSTOM_SPIKE_H
#define _CUSTOM_SPIKE_H

#include <vector>

#include "simif.h"
#include "processor.h"
#include "LoadTracer.h"
#include "StoreTracer.h"
#include "TestbenchTypes.h"
#include "Tandem.h"

class CustomSpike : public simif_t {
    public:

    	// class
        CustomSpike(const std::string elf_file, size_t memory_sz);
        ~CustomSpike();

        // simif_t
        char* addr_to_mem(reg_t addr);
        bool mmio_load(reg_t addr, size_t len, uint8_t* bytes);
        bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes);
        void proc_reset(unsigned id) { /* do nothing */ }
        const char* get_symbol(uint64_t addr);

        // custom
       	CommitReport step(VerifID feID);

    private:
        isa_parser_t isa;
        std::ostream sout_;
        std::map<VerifID, processor_t*> proc;
        std::map<VerifID, Addr> fp;

        char*        mem;
        size_t       mem_sz;

        Data         cycleCnt;
        loadTracer   lt;
        storeTracer  st;

        void load_vmh(std::string path);
        void add_proc(VerifID id, Addr pc, Addr fp);
        void remove_proc(VerifID id);

};

#endif