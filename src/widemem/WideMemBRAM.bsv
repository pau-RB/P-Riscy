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

	BRAM1PortBE#(WMBAddr, CacheLine, CacheLineBytes) bram <- mkBRAM1ServerBE(cfg);

	FIFOF#(tagT) bramQ <- mkFIFOF();

	interface request = (interface Put#(WideMemReq);
		method Action put(WideMemReq#(tagT) r);
			if(r.write) begin
				bram.portA.request.put( BRAMRequestBE { writeen        : r.byte_enable   ,
				                                        responseOnWrite: False           ,
				                                        address        : truncate(r.addr),
				                                        datain         : r.data          });
			end else begin
				bram.portA.request.put( BRAMRequestBE { writeen        : '0              ,
				                                        responseOnWrite: False           ,
				                                        address        : truncate(r.addr),
				                                        datain         : r.data          });
			end
			if(!r.write)
				bramQ.enq(r.tag);
		endmethod
	endinterface);

	interface response = (interface Get#(WideMemRes#(tagT));
		method ActionValue#(WideMemRes#(tagT)) get();
			CacheLine data <- bram.portA.response.get;
			tagT tag = bramQ.first(); bramQ.deq();
			return WideMemRes{ tag: tag, data: data };
		endmethod
	endinterface);

endmodule