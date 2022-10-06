interface FromHost;
	method Action setMem (Bit#(32) addr, Bit#(32) word);
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action printCMR(Bit#(32) cycle, Bit#(32) pc, Bit#(32) rawInst, Bit#(32) iType, Bit#(32) wbDst, Bit#(32) wbRes, Bit#(32) addr);
	method Action printMSG(Bit#(32) msg);
endinterface