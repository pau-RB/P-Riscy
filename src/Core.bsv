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

// state
import Scoreboard::*;
import RFile::*;

// top level modules
import FrontEnd::*;
import SyncArbiter::*;
import BackEnd::*;
import LSU::*;
import NTTX::*;

interface Core;

	// Thread control
	method Action start (FrontID feID, ContToken token);
	method Action evict(FrontID feID);
	method Bool   available(FrontID feID);
	method Data   getNumCommit();

	// ContToken
	method ActionValue#(ContToken)    getContToken();

	// CMR
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Message)      getMSG();
	method ActionValue#(MemStat)      getMSR();

endinterface

module mkCore7SS(WideMem instMem, WideMem dataMem, VerifMaster verif, Core ifc);

	//////////// COUNTERS ////////////

	Reg#(Bool)   coreStarted <- mkReg(False);
	Ehr#(2,Data) numCycles   <- mkEhr(0);

	rule do_cnt_cycles if(coreStarted);
		numCycles[0] <= numCycles[0]+1;
	endrule

	//////////// INT STATE ////////////

	Vector#(FrontWidth, RFile         ) regFile    <- replicateM(mkBypassRFile);
	Vector#(FrontWidth, Scoreboard#(8)) scoreboard <- replicateM(mkPipelineScoreboard);
	Vector#(FrontWidth, Ehr#(2,Epoch) ) wbEpoch    <- replicateM(mkEhr('0));

	//////////// FRONTEND ////////////

	FrontEnd frontend <- mkFrontEnd(instMem     ,
	                                regFile     ,
	                                scoreboard  ,
	                                wbEpoch     ,
	                                coreStarted );

	//////////// ARBITER ////////////

	function Bool isMemInst(ExecToken inst);
		return True;
	endfunction

	function Bool isArithInst(ExecToken inst);
		return (inst.inst.iType == Unsupported || inst.inst.iType == Alu   ||
		        inst.inst.iType == Mul         || inst.inst.iType == J     ||
		        inst.inst.iType == Jr          || inst.inst.iType == Br    ||
		        inst.inst.iType == Auipc );
	endfunction

	Vector#(BackWidth, function Bool accept(ExecToken inst)) filter = newVector;
	for(Integer i = 1; i < valueOf(BackWidth); i = i+1) filter[i] = isArithInst; filter[0] = isMemInst;

	SyncArbiter#(FrontWidth, BackWidth, ExecToken) arbiter <- mkSyncArbiter(coreStarted, filter);

	//////////// BACKEND ////////////

	BareDataCache l1d     <- (lsuAssociative ? mkAssociativeDataCache() : mkDirectDataCache());
	LSU#(WBToken) lsu     <- mkLSU(dataMem, l1d);
	NTTX          nttx    <- mkNTTX(regFile, verif);
	BackEnd       backend <- mkBackEnd (lsu         ,
	                                    verif       ,
	                                    nttx        ,
	                                    regFile     ,
	                                    scoreboard  ,
	                                    wbEpoch     ,
	                                    coreStarted ,
	                                    numCycles[0]);

	//////////// FORWARD QUEUES ////////////

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_frontend;
			let inst <- frontend.hart[i].readInst();
			arbiter.eport[i].enq(inst);
		endrule
	end

	rule do_forward_arbiter;
		let inst = arbiter.dport.first(); arbiter.dport.deq();
		backend.enq(inst);
	endrule

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_redirect;
			let redirect <- backend.hart[i].getRedirect();
			frontend.hart[i].redirect(redirect);
		endrule
	end

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_dry;
			let dry <- backend.hart[i].getBackendDry();
			frontend.hart[i].backendDry();
		endrule
	end

	//////////// PERFORMANCE CNT ////////////

	rule do_perf_DEBUG if(perf_DEBUG == True && coreStarted);

		Vector#(FrontWidth,Maybe#(ExecToken)) perf_sel_inst    = arbiter.perf_get_inst ();
		Vector#(FrontWidth,Bool)              perf_sel_taken   = arbiter.perf_get_taken();

		Vector#(BackWidth, Maybe#(ExecToken)) perf_exec_inst   = backend.get_exec_inst  ();
		Vector#(BackWidth, Maybe#(MemToken) ) perf_mem_inst    = backend.get_mem_inst   ();
		Vector#(BackWidth, Maybe#(WBToken)  ) perf_wb_inst     = backend.get_wb_inst    ();
		Vector#(BackWidth, Bool             ) perf_wb_valid    = backend.get_wb_valid   ();
		Vector#(BackWidth, Bool             ) perf_wb_miss     = backend.get_wb_miss    ();

		Maybe#(WBToken)                       perf_old_wb_inst = backend.get_old_wb_inst();

		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

			     if(i == 0) $write("%d ", numCycles[1]);
			else if(i == 1) $write("%d ", backend.get_wb_commit());
			else            $write("           ");

			//////////// FETCH ////////////

			if(frontend.fetch[i].currentState() != Empty) $write("|| %d ", verif.getVerifID(fromInteger(i))); else $write("||            ");

			case (frontend.fetch[i].currentState())
				Full :   $write("|| Full  ");
				Evict:   $write("|| Evict ");
				Ghost:   $write("|| Ghost ");
				Dry  :   $write("|| Dry   ");
				Empty:   $write("|| Empty ");
				default: $write("||       ");
			endcase

			if(frontend.fetch   [i].isl0Ihit) $write("h "); else $write("m ");
			if(frontend.fetch   [i].currentState() != Empty) $write("| F 0x%h |", frontend.fetch[i].currentPC()); else $write("| F            |");
			
			//////////// DECODE ////////////

			if(frontend.decode  [i].notEmpty) $write(" D 0x%h |", frontend.decode  [i].firstPC); else $write(" D            |");
			
			//////////// REGFETCH ////////////

			if(frontend.regfetch[i].notEmpty) $write(" R 0x%h |", frontend.regfetch[i].firstPC); else $write(" R            |");

			//////////// SELECT ////////////

			if(perf_sel_taken[i]) $write(" S 0x%h |", fromMaybe(?,perf_sel_inst[i]).pc);
			else if(isValid(perf_sel_inst[i])) $write("%c[2;97m S 0x%h %c[0;0m|", 27, fromMaybe(?,perf_sel_inst[i]).pc, 27);
			else $write(" S            |");

			//////////// EXECUTE ////////////

			Bool exec = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_exec_inst[j]) && (fromMaybe(?,perf_exec_inst[j]).feID == fromInteger(i))) begin
					$write(" E 0x%h |",  fromMaybe(?,perf_exec_inst[j]).pc);
					exec = True;
				end
			end
			if(!exec) $write("              |");

			//////////// MEM ////////////

			Bool mem = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_mem_inst[j]) && (fromMaybe(?,perf_mem_inst[j]).feID == fromInteger(i))) begin
					$write(" M 0x%h |",  fromMaybe(?,perf_mem_inst[j]).pc);
					mem = True;
				end
			end
			if(!mem) $write("              |");

			//////////// WB ////////////

			Bool wb = False;
			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(isValid(perf_wb_inst[j]) && (fromMaybe(?,perf_wb_inst[j]).feID == fromInteger(i))) begin
					$write(" W 0x%h | ", fromMaybe(?,perf_wb_inst[j]).pc);
					wb = True;
				end
			end
			if(!wb) $write("              | ");

			//////////// COMMIT ////////////

			for(Integer j = 0; j < valueOf(BackWidth); j=j+1) begin
				if(perf_wb_valid[j] && !perf_wb_miss[j] && (fromMaybe(?,perf_wb_inst[j]).feID == fromInteger(i))) begin
					$write("%c[1;93m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j]).rawInst));
					$write("%c[0m",27);
				end else if(perf_wb_miss[j] && (fromMaybe(?,perf_wb_inst[j]).feID == fromInteger(i))) begin
					$write("%c[2;97m",27);
					$write("", showInst(fromMaybe(?,perf_wb_inst[j]).rawInst));
					$write("%c[0m",27);
				end
			end

			if(isValid(perf_old_wb_inst) && (fromMaybe(?,perf_old_wb_inst).feID == fromInteger(i))) begin
				$write("%c[1;33m",27);
				$write("", showInst(fromMaybe(?,perf_old_wb_inst).rawInst));
				$write("%c[0m",27);
			end

			$display("");

		end

		$write("---------------------------------------------------------------------------------------------------------------------------------------------\n");

	endrule

	//////////// INTERFACE ////////////

	// Thread control
	method Action start (FrontID feID, ContToken token);
		frontend.hart[feID].start(token.pc );
		regFile      [feID].setL (token.rfL);
		regFile      [feID].setH (token.rfH);

		verif.setVerifID(feID, token.verifID);

		coreStarted <= True;
	endmethod

	method Action evict(FrontID feID);
		frontend.hart[feID].evict();
	endmethod

	method Bool available(FrontID feID);
		return frontend.hart[feID].available();
	endmethod

	method Data getNumCommit();
		return backend.getNumCommit();
	endmethod


	// ContToken
	method ActionValue#(ContToken) getContToken();
		let latest = nttx.first(); nttx.deq();
		return latest;
	endmethod


	// CMR
	method ActionValue#(CommitReport) getCMR();
		let latest <- backend.getCMR();
		return latest;
	endmethod

	method ActionValue#(Message) getMSG();
		let latest <- backend.getMSG();
		return latest;
	endmethod

	method ActionValue#(MemStat) getMSR();
		let latest <- backend.getMSR();
		return latest;
	endmethod

endmodule
