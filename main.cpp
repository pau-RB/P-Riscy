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

#include "Platform.hpp"
#include "FromHost.h"
#include "ToHost.h"

using namespace std;

static FromHostProxy *connectalProc= 0;
static ConnectalMemoryInitializationProxy *memoryRequest = 0; 
static Platform *platform = 0;
static sem_t responseSem;
volatile int run = 1;
uint32_t print_int = 0;

class ToHost: public ToHostWrapper 
{
public:
    virtual void print ( const uint32_t word ){
        printf("pc    %d: ", word   );
    }
   ToHost(unsigned int id) : ToHostWrapper(id){}
};

static ToHost *ind = 0;
int main(int argc, char * const *argv) {

    printf("Start testbench:\n"); fflush(stdout);

    connectalProc = new FromHostProxy(IfcNames_FromHostS2H);
    ind           = new ToHost(IfcNames_ToHostH2S);
    memoryRequest = new ConnectalMemoryInitializationProxy(IfcNames_ConnectalMemoryInitializationS2H);
    platform      = new Platform(memoryRequest, &responseSem);

    char cwd[1024];
    platform->load_elf(strcat(getcwd(cwd,sizeof(cwd)),"/program"));
    memoryRequest->done();
    connectalProc->startPC(0x200);

    printf("Processor started"); fflush(stdout);

    while (run != 0){}     
    return 0;
}

