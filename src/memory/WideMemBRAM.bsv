import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import BRAM::*;

module mkWideMemBRAM(WideMem);

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM1Port#(WMBAddr, CacheLine) bram <- mkBRAM1Server(cfg);

	interface request = (interface Put#(WideMemReq);
		method Action put(WideMemReq r);
			bram.portA.request.put( BRAMRequest { write          : r.write, 
			                                      responseOnWrite: False, 
			                                      address        : truncate(r.num), 
			                                      datain         : r.line  } );
		endmethod
	endinterface);
	interface response = (interface Get#(WidememResp);
		method ActionValue#(CacheLine) get();
			CacheLine line <- bram.portA.response.get;
		endrule
	endinterface);

endmodule