import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Config::*;
import Fifo::*;
import Ehr::*;
import RFile::*;
import Vector::*;
import VerifMaster::*;




interface NTTX;

	method Action    evict(FrontID feID, Addr pc);
	method Action    deq;
    method ContToken first;

endinterface

module mkNTTX (Vector#(FrontWidth, RFile) rf, VerifMaster verif, NTTX ifc);

	Fifo#(2,ContToken) out <- mkBypassFifo();

	method Action evict(FrontID feID, Addr pc);
		out.enq(ContToken{
					verifID: verif.getVerifID(feID),
					pc     : pc,
					rfL    : rf[feID].getL(),
					rfH    : rf[feID].getH() });
	endmethod

	method Action deq();
		out.deq();
	endmethod

	method ContToken first();
		return out.first();
	endmethod

endmodule