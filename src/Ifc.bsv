interface FromHost;
	method Action tstMem (Bit#(64) testlen, Bit#(8) testtyp, Bit#(32) teststr);
	method Action setMem (Bit#(32) addr, Bit#(32) word);
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action testMem  (Bit#(64) testlen, Bit#(8)  testtyp, Bit#(32) teststr,
	                        Bit#(64) latency, Bit#(64) delayTX, Bit#(64) delayRX);
	method Action reportCMR(Bit#(64) cycle, Bit#(32) verifID, Bit#(32) pc, Bit#(32) rawInst, Bit#(8) iType, Bit#(8) wbDst, Bit#(32) wbRes, Bit#(32) addr);
	method Action reportMSG(Bit#(32) verifID, Bit#(64) cycle, Bit#(64) commit, Bit#(32) data);
	method Action reportHEX(Bit#(32) verifID, Bit#(64) cycle, Bit#(64) commit, Bit#(32) data);
	method Action reportMSR(Bit#(32) verifID,
	                        Bit#(64) cycle  , Bit#(64) commit   , Bit#(32) data    ,

	                        Bit#(64) l1IhRD ,
	                        Bit#(64) l1ImRD ,

	                        Bit#(64) l1DhLd , Bit#(64) l1DhSt   , Bit#(64) l1DhJoin,
	                        Bit#(64) l1DmLd , Bit#(64) l1DmSt   , Bit#(64) l1DmJoin,

	                        Bit#(64) l2ShRD , Bit#(64) l2ShWR   , Bit#(64) l2StWB  ,
	                        Bit#(64) l2SmRD , Bit#(64) l2SmWR                      );
endinterface