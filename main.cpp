#include <errno.h>
#include <stdio.h>
#include <cstring>
#include <cassert>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <signal.h>
#include <unistd.h>

#include "FromHost.h"
#include "ToHost.h"
#include "TestbenchTypes.h"
#include "CustomSpike.h"
#include "Tandem.h"
#include "Interpreter.h"


#define PRINT_COMMIT true

using namespace std;

// Custom spike
CustomSpike* spike;
Bool error_detected = false;

class ToHost: public ToHostWrapper {

    private:

    public:

        virtual void reportCMR (const uint32_t cycle,   const uint32_t verifID, const uint32_t pc,
                                const uint32_t rawInst, const uint8_t  iType,   const uint8_t  wbDst,
                                const uint32_t wbRes,   const uint32_t addr) {

            if(error_detected) {
                return;
            }

            // Get DUT commit
            CommitReport cmrDut;

            cmrDut.cycle   = cycle   ;
            cmrDut.verifID = verifID ;
            cmrDut.pc      = pc      ;
            cmrDut.rawInst = rawInst ;
            cmrDut.iType   = iType   ;
            cmrDut.wbDst   = wbDst   ;
            cmrDut.wbRes   = wbRes   ;
            cmrDut.addr    = addr    ;

            // Check if thread is active
            if(spike->dead(verifID)) {
                tandem_report("Unexpected commit from verifID: "+to_string(verifID));
                error_detected = true;
                return;
            }

            // Get Spike commit
            Data joinRead; memcpy(&joinRead, spike->addr_to_mem(addr), sizeof(addr));

            CommitReport cmrSpike = spike->step(verifID);

            if(cmrSpike.iType == iTypeJoin) {
                cmrSpike.wbRes = joinRead;
            }

            // Check
            tandem_mm mm = tandem_compare(cmrSpike, cmrDut);
            if(mm != tandem_mm::correct) {
                error_detected = true;
            }

            if(iType == iTypeFork) {
                spike->fork(verifID, wbRes, addr);
            }

            if(iType == iTypeJoin) {
                spike->join(verifID, wbRes);
            }

            // Print
            if (PRINT_COMMIT) {
                printCMRSpike(cmrSpike);
                printCMRDut  (cmrDut);
                printf("\n");
            }

            // Status
            if(error_detected) {
                print_stats(spike->get_stats());
            }

        }

        virtual void reportMSG ( const uint32_t verifID, const uint8_t msg ){

            if(error_detected) {
                return;
            }

            printMSGDut(verifID, msg);

        }
    
    ToHost(unsigned int id) : ToHostWrapper(id){}

};


// Connectal proxy
static FromHostProxy *connectalProc=0;
static ToHost        *connectalHost=0;

void initMemOBJ(string path) {

    std::ifstream input( path, std::ios::binary );

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    for (uint32_t addr = 0; addr < MEM_MAX_ADDR; addr=addr+4) {

        uint32_t byte0 = (addr+0<(uint32_t)buffer.size()) ? buffer[addr+0] : 0;
        uint32_t byte1 = (addr+1<(uint32_t)buffer.size()) ? buffer[addr+1] : 0;
        uint32_t byte2 = (addr+2<(uint32_t)buffer.size()) ? buffer[addr+2] : 0;
        uint32_t byte3 = (addr+3<(uint32_t)buffer.size()) ? buffer[addr+3] : 0;
        Data word = byte3<<24|byte2<<16|byte1<<8|byte0;

        connectalProc->setMem(addr, word);

    }
}

int main(int argc, char * const *argv) {

    string   current_exec_name = argv[0];
    vector<string> all_args;

    if (argc > 1) {
      all_args.assign(argv + 1, argv + argc);
    }

    printf("------ Start testbench ------\n"); fflush(stdout);
        connectalProc = new FromHostProxy(IfcNames_FromHostS2H);
        connectalHost = new ToHost(IfcNames_ToHostH2S);

    printf("------ Initializing memory ------\n"); fflush(stdout);
        string test = all_args[0];
        initMemOBJ(test);

    printf("------ Setup Spike ------\n"); fflush(stdout);
        spike = new CustomSpike(test, MEM_MAX_ADDR);

    printf("------ Start core ------\n"); fflush(stdout);
    int sim_threads = std::stoi(all_args[1]);
        for(int i = 0; i < sim_threads; ++i)
            connectalProc->startPC(StartPC);

    uint32_t sim_time = std::stoi(all_args[2]);
    usleep(sim_time*1000000);

    if(!error_detected) {
        print_stats(spike->get_stats());
    }

    return 0;
    
}