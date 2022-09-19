#include "GeneratedTypes.h"
#ifdef PORTAL_JSON
#include "jsoncpp/json/json.h"

int ToHostJson_print ( struct PortalInternal *p, const uint32_t word )
{
    Json::Value request;
    request.append(Json::Value("print"));
    request.append((Json::UInt64)word);

    std::string requestjson = Json::FastWriter().write(request);;
    connectalJsonSend(p, requestjson.c_str(), (int)CHAN_NUM_ToHost_print);
    return 0;
};

ToHostCb ToHostJsonProxyReq = {
    portal_disconnect,
    ToHostJson_print,
};
ToHostCb *pToHostJsonProxyReq = &ToHostJsonProxyReq;
const char * ToHostJson_methodSignatures()
{
    return "{\"print\": [\"long\"]}";
}

int ToHostJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    ToHostData tempdata __attribute__ ((unused));
    memset(&tempdata, 0, sizeof(tempdata));
    Json::Value msg = Json::Value(connectalJsonReceive(p));
    switch (channel) {
    case CHAN_NUM_ToHost_print: {
        ((ToHostCb *)p->cb)->print(p, tempdata.print.word);
      } break;
    default:
        PORTAL_PRINTF("ToHostJson_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("ToHostJson_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
#endif /* PORTAL_JSON */
