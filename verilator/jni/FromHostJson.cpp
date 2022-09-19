#include "GeneratedTypes.h"
#ifdef PORTAL_JSON
#include "jsoncpp/json/json.h"

int FromHostJson_startPC ( struct PortalInternal *p, const uint32_t pc )
{
    Json::Value request;
    request.append(Json::Value("startPC"));
    request.append((Json::UInt64)pc);

    std::string requestjson = Json::FastWriter().write(request);;
    connectalJsonSend(p, requestjson.c_str(), (int)CHAN_NUM_FromHost_startPC);
    return 0;
};

FromHostCb FromHostJsonProxyReq = {
    portal_disconnect,
    FromHostJson_startPC,
};
FromHostCb *pFromHostJsonProxyReq = &FromHostJsonProxyReq;
const char * FromHostJson_methodSignatures()
{
    return "{\"startPC\": [\"long\"]}";
}

int FromHostJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    FromHostData tempdata __attribute__ ((unused));
    memset(&tempdata, 0, sizeof(tempdata));
    Json::Value msg = Json::Value(connectalJsonReceive(p));
    switch (channel) {
    case CHAN_NUM_FromHost_startPC: {
        ((FromHostCb *)p->cb)->startPC(p, tempdata.startPC.pc);
      } break;
    default:
        PORTAL_PRINTF("FromHostJson_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("FromHostJson_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
#endif /* PORTAL_JSON */
