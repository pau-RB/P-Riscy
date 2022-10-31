interface FromHost;
	method Action setMem (Bit#(32) addr, Bit#(32) word);
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action reportCMR(Bit#(32) cycle, Bit#(32) verifID, Bit#(32) pc, Bit#(32) rawInst, Bit#(8) iType, Bit#(8) wbDst, Bit#(32) wbRes, Bit#(32) addr);
	method Action reportMSG(Bit#(32) verifID, Bit#(8) msg);
endinterface