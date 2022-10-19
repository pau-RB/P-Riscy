import Types::*;
import ProcTypes::*;
import Config::*;
import Vector::*;

interface VerifMaster;

	method Action                setVerifID(FrontID feID, VerifID verifID);
	method VerifID               getVerifID(FrontID feID);
	method ActionValue#(VerifID) newVerifID();

endinterface

module mkVerifMaster (VerifMaster ifc);

	Vector#(FrontWidth, Reg#(VerifID)) mapID <- replicateM(mkRegU());
	Reg#(VerifID)                      newID <- mkReg('0);

	method Action                setVerifID(FrontID feID, VerifID verifID);
		mapID[feID] <= verifID;
	endmethod

	method VerifID               getVerifID(FrontID feID);
		return mapID[feID];
	endmethod

	method ActionValue#(VerifID) newVerifID();
		newID <= newID+1;
		return newID;
	endmethod

endmodule