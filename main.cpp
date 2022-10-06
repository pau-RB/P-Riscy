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
#include <iostream>

#include "FromHost.h"
#include "ToHost.h"
#include "TestbenchTypes.h"
#include "Interpreter.h"

using namespace std;

static FromHostProxy *connectalProc= 0;
volatile int run = 1;
uint32_t print_int = 0;

class ToHost: public ToHostWrapper 
{   
    private:

        void printCMR(const CommitReport cmr) {
            string phrase = " cycle:          | pc:          | iType:          | res:           ";
            overwrite(phrase, std::to_string(cmr.cycle),  8, 8 );
            overwrite(phrase,    uint_to_hex(cmr.pc   ), 23, 8 );
            overwrite(phrase,     printIType(cmr.iType), 41, 8 );
            overwrite(phrase,    uint_to_hex(cmr.wbRes), 57, 8 );
            printf("%s | %s\n", phrase.c_str(), interpreter(cmr.rawInst).c_str());
            fflush(stdout);
        }

    public:

        virtual void reportCMR (const uint32_t cycle, const uint32_t pc,  const uint32_t rawInst,
                        const uint8_t iType, const uint8_t wbDst, const uint32_t wbRes,  const uint32_t addr) {
            CommitReport cmr;
            cmr.cycle   = cycle   ;
            cmr.pc      = pc      ;
            cmr.rawInst = rawInst ;
            cmr.iType   = iType   ;
            cmr.wbDst   = wbDst   ;
            cmr.wbRes   = wbRes   ;
            cmr.addr    = addr    ;
            printCMR(cmr);
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
    for (uint32_t addr = 0; addr < (1<<WMBAddrSz)*CacheLineBytes; addr=addr+4) {
        srcfile >> std::hex >> word;
        connectalProc->setMem(addr, word);
    }

    connectalProc->startPC(0x200);
    printf("------ Core started! ------\n"); fflush(stdout);

    usleep(3000000);

    return 0;
}

