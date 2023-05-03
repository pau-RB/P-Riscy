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


#define PRINT_COMMIT false
#define ERROR_THRESHOLD  4

using namespace std;

isa_parser_t*isa;
CustomSpike *spike;
Interpreter *inter;

uint32_t error_detected = 0;

class ToHost: public ToHostWrapper {

    private:

    public:

        virtual void testMem   (const uint64_t testlen, const uint8_t  testtyp, const uint32_t teststr,
                                const uint64_t latency, const uint64_t delayTX, const uint64_t delayRX) {

            TestRes tst;

            tst.testlen = testlen;
            tst.testtyp = testtyp;
            tst.teststr = teststr;
            tst.latency = latency;
            tst.delayTX = delayTX;
            tst.delayRX = delayRX;

            inter->print_TST_dut(tst);

        }

        virtual void reportCMR (const uint64_t cycle,   const uint32_t verifID, const uint32_t pc,
                                const uint32_t rawInst, const uint8_t  iType,   const uint8_t  wbDst,
                                const uint32_t wbRes,   const uint32_t addr) {

            if(error_detected >= ERROR_THRESHOLD)
                return;

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
                ++error_detected;
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
                ++error_detected;
            }

            if(iType == iTypeFork || iType == iTypeForkr) {
                spike->fork(verifID, wbRes, addr);
            }

            if(iType == iTypeJoin) {
                spike->join(verifID, wbRes);
            }

            // Print
            if (PRINT_COMMIT || error_detected > 0) {
                inter->print_CMR_spk(cmrSpike);
                inter->print_CMR_dut(cmrDut);
                printf("\n");
            }

            // Status
            if(error_detected >= ERROR_THRESHOLD) {
                inter->print_stats(spike->get_stats());
                delete spike;
            }

        }

        virtual void reportMSG ( const uint32_t verifID, const uint64_t cycle,
                                 const uint64_t commit,  const uint32_t data ){

            if(error_detected >= ERROR_THRESHOLD)
                return;

            Message msg;
            msg.verifID = verifID;
            msg.cycle   = cycle  ;
            msg.commit  = commit ;
            msg.data    = data   ;

            inter->print_MSG_dut(msg);

        }

        virtual void reportHEX ( const uint32_t verifID, const uint64_t cycle,
                                 const uint64_t commit,  const uint32_t data ){

            if(error_detected >= ERROR_THRESHOLD)
                return;

            Message msg;
            msg.verifID = verifID;
            msg.cycle   = cycle  ;
            msg.commit  = commit ;
            msg.data    = data   ;

            inter->print_HEX_dut(msg);

        }

        virtual void reportMSR ( const uint32_t verifID,
                                 const uint64_t cycle  , const uint64_t commit, const uint32_t data    ,
                                 const uint64_t l1IhRD ,
                                 const uint64_t l1ImRD ,
                                 const uint64_t l1DhLd , const uint64_t l1DhSt, const uint64_t l1DhJoin,
                                 const uint64_t l1DmLd , const uint64_t l1DmSt, const uint64_t l1DmJoin,
                                 const uint64_t l2ShRD , const uint64_t l2ShWR, const uint64_t l2StWB  ,
                                 const uint64_t l2SmRD , const uint64_t l2SmWR                         ){

            if(error_detected >= ERROR_THRESHOLD)
                return;

            MemStat msr;
            msr.verifID        = verifID ;
            msr.cycle          = cycle   ;
            msr.commit         = commit  ;
            msr.data           = data    ;

            msr.l1IStat.hRD    = l1IhRD  ;
            msr.l1IStat.mRD    = l1ImRD  ;

            msr.l1DStat.hLd    = l1DhLd  ;
            msr.l1DStat.hSt    = l1DhSt  ;
            msr.l1DStat.hJoin  = l1DhJoin;
            msr.l1DStat.mLd    = l1DmLd  ;
            msr.l1DStat.mSt    = l1DmSt  ;
            msr.l1DStat.mJoin  = l1DmJoin;

            msr.l2SStat.hWR    = l2ShWR  ;
            msr.l2SStat.mWR    = l2SmWR  ;
            msr.l2SStat.hRD    = l2ShRD  ;
            msr.l2SStat.mRD    = l2SmRD  ;
            msr.l2SStat.tWB    = l2StWB  ;

            inter->print_MSR_dut(msr);

        }

    ToHost(unsigned int id) : ToHostWrapper(id){}

};


// Connectal proxy
static FromHostProxy *connectalProc=0;
static ToHost        *connectalHost=0;

void testMem() {

    connectalProc->tstMem(100 , RDLAT, 0);
    connectalProc->tstMem(100 , RDLAT, 1);
    connectalProc->tstMem(100 , RDLAT, 5);

    connectalProc->tstMem(100 , MXLAT, 0);
    connectalProc->tstMem(100 , MXLAT, 1);
    connectalProc->tstMem(100 , MXLAT, 5);

    connectalProc->tstMem(1000, RDTHP, 0);
    connectalProc->tstMem(1000, RDTHP, 1);
    connectalProc->tstMem(1000, RDTHP, 5);

    connectalProc->tstMem(1000, WRTHP, 0);
    connectalProc->tstMem(1000, WRTHP, 1);
    connectalProc->tstMem(1000, WRTHP, 5);

    connectalProc->tstMem(1000, MXTHP, 0);
    connectalProc->tstMem(1000, MXTHP, 1);
    connectalProc->tstMem(1000, MXTHP, 5);

    connectalProc->tstMem(1000, TTEND, 0);

}

void initMemOBJ(string path) {

    std::ifstream input( path, std::ios::binary );

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    for (uint32_t addr = 0; addr < MEM_MAX_ADDR && addr<(uint32_t)buffer.size(); addr=addr+4) {

        uint32_t byte0 = (addr+0<(uint32_t)buffer.size()) ? buffer[addr+0] : 0;
        uint32_t byte1 = (addr+1<(uint32_t)buffer.size()) ? buffer[addr+1] : 0;
        uint32_t byte2 = (addr+2<(uint32_t)buffer.size()) ? buffer[addr+2] : 0;
        uint32_t byte3 = (addr+3<(uint32_t)buffer.size()) ? buffer[addr+3] : 0;
        Data word = byte3<<24|byte2<<16|byte1<<8|byte0;

        connectalProc->setMem(addr, word);
    }

    connectalProc->setMem(MEM_MAX_ADDR, 0);

}

int main(int argc, char * const *argv) {

    string   current_exec_name = argv[0];
    vector<string> all_args;

    if (argc > 1) {
      all_args.assign(argv + 1, argv + argc);
    }

    printf("------------ Start testbench     ------------\n"); fflush(stdout);
        connectalProc = new FromHostProxy(IfcNames_FromHostS2H);
        connectalHost = new ToHost(IfcNames_ToHostH2S);

    #ifdef MEMTEST
    printf("------------ Testing memory    ------------\n"); fflush(stdout);
        testMem();
    #endif

    printf("------------ Initializing memory ------------\n"); fflush(stdout);
        string test = all_args[0];
        initMemOBJ(test);

    printf("------------ Setup Spike         ------------\n"); fflush(stdout);
        isa   = new isa_parser_t("RV32IM", "m");
        spike = new CustomSpike(isa, test, MEM_MAX_ADDR);
        inter = new Interpreter(isa);

    printf("------------ Start core          ------------\n"); fflush(stdout);
    int sim_threads = std::stoi(all_args[1]);
        for(int i = 0; i < sim_threads; ++i)
            connectalProc->startPC(StartPC);

    uint32_t sim_time = std::stoi(all_args[2]);
    usleep(sim_time*1000000);

    if(error_detected == 0)
        inter->print_stats(spike->get_stats());

    return 0;
    
}