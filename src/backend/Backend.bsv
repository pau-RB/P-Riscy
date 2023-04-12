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
	interface WideMemClient#(HartID) mem;

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);

	// To upstream
	interface Vector#(FrontWidth,FifoDeq#(void    )) deqSBremove;
	interface Vector#(FrontWidth,FifoDeq#(RFwb    )) deqRFwriteBack;
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// To NTTX
	method ActionValue#(NTTXreq) getFork();
	method Action setHartID(FrontID feID, HartID hartID);
	method HartID getHartID(FrontID feID);

	// To sched
	method Data getNumCommit();

	// CMR
	method Action startCore();
	method Action setVerifID(FrontID feID, VerifID verifID);
	method VerifID getVerifID(FrontID feID);
	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
	`endif

	// MMIO
	`ifdef DEBUG_STATS
	method ActionValue#(Message) getMSG();
	method ActionValue#(Message) getHEX();
	method ActionValue#(MemStat) getMSR();
	`endif

	// Performance Debug
	`ifdef DEBUG_CYC
	method Vector#(BackWidth,Maybe#(ExecToken)) get_exec_inst  ();
	method Vector#(BackWidth,Maybe#(MemToken) ) get_mem_inst   ();
	method Vector#(BackWidth,Maybe#(ComToken) ) get_wb_inst    ();
	method Vector#(BackWidth,Bool             ) get_wb_valid   ();
	method Vector#(BackWidth,Bool             ) get_wb_miss    ();
	method Data                                 get_wb_commit  ();
	method Maybe#(OldToken)                     get_old_wb_inst();
	`endif

endinterface

module mkBackend (Backend ifc);

	// LSU
	LSU#(NumHart) lsu <- mkLSU();

	// Missed access table
	Vector#(NumHart, FIFOF#(OldToken)) miata    <- replicateM(mkPipelineFIFOF());
	Vector#(NumHart, Ehr#(3,MiataAge)) miataAge <- replicateM(mkEhr('0  ));
	Vector#(NumHart, Ehr#(3,Bool    )) miataEvi <- replicateM(mkEhr(True));
	Vector#(NumHart, Ehr#(3,VerifID )) miataVer <- replicateM(mkEhr(?   ));

	// Epoch
	Vector#(FrontWidth, Ehr#(2,Epoch) ) commitEpoch <- replicateM(mkEhr('0));

	// Stages
	FIFOF#(Vector#(BackWidth,Maybe#(ExecToken)))    executeQ        <- mkBypassFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(MemToken)))     memoryQ         <- mkPipelineFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(ComToken)))     commitQ         <- mkPipelineFIFOF();

	Vector#(3,Vector#(FrontWidth, FIFOF#(void    ))) toWBsbRemove    <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(3,Vector#(FrontWidth, FIFOF#(RFwb    ))) toWBrfWriteBack <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(3,Vector#(FrontWidth, FIFOF#(Epoch   ))) toWBstEpoch     <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(3,Vector#(FrontWidth, FIFOF#(Redirect))) toWBstRedirect  <- replicateM(replicateM(mkBypassFIFOF));

	// To NTTX
	Vector#(3,FIFOF#(NTTXreq))                     tonttx          <- replicateM(mkFIFOF());
	Vector#(FrontWidth, Reg#(HartID))              mapHartID       <- replicateM(mkRegU());

	// MulDiv
	Vector#(TSub#(BackWidth,1), XilinxIntMul#(void)) mulArray <- replicateM(mkMul);
	Vector#(TSub#(BackWidth,1), XilinxIntDiv#(void)) divArray <- replicateM(mkDiv);

	// Upstream
	Vector#(FrontWidth, FIFOF#(void))              sbRemoveQ       <- replicateM(mkFIFOF());
	Vector#(FrontWidth, FIFOF#(RFwb))              rfWriteBackQ    <- replicateM(mkFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect))          redirectQ       <- replicateM(mkFIFOF());

	// CMR
	Vector#(FrontWidth, Reg#(VerifID))             mapVerifID      <- replicateM(mkRegU());
	Reg#(VerifID)                                  nextID          <- mkReg('d1);

	`ifdef DEBUG_CMR
	MFifo#(TAdd#(BackWidth,1),BackWidth,CommitReport) commitReportQ   <- mkPipelineMFifo();
	`endif
	`ifdef MMIO
	FIFOF#(Message)                                messageReportQ  <- mkFIFOF();
	FIFOF#(Message)                                hexReportQ      <- mkFIFOF();
	FIFOF#(MemStat)                                memStatReportQ  <- mkFIFOF();
	`endif

	// Perf debug
	`ifdef DEBUG_CYC
	Ehr#(2,Vector#(BackWidth,Maybe#(ExecToken)))   perf_exec_inst  <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Maybe#(MemToken) ))   perf_mem_inst   <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Maybe#(ComToken) ))   perf_wb_inst    <- mkEhr(replicate(tagged Invalid));
	Ehr#(2,Vector#(BackWidth,Bool             ))   perf_wb_valid   <- mkEhr(replicate(       False  ));
	Ehr#(2,Vector#(BackWidth,Bool             ))   perf_wb_miss    <- mkEhr(replicate(       False  ));
	`endif

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

			Exec exec = execmem(eToken.iType  ,
			                    eToken.arg1   ,
			                    eToken.arg2   ,
			                    eToken.imm    ,
			                    eToken.pc     );

			let mToken = MemToken{ feID   : eToken.feID   ,
			                       epoch  : eToken.epoch  ,
			                       `ifdef DEBUG_RAW_INST
			                       pc     : eToken.pc     ,
			                       rawInst: eToken.rawInst,
			                       `endif
			                       // iType
			                       iType  : eToken.iType  ,
			                       mulFunc: eToken.mulFunc,
			                       divFunc: eToken.divFunc,
			                       ldFunc : eToken.ldFunc ,
			                       stFunc : eToken.stFunc ,
			                       // Op
			                       res    : exec.res      ,
			                       addr   : exec.add      ,
			                       nextpc : exec.npc      ,
			                       brTaken: exec.brt      ,
			                       dst    : eToken.dst    };

			toMem[0] = tagged Valid mToken;

		end

		// Arith lanes
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
		if(toExec[i] matches tagged Valid .eToken) begin

			Exec exec = execari(eToken.iType  ,
			                    eToken.aluFunc,
			                    eToken.brFunc ,
			                    eToken.arg1   ,
			                    eToken.arg2   ,
			                    eToken.imm    ,
			                    eToken.pc     );

			let mToken = MemToken{ feID   : eToken.feID   ,
			                       epoch  : eToken.epoch  ,
			                       `ifdef DEBUG_RAW_INST
			                       pc     : eToken.pc     ,
			                       rawInst: eToken.rawInst,
			                       `endif
			                       // iType
			                       iType  : eToken.iType  ,
			                       mulFunc: eToken.mulFunc,
			                       divFunc: eToken.divFunc,
			                       ldFunc : eToken.ldFunc ,
			                       stFunc : eToken.stFunc ,
			                       // Op
			                       res    : exec.res      ,
			                       addr   : exec.add      ,
			                       nextpc : exec.npc      ,
			                       brTaken: exec.brt      ,
			                       dst    : eToken.dst    };

			toMem[i] = tagged Valid mToken;

			// Mul/Div
			if(eToken.iType == Mul) begin
				case(eToken.mulFunc)
				Mul   : mulArray[i-1].req(eToken.arg1, eToken.arg2, Signed        , ?);
				Mulh  : mulArray[i-1].req(eToken.arg1, eToken.arg2, Signed        , ?);
				Mulhsu: mulArray[i-1].req(eToken.arg1, eToken.arg2, SignedUnsigned, ?);
				Mulhu : mulArray[i-1].req(eToken.arg1, eToken.arg2, Unsigned      , ?);
				endcase
			end
			if(eToken.iType == Div) begin
				case(eToken.divFunc)
				Div   : divArray[i-1].req(eToken.arg1, eToken.arg2, True          , ?);
				Divu  : divArray[i-1].req(eToken.arg1, eToken.arg2, False         , ?);
				Rem   : divArray[i-1].req(eToken.arg1, eToken.arg2, True          , ?);
				Remu  : divArray[i-1].req(eToken.arg1, eToken.arg2, False         , ?);
				endcase
			end

		end
		end

		memoryQ.enq(toMem);

		`ifdef DEBUG_CYC
		perf_exec_inst[0] <= toExec;
		`endif

	endrule

	//////////// MEMORY ////////////

	rule do_mem;

		Vector#(BackWidth, Maybe#(MemToken)) toMem    = memoryQ.first(); memoryQ.deq();
		Vector#(BackWidth, Maybe#(ComToken)) toCommit = replicate(tagged Invalid);

		// Mem lane
		if(toMem[0] matches tagged Valid .mToken) begin
			let cToken = ComToken { feID   : mToken.feID   ,
			                        epoch  : mToken.epoch  ,
			                        `ifdef DEBUG_RAW_INST
			                        pc     : mToken.pc     ,
			                        rawInst: mToken.rawInst,
			                        `endif
			                        // iType
			                        iType  : mToken.iType  ,
			                        mulFunc: mToken.mulFunc,
			                        divFunc: mToken.divFunc,
			                        // Op
			                        res    : mToken.res    ,
			                        addr   : mToken.addr   ,
			                        nextpc : mToken.nextpc ,
			                        brTaken: mToken.brTaken,
			                        dst    : mToken.dst    };
			toCommit[0] = tagged Valid cToken;

			// Send LSU req, if the instruction is valid
			if (mToken.epoch == commitEpoch[mToken.feID][1]) begin
				if (mToken.iType == Ld) begin
					lsu.req(LSUReq{ op     : Ld,
					                ldFunc : mToken.ldFunc,
					                stFunc : mToken.stFunc,
					                addr   : mToken.addr,
					                data   : mToken.res,
					                transId: mapHartID[mToken.feID] });
				end else if (mToken.iType == St) begin
					lsu.req(LSUReq{ op     : St,
					                ldFunc : mToken.ldFunc,
					                stFunc : mToken.stFunc,
					                addr   : mToken.addr,
					                data   : mToken.res,
					                transId: mapHartID[mToken.feID] });
				end else if(mToken.iType == Join) begin
					lsu.req(LSUReq{ op     : Join,
					                ldFunc : mToken.ldFunc,
					                stFunc : mToken.stFunc,
					                addr   : mToken.addr,
					                data   : mToken.res,
					                transId: mapHartID[mToken.feID] });
				end
			end
		end

		// Arith lanes
		for(Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
		if(toMem[i] matches tagged Valid .mToken) begin
			let cToken = ComToken { feID   : mToken.feID   ,
			                        epoch  : mToken.epoch  ,
			                        `ifdef DEBUG_RAW_INST
			                        pc     : mToken.pc     ,
			                        rawInst: mToken.rawInst,
			                        `endif
			                        // iType
			                        iType  : mToken.iType  ,
			                        mulFunc: mToken.mulFunc,
			                        divFunc: mToken.divFunc,
			                        // Op
			                        res    : mToken.res    ,
			                        addr   : mToken.addr   ,
			                        nextpc : mToken.nextpc ,
			                        brTaken: mToken.brTaken,
			                        dst    : mToken.dst    };
			toCommit[i] = tagged Valid cToken;
		end
		end

		commitQ.enq(toCommit);

		`ifdef DEBUG_CYC
		perf_mem_inst[0] <= toMem;
		`endif

	endrule

	//////////// COMMIT ////////////

	rule do_commit;

		// Upstream actions
		Vector#(FrontWidth, Maybe#(void    )) sbRemove     = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(RFwb    )) rfWriteBack  = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Epoch   )) stEpoch      = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Redirect)) stRedirect   = replicate(tagged Invalid);

		// WB
		Vector#(BackWidth, Maybe#(ComToken))  toCommit     = commitQ.first(); commitQ.deq();
		Vector#(BackWidth,Bool             )  commit_valid = replicate(False);
		Vector#(BackWidth,Bool             )  commit_miss  = replicate(False);
		Data numWB = 0;


		// Mem lane
		if(toCommit[0] matches tagged Valid .cToken) begin

			if(cToken.epoch == commitEpoch[cToken.feID][0])  begin

				sbRemove[cToken.feID] = tagged Valid(?);

				if(cToken.iType == Ghost) begin

					tonttx[2].enq(NTTXreq { frontID: cToken.feID            ,
					                        hartID : mapHartID [cToken.feID],
					                        verifID: mapVerifID[cToken.feID],
					                        nextpc : cToken.nextpc          ,
					                        reqtype: EVICT                  });

				end else if(cToken.iType == Ld) begin

					let res <- lsu.resp();
					if(res.valid) begin
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe(?, cToken.dst), res: res.data};
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapVerifID[cToken.feID], ?, cToken, res.data, ?));
						`endif
					end else begin
						miata     [mapHartID[cToken.feID]].enq(OldToken{ feID   : cToken.feID              ,
						                                                 `ifdef DEBUG_CMR
						                                                 pc     : cToken.pc                ,
						                                                 `endif
						                                                 `ifdef  DEBUG_RAW_INST
						                                                 rawInst: cToken.rawInst           ,
						                                                 `endif
						                                                 iType  : Ld                       ,
						                                                 `ifdef  DEBUG_CMR
						                                                 addr   : cToken.addr              ,
						                                                 `endif
						                                                 nextpc : cToken.nextpc            ,
						                                                 dst    : fromMaybe('0,cToken.dst) });
						miataAge  [mapHartID[cToken.feID]][2] <= '0;
						miataEvi  [mapHartID[cToken.feID]][2] <= False;
						miataVer  [mapHartID[cToken.feID]][2] <= mapVerifID[cToken.feID];

						stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[cToken.feID][0]+1,
						                                                 nextPc  : cToken.nextpc };
						`ifdef DEBUG_CYC
						commit_miss [0] = True;
						`endif
					end

				end else if(cToken.iType == St) begin

					let res <- lsu.resp();
					if(res.valid) begin
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapVerifID[cToken.feID], ?, cToken, ?, ?));
						`endif
					end else begin
						miata     [mapHartID[cToken.feID]].enq(OldToken{feID   : cToken.feID              ,
						                                                `ifdef DEBUG_CMR
						                                                pc     : cToken.pc                ,
						                                                `endif
						                                                `ifdef  DEBUG_RAW_INST
						                                                rawInst: cToken.rawInst           ,
						                                                `endif
						                                                iType  : St                       ,
						                                                `ifdef  DEBUG_CMR
						                                                addr   : cToken.addr              ,
						                                                `endif
						                                                nextpc : cToken.nextpc            ,
						                                                dst    : fromMaybe('0,cToken.dst) });
						miataAge  [mapHartID[cToken.feID]][2] <= '0;
						miataEvi  [mapHartID[cToken.feID]][2] <= False;
						miataVer  [mapHartID[cToken.feID]][2] <= mapVerifID[cToken.feID];

						stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[cToken.feID][0]+1,
						                                                 nextPc  : cToken.nextpc };
						`ifdef DEBUG_CYC
						commit_miss [0] = True;
						`endif
					end

				end else if(cToken.iType == Join) begin

					let res <- lsu.resp();
					if(res.valid) begin
						if(res.data == '0) begin
							stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
							stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : False,
							                                                 dry     : False,
							                                                 kill    : True,
							                                                 redirect: False,
							                                                 epoch   : commitEpoch[cToken.feID][0]+1,
							                                                 nextPc  : ? };
							tonttx[2].enq(NTTXreq { frontID: cToken.feID            ,
							                        hartID : mapHartID [cToken.feID],
							                        verifID: mapVerifID[cToken.feID],
							                        nextpc : cToken.nextpc          ,
							                        reqtype: JOIN                   });
						end
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapVerifID[cToken.feID], ?, cToken, res.data, ?));
						`endif
					end else begin
						miata     [mapHartID[cToken.feID]].enq(OldToken{feID   : cToken.feID              ,
						                                                `ifdef DEBUG_CMR
						                                                pc     : cToken.pc                ,
						                                                `endif
						                                                `ifdef  DEBUG_RAW_INST
						                                                rawInst: cToken.rawInst           ,
						                                                `endif
						                                                iType  : Join                     ,
						                                                `ifdef  DEBUG_CMR
						                                                addr   : cToken.addr              ,
						                                                `endif
						                                                nextpc : cToken.nextpc            ,
						                                                dst    : fromMaybe('0,cToken.dst) });
						miataAge  [mapHartID[cToken.feID]][2] <= '0;
						miataEvi  [mapHartID[cToken.feID]][2] <= False;
						miataVer  [mapHartID[cToken.feID]][2] <= mapVerifID[cToken.feID];

						stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : True,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[cToken.feID][0]+1,
						                                                 nextPc  : cToken.nextpc };
						`ifdef DEBUG_CYC
						commit_miss [0] = True;
						`endif
					end

				end else if(cToken.iType == Fork || cToken.iType == Forkr) begin

					nextID <= nextID+1;

					tonttx[2].enq(NTTXreq { frontID: cToken.feID           ,
					                        hartID : mapHartID[cToken.feID],
					                        verifID: nextID                ,
					                        nextpc : cToken.addr           ,
					                        reqtype: FORK                  });

					stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
					stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : True,
					                                                 dry     : False,
					                                                 kill    : False,
					                                                 redirect: True,
					                                                 epoch   : commitEpoch[cToken.feID][0]+1,
					                                                 nextPc  : cToken.nextpc };

					numWB = numWB+1;

					`ifdef DEBUG_CMR
					commitReportQ.port[0].enq(generateCMR(numCycles, mapVerifID[cToken.feID], nextID, cToken, ?, ?));
					`endif
				end

				`ifdef MMIO
				if (msg_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == msg_ADDR) begin
						messageReportQ.enq(Message { verifID: mapVerifID[cToken.feID],
						                             cycle  : numCycles,
						                             commit : numCommit[1],
						                             data   : cToken.res });
					end
				end
				if (hex_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == hex_ADDR) begin
						hexReportQ.enq(Message { verifID: mapVerifID[cToken.feID],
						                         cycle  : numCycles,
						                         commit : numCommit[1],
						                         data   : cToken.res });
					end
				end
				if (mem_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == msr_ADDR) begin
						LSUStat   lsr = lsu.getStat();
						MemStat   msr = MemStat{ verifID: mapVerifID[cToken.feID],
						                         cycle  : numCycles,
						                         commit : numCommit[1],
						                         data   : cToken.res,
						                         fetch  : ?,
						                         arbiter: ?,
						                         lsu    : lsr };
						memStatReportQ.enq(msr);
					end
				end
				`endif

				`ifdef DEBUG_CYC
				commit_valid[0] = True;
				`endif

			end

		end

		// Arith lanes
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin

			if(toCommit[i] matches tagged Valid .cToken) begin

				if(cToken.iType == Mul) mulArray[i-1].deqResp();
				if(cToken.iType == Div) divArray[i-1].deqResp();

				if (cToken.epoch == commitEpoch[cToken.feID][0])  begin

					sbRemove[cToken.feID] = tagged Valid(?);

					Data muldivRes = ?;

					if(cToken.iType == Mul) begin
						muldivRes = (case(cToken.mulFunc)
							Mul   : truncate   (mulArray[i-1].product);
							Mulh  : truncateLSB(mulArray[i-1].product);
							Mulhsu: truncateLSB(mulArray[i-1].product);
							Mulhu : truncateLSB(mulArray[i-1].product);
						endcase);
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: muldivRes};
					end else if(cToken.iType == Div) begin
						muldivRes = (case(cToken.divFunc)
							Div   : divArray[i-1].quotient ;
							Divu  : divArray[i-1].quotient ;
							Rem   : divArray[i-1].remainder;
							Remu  : divArray[i-1].remainder;
						endcase);
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: muldivRes};
					end else if(isValid(cToken.dst))
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: cToken.res};

					if(cToken.brTaken || cToken.iType == J || cToken.iType == Jr) begin
						stEpoch   [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect[cToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                 dry     : False,
						                                                 kill    : False,
						                                                 redirect: True,
						                                                 epoch   : commitEpoch[cToken.feID][0]+1,
						                                                 nextPc  : cToken.addr };
					end

					numWB = numWB+1;

					`ifdef DEBUG_CMR
					commitReportQ.port[i].enq(generateCMR(numCycles, mapVerifID[cToken.feID], ?, cToken, ?, muldivRes));
					`endif

					`ifdef DEBUG_CYC
					commit_valid[i] = True;
					`endif

				end

			end

		end

		// To WB
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(sbRemove   [i] matches tagged Valid .lat) toWBsbRemove   [2][i].enq(lat);
			if(rfWriteBack[i] matches tagged Valid .lat) toWBrfWriteBack[2][i].enq(lat);
			if(stEpoch    [i] matches tagged Valid .lat) toWBstEpoch    [2][i].enq(lat);
			if(stRedirect [i] matches tagged Valid .lat) toWBstRedirect [2][i].enq(lat);
		end

		// Num  commit
		numCommit[1] <= numCommit[1]+numWB;

		// Perf debug
		`ifdef DEBUG_CYC
		perf_wb_inst [0] <= toCommit;
		perf_wb_valid[0] <= commit_valid;
		perf_wb_miss [0] <= commit_miss;
		`endif

	endrule


	//////////// OLD COMMIT ////////////

	Ehr#(2,Maybe#(OldToken)) perf_old_wb_inst  <- mkEhr(tagged Invalid);

	rule do_old_commit;

		LSUResp#(HartID) resp   <- lsu.oldResp();
		OldToken         cToken  = miata[resp.transId].first; miata[resp.transId].deq();
		FrontID          feID    = cToken.feID;
		Data             loadRes = 'hdeadbeef;

		if(!miataEvi[resp.transId][1]) begin
			// The stream has not yet been evicted, can commit and resume execution as usual

			if(cToken.iType == Ld) begin

				loadRes = resp.data;
				toWBrfWriteBack[1][cToken.feID].enq(RFwb{dst: cToken.dst, res: loadRes});
				toWBstRedirect [1][cToken.feID].enq(Redirect{ lock    : False,
				                                              dry     : False,
				                                              kill    : False,
				                                              redirect: False,
				                                              epoch   : ?    ,
				                                              nextPc  : ?    });

			end else if(cToken.iType == St) begin

				toWBstRedirect [1][cToken.feID].enq(Redirect{ lock    : False,
				                                              dry     : False,
				                                              kill    : False,
				                                              redirect: False,
				                                              epoch   : ?    ,
				                                              nextPc  : ?    });

			end else if(cToken.iType == Join) begin

				loadRes = resp.data;
				if(resp.data == '0) begin
					toWBstEpoch    [1][cToken.feID].enq(commitEpoch[feID][0]+1);
					toWBstRedirect [1][cToken.feID].enq(Redirect{ lock    : False                 ,
					                                              dry     : False                 ,
					                                              kill    : True                  ,
					                                              redirect: False                 ,
					                                              epoch   : commitEpoch[feID][0]+1,
					                                              nextPc  : ?                     });
				end else begin
					toWBstRedirect [1][cToken.feID].enq(Redirect{ lock    : False,
					                                              dry     : False,
					                                              kill    : False,
					                                              redirect: False,
					                                              epoch   : ?    ,
					                                              nextPc  : ?    });
				end

			end

			numCommit[0] <= numCommit[0]+1;

		end else begin
			// The stream has been evicted, cannot commit Ld or trust any feID-indexed field

			if(cToken.iType == Ld) begin
				tonttx[1].enq(NTTXreq { frontID: ?           ,
				                        hartID : resp.transId,
				                        verifID: ?           ,
				                        nextpc : ?           ,
				                        reqtype: MKRD        });

			end else if(cToken.iType == St) begin
				tonttx[1].enq(NTTXreq { frontID: ?           ,
				                        hartID : resp.transId,
				                        verifID: ?           ,
				                        nextpc : ?           ,
				                        reqtype: MKRD        });

				numCommit[0] <= numCommit[0]+1;

			end

		end

		`ifdef DEBUG_CMR
		if(!miataEvi[resp.transId][1] || cToken.iType == St)
			commitReportQ.port[0].enq(generateOldCMR(numCycles, miataVer[resp.transId][0], cToken, loadRes));
		`endif

		`ifdef DEBUG_CYC
		perf_old_wb_inst[0] <= tagged Valid cToken;
		`endif

	endrule

	for(Integer i = 0; i < valueOf(NumHart); i=i+1) begin
		rule do_miata_evi if(miataAge[i][0] == fromInteger(valueOf(MiataThresh)) && !miataEvi[i][0]);

				OldToken cToken = miata[i].first;
				if(cToken.iType == Ld) begin

					miataEvi   [i][0] <= True;
					toWBstEpoch   [0][cToken.feID].enq(commitEpoch[cToken.feID][0]+1);
					toWBstRedirect[0][cToken.feID].enq(Redirect{lock    : True                         ,
					                                            dry     : False                        ,
					                                            kill    : True                         ,
					                                            redirect: False                        ,
					                                            epoch   : commitEpoch[cToken.feID][0]+1,
					                                            nextPc  : ?                            });
					tonttx[0].enq(NTTXreq { frontID: cToken.feID    ,
					                        hartID : fromInteger(i) ,
					                        verifID: miataVer[i][1] ,
					                        nextpc : cToken.nextpc-4,
					                        reqtype: STALL          });

				end else if(cToken.iType == St) begin

					miataEvi   [i][0] <= True;
					toWBstEpoch   [0][cToken.feID].enq(commitEpoch[cToken.feID][0]+1);
					toWBstRedirect[0][cToken.feID].enq(Redirect{lock    : True                         ,
					                                            dry     : False                        ,
					                                            kill    : True                         ,
					                                            redirect: False                        ,
					                                            epoch   : commitEpoch[cToken.feID][0]+1,
					                                            nextPc  : ?                            });
					tonttx[0].enq(NTTXreq { frontID: cToken.feID   ,
					                        hartID : fromInteger(i),
					                        verifID: miataVer[i][1],
					                        nextpc : cToken.nextpc ,
					                        reqtype: STALL         });

				end

		endrule
	end

	for(Integer i = 0; i < valueOf(NumHart); i=i+1) begin
		rule do_miata_age if(miataAge[i][0] != fromInteger(valueOf(MiataThresh)) && !miataEvi[i][0]);
				miataAge[i][0] <= (miataAge[i][0]+1);
		endrule
	end

	//////////// WRBACK ////////////
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		rule do_wb;

			     if(toWBsbRemove   [2][i].notEmpty) begin sbRemoveQ   [i].enq(toWBsbRemove   [2][i].first); toWBsbRemove   [2][i].deq(); end
			else if(toWBsbRemove   [1][i].notEmpty) begin sbRemoveQ   [i].enq(toWBsbRemove   [1][i].first); toWBsbRemove   [1][i].deq(); end
			else if(toWBsbRemove   [0][i].notEmpty) begin sbRemoveQ   [i].enq(toWBsbRemove   [0][i].first); toWBsbRemove   [0][i].deq(); end

			     if(toWBrfWriteBack[2][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[2][i].first); toWBrfWriteBack[2][i].deq(); end
			else if(toWBrfWriteBack[1][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[1][i].first); toWBrfWriteBack[1][i].deq(); end
			else if(toWBrfWriteBack[0][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[0][i].first); toWBrfWriteBack[0][i].deq(); end

			     if(toWBstEpoch    [2][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [2][i].first ; toWBstEpoch    [2][i].deq(); end
			else if(toWBstEpoch    [1][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [1][i].first ; toWBstEpoch    [1][i].deq(); end
			else if(toWBstEpoch    [0][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [0][i].first ; toWBstEpoch    [0][i].deq(); end

			     if(toWBstRedirect [2][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [2][i].first); toWBstRedirect [2][i].deq(); end
			else if(toWBstRedirect [1][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [1][i].first); toWBstRedirect [1][i].deq(); end
			else if(toWBstRedirect [0][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [0][i].first); toWBstRedirect [0][i].deq(); end

		endrule

	end


	//////////// PERF DEBUG ////////////

	`ifdef DEBUG_CYC
	rule do_DEBUG_CYC;

		perf_exec_inst  [1] <= replicate(tagged Invalid);
		perf_mem_inst   [1] <= replicate(tagged Invalid);
		perf_wb_inst    [1] <= replicate(tagged Invalid);
		perf_wb_valid   [1] <= replicate(       False  );
		perf_wb_miss    [1] <= replicate(       False  );
		perf_old_wb_inst[1] <= tagged Invalid;

	endrule
	`endif


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
		     if(tonttx[2].notEmpty) begin tonttx[2].deq; return tonttx[2].first; end
		else if(tonttx[1].notEmpty) begin tonttx[1].deq; return tonttx[1].first; end
		else                        begin tonttx[0].deq; return tonttx[0].first; end
	endmethod

	method Action setHartID(FrontID feID, HartID hartID);
		mapHartID[feID] <= hartID;
	endmethod

	method HartID getHartID(FrontID feID);
		return mapHartID[feID];
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
		mapVerifID[feID] <= verifID;
	endmethod

	method VerifID getVerifID(FrontID feID);
		return mapVerifID[feID];
	endmethod

	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;
	endmethod
	`endif

	`ifdef MMIO
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
	`endif

	// Performance Debug
	`ifdef DEBUG_CYC

	method Vector#(BackWidth,Maybe#(ExecToken)) get_exec_inst();
		return perf_exec_inst[1];
	endmethod

	method Vector#(BackWidth,Maybe#(MemToken)) get_mem_inst();
		return perf_mem_inst[1];
	endmethod

	method Vector#(BackWidth,Maybe#(ComToken)) get_wb_inst();
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

	method Maybe#(OldToken) get_old_wb_inst();
		return perf_old_wb_inst[1];
	endmethod

	`endif

endmodule
