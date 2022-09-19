#include "GeneratedTypes.h"
#ifndef _FROMHOST_H_
#define _FROMHOST_H_
#include "portal.h"

class FromHostProxy : public Portal {
    FromHostCb *cb;
public:
    FromHostProxy(int id, int tile = DEFAULT_TILE, FromHostCb *cbarg = &FromHostProxyReq, int bufsize = FromHost_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    FromHostProxy(int id, PortalTransportFunctions *transport, void *param, FromHostCb *cbarg = &FromHostProxyReq, int bufsize = FromHost_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    FromHostProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, FromHost_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&FromHostProxyReq) {};
    int startPC ( const uint32_t pc ) { return cb->startPC (&pint, pc); };
};

extern FromHostCb FromHost_cbTable;
class FromHostWrapper : public Portal {
public:
    FromHostWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = FromHost_handleMessage, int bufsize = FromHost_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&FromHost_cbTable, this, poller) {
    };
    FromHostWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = FromHost_handleMessage, int bufsize = FromHost_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&FromHost_cbTable, transport, param, this, poller) {
    };
    FromHostWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, FromHost_reqinfo, FromHost_handleMessage, (void *)&FromHost_cbTable, this, poller) {
    };
    FromHostWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, FromHost_reqinfo, FromHost_handleMessage, (void *)&FromHost_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("FromHostWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void startPC ( const uint32_t pc ) = 0;
};
#endif // _FROMHOST_H_
