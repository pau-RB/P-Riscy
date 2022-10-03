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
#include "interpreter.h"

#define CacheLineWords 16
#define CacheLineBytes 64
#define WMBAddrSz 12

using namespace std;

static FromHostProxy *connectalProc= 0;
volatile int run = 1;
uint32_t print_int = 0;

class ToHost: public ToHostWrapper 
{   
    private:
        // Overwrite part of a string
        void overwrite (string &base, const string &text, int position, int max) {
            int base_size = base.size();
            int text_size = text.size();
        
            if(text_size < max) {
                position += (max-text_size)/2;
            }
        
            for (int i = 0; i < text_size && i < max; ++i) {
                if (position+i < base_size)
                    base[position+i] = text[i];
                else
                    base += text[i]; 
            }
        }

        std::string printIType (const uint32_t iType) {
            switch (iType) {
                case 0:
                    return "Unsup";
                case 1:
                    return "Alu";
                case 2:
                    return "Ld";
                case 3:
                    return "St";
                case 4:
                    return "J";
                case 5:
                    return "Jr";
                case 6:
                    return "Br";
                case 7:
                    return "Csrr";
                case 8:
                    return "Csrw";
                case 9:
                    return "Auipc";
                default:
                    return "???";
            }
        }

    public:
        virtual void printCMR ( const uint32_t cycle, const uint32_t pc, const uint32_t iType, const uint32_t res, const uint32_t rawInst){
            string phrase = " cycle:          | pc:          | iType:          | res:           ";
            overwrite(phrase, std::to_string(cycle),  8, 8 );
            overwrite(phrase,    uint_to_hex(pc   ), 23, 8 );
            overwrite(phrase,     printIType(iType), 41, 8 );
            overwrite(phrase,    uint_to_hex(res  ), 57, 8 );
            printf("%s | %s\n", phrase.c_str(), interpreter(rawInst).c_str());
            fflush(stdout);
        }

        virtual void printMSG ( const uint32_t msg){
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

    while (run != 0){}     
    return 0;
}

