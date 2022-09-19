#include "GeneratedTypes.h"
#ifndef _TOHOST_H_
#define _TOHOST_H_
#include "portal.h"

class ToHostProxy : public Portal {
    ToHostCb *cb;
public:
    ToHostProxy(int id, int tile = DEFAULT_TILE, ToHostCb *cbarg = &ToHostProxyReq, int bufsize = ToHost_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    ToHostProxy(int id, PortalTransportFunctions *transport, void *param, ToHostCb *cbarg = &ToHostProxyReq, int bufsize = ToHost_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    ToHostProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, ToHost_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&ToHostProxyReq) {};
    int print ( const uint32_t word ) { return cb->print (&pint, word); };
};

extern ToHostCb ToHost_cbTable;
class ToHostWrapper : public Portal {
public:
    ToHostWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = ToHost_handleMessage, int bufsize = ToHost_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&ToHost_cbTable, this, poller) {
    };
    ToHostWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = ToHost_handleMessage, int bufsize = ToHost_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&ToHost_cbTable, transport, param, this, poller) {
    };
    ToHostWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, ToHost_reqinfo, ToHost_handleMessage, (void *)&ToHost_cbTable, this, poller) {
    };
    ToHostWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, ToHost_reqinfo, ToHost_handleMessage, (void *)&ToHost_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("ToHostWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void print ( const uint32_t word ) = 0;
};
#endif // _TOHOST_H_
