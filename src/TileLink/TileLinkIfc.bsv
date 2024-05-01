import TileLinkTypes::*;

//////////// CAHCED TL ////////////

interface TileLinkMasterCached;

    // Master to Slave
    method ActionValue#(TLreqApacked) getA();
    method ActionValue#(TLreqCpacked) getC();
    method ActionValue#(TLreqEpacked) getE();

    // Slave to master
    method Action putB(TLreqBpacked beat);
    method Action putD(TLreqDpacked beat);

endinterface : TileLinkMasterCached

interface TileLinkSlaveCached;

    // Slave to master
    method ActionValue#(TLreqBpacked) getB();
    method ActionValue#(TLreqDpacked) getD();

    // Master to Slave
    method Action putA(TLreqApacked beat);
    method Action putC(TLreqCpacked beat);
    method Action putE(TLreqEpacked beat);

endinterface : TileLinkSlaveCached

//////////// UNCACHED TL ////////////

interface TileLinkMasterUncached;

    // Master to Slave
    method ActionValue#(TLreqApacked) getA();

    // Slave to master
    method Action putD(TLreqDpacked beat);

endinterface : TileLinkMasterUncached

interface TileLinkSlaveUncached;

    // Slave to master
    method ActionValue#(TLreqDpacked) getD();

    // Master to Slave
    method Action putA(TLreqApacked beat);

endinterface : TileLinkSlaveUncached