import FShow::*;
import Config::*;

// types
import Types::*;
import WideMemTypes::*;
import ProcTypes::*;
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
import LSU::*;
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

interface FifoDeq#(type t);
	method Bool notEmpty;
	method Action deq;
	method t first;
endinterface

interface Backend;

	// DMEM
	interface WideMemClient#(FrontID) mem;

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);

	// To upstream
	interface Vector#(FrontWidth,FifoDeq#(void    )) deqSBremove;
	interface Vector#(FrontWidth,FifoDeq#(RFwb    )) deqRFwriteBack;
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// To NTTX
	method ActionValue#(NTTXreq) getFork();

	// To sched
	method Data getNumCommit();

	// CMR
	method Action startCore();
	method Action setVerifID(FrontID feID, VerifID verifID);
	method VerifID getVerifID(FrontID feID);
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

module mkBackend (Backend ifc);

	// LSU
	LSU#(FrontWidth) lsu <- mkLSU();

	// Missed access table
	Vector#(FrontWidth, FIFOF#(WBToken)) miata <- replicateM(mkPipelineFIFOF());

	// Epoch
	Vector#(FrontWidth, Ehr#(2,Epoch) ) commitEpoch <- replicateM(mkEhr('0));

	// Stages
	FIFOF#(Vector#(BackWidth,Maybe#(ExecToken)))    executeQ        <- mkBypassFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(MemToken)))     memoryQ         <- mkPipelineFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(WBToken)))      commitQ         <- mkPipelineFIFOF();

	Vector#(2,Vector#(FrontWidth, FIFOF#(void    ))) toWBsbRemove    <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(2,Vector#(FrontWidth, FIFOF#(RFwb    ))) toWBrfWriteBack <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(2,Vector#(FrontWidth, FIFOF#(Epoch   ))) toWBstEpoch     <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(2,Vector#(FrontWidth, FIFOF#(Redirect))) toWBstRedirect  <- replicateM(replicateM(mkBypassFIFOF));

	// To NTTX
	FIFOF#(NTTXreq)                                eforkQ          <- mkFIFOF();

	// MulDiv
	Vector#(TSub#(BackWidth,1), XilinxIntMul#(void)) mulArray <- replicateM(mkMul);
	Vector#(TSub#(BackWidth,1), XilinxIntDiv#(void)) divArray <- replicateM(mkDiv);

	// Upstream
	Vector#(FrontWidth, FIFOF#(void))              sbRemoveQ       <- replicateM(mkFIFOF());
	Vector#(FrontWidth, FIFOF#(RFwb))              rfWriteBackQ    <- replicateM(mkFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect))          redirectQ       <- replicateM(mkFIFOF());

	// CMR
	Vector#(FrontWidth, Reg#(VerifID))             mapID           <- replicateM(mkRegU());
	Reg#(VerifID)                                  nextID          <- mkReg('d1);

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

	//////////// COUNTERS ////////////

	Reg#(Bool) coreStarted <- mkReg(False);
	Reg#(Data) numCycles   <- mkReg('0);

	rule do_cnt_cycles if(coreStarted);
		numCycles <= numCycles+1;
	endrule

	//////////// EXECUTE ////////////

	rule do_execute;

		Vector#(BackWidth, Maybe#(ExecToken)) toExec = executeQ.first(); executeQ.deq();
		Vector#(BackWidth, Maybe#(MemToken) ) toMem  = replicate(tagged Invalid);

		// Mem lane
		if(toExec[0] matches tagged Valid .eToken) begin
			// Alu and branch, mem pass through
			ExecInst execInst = addr(eToken.iType  ,
			                         eToken.aluFunc,
			                         eToken.mulFunc,
			                         eToken.brFunc ,
			                         eToken.ldFunc ,
			                         eToken.stFunc ,
			                         eToken.arg1   ,
			                         eToken.arg2   ,
			                         eToken.imm    ,
			                         eToken.dst    ,
			                         eToken.pc     );
			let mToken   = MemToken{ inst   : execInst      ,
			                         pc     : eToken.pc     ,
			                         feID   : eToken.feID   ,
			                         epoch  : eToken.epoch  ,
			                         rawInst: eToken.rawInst};
			toMem[0] = tagged Valid mToken;
		end

		// Arith lanes
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
			if(toExec[i] matches tagged Valid .eToken) begin

				// Alu and branch, mem pass through
				ExecInst execInst = exec(eToken.iType  ,
				                         eToken.aluFunc,
				                         eToken.mulFunc,
				                         eToken.brFunc ,
				                         eToken.ldFunc ,
				                         eToken.stFunc ,
				                         eToken.arg1   ,
				                         eToken.arg2   ,
				                         eToken.imm    ,
				                         eToken.dst    ,
				                         eToken.pc     );

				// Mul/Div
				if(eToken.iType == Mul) begin
					case(eToken.mulFunc)
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
			if (mToken.epoch == commitEpoch[mToken.feID][1]) begin
				if (mToken.inst.iType == Ld) begin
					lsu.req(LSUReq{ op     : Ld,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: mToken.feID });
				end else if (mToken.inst.iType == St) begin
					lsu.req(LSUReq{ op     : St,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: mToken.feID });
				end else if(mToken.inst.iType == Join) begin
					lsu.req(LSUReq{ op     : Join,
					                ldFunc : mToken.inst.ldFunc,
					                stFunc : mToken.inst.stFunc,
					                addr   : mToken.inst.addr,
					                data   : mToken.inst.data,
					                transId: mToken.feID });
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

			if(wToken.epoch == commitEpoch[wToken.feID][0])  begin

				sbRemove[wToken.feID] = tagged Valid(?);

				if(wToken.inst.iType == Ghost) begin

					eforkQ.enq(NTTXreq { frontID: wToken.feID,
					                     verifID: mapID[wToken.feID],
					                     nextpc : wToken.pc,
					                     evict  : True });

				end else if(wToken.inst.iType == Ld) begin

					let res <- lsu.resp();
					if(res.valid) begin
						rfWriteBack[wToken.feID] = tagged Valid RFwb{dst: fromMaybe(?, wToken.inst.dst), res: res.data};
						numWB = numWB+1;
						if(cmr_ext_DEBUG == True)
							commitReportQ.port[0].enq(generateCMR(numCycles, mapID[wToken.feID], ?, wToken, res.data, ?));
					end else begin
						miata     [wToken.feID].enq(wToken);
						stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == St) begin

					let res <- lsu.resp();
					if(res.valid) begin
						numWB = numWB+1;
						if(cmr_ext_DEBUG == True)
							commitReportQ.port[0].enq(generateCMR(numCycles, mapID[wToken.feID], ?, wToken, ?, ?));
					end else begin
						miata     [wToken.feID].enq(wToken);
						stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == Join) begin

					let res <- lsu.resp();
					if(res.valid) begin
						if(res.data == '0) begin
							stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
							stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
							                                                 dry     : False,
							                                                 kill    : True,
							                                                 redirect: False,
							                                                 epoch   : commitEpoch[wToken.feID][0]+1,
							                                                 nextPc  : ? };
						end
						numWB = numWB+1;
						if (cmr_ext_DEBUG == True)
								commitReportQ.port[0].enq(generateCMR(numCycles, mapID[wToken.feID], ?, wToken, res.data, ?));
					end else begin
						miata     [wToken.feID].enq(wToken);
						stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.pc+4 };
						if(perf_DEBUG == True)
							commit_miss [0] = True;
					end

				end else if(wToken.inst.iType == Fork || wToken.inst.iType == Forkr) begin

					nextID <= nextID+1;

					eforkQ.enq(NTTXreq { frontID: wToken.feID,
					                     verifID: nextID,
					                     nextpc : wToken.inst.addr,
					                     evict  : False });

					stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
					stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : True,
					                                                 dry     : False,
					                                                 kill    : False,
					                                                 redirect: True,
					                                                 epoch   : commitEpoch[wToken.feID][0]+1,
					                                                 nextPc  : wToken.pc+4 };

					numWB = numWB+1;
					if (cmr_ext_DEBUG == True)
						commitReportQ.port[0].enq(generateCMR(numCycles, mapID[wToken.feID], nextID, wToken, ?, ?));

				end

				if (msg_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == msg_ADDR) begin
						messageReportQ.enq(Message { verifID: mapID[wToken.feID],
						                             cycle  : numCycles,
						                             commit : numCommit[1],
						                             data   : wToken.inst.data });
					end
				end

				if (hex_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == hex_ADDR) begin
						hexReportQ.enq(Message { verifID: mapID[wToken.feID],
						                         cycle  : numCycles,
						                         commit : numCommit[1],
						                         data   : wToken.inst.data });
					end
				end

				if (mem_ext_DEBUG == True) begin
					if(wToken.inst.iType == St && wToken.inst.addr == msr_ADDR) begin
						LSUStat   lsr = lsu.getStat();
						MemStat   msr = MemStat{ verifID: mapID[wToken.feID],
						                         cycle  : numCycles,
						                         commit : numCommit[1],
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

				if (wToken.epoch == commitEpoch[wToken.feID][0])  begin

					sbRemove[wToken.feID] = tagged Valid(?);

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
						stEpoch   [wToken.feID] = tagged Valid (commitEpoch[wToken.feID][0]+1);
						stRedirect[wToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[wToken.feID][0]+1,
						                                                 nextPc  : wToken.inst.addr };
					end

					numWB = numWB+1;

					if (cmr_ext_DEBUG == True) begin
						commitReportQ.port[i].enq(generateCMR(numCycles, mapID[wToken.feID], ?, wToken, ?, mulRes));
					end

					if(perf_DEBUG == True) begin
						commit_valid[i] = True;
					end

				end

			end

		end

		// To WB
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(sbRemove   [i] matches tagged Valid .lat) toWBsbRemove   [0][i].enq(lat);
			if(rfWriteBack[i] matches tagged Valid .lat) toWBrfWriteBack[0][i].enq(lat);
			if(stEpoch    [i] matches tagged Valid .lat) toWBstEpoch    [0][i].enq(lat);
			if(stRedirect [i] matches tagged Valid .lat) toWBstRedirect [0][i].enq(lat);
		end

		// Num  commit
		numCommit[1] <= numCommit[1]+numWB;

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

		LSUResp#(FrontID) resp   <- lsu.oldResp();
		WBToken           wToken  = miata[resp.transId].first; miata[resp.transId].deq();
		FrontID           feID    = wToken.feID;
		Data              loadRes = 'hdeadbeef;

		if(wToken.inst.iType == Ld) begin

			loadRes = resp.data;
			toWBrfWriteBack[1][wToken.feID].enq(RFwb{dst: fromMaybe(?, wToken.inst.dst), res: loadRes});
			toWBstRedirect [1][wToken.feID].enq(Redirect{ lock    : False,
			                                              dry     : False,
			                                              kill    : False,
			                                              redirect: False,
			                                              epoch   : ?    ,
			                                              nextPc  : ?    });

		end else if(wToken.inst.iType == St) begin

			toWBstRedirect [1][wToken.feID].enq(Redirect{ lock    : False,
			                                              dry     : False,
			                                              kill    : False,
			                                              redirect: False,
			                                              epoch   : ?    ,
			                                              nextPc  : ?    });

		end else if(wToken.inst.iType == Join) begin

			loadRes = resp.data;
			if(resp.data == '0) begin
				toWBstEpoch    [1][wToken.feID].enq(commitEpoch[feID][0]+1);
				toWBstRedirect [1][wToken.feID].enq(Redirect{ lock    : False                 ,
				                                              dry     : False                 ,
				                                              kill    : True                  ,
				                                              redirect: False                 ,
				                                              epoch   : commitEpoch[feID][0]+1,
				                                              nextPc  : ?                     });
			end else begin
				toWBstRedirect [1][wToken.feID].enq(Redirect{ lock    : False,
				                                              dry     : False,
				                                              kill    : False,
				                                              redirect: False,
				                                              epoch   : ?    ,
				                                              nextPc  : ?    });
			end

		end

		numCommit[0] <= numCommit[0]+1;

		if (cmr_ext_DEBUG == True) begin
			commitReportQ.port[0].enq(generateCMR(numCycles, mapID[feID], ?, wToken, loadRes, ?));
		end

		if(perf_DEBUG == True) begin
			perf_old_wb_inst[0] <= tagged Valid wToken;
		end

	endrule


	//////////// WRBACK ////////////
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		rule do_wb;

			     if(toWBsbRemove   [0][i].notEmpty) begin sbRemoveQ   [i].enq(toWBsbRemove   [0][i].first); toWBsbRemove   [0][i].deq(); end
			else if(toWBsbRemove   [1][i].notEmpty) begin sbRemoveQ   [i].enq(toWBsbRemove   [1][i].first); toWBsbRemove   [1][i].deq(); end

			     if(toWBrfWriteBack[0][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[0][i].first); toWBrfWriteBack[0][i].deq(); end
			else if(toWBrfWriteBack[1][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[1][i].first); toWBrfWriteBack[1][i].deq(); end

			     if(toWBstEpoch    [0][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [0][i].first ; toWBstEpoch    [0][i].deq(); end
			else if(toWBstEpoch    [1][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [1][i].first ; toWBstEpoch    [1][i].deq(); end

			     if(toWBstRedirect [0][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [0][i].first); toWBstRedirect [0][i].deq(); end
			else if(toWBstRedirect [1][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [1][i].first); toWBstRedirect [1][i].deq(); end

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

	Vector#(FrontWidth, FifoDeq#(void)) deqSBremoveIfc = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deqSBremoveIfc[i] =
			(interface FifoDeq#(Redirect);
				method notEmpty = sbRemoveQ[i].notEmpty;
				method deq      = sbRemoveQ[i].deq;
				method first    = sbRemoveQ[i].first;
			endinterface);
	end

	Vector#(FrontWidth, FifoDeq#(RFwb)) deqRFwriteBackIfc = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deqRFwriteBackIfc[i] =
			(interface FifoDeq#(Redirect);
				method notEmpty = rfWriteBackQ[i].notEmpty;
				method deq      = rfWriteBackQ[i].deq;
				method first    = rfWriteBackQ[i].first;
			endinterface);
	end

	Vector#(FrontWidth, FifoDeq#(Redirect)) deqRedirectIfc = newVector;
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
		deqRedirectIfc[i] =
			(interface FifoDeq#(Redirect);
				method notEmpty = redirectQ[i].notEmpty;
				method deq      = redirectQ[i].deq;
				method first    = redirectQ[i].first;
			endinterface);
	end

	// DMEM
	interface mem = lsu.mem;

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);
		executeQ.enq(inst);
	endmethod

	// To upstream
	interface deqSBremove    = deqSBremoveIfc;
	interface deqRFwriteBack = deqRFwriteBackIfc;
	interface deqRedirect    = deqRedirectIfc;

	// To NTTX
	method ActionValue#(NTTXreq) getFork();
		eforkQ.deq(); return eforkQ.first();
	endmethod

	// To sched
	method Data getNumCommit();
		return numCommit[0];
	endmethod

	// CMR
	method Action startCore();
		coreStarted <= True;
	endmethod

	method Action setVerifID(FrontID feID, VerifID verifID);
		mapID[feID] <= verifID;
	endmethod

	method VerifID getVerifID(FrontID feID);
		return mapID[feID];
	endmethod


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
