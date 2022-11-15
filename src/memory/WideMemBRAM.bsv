import Types::*;
import BRAM::*;

module mkWideMemBRAM(WideMem);

	BRAM_Configure cfg = defaultValue;
	cfg.memorySize = valueOf(TExp#(WMBAddrSz));
	cfg.latency    = 2;

	BRAM1PortBE#(WMBAddr, CacheLine, CacheLineBytes) bram <- mkBRAM1ServerBE(cfg);

	method Action req(WideMemReq r);
		bram.portA.request.put( BRAMRequestBE{
			writeen:         r.write_en, 
			responseOnWrite: False, 
			address:         truncate(r.addr >> valueOf(TLog#(CacheLineBytes))), 
			datain:          r.data 
		} );
	endmethod

	method ActionValue#(CacheLine) resp;
    	let d <- bram.portA.response.get;
        return d;
    endmethod

endmodule