import Types::*;
import MemTypes::*;
import MemUtil::*;
import BRAMCore::*;

module mkWideMemBRAM(WideMem);

	BRAM_PORT_BE#(WMBAddr, CacheLine, CacheLineBytes) bram <- mkBRAMCore1BELoad(valueOf(TExp#(WMBAddrSz)), False, "mem.vmh", False);

	method Action req(WideMemReq r);
		bram.put(r.write_en, truncate(r.addr >> valueOf(TLog#(CacheLineBytes))), r.data);
	endmethod
    
    method ActionValue#(CacheLine) resp;
    	return bram.read;
    endmethod

endmodule