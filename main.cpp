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
public:
    virtual void print(uint32_t msg){
	  // THIS IS THE CODE BEING CALLED ASYNCHRONOUSLY WHEN YOUR HARDWARE DESIGN CALL THE ind.print(mess)  
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

