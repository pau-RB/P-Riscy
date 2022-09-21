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

#include "FromHost.h"
#include "ToHost.h"

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

        std::string uint_to_hex(uint32_t w) {
            static const char* digits = "0123456789ABCDEF";
            std::string rc(8,'0');
            for (size_t i=0, j=(8-1)*4 ; i<8; ++i,j-=4)
                rc[i] = digits[(w>>j) & 0x0f];
            return rc;
        }

    public:
        virtual void print ( const uint32_t cycle, const uint32_t pc, const uint32_t iType, const uint32_t res ){
            string phrase = " cycle:          | pc:          | iType:          | res:           ";
            overwrite(phrase, std::to_string(cycle),  8, 8 );
            overwrite(phrase,    uint_to_hex(pc   ), 23, 8 );
            overwrite(phrase,     printIType(iType), 41, 8 );
            overwrite(phrase,    uint_to_hex(res  ), 57, 8 );
            printf("%s\n", phrase.c_str());
        }
    
    ToHost(unsigned int id) : ToHostWrapper(id){}
};

static ToHost *ind = 0;
int main(int argc, char * const *argv) {
    printf("Start testbench:\n");
    fflush(stdout);
    connectalProc = new FromHostProxy(IfcNames_FromHostS2H);
    ind = new ToHost(IfcNames_ToHostH2S);
    connectalProc->startPC(0x200);
    printf("Processor started");
    fflush(stdout);
    // Now the processor is running we are waiting for it to be done 
    while (run != 0){}     
    return 0;
}

