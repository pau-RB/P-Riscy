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
                                 const uint64_t cycle,   const uint64_t commit,    const uint32_t data,
                                 const uint64_t fHit,    const uint64_t fMiss,     const uint64_t fEmpty, 
                                 const uint64_t aMemOvb, const uint64_t aArithOvb, const uint64_t aEmpty, 
                                 const uint64_t hLd,     const uint64_t hSt,       const uint64_t hJoin,
                                 const uint64_t mLd,     const uint64_t mSt,       const uint64_t mJoin,
                                 const uint64_t dLd,     const uint64_t dSt,       const uint64_t dJoin,
                                 const uint64_t l2hWR,   const uint64_t l2mWR,     
                                 const uint64_t l2hRD,   const uint64_t l2mRD,
                                 const uint64_t l2tWB){

            if(error_detected >= ERROR_THRESHOLD)
                return;

            FetchStat   fetch  ;
            ArbiterStat arbiter;
            LSUStat     lsu    ;
            WMCStat     l2s    ;
            MemStat     msr    ;

            fetch.hit        = fHit     ;
            fetch.miss       = fMiss    ;
            fetch.empty      = fEmpty   ;

            arbiter.memOvb   = aMemOvb  ;
            arbiter.arithOvb = aArithOvb;
            arbiter.empty    = aEmpty   ;

            lsu.hLd          = hLd      ;
            lsu.hSt          = hSt      ;
            lsu.hJoin        = hJoin    ;
            lsu.mLd          = mLd      ;
            lsu.mSt          = mSt      ;
            lsu.mJoin        = mJoin    ;
            lsu.dLd          = dLd      ;
            lsu.dSt          = dSt      ;
            lsu.dJoin        = dJoin    ;

            l2s.hWR          = l2hWR    ;
            l2s.mWR          = l2mWR    ;
            l2s.hRD          = l2hRD    ;
            l2s.mRD          = l2mRD    ;
            l2s.tWB          = l2tWB    ;

            msr.verifID      = verifID  ;
            msr.cycle        = cycle    ;
            msr.commit       = commit   ;
            msr.data         = data     ;
            msr.fetch        = fetch    ;
            msr.arbiter      = arbiter  ;
            msr.lsu          = lsu      ;
            msr.l2s          = l2s      ;

            inter->print_MSR_dut(msr);

        }
    
    ToHost(unsigned int id) : ToHostWrapper(id){}

};


// Connectal proxy
static FromHostProxy *connectalProc=0;
static ToHost        *connectalHost=0;

void testMem() {

    connectalProc->tstMem(100, RDLAT, 0);
    connectalProc->tstMem(100, RDLAT, 1);
    connectalProc->tstMem(100, RDLAT, 5);

    connectalProc->tstMem(100, MXLAT, 0);
    connectalProc->tstMem(100, MXLAT, 1);
    connectalProc->tstMem(100, MXLAT, 5);

    connectalProc->tstMem(100, RDTHP, 0);
    connectalProc->tstMem(100, RDTHP, 1);
    connectalProc->tstMem(100, RDTHP, 5);

    connectalProc->tstMem(100, WRTHP, 0);
    connectalProc->tstMem(100, WRTHP, 1);
    connectalProc->tstMem(100, WRTHP, 5);

    connectalProc->tstMem(100, MXTHP, 0);
    connectalProc->tstMem(100, MXTHP, 1);
    connectalProc->tstMem(100, MXTHP, 5);

    connectalProc->tstMem(100, TTEND, 0);

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