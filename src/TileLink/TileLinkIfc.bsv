import TileLinkTypes::*;

//////////// CAHCED TL ////////////

interface TileLinkMasterCached;

    // Master to Slave

    // Look at packet if tl-valid
    method TLreqApacked getA();
    method TLreqCpacked getC();
    method TLreqEpacked getE();

    // Assert tl-ready if taken
    method Action readyA();
    method Action readyC();
    method Action readyE();

    // Slave to master

    // Present packet and assert tl-valid
    (* always_ready *)
    method Action putB(TLreqBpacked beat);
    (* always_ready *)
    method Action putD(TLreqDpacked beat);

    // Inform wether tl-ready
    (* always_ready *)
    method Bool readyB();
    (* always_ready *)
    method Bool readyD();

endinterface : TileLinkMasterCached

interface TileLinkSlaveCached;

    // Slave to master

    // Look at packet if tl-valid
    method TLreqBpacked getB();
    method TLreqDpacked getD();

    // Assert tl-ready if taken
    method Action readyB();
    method Action readyD();

    // Master to Slave

    // Present packet and assert tl-valid
    (* always_ready *)
    method Action putA(TLreqApacked beat);
    (* always_ready *)
    method Action putC(TLreqCpacked beat);
    (* always_ready *)
    method Action putE(TLreqEpacked beat);

    // Inform wether tl-ready
    (* always_ready *)
    method Bool readyA();
    (* always_ready *)
    method Bool readyC();
    (* always_ready *)
    method Bool readyE();

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