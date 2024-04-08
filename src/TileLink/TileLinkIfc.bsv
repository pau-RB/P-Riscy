import TileLinkTypes::*;


//////////// CAHCED TL ////////////

interface TileLinkMasterCached #(numeric type w, numeric type a);

    // Master to Slave
    method ActionValue#(TLreqA#(w,a)) getA();
    method ActionValue#(TLreqC#(w,a)) getC();
    method ActionValue#(TLreqE      ) getE();

    // Slave to master
    method Action putB(TLreqB#(w,a) beat);
    method Action putD(TLreqD#(w) beat);

endinterface : TileLinkMasterCached

interface TileLinkSlaveCached #(numeric type w, numeric type a);

    // Slave to master
    method ActionValue#(TLreqB#(w,a)) getB();
    method ActionValue#(TLreqD#(w)  ) getD();

    // Master to Slave
    method Action putA(TLreqA#(w,a) beat);
    method Action putC(TLreqC#(w,a) beat);
    method Action putE(TLreqE beat);

endinterface : TileLinkSlaveCached

//////////// UNCACHED TL ////////////

interface TileLinkMasterUncached #(numeric type w, numeric type a);

    // Master to Slave
    method ActionValue#(TLreqA#(w,a)) getA();

    // Slave to master
    method Action putD(TLreqD#(w) beat);

endinterface : TileLinkMasterUncached

interface TileLinkSlaveUncached #(numeric type w, numeric type a);

    // Slave to master
    method ActionValue#(TLreqD#(w)  ) getD();

    // Master to Slave
    method Action putA(TLreqA#(w,a) beat);

endinterface : TileLinkSlaveUncached