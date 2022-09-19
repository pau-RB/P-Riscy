#include "GeneratedTypes.h"

int ToHost_print ( struct PortalInternal *p, const uint32_t word )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_ToHost_print, 2);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_ToHost_print, "ToHost_print")) return 1;
    p->transport->write(p, &temp_working_addr, word);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_ToHost_print << 16) | 2, -1);
    return 0;
};

ToHostCb ToHostProxyReq = {
    portal_disconnect,
    ToHost_print,
};
ToHostCb *pToHostProxyReq = &ToHostProxyReq;

const uint32_t ToHost_reqinfo = 0x10008;
const char * ToHost_methodSignatures()
{
    return "{\"print\": [\"long\"]}";
}

int ToHost_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    ToHostData tempdata __attribute__ ((unused));
    memset(&tempdata, 0, sizeof(tempdata));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    switch (channel) {
    case CHAN_NUM_ToHost_print: {
        p->transport->recv(p, temp_working_addr, 1, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.print.word = (uint32_t)(((tmp)&0xfffffffful));
        ((ToHostCb *)p->cb)->print(p, tempdata.print.word);
      } break;
    default:
        PORTAL_PRINTF("ToHost_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("ToHost_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
