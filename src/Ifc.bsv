interface FromHost;
	method Action startPC(Bit#(32) pc);
endinterface

interface ToHost;
	method Action print(Bit#(32) word);
endinterface