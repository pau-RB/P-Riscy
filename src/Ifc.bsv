interface FromHost;
	method Action setMem (Bit#(32) addr, Bit#(32) word);
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action printCMR(Bit#(32) cycle, Bit#(32) pc, Bit#(32) inst, Bit#(32) res, Bit#(32) rawInst);
	method Action printMSG(Bit#(32) msg);
endinterface