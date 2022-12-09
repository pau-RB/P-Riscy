import FShow::*;
import Config::*;
import VerifMaster::*;

// types
import Types::*;
import ProcTypes::*;
import LSUTypes::*;
import CMRTypes::*;
import Stream::*;

// include
import Fifo::*;
import MFifo::*;
import Vector::*;
import Ehr::*;

// mem
import WideMemSplit::*;

// top level modules
import FrontEnd::*;
import SyncArbiter::*;
import BackEnd::*;
import LSU::*;
import NTTX::*;

// state
import Scoreboard::*;
import RFile::*;

function Bool isMemInst(ExecToken inst);
	return True;
endfunction

function Bool isArithInst(ExecToken inst);
	return (inst.inst.iType == Unsupported || inst.inst.iType == Alu   ||
	        inst.inst.iType == Mul         || inst.inst.iType == J     ||
	        inst.inst.iType == Jr          || inst.inst.iType == Br    ||
	        inst.inst.iType == Auipc );
endfunction

interface Core;

	method Action start (FrontID feID, ContToken token);
	method Action evict(FrontID feID);
	method Bool   available(FrontID feID);
	method Data   getNumCommit();

	method ActionValue#(ContToken)    getContToken();
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Message)      getMSG();
	method ActionValue#(MemStat)      getMSR();

endinterface

module mkCore6S(WideMem mem, VerifMaster verif, Core ifc);

	//////////// EXT STATE ////////////

	Reg#(Bool)                             coreStarted    <- mkReg(False);
	Ehr#(3,Data)                           numCommit      <- mkEhr(0);
	Ehr#(2,Data)                           numCycles      <- mkEhr(0);

	//////////// MEMORY ////////////

	SplitWideMem#(FrontWidth,TMul#(2,FrontWidth)) mainSplit <- mkSplitWideMem(True, mem);
	BareDataCache                                 l1d       <- (lsuAssociative ? mkAssociativeDataCache() : mkDirectDataCache());
	LSU#(WBToken)                                 lsu       <- mkLSU(mainSplit.port[1], l1d);


	//////////// INT STATE ////////////

	Vector#(FrontWidth, RFile         ) regFile    <- replicateM(mkBypassRFile);
	Vector#(FrontWidth, Scoreboard#(8)) scoreboard <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, Ehr#(2,Epoch) ) wbEpoch    <- replicateM(mkEhr('0)    );

	//////////// FRONTEND ////////////

	Vector#(FrontWidth, Epoch) frontWBepoch = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i = i+1) frontWBepoch[i] = wbEpoch[i][1];

	FrontEnd frontEnd <- mkFrontEnd(mainSplit.port[0],
	                               regFile           ,
	                               scoreboard        ,
	                               frontWBepoch      ,
	                               coreStarted       );


	//////////// ARBITER ////////////

	Vector#(BackWidth, function Bool accept(ExecToken inst)) filter = newVector;
	for(Integer i = 1; i < valueOf(BackWidth); i = i+1) filter[i] = isArithInst; filter[0] = isMemInst;

	SyncArbiter#(FrontWidth, BackWidth, ExecToken) arbiter <- mkSyncArbiter(coreStarted, filter);

	//////////// BACKEND ////////////

	NTTX nttx <- mkNTTX(regFile, verif);

	BackEnd backEnd <- mkBackEnd (lsu         ,
	                              verif       ,
	                              nttx        ,
	                              regFile     ,
	                              scoreboard  ,
	                              wbEpoch     ,
	                              coreStarted ,
	                              numCycles[0]);

	//////////// FTA ////////////

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_frontEnd;
			let inst <- frontEnd.hart[i].readInst();
			arbiter.eport[i].enq(inst);
		endrule
	end

	//////////// ATB ////////////

	rule do_forward_arbiter;
		let inst = arbiter.dport.first(); arbiter.dport.deq();
		backEnd.execute(inst);
	endrule

	//////////// BTF ////////////

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_redirect;
			let redirect <- backEnd.hart[i].getRedirect();
			frontEnd.hart[i].redirect(redirect);
		endrule
	end

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_dry;
			let dry <- backEnd.hart[i].getBackendDry();
			frontEnd.hart[i].backendDry();
		endrule
	end

	//////////// PERFORMANCE CNT ////////////

	rule do_cnt_cycles if(coreStarted);
		numCycles[0] <= numCycles[0]+1;
	endrule

	rule do_perf_DEBUG if(perf_DEBUG == True && coreStarted);

		Vector#(FrontWidth,Maybe#(ExecToken)) perf_sel_inst  = arbiter.perf_get_inst ();
		Vector#(FrontWidth,Bool)              perf_sel_taken = arbiter.perf_get_taken();
/*
		perf_exec_inst[1] <= replicate(tagged Invalid);
		perf_mem_inst [1] <= replicate(tagged Invalid);
		
		for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
			perf_wb_inst [j][1] <= tagged Invalid;
			perf_wb_valid[j][1] <= False;
			perf_wb_miss [j][1] <= False;
		end

		perf_old_wb_inst[1] <= tagged Invalid;
*/
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

			     if(i == 0) $write("%d ", numCycles[1]);
			else if(i == 1) $write("%d ", numCommit[2]);
			else            $write("           ");

			//////////// FETCH ////////////

			if(frontEnd.fetch[i].currentState() != Empty) $write("|| %d ", verif.getVerifID(fromInteger(i))); else $write("||            ");

			case (frontEnd.fetch[i].currentState())
				Full :   $write("|| Full  ");
				Evict:   $write("|| Evict ");
				Ghost:   $write("|| Ghost ");
				Dry  :   $write("|| Dry   ");
				Empty:   $write("|| Empty ");
				default: $write("||       ");
			endcase

			if(frontEnd.fetch   [i].isl0Ihit) $write("h "); else $write("m ");
			if(frontEnd.fetch   [i].currentState() != Empty) $write("| F 0x%h |", frontEnd.fetch[i].currentPC()); else $write("| F            |");
			
			//////////// DECODE ////////////

			if(frontEnd.decode  [i].notEmpty) $write(" D 0x%h |", frontEnd.decode  [i].firstPC); else $write(" D            |");
			
			//////////// REGFETCH ////////////

			if(frontEnd.regfetch[i].notEmpty) $write(" R 0x%h |", frontEnd.regfetch[i].firstPC); else $write(" R            |");

			//////////// SELECT ////////////

			if(perf_sel_taken[i]) $write(" S 0x%h |", fromMaybe(?,perf_sel_inst[i]).pc);
			else if(isValid(perf_sel_inst[i])) $write("%c[2;97m S 0x%h %c[0;0m|", 27, fromMaybe(?,perf_sel_inst[i]).pc, 27);
			else $write(" S            |");
/*
			//////////// EXECUTE ////////////

			Bool exec = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_exec_inst[1][j]) && (fromMaybe(?,perf_exec_inst[1][j]).feID == fromInteger(i))) begin
					$write(" E 0x%h |",  fromMaybe(?,perf_exec_inst[1][j]).pc);
					exec = True;
				end
			end
			if(!exec) $write("              |");

			//////////// MEM ////////////

			Bool mem = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_mem_inst[1][j]) && (fromMaybe(?,perf_mem_inst[1][j]).feID == fromInteger(i))) begin
					$write(" M 0x%h |",  fromMaybe(?,perf_mem_inst[1][j]).pc);
					mem = True;
				end
			end
			if(!mem) $write("              |");

			//////////// WB ////////////

			Bool wb = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_wb_inst[j][1]) && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write(" W 0x%h | ", fromMaybe(?,perf_wb_inst[j][1]).pc);
					wb = True;
				end
			end
			if(!wb) $write("              | ");

			//////////// COMMIT ////////////

			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(perf_wb_valid[j][1] && !perf_wb_miss[j][1] && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write("%c[1;93m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j][1]).rawInst));
					$write("%c[0m",27);
				end else if(perf_wb_miss[j][1] && (fromMaybe(?,perf_wb_inst[j][1]).feID == fromInteger(i))) begin
					$write("%c[2;97m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j][1]).rawInst));
					$write("%c[0m",27);
				end
			end

			if(isValid(perf_old_wb_inst[1]) && (fromMaybe(?,perf_old_wb_inst[1]).feID == fromInteger(i))) begin
				$write("%c[1;33m",27);
				$write("", showInst(fromMaybe(?,perf_old_wb_inst[1]).rawInst));
				$write("%c[0m",27);
			end
			*/
			$display("");

		end

		$write("---------------------------------------------------------------------------------------------------------------------------------------------\n");

	endrule


	//////////// INTERFACE ////////////

	method Action start (FrontID feID, ContToken token);

		frontEnd.hart[feID].start(token.pc );
		regFile      [feID].setL (token.rfL);
		regFile      [feID].setH (token.rfH);

		verif.setVerifID(feID, token.verifID);

		coreStarted <= True;

	endmethod

	method Action evict(FrontID feID);
		frontEnd.hart[feID].evict();
	endmethod

	method Bool available(FrontID feID);
		return frontEnd.hart[feID].available();
	endmethod

	method Data getNumCommit();
		return numCommit[0];
	endmethod

	method ActionValue#(ContToken) getContToken();
		let latest = nttx.first(); nttx.deq();
		return latest;
	endmethod

	method ActionValue#(CommitReport) getCMR();
		let latest <- backEnd.getCMR();
		return latest;
	endmethod

	method ActionValue#(Message) getMSG();
		let latest <- backEnd.getMSG();
		return latest;
	endmethod

	method ActionValue#(MemStat) getMSR();
		let latest <- backEnd.getMSR();
		return latest;
	endmethod

endmodule // mkBackend
