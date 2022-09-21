interface FromHost;
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action print(Bit#(32) cycle, Bit#(32) pc, Bit#(32) iType, Bit#(32) res);
endinterface