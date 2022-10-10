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

static FromHostProxy *connectalProc= 0;
volatile int run = 1;
uint32_t print_int = 0;

CustomSpike* spike;

class ToHost: public ToHostWrapper 
{   
    private:

    public:

        virtual void reportCMR (const uint32_t cycle, const uint32_t pc,  const uint32_t rawInst,
                        const uint8_t iType, const uint8_t wbDst, const uint32_t wbRes,  const uint32_t addr) {

            // Get DUT commit
            CommitReport cmrDut;

            cmrDut.cycle   = cycle   ;
            cmrDut.pc      = pc      ;
            cmrDut.rawInst = rawInst ;
            cmrDut.iType   = iType   ;
            cmrDut.wbDst   = wbDst   ;
            cmrDut.wbRes   = wbRes   ;
            cmrDut.addr    = addr    ;

            // Get Spike commit
            CommitReport cmrSpike = spike->step();

            // Check
            tandem_compare(cmrSpike, cmrDut);

            // Print
            if (PRINT_COMMIT) {
                printCMRSpike(cmrSpike);
                printCMRDut  (cmrDut);
                printf("\n");
            }

        }

        virtual void reportMSG ( const uint32_t msg){
            printf("MESSAGE:  %s\n", uint_to_hex(msg).c_str());
            fflush(stdout);
        }
    
    ToHost(unsigned int id) : ToHostWrapper(id){}
};

static ToHost *ind = 0;
int main(int argc, char * const *argv) {

    string current_exec_name = argv[0];
    vector<string> all_args;

    if (argc > 1) {
      all_args.assign(argv + 1, argv + argc);
    }

    printf("------ Start testbench ------\n"); fflush(stdout);
    connectalProc = new FromHostProxy(IfcNames_FromHostS2H);
    ind = new ToHost(IfcNames_ToHostH2S);

    printf("------ Initializing memory ------\n"); fflush(stdout);
    string test = all_args[0];
    string path = "./vmh/"+ test +".riscv.vmh";
    ifstream srcfile; srcfile.open(path,fstream::in|fstream::out|fstream::app);

    uint32_t word;
    string aux;
    srcfile >> aux;
    for (uint32_t addr = 0; addr < MEM_MAX_ADDR; addr=addr+4) {
        srcfile >> std::hex >> word;
        connectalProc->setMem(addr, word);
    }

    printf("------ Setup Spike ------\n"); fflush(stdout);
    spike = new CustomSpike(path, MEM_MAX_ADDR);

    connectalProc->startPC(StartPC);
    printf("------ Core started! ------\n"); fflush(stdout);

    usleep(3000000);

    return 0;
}

