import FShow::*;
import Config::*;

// types
import Types::*;
import WideMemTypes::*;
import ProcTypes::*;
import CMRTypes::*;

// include
import Vector::*;
import FIFO::*;
import Ehr::*;
import Connectable::*;

// state
import Scoreboard::*;
import RFile::*;

// top level modules
import Frontend::*;
import SyncArbiter::*;
import Backend::*;
import NTTX::*;

interface Core;

	// IMEM and DMEM
	interface WideMemClient#(FrontID) instMem;
	interface WideMemClient#(FrontID) dataMem;

	// Stream control
	interface FIFO#(ContToken) toMTQ;

	// CMR
	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
	`endif
	method ActionValue#(Message)      getMSG();
	method ActionValue#(Message)      getHEX();
	method ActionValue#(MemStat)      getMSR();

endinterface

(*synthesize*)
module mkCore7SS(Core ifc);

	//////////// COUNTERS ////////////

	Reg#(Bool)      coreStarted <- mkReg(False);
	Ehr#(2,PerfCnt) numCycles   <- mkEhr(0);

	rule do_cnt_cycles if(coreStarted);
		numCycles[0] <= numCycles[0]+1;
	endrule

	//////////// TOP-LEVEL MODULES ////////////

	Frontend    frontend <- mkFrontend();
	SyncArbiter arbiter  <- mkSyncArbiter();
	Backend     backend  <- mkBackend();
	NTTX        nttx     <- mkNTTX();

	//////////// SWITCH ////////////

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

	rule do_forward_btn;
		let fr <- backend.getFork();
		nttx.putFork(fr);
	endrule

	rule do_forward_btf;
		FrontID feID <- nttx.getReadRF();
		nttx.putLineRF(frontend.regFile[feID].getL, frontend.regFile[feID].getH);
	endrule

	for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		rule do_forward_rf_writeback;
			let rfwriteback = backend.deqRFwriteBack[i].first(); backend.deqRFwriteBack[i].deq();
			frontend.regFile[i].wr(rfwriteback);
			if(rfwriteback.rmv)
				frontend.scoreboard[i].remove();
			if(rfwriteback.clr)
				frontend.scoreboard[i].clear();
		endrule
		rule do_forward_redirect_bta;
			if(backend.deqRedirect[i].notEmpty()) begin
				let redirect = backend.deqRedirect[i].first(); backend.deqRedirect[i].deq();
				arbiter.enqRedirect[i].enq(redirect);
			end else begin
				let redirect = nttx.deqRedirect[i].first(); nttx.deqRedirect[i].deq();
				arbiter.enqRedirect[i].enq(redirect);
			end
		endrule
		rule do_forward_redirect_atf;
			let redirect = arbiter.deqRedirect[i].first(); arbiter.deqRedirect[i].deq();
			frontend.hart[i].redirect(redirect);
		endrule
	end

	//////////// STREAM SCHEDULING ////////////

	rule do_schedule_stream;

		FrontID feID = 0;
		Bool    free = False;

		for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(frontend.hart[i].available()) begin
				feID = fromInteger(i);
				free = True;
			end
		end

		if(free) begin

			ContToken token = nttx.ready.first(); nttx.ready.deq();

			frontend.hart   [feID].start(token.pc );
			frontend.regFile[feID].setL (token.rfL);
			frontend.regFile[feID].setH (token.rfH);

			backend.setVerifID(feID, token.verifID);

			coreStarted <= True;
			frontend.startCore();
			arbiter .startCore();
			backend .startCore();

		end

	endrule

	//////////// PERFORMANCE CNT ////////////

	`ifdef DEBUG_CYC
	rule do_DEBUG_CYC if(coreStarted);

		Vector#(FrontWidth, DEB_CYC_fet) cycFet = frontend.cycFet();
		Vector#(FrontWidth, DEB_CYC_dec) cycDec = frontend.cycDec();
		Vector#(FrontWidth, DEB_CYC_arb) cycArb = arbiter .cycArb();



		Vector#(BackWidth, Maybe#(ExecToken)) perf_exec_inst   = backend.get_exec_inst  ();
		Vector#(BackWidth, Maybe#(MemToken) ) perf_mem_inst    = backend.get_mem_inst   ();
		Vector#(BackWidth, Maybe#(ComToken) ) perf_wb_inst     = backend.get_wb_inst    ();
		Vector#(BackWidth, Bool             ) perf_wb_valid    = backend.get_wb_valid   ();
		Vector#(BackWidth, Bool             ) perf_wb_miss     = backend.get_wb_miss    ();

		Maybe#(OldToken)                      perf_old_wb_inst = backend.get_old_wb_inst();

		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

			     if(i == 0) $write("%d ", numCycles[1]);
			else if(i == 1) $write("%d ", backend.get_wb_commit());
			else            $write("                     ");

			//////////// FETCH ////////////

			if(cycFet[i].status != Empty) $write("|| %d ", backend.getVerifID(fromInteger(i))); else $write("||            ");

			case (cycFet[i].status)
				Full :   $write("|| Full  ");
				Evict:   $write("|| Evict ");
				Ghost:   $write("|| Ghost ");
				Dry  :   $write("|| Dry   ");
				Empty:   $write("|| Empty ");
				default: $write("||       ");
			endcase

			if(cycFet[i].l0IHit) $write("h "); else $write("m ");
			if(cycFet[i].status != Empty) $write("| F 0x%h |", cycFet[i].nextPC); else $write("| F            |");
			
			//////////// DECODE ////////////

			if(cycDec[i].notEmpty && cycDec[i].notStall) $write(" D 0x%h |", cycDec[i].nextPC);
			else if (cycDec[i].notEmpty) $write("%c[2;97m D 0x%h %c[0;0m|", 27, cycDec[i].nextPC, 27);
			else $write(" D            |");

			//////////// ARBITER ////////////

			if(cycArb[i].notEmpty && cycArb[i].notStall) $write(" A 0x%h |", cycArb[i].nextPC);
			else if(cycArb[i].notEmpty) $write("%c[2;97m A 0x%h %c[0;0m|", 27, cycArb[i].nextPC, 27);
			else $write(" A            |");

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
					$write(" C 0x%h | ", fromMaybe(?,perf_wb_inst[j]).pc);
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

		$write("----------------------------------------------------------------------------------------------------------------------------------------\n");

	endrule
	`endif

	//////////// INTERFACE ////////////

	//IMEM and DMEM
	interface WideMemClient instMem = frontend.mem;
	interface WideMemClient dataMem = backend .mem;

	// Stream control
	interface toMTQ = nttx.toMTQ;

	// CMR
	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
		let latest <- backend.getCMR();
		return latest;
	endmethod
	`endif

	`ifdef MMIO
	method ActionValue#(Message) getMSG();
		let latest <- backend.getMSG();
		return latest;
	endmethod
	method ActionValue#(Message) getHEX();
		let latest <- backend.getHEX();
		return latest;
	endmethod
	method ActionValue#(MemStat) getMSR();
		let latest <- backend.getMSR();
		latest.fetch   = frontend.getStat();
		latest.arbiter = arbiter.getStat();
		return latest;
	endmethod
	`endif

endmodule