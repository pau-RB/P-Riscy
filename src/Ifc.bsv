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
	                        Bit#(64) cycle,   Bit#(64) commit,    Bit#(32) data,
	                        Bit#(64) fHit,    Bit#(64) fMiss,     Bit#(64) fEmpty,
	                        Bit#(64) aMemOvb, Bit#(64) aArithOvb, Bit#(64) aEmpty,
	                        Bit#(64) hLd,     Bit#(64) hSt,       Bit#(64) hJoin,
	                        Bit#(64) mLd,     Bit#(64) mSt,       Bit#(64) mJoin,
	                        Bit#(64) dLd,     Bit#(64) dSt,       Bit#(64) dJoin,
	                        Bit#(64) l2hWR,   Bit#(64) l2mWR,
	                        Bit#(64) l2hRD,   Bit#(64) l2mRD,
	                        Bit#(64) l2tWB );
endinterface