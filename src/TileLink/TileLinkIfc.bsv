import TileLinkTypes::*;

//////////// CAHCED TL ////////////

interface TileLinkMasterCached;

    // Master to Slave
    method ActionValue#(TLreqApacked) getA();
    method ActionValue#(TLreqCpacked) getC();
    method ActionValue#(TLreqEpacked) getE();

    // Slave to master
    method Action putB(TLreqB beat);
    method Action putD(TLreqD beat);

endinterface : TileLinkMasterCached

interface TileLinkSlaveCached;

    // Slave to master
    method ActionValue#(TLreqBpacked) getB();
    method ActionValue#(TLreqDpacked) getD();

    // Master to Slave
    method Action putA(TLreqA beat);
    method Action putC(TLreqC beat);
    method Action putE(TLreqE beat);

endinterface : TileLinkSlaveCached

//////////// UNCACHED TL ////////////

interface TileLinkMasterUncached;

    // Master to Slave
    method ActionValue#(TLreqApacked) getA();

    // Slave to master
    method Action putD(TLreqD beat);

endinterface : TileLinkMasterUncached

interface TileLinkSlaveUncached;

    // Slave to master
    method ActionValue#(TLreqDpacked) getD();

    // Master to Slave
    method Action putA(TLreqA beat);

endinterface : TileLinkSlaveUncached