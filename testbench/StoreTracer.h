#ifndef STORETRACER_H
#define STORETRACER_H

#include <cstdint>
#include <string.h>
#include <vector>

// Testbench
#include "TestbenchTypes.h"

// Spike
#include "memtracer.h"


class storeTracer : public memtracer_t
{
    private:
        Addr last_access = 0;

    public:
        bool interested_in_range(uint64_t begin, uint64_t end, access_type type) {
            return (type==STORE);
        }

        void trace(uint64_t addr, size_t bytes, access_type type) {
            last_access = addr;
        }

        void clean_invalidate(uint64_t addr, size_t bytes, bool clean, bool inval) {
            last_access = 0;
        }

        Addr get_last_access() {
            return last_access;
        }
};

#endif
