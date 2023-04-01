interface FromHost;
	method Action setMem (Bit#(32) addr, Bit#(32) word);
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action reportCMR(Bit#(32) cycle, Bit#(32) verifID, Bit#(32) pc, Bit#(32) rawInst, Bit#(8) iType, Bit#(8) wbDst, Bit#(32) wbRes, Bit#(32) addr);
	method Action reportMSG(Bit#(32) verifID, Bit#(32) cycle, Bit#(32) commit, Bit#(32) data);
	method Action reportHEX(Bit#(32) verifID, Bit#(32) cycle, Bit#(32) commit, Bit#(32) data);
	method Action reportMSR(Bit#(32) verifID,
	                        Bit#(32) cycle,   Bit#(32) commit,    Bit#(32) data,
	                        Bit#(32) fHit,    Bit#(32) fMiss,     Bit#(32) fEmpty,
	                        Bit#(32) aMemOvb, Bit#(32) aArithOvb, Bit#(32) aEmpty,
	                        Bit#(32) hLd,     Bit#(32) hSt,       Bit#(32) hJoin,
	                        Bit#(32) mLd,     Bit#(32) mSt,       Bit#(32) mJoin,
	                        Bit#(32) dLd,     Bit#(32) dSt,       Bit#(32) dJoin,
	                        Bit#(32) l2hWR,   Bit#(32) l2mWR,
	                        Bit#(32) l2hRD,   Bit#(32) l2mRD,
	                        Bit#(32) l2tWB );
endinterface