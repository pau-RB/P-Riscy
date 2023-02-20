import FShow::*;
import VerifMaster::*;
import Config::*;

// types
import Types::*;
import ProcTypes::*;
import LSUTypes::*;
import CMRTypes::*;

// include
import FIFOF::*;
import SpecialFIFOs::*;
import MFifo::*;
import Vector::*;
import Ehr::*;

// back
import XilinxIntMul::*;
import XilinxIntDiv::*;
import Scoreboard::*;
import RFile::*;
import Execution::*;
import NTTX::*;

(* synthesize *)
module mkMul(XilinxIntMul#(void));
	let m <- mkXilinxIntMul;
	return m;
endmodule

(* synthesize *)
module mkDiv(XilinxIntDiv#(void));
	let m <- mkXilinxIntDiv;
	return m;
endmodule

interface Writeback;

	// To upstream
	method ActionValue#(Redirect)     getRedirect();

endinterface

interface Backend;

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);

	// To upstream
	interface Vector#(FrontWidth, Writeback) hart;

	// To sched
	method Data getNumCommit();

	// CMR
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Message)      getMSG();
	method ActionValue#(Message)      getHEX();
	method ActionValue#(MemStat)      getMSR();

	// Performance Debug
	method Vector#(BackWidth,Maybe#(ExecToken)) get_exec_inst  ();
	method Vector#(BackWidth,Maybe#(MemToken) ) get_mem_inst   ();
	method Vector#(BackWidth,Maybe#(WBToken)  ) get_wb_inst    ();
	method Vector#(BackWidth,Bool             ) get_wb_valid   ();
	method Vector#(BackWidth,Bool             ) get_wb_miss    ();

	method Data                                 get_wb_commit  ();

	method Maybe#(WBToken)                      get_old_wb_inst();

endinterface

module mkBackend (LSU#(WBToken)                       lsu        ,
	              VerifMaster                         verif      ,
	              NTTX                                nttx       ,
	              Vector#(FrontWidth, RFile)          regFile    ,
	              Vector#(FrontWidth, Scoreboard#(8)) scoreboard ,
	              Vector#(FrontWidth, Ehr#(2,Epoch))  wbEpoch    ,
	              Bool                                coreStarted,
	              Data                                numCycles  ,
	              Backend ifc);

	// Stages
	FIFOF#(Vector#(BackWidth,Maybe#(ExecToken)))    executeQ        <- mkBypassFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(MemToken)))     memoryQ         <- mkPipelineFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(WBToken)))      commitQ         <- mkPipelineFIFOF();

	Vector#(FrontWidth, Ehr#(3, Maybe#(void    ))) toWBsbRemove    <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(RFwb    ))) toWBrfWriteBack <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Epoch   ))) toWBstEpoch     <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Redirect))) toWBstRedirect  <- replicateM(mkEhr(tagged Invalid));

	// MulDiv
	Vector#(TSub#(FrontWidth,1), XilinxIntMul#(void)) mulArray <- replicateM(mkMul);
	Vector#(TSub#(FrontWidth,1), XilinxIntDiv#(void)) divArray <- replicateM(mkDiv);

	// Upstream
	Vector#(FrontWidth, FIFOF#(Redirect))          redirectQ       <- replicateM(mkBypassFIFOF());

	// CMR
	MFifo#(CTHQ_LEN,BackWidth,CommitReport)        commitReportQ   <- mkPipelineMFifo();
	FIFOF#(Message)                                messageReportQ  <- mkSizedFIFOF(valueOf(CTHQ_LEN));
	FIFOF#(Message)                                hexReportQ      <- mkSizedFIFOF(valueOf(CTHQ_LEN));
	FIFOF#(MemStat)                                memStatReportQ  <- mkSizedFIFOF(valueOf(CTHQ_LEN));

	// Perf debug
	Ehr#(2,Vector#(BackWidth,Maybe#(ExecToken)))   perf_exec_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Maybe#(MemToken) ))   perf_mem_inst   <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Maybe#(WBToken)  ))   perf_wb_inst    <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Bool             ))   perf_wb_valid   <- mkEhr(replicate(       False  ));
	Ehr#(2,Vector#(BackWidth,Bool             ))   perf_wb_miss    <- mkEhr(replicate(       False  ));

	// Stats
	Ehr#(3,Data)                                   numCommit       <- mkEhr(0);

	//////////// EXECUTE ////////////

	rule do_execute;

		Vector#(BackWidth, Maybe#(ExecToken)) toExec = executeQ.first(); executeQ.deq();
		Vector#(BackWidth, Maybe#(MemToken) ) toMem  = replicate(tagged Invalid);

		// Mem lane
		if(toExec[0] matches tagged Valid .eToken) begin
			let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);
			let mToken   = MemToken{ inst   : execInst,
				                     pc     : eToken.pc,
				                     feID   : eToken.feID,
				                     epoch  : eToken.epoch,
				                     rawInst: eToken.rawInst};
			toMem[0] = tagged Valid mToken;
		end

		// Arith lanes
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
			if(toExec[i] matches tagged Valid .eToken) begin

				ExecInst execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);

				if(eToken.inst.iType == Mul) begin
					case(eToken.inst.mulFunc)
					Mul   : mulArray[i-1].req(eToken.arg1, eToken.arg2, Signed        , ?);
					Mulh  : mulArray[i-1].req(eToken.arg1, eToken.arg2, Signed        , ?);
					Mulhsu: mulArray[i-1].req(eToken.arg1, eToken.arg2, SignedUnsigned, ?);
					Mulhu : mulArray[i-1].req(eToken.arg1, eToken.arg2, Unsigned      , ?);
					Div   : divArray[i-1].req(eToken.arg1, eToken.arg2, True          , ?);
					Divu  : divArray[i-1].req(eToken.arg1, eToken.arg2, False         , ?);
					Rem   : divArray[i-1].req(eToken.arg1, eToken.arg2, True          , ?);
					Remu  : divArray[i-1].req(eToken.arg1, eToken.arg2, False         , ?);
					endcase
				end

				let mToken   = MemToken{ inst   : execInst,
				                         pc     : eToken.pc,
				                         feID   : eToken.feID,
				                         epoch  : eToken.epoch,
				                         rawInst: eToken.rawInst};

				toMem[i] = tagged Valid mToken;
			end
		end

		memoryQ.enq(toMem);

		if(perf_DEBUG) begin
			perf_exec_inst[0] <= toExec;
		end

	endrule

	//////////// MEMORY ////////////

	rule do_mem;

		Vector#(BackWidth, Maybe#(MemToken)) toMem    = memoryQ.first(); memoryQ.deq();
		Vector#(BackWidth, Maybe#(WBToken))  toCommit = replicate(tagged Invalid);

		// Mem lane
		if(toMem[0] matches tagged Valid .mToken) begin
			let wToken = WBToken{ inst   : mToken.inst,
			                      pc     : mToken.pc,
			                      feID   : mToken.feID,
			                      epoch  : mToken.epoch,
			                      rawInst: mToken.rawInst};

			toCommit[0] = tagged Valid wToken;

			// Send LSU req, if the instruction is valid
			if (mToken.epoch == wbEpoch[mToken.feID][1]) begin
				if (mToken.inst.iType == Ld) begin
					lsu.req(LSUReq{ op     : Ld,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: wToken });
				end else if (mToken.inst.iType == St) begin
					lsu.req(LSUReq{ op     : St,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: wToken });
				end else if(mToken.inst.iType == Join) begin
					lsu.req(LSUReq{ op     : Join,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: wToken });
				end 
			end
		end

		// Arith lanes
		for(Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
			if(toMem[i] matches tagged Valid .mToken) begin
				let wToken = WBToken{ inst   : mToken.inst,
				                      pc     : mToken.pc,
				                      feID   : mToken.feID,
				                      epoch  : mToken.epoch,
				                      rawInst: mToken.rawInst};
				toCommit[i] = tagged Valid wToken;
			end
		end

		commitQ.enq(toCommit);

		if(perf_DEBUG) begin
			perf_mem_inst[0] <= toMem;
		end

	endrule


	//////////// COMMIT ////////////

	rule do_commit;

		// Upstream actions
		Vector#(FrontWidth, Maybe#(void    )) sbRemove     = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(RFwb    )) rfWriteBack  = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Epoch   )) stEpoch      = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Redirect)) stRedirect   = replicate(tagged Invalid);

		// WB
		Vector#(BackWidth, Maybe#(WBToken))   toCommit     = commitQ.first(); commitQ.deq();
		Vector#(BackWidth,Bool            )   commit_valid = replicate(False);
		Vector#(BackWidth,Bool            )   commit_miss  = replicate(False);
		Data numWB = 0;


		// Mem lane
		if(toCommit[0] matches tagged Valid .wToken) begin

			sbRemove[wToken.feID] = tagged Valid(?);

			if(wToken.epoch == wbEpoch[wToken.feID][0])  begin

				if(wToken.inst.iType == Ghost) begin

					nttx.evict(wToken.feID, wToken.pc);
					stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
					                                                 dry     : True,
					                                                 kill    : False,
					                                                 redirect: False,
					                                                 epoch   : ?,
					                                                 nextPc  : ?};

				end else if(wToken.inst.iType == Ld) begin

					let res <- lsu.resp();
					if(res.valid) begin
						rfWriteBack[wToken.feID] = tagged Valid RFwb{dst: fromMaybe(?, wToken.inst.dst), res: res.data};
						numWB = numWB+1;
						if(cmr_ext_DEBUG == True)
							commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(wToken.feID), ?, wToken, res.data, ?));
					end else begin
						stEpoch   [wToken.feID] = tagged Valid (wbEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : wbEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == St) begin

					let res <- lsu.resp();
					if(res.valid) begin
						numWB = numWB+1;
						if(cmr_ext_DEBUG == True)
							commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(wToken.feID), ?, wToken, ?, ?));
					end else begin
						stEpoch   [wToken.feID] = tagged Valid (wbEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : wbEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == Join) begin

					let res <- lsu.resp();
					if(res.valid) begin
						if(res.data == '0) begin
							stEpoch   [wToken.feID] = tagged Valid (wbEpoch[wToken.feID][0]+1);
							stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
							                                                 dry     : False,
							                                                 kill    : True,
							                                                 redirect: False,
							                                                 epoch   : wbEpoch[wToken.feID][0]+1,
							                                                 nextPc  : ? };
						end
						numWB = numWB+1;
						if (cmr_ext_DEBUG == True)
								commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(wToken.feID), ?, wToken, res.data, ?));
					end else begin
						stEpoch   [wToken.feID] = tagged Valid (wbEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : wbEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == Fork || wToken.inst.iType == Forkr) begin

					VerifID childVerifID <- nttx.efork(wToken.feID, wToken.inst.addr);
					numWB = numWB+1;
					if (cmr_ext_DEBUG == True)
						commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(wToken.feID), childVerifID, wToken, ?, ?));

				end

				if (msg_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == msg_ADDR) begin
						messageReportQ.enq(Message { verifID: verif.getVerifID(wToken.feID),
						                             cycle:   numCycles,
						                             commit:  numCommit[0],
						                             data:    wToken.inst.data });
					end
				end

				if (hex_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == hex_ADDR) begin
						hexReportQ.enq(Message { verifID: verif.getVerifID(wToken.feID),
						                         cycle:   numCycles,
						                         commit:  numCommit[0],
						                         data:    wToken.inst.data });
					end
				end

				if (mem_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == msr_ADDR) begin
						LSUStat   lsr = lsu.getStat();
						MemStat   msr = MemStat{ verifID: verif.getVerifID(wToken.feID),
						                         cycle  : numCycles,
						                         commit : numCommit[0],
						                         data   : wToken.inst.data,
						                         fetch  : ?,
						                         arbiter: ?,
						                         lsu    : lsr };
						memStatReportQ.enq(msr);
					end
				end

				if(perf_DEBUG == True) begin
					commit_valid[0] = True;
				end

			end

		end

		// Arith lanes
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin

			if(toCommit[i] matches tagged Valid .wToken) begin

				sbRemove[wToken.feID] = tagged Valid(?);

				if(wToken.inst.iType == Mul) begin
					case(wToken.inst.mulFunc)
						Mul   : mulArray[i-1].deqResp();
						Mulh  : mulArray[i-1].deqResp();
						Mulhsu: mulArray[i-1].deqResp();
						Mulhu : mulArray[i-1].deqResp();
						Div   : divArray[i-1].deqResp();
						Divu  : divArray[i-1].deqResp();
						Rem   : divArray[i-1].deqResp();
						Remu  : divArray[i-1].deqResp();
					endcase
				end

				if (wToken.epoch == wbEpoch[wToken.feID][0])  begin

					Data mulRes = ?;

					if(wToken.inst.iType == Mul) begin
						mulRes = (case(wToken.inst.mulFunc)
							Mul   : truncate   (mulArray[i-1].product);
							Mulh  : truncateLSB(mulArray[i-1].product);
							Mulhsu: truncateLSB(mulArray[i-1].product);
							Mulhu : truncateLSB(mulArray[i-1].product);
							Div   : divArray[i-1].quotient ;
							Divu  : divArray[i-1].quotient ;
							Rem   : divArray[i-1].remainder;
							Remu  : divArray[i-1].remainder;
						endcase);
						rfWriteBack[wToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, wToken.inst.dst), res: mulRes};
					end else if(isValid(wToken.inst.dst))
						rfWriteBack[wToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, wToken.inst.dst), res: wToken.inst.data};

					if(wToken.inst.brTaken || wToken.inst.iType == J || wToken.inst.iType == Jr) begin
						stEpoch   [wToken.feID] = tagged Valid (wbEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : wbEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.inst.addr };
					end else if (wToken.inst.iType == Br) begin
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: False,
						                                                 epoch   : ?,
						                                                 nextPc  : ?};
					end

					numWB = numWB+1;

					if (cmr_ext_DEBUG == True) begin
						commitReportQ.port[i].enq(generateCMR(numCycles, verif.getVerifID(wToken.feID), ?, wToken, ?, mulRes));
					end

					if(perf_DEBUG == True) begin
						commit_valid[i] = True;
					end

				end

			end

		end

		// To WB
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			toWBsbRemove   [i][0] <= sbRemove   [i];
			toWBrfWriteBack[i][0] <= rfWriteBack[i];
			toWBstEpoch    [i][0] <= stEpoch    [i];
			toWBstRedirect [i][0] <= stRedirect [i];
		end

		// Num  commit
		numCommit[0] <= numCommit[0]+numWB;

		// Perf debug
		if(perf_DEBUG == True) begin
			perf_wb_inst [0] <= toCommit;
			perf_wb_valid[0] <= commit_valid;
			perf_wb_miss [0] <= commit_miss;
		end

	endrule


	//////////// OLD COMMIT ////////////

	Ehr#(2,Maybe#(WBToken)) perf_old_wb_inst  <- mkEhr(tagged Invalid);

	rule do_old_commit;

		LSUResp#(WBToken) resp      <- lsu.oldResp();
		WBToken           wToken     = resp.transId;
		FrontID           feID       = wToken.feID;
		Data              loadRes    = 'hdeadbeef;

		if(wToken.inst.iType == Ld) begin

			loadRes = resp.data;
			toWBrfWriteBack[feID][1] <= tagged Valid RFwb{dst: fromMaybe(?, wToken.inst.dst), res: loadRes};
			toWBstRedirect [feID][1] <= tagged Valid Redirect{ lock    : False,
			                                                   dry     : False,
			                                                   kill    : False,
			                                                   redirect: False,
			                                                   epoch   : ?,
			                                                   nextPc  : ? };

		end else if(wToken.inst.iType == St) begin

			toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
			                                        dry     : False,
			                                        kill    : False,
			                                        redirect: False,
			                                        epoch   : ?,
			                                        nextPc  : ? };

		end else if(wToken.inst.iType == Join) begin

			loadRes = resp.data;
			if(resp.data == '0) begin
				toWBstEpoch   [feID][1] <= tagged Valid (wbEpoch[feID][0]+1);
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
				                                                  dry     : False,
				                                                  kill    : True,
				                                                  redirect: False,
				                                                  epoch   : wbEpoch[feID][0]+1,
				                                                  nextPc  : ? };
			end else begin
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
				                                                  dry     : False,
				                                                  kill    : False,
				                                                  redirect: False,
				                                                  epoch   : ?,
				                                                  nextPc  : ? };
			end

		end

		numCommit[1] <= numCommit[1]+1;

		if (cmr_ext_DEBUG == True) begin
			commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(feID), ?, wToken, loadRes, ?));
		end

		if(perf_DEBUG == True) begin
			perf_old_wb_inst[0] <= tagged Valid wToken;
		end

	endrule


	//////////// WRBACK ////////////
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		rule do_wb;

			if(isValid(toWBsbRemove[i][2])) begin
				scoreboard[i].remove();
			end

			regFile[i].wr(fromMaybe(RFwb{dst: '0, res: 'hdeadbeef}, toWBrfWriteBack[i][2]));

			wbEpoch[i][0] <= fromMaybe(wbEpoch[i][0], toWBstEpoch[i][2]);

			if(isValid(toWBstRedirect[i][2])) begin
				redirectQ[i].enq(fromMaybe(?,toWBstRedirect[i][2]));
			end

			toWBsbRemove   [i][2] <= tagged Invalid;
			toWBrfWriteBack[i][2] <= tagged Invalid;
			toWBstEpoch    [i][2] <= tagged Invalid;
			toWBstRedirect [i][2] <= tagged Invalid;

		endrule

	end


	//////////// PERF DEBUG ////////////

	rule do_perf_DEBUG;

		perf_exec_inst  [1] <= replicate(tagged Invalid);
		perf_mem_inst   [1] <= replicate(tagged Invalid);
		perf_wb_inst    [1] <= replicate(tagged Invalid);
		perf_wb_valid   [1] <= replicate(       False  );
		perf_wb_miss    [1] <= replicate(       False  );
		perf_old_wb_inst[1] <= tagged Invalid;

	endrule


	//////////// INTERFACE ////////////

	Vector#(FrontWidth, Writeback) wbIfc = newVector;
 	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		wbIfc[i] =
			(interface Writeback;

				method ActionValue#(Redirect) getRedirect();
					let latest = redirectQ[i].first(); redirectQ[i].deq();
					return latest;
				endmethod

			endinterface);
	end

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);
		executeQ.enq(inst);
	endmethod

	// To upstream
	interface hart = wbIfc;

	// To sched
	method Data getNumCommit();
		return numCommit[0];
	endmethod

	// CMR
	method ActionValue#(CommitReport) getCMR();
		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;
	endmethod

	method ActionValue#(Message) getMSG();
		let latest = messageReportQ.first(); messageReportQ.deq();
		return latest;
	endmethod

	method ActionValue#(Message) getHEX();
		let latest = hexReportQ.first(); hexReportQ.deq();
		return latest;
	endmethod

	method ActionValue#(MemStat) getMSR();
		let latest = memStatReportQ.first(); memStatReportQ.deq();
		return latest;
	endmethod

	// Performance Debug
	method Vector#(BackWidth,Maybe#(ExecToken)) get_exec_inst();
		return perf_exec_inst[1];
	endmethod

	method Vector#(BackWidth,Maybe#(MemToken)) get_mem_inst();
		return perf_mem_inst[1];
	endmethod

	method Vector#(BackWidth,Maybe#(WBToken)) get_wb_inst();
		return perf_wb_inst[1];
	endmethod

	method Vector#(BackWidth,Bool) get_wb_valid();
		return perf_wb_valid[1];
	endmethod

	method Vector#(BackWidth,Bool) get_wb_miss();
		return perf_wb_miss[1];
	endmethod

	method Data get_wb_commit();
		return numCommit[2];
	endmethod

	method Maybe#(WBToken) get_old_wb_inst();
		return perf_old_wb_inst[1];
	endmethod

endmodule