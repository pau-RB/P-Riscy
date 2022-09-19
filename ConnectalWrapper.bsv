import Ifc::*;
import Core::*; 

interface ConnectalWrapper;
   interface FromHost connectProc;
endinterface

module [Module] mkConnectalWrapper#(ToHost ind)(ConnectalWrapper);
// Instantiate your processor below
   DDR memory <- mkSIMDDR;
   Core5S m <- mkCore5S(memory.req, memory.resp);

// TODO comment the if false
   rule relayMessage if (False);
	// FILL in to receive something from the processor (calling a method)
	Bit#(32) mess = 0;
        ind.print(mess);	
   endrule

   interface FromHost connectProc;
      method Action startPC(Bit#(32) startpc);
        $display("Received software req to start pc\n");
        $fflush(stdout);
// FILL IN to call m.startProc or somethign like that
      endmethod
   endinterface
endmodule
