import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import BRAM::*;
import FIFOF::*;

module mkWideMemBRAM(WideMemServer#(tagT)) provisos(Bits#(tagT, t__));

	BRAM_Configure cfg = BRAM_Configure { memorySize              : 0,
	                                      latency                 : 2,
	                                      outFIFODepth            : 2,
	                                      loadFormat              : None,
	                                      allowWriteResponseBypass: False };

	BRAM1Port#(WMBAddr, CacheLine) bram <- mkBRAM1Server(cfg);

	FIFOF#(tagT) bramQ <- mkFIFOF();

	interface request = (interface Put#(WideMemReq);
		method Action put(WideMemReq#(tagT) r);
			bram.portA.request.put( BRAMRequest { write          : r.write, 
			                                      responseOnWrite: False, 
			                                      address        : truncate(r.num), 
			                                      datain         : r.line  } );
			if(!r.write)
				bramQ.enq(r.tag);
		endmethod
	endinterface);

	interface response = (interface Get#(WideMemRes#(tagT));
		method ActionValue#(WideMemRes#(tagT)) get();
			CacheLine line <- bram.portA.response.get;
			tagT tag = bramQ.first(); bramQ.deq();
			return WideMemRes{ tag: tag, line: line };
		endmethod
	endinterface);

endmodule