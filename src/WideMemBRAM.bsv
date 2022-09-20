import Types::*;
import MemTypes::*;
import BRAM::*;

module mkWideMemBRAM(WideMem);

	BRAM_Configure cfg = defaultValue;
	cfg.loadFormat = Hex ("mem.vmh");
	BRAM1Port#(WMBAddr, CacheLine) bram <- mkBRAM1Server(cfg);

	method Action req(WideMemReq r);
		bram.portA.request.put( BRAMRequest{
			write: (r.write_en != 0), 
			responseOnWrite: False, 
			address: truncate(r.addr >> valueOf(TLog#(CacheLineBytes))), 
			datain: r.data 
		} );
	endmethod
    
    method ActionValue#(CacheLine) resp;
    	let d <- bram.portA.response.get;
        return d;
    endmethod

endmodule