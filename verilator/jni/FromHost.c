#include "GeneratedTypes.h"

int FromHost_startPC ( struct PortalInternal *p, const uint32_t pc )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_FromHost_startPC, 2);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_FromHost_startPC, "FromHost_startPC")) return 1;
    p->transport->write(p, &temp_working_addr, pc);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_FromHost_startPC << 16) | 2, -1);
    return 0;
};

FromHostCb FromHostProxyReq = {
    portal_disconnect,
    FromHost_startPC,
};
FromHostCb *pFromHostProxyReq = &FromHostProxyReq;

const uint32_t FromHost_reqinfo = 0x10008;
const char * FromHost_methodSignatures()
{
    return "{\"startPC\": [\"long\"]}";
}

int FromHost_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    FromHostData tempdata __attribute__ ((unused));
    memset(&tempdata, 0, sizeof(tempdata));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    switch (channel) {
    case CHAN_NUM_FromHost_startPC: {
        p->transport->recv(p, temp_working_addr, 1, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.startPC.pc = (uint32_t)(((tmp)&0xfffffffful));
        ((FromHostCb *)p->cb)->startPC(p, tempdata.startPC.pc);
      } break;
    default:
        PORTAL_PRINTF("FromHost_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("FromHost_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
