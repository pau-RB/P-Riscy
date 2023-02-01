import Types::*;
import BRAM::*;

module mkWideMemBRAM(WideMem);

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM1Port#(WMBAddr, CacheLine) bram <- mkBRAM1Server(cfg);

	method Action req(WideMemReq r);
		bram.portA.request.put( BRAMRequest { write          : r.write, 
		                                      responseOnWrite: False, 
		                                      address        : truncate(r.num), 
		                                      datain         : r.line  } );
	endmethod

	method ActionValue#(CacheLine) resp;
		CacheLine line <- bram.portA.response.get;
	return line;
	endmethod

endmodule