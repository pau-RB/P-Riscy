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
import L1D::*;
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

`ifdef DEBUG_CYC
interface DEB_CYC_exe;
	method Bool    notEmpty;
	method Addr    nextPC  ;
	method FrontID feID    ;
endinterface
interface DEB_CYC_mem;
	method Bool    notEmpty;
	method Addr    nextPC  ;
	method FrontID feID    ;
endinterface
interface DEB_CYC_com;
	method Bool    notEmpty;
	method Addr    nextPC  ;
	method FrontID feID    ;
	method Bool    valid   ;
	method Bool    miss    ;
	method Data    rawInst ;
endinterface
interface DEB_CYC_lat;
	method Bool    notEmpty;
	method FrontID feID    ;
	method Data    rawInst ;
endinterface
`endif

interface Backend;

	// DMEM
	interface WideMemClient#(FrontID) mem;

	// Execute
	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);

	// To upstream
	interface Vector#(FrontWidth,FifoDeq#(RFwb    )) deqRFwriteBack;
	interface Vector#(FrontWidth,FifoDeq#(Redirect)) deqRedirect;

	// To NTTX
	method ActionValue#(NTTXreq) getFork();

	// To sched
	method PerfCnt getNumCommit();

	// CMR
	method Action startCore();
	method Action setVerifID(FrontID feID, VerifID verifID);
	method VerifID getVerifID(FrontID feID);
	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
	`endif

	// MMIO
	`ifdef MMIO
	method ActionValue#(StatReq) getMSG();
	method ActionValue#(StatReq) getHEX();
	method ActionValue#(StatReq) getMSR();
	`endif

	// Performance Debug
	`ifdef DEBUG_CYC
	method Vector#(BackWidth,DEB_CYC_exe) cycExe;
	method Vector#(BackWidth,DEB_CYC_mem) cycMem;
	method Vector#(BackWidth,DEB_CYC_com) cycCom;
	method                   DEB_CYC_lat  cycLat;
	method PerfCnt cycNumCommit();
	`endif

	`ifdef DEBUG_STATS
	method L1DStat getL1DStat();
	`endif

endinterface

module mkBackend (Backend ifc);

	// L1D
	L1D#(FrontWidth, L1DCacheRows, L1DCacheColumns, L1DCacheHashBlocks) l1D <- mkL1D();

	// Missed access table
	Vector#(FrontWidth, FIFOF#(OldToken)) miata <- replicateM(mkPipelineFIFOF());

	// Epoch
	Vector#(FrontWidth, Ehr#(2,Epoch) ) commitEpoch <- replicateM(mkEhr('0));

	// Stages
	FIFOF#(Vector#(BackWidth,Maybe#(MemToken)))     memoryQ         <- mkPipelineFIFOF();
	FIFOF#(Vector#(BackWidth,Maybe#(ComToken)))     commitQ         <- mkPipelineFIFOF();

	Vector#(2,Vector#(FrontWidth, FIFOF#(RFwb    ))) toWBrfWriteBack <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(2,Vector#(FrontWidth, FIFOF#(Epoch   ))) toWBstEpoch     <- replicateM(replicateM(mkBypassFIFOF));
	Vector#(2,Vector#(FrontWidth, FIFOF#(Redirect))) toWBstRedirect  <- replicateM(replicateM(mkBypassFIFOF));

	// To NTTX
	FIFOF#(NTTXreq)                                eforkQ          <- mkFIFOF();

	// MulDiv
	Vector#(TSub#(BackWidth,1), XilinxIntMul#(void)) mulArray <- replicateM(mkMul);
	Vector#(TSub#(BackWidth,1), XilinxIntDiv#(void)) divArray <- replicateM(mkDiv);

	// Upstream
	Vector#(FrontWidth, FIFOF#(RFwb))              rfWriteBackQ    <- replicateM(mkFIFOF());
	Vector#(FrontWidth, FIFOF#(Redirect))          redirectQ       <- replicateM(mkFIFOF());

	// CMR
	Vector#(FrontWidth, Reg#(VerifID))             mapID           <- replicateM(mkRegU());
	Reg#(VerifID)                                  nextID          <- mkReg('d1);

	`ifdef DEBUG_CMR
	MFifo#(TAdd#(BackWidth,1),BackWidth,CommitReport) commitReportQ   <- mkPipelineMFifo();
	`endif

	// MMIO
	`ifdef MMIO
	FIFOF#(StatReq)                                mmioMSGQ        <- mkFIFOF();
	FIFOF#(StatReq)                                mmioHEXQ        <- mkFIFOF();
	FIFOF#(StatReq)                                mmioMSRQ        <- mkFIFOF();
	`endif

	// Stats
	Ehr#(3,PerfCnt)                                numCommit       <- mkEhr(0);

	//////////// COUNTERS ////////////

	Reg#(Bool)    coreStarted <- mkReg(False);
	Reg#(PerfCnt) numCycles   <- mkReg('0);

	rule do_cnt_cycles if(coreStarted);
		numCycles <= numCycles+1;
	endrule

	//////////// EXECUTE ////////////

	`ifdef DEBUG_CYC
	Vector#(BackWidth, RWire#(Bool   )) deb_cyc_exe_notEmpty <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Addr   )) deb_cyc_exe_nextPC   <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(FrontID)) deb_cyc_exe_feID     <- replicateM(mkRWire);
	`endif

	//////////// MEMORY ////////////

	`ifdef DEBUG_CYC
	Vector#(BackWidth, RWire#(Bool   )) deb_cyc_mem_notEmpty <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Addr   )) deb_cyc_mem_nextPC   <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(FrontID)) deb_cyc_mem_feID     <- replicateM(mkRWire);
	`endif

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

			// Confirm L1D req, if the instruction is valid
			if(mToken.iType == Ld || mToken.iType == St || mToken.iType == Join)
				l1D.confirm((mToken.epoch == commitEpoch[mToken.feID][1]));

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
		for (Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
			if(toMem[i] matches tagged Valid .inst) begin
				deb_cyc_mem_notEmpty[i].wset(True     );
				deb_cyc_mem_nextPC  [i].wset(inst.pc  );
				deb_cyc_mem_feID    [i].wset(inst.feID);
			end
		end
		`endif

	endrule

	//////////// COMMIT ////////////

	`ifdef DEBUG_CYC
	Vector#(BackWidth, RWire#(Bool   )) deb_cyc_com_notEmpty <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Addr   )) deb_cyc_com_nextPC   <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(FrontID)) deb_cyc_com_feID     <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Bool   )) deb_cyc_com_valid    <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Bool   )) deb_cyc_com_miss     <- replicateM(mkRWire);
	Vector#(BackWidth, RWire#(Data   )) deb_cyc_com_rawInst  <- replicateM(mkRWire);
	`endif

	rule do_commit;

		// Upstream actions
		Vector#(FrontWidth, Maybe#(RFwb    )) rfWriteBack  = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Epoch   )) stEpoch      = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Redirect)) stRedirect   = replicate(tagged Invalid);

		// WB
		Vector#(BackWidth, Maybe#(ComToken))  toCommit     = commitQ.first(); commitQ.deq();
		Vector#(BackWidth,Bool             )  commit_valid = replicate(False);
		Vector#(BackWidth,Bool             )  commit_miss  = replicate(False);
		PerfCnt numWB = 0;


		// Mem lane
		if(toCommit[0] matches tagged Valid .cToken) begin

			if(cToken.epoch == commitEpoch[cToken.feID][0])  begin

				if(cToken.iType == Ghost) begin

					eforkQ.enq(NTTXreq { frontID: cToken.feID,
					                     verifID: mapID[cToken.feID],
					                     nextpc : cToken.nextpc,
					                     evict  : True });

				end else if(cToken.iType == Ld) begin

					let res = l1D.getres(); l1D.deqres();
					if(res.valid) begin
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe(?, cToken.dst), res: res.data, rmv: True, clr: False};
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapID[cToken.feID], ?, cToken, res.data, ?));
						`endif
					end else begin
						miata     [cToken.feID].enq(OldToken{`ifdef DEBUG_CYC
						                                     feID   : cToken.feID              ,
						                                     `endif
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
						                                     dst    : fromMaybe('0,cToken.dst) });
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0, rmv: False, clr: True};
						stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : True,
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

					let res = l1D.getres(); l1D.deqres();
					if(res.valid) begin
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapID[cToken.feID], ?, cToken, ?, ?));
						`endif
					end else begin
						miata     [cToken.feID].enq(OldToken{`ifdef DEBUG_CYC
						                                     feID   : cToken.feID              ,
						                                     `endif
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
						                                     dst    : fromMaybe('0,cToken.dst) });
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0,  rmv: False, clr: True};
						stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : True,
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

					let res = l1D.getres(); l1D.deqres();
					if(res.valid) begin
						if(res.data == '0) begin
							rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0, rmv: False, clr: True};
							stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
							stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : False,
							                                                  dry     : False,
							                                                  kill    : True,
							                                                  redirect: False,
							                                                  epoch   : commitEpoch[cToken.feID][0]+1,
							                                                  nextPc  : ? };
						end
						numWB = numWB+1;
						`ifdef DEBUG_CMR
						commitReportQ.port[0].enq(generateCMR(numCycles, mapID[cToken.feID], ?, cToken, res.data, ?));
						`endif
					end else begin
						miata     [cToken.feID].enq(OldToken{`ifdef DEBUG_CYC
						                                     feID   : cToken.feID              ,
						                                     `endif
						                                     `ifdef DEBUG_CMR
						                                     pc     : cToken.pc                ,
						                                     `endif
						                                     `ifdef  DEBUG_RAW_INST
						                                     rawInst: cToken.rawInst           ,
						                                     `endif
						                                     iType  : Join                       ,
						                                     `ifdef  DEBUG_CMR
						                                     addr   : cToken.addr              ,
						                                     `endif
						                                     dst    : fromMaybe('0,cToken.dst) });
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0,  rmv: False, clr: True};
						stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : True,
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

					eforkQ.enq(NTTXreq { frontID: cToken.feID,
					                     verifID: nextID,
					                     nextpc : cToken.addr,
					                     evict  : False });

					rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0, rmv: False, clr: True};
					stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
					stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : True,
					                                                  dry     : False,
					                                                  kill    : False,
					                                                  redirect: True,
					                                                  epoch   : commitEpoch[cToken.feID][0]+1,
					                                                  nextPc  : cToken.nextpc };

					numWB = numWB+1;
					`ifdef DEBUG_CMR
					commitReportQ.port[0].enq(generateCMR(numCycles, mapID[cToken.feID], nextID, cToken, ?, ?));
					`endif
				end

				`ifdef MMIO
				if (msg_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == msg_ADDR) begin
						mmioMSGQ.enq(StatReq { verifID: mapID[cToken.feID],
						                       cycle  : numCycles         ,
						                       commit : numCommit[1]      ,
						                       data   : cToken.res        });
					end
				end
				if (hex_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == hex_ADDR) begin
						mmioHEXQ.enq(StatReq { verifID: mapID[cToken.feID],
						                       cycle  : numCycles         ,
						                       commit : numCommit[1]      ,
						                       data   : cToken.res        });
					end
				end
				if (msr_ext_DEBUG == True) begin
					if(cToken.iType == St && cToken.addr == msr_ADDR) begin
						mmioMSRQ.enq(StatReq { verifID: mapID[cToken.feID],
						                       cycle  : numCycles         ,
						                       commit : numCommit[1]      ,
						                       data   : cToken.res        });
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

					Data muldivRes = ?;

					if(cToken.iType == Mul) begin
						muldivRes = (case(cToken.mulFunc)
							Mul   : truncate   (mulArray[i-1].product);
							Mulh  : truncateLSB(mulArray[i-1].product);
							Mulhsu: truncateLSB(mulArray[i-1].product);
							Mulhu : truncateLSB(mulArray[i-1].product);
						endcase);
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: muldivRes, rmv: True, clr: False};
					end else if(cToken.iType == Div) begin
						muldivRes = (case(cToken.divFunc)
							Div   : divArray[i-1].quotient ;
							Divu  : divArray[i-1].quotient ;
							Rem   : divArray[i-1].remainder;
							Remu  : divArray[i-1].remainder;
						endcase);
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: muldivRes, rmv: True, clr: False};
					end else if (cToken.iType == J || cToken.iType == Jr) begin
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: cToken.res,  rmv: False, clr: True};
						stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                  dry     : False,
						                                                  kill    : False,
						                                                  redirect: True,
						                                                  epoch   : commitEpoch[cToken.feID][0]+1,
						                                                  nextPc  : cToken.addr };
					end else if(cToken.iType == Br && cToken.brTaken) begin
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: '0, res: '0, rmv: False, clr: True};
						stEpoch    [cToken.feID] = tagged Valid (commitEpoch[cToken.feID][0]+1);
						stRedirect [cToken.feID] = tagged Valid Redirect{ lock    : False,
						                                                  dry     : False,
						                                                  kill    : False,
						                                                  redirect: True,
						                                                  epoch   : commitEpoch[cToken.feID][0]+1,
						                                                  nextPc  : cToken.addr };
					end else if(isValid(cToken.dst))
						rfWriteBack[cToken.feID] = tagged Valid RFwb{dst: fromMaybe('0, cToken.dst), res: cToken.res, rmv: True, clr: False};

					numWB = numWB+1;

					`ifdef DEBUG_CMR
					commitReportQ.port[i].enq(generateCMR(numCycles, mapID[cToken.feID], ?, cToken, ?, muldivRes));
					`endif

					`ifdef DEBUG_CYC
					commit_valid[i] = True;
					`endif

				end

			end

		end

		// To WB
		for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
			if(rfWriteBack[i] matches tagged Valid .lat) toWBrfWriteBack[0][i].enq(lat);
			if(stEpoch    [i] matches tagged Valid .lat) toWBstEpoch    [0][i].enq(lat);
			if(stRedirect [i] matches tagged Valid .lat) toWBstRedirect [0][i].enq(lat);
		end

		// Num  commit
		numCommit[1] <= numCommit[1]+numWB;

		// Perf debug
		`ifdef DEBUG_CYC
		for(Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
			if(toCommit[i] matches tagged Valid .inst) begin
				deb_cyc_com_notEmpty[i].wset(True           );
				deb_cyc_com_nextPC  [i].wset(inst.pc        );
				deb_cyc_com_feID    [i].wset(inst.feID      );
				deb_cyc_com_valid   [i].wset(commit_valid[i]);
				deb_cyc_com_miss    [i].wset(commit_miss [i]);
				deb_cyc_com_rawInst [i].wset(inst.rawInst   );
			end
		end
		`endif

	endrule


	//////////// OLD COMMIT ////////////

	`ifdef DEBUG_CYC
	RWire#(Bool   ) deb_cyc_lat_notEmpty <- mkRWire;
	RWire#(FrontID) deb_cyc_lat_feID     <- mkRWire;
	RWire#(Data   ) deb_cyc_lat_rawInst  <- mkRWire;
	`endif

	rule do_old_commit;

		L1DResp#(FrontID) resp    = l1D.getoldres(); l1D.deqoldres();
		OldToken          cToken  = miata[resp.transId].first; miata[resp.transId].deq();
		FrontID           feID    = resp.transId;
		Data              loadRes = 'hdeadbeef;

		if(cToken.iType == Ld) begin

			loadRes = resp.data;
			toWBrfWriteBack[1][feID].enq(RFwb{dst: cToken.dst, res: loadRes, rmv: False, clr: False});
			toWBstRedirect [1][feID].enq(Redirect{ lock    : False,
			                                       dry     : False,
			                                       kill    : False,
			                                       redirect: False,
			                                       epoch   : ?    ,
			                                       nextPc  : ?    });

		end else if(cToken.iType == St) begin

			toWBstRedirect [1][feID].enq(Redirect{ lock    : False,
			                                       dry     : False,
			                                       kill    : False,
			                                       redirect: False,
			                                       epoch   : ?    ,
			                                       nextPc  : ?    });

		end else if(cToken.iType == Join) begin

			loadRes = resp.data;
			if(resp.data == '0) begin
				toWBstEpoch    [1][feID].enq(commitEpoch[feID][0]+1);
				toWBstRedirect [1][feID].enq(Redirect{ lock    : False                 ,
				                                       dry     : False                 ,
				                                       kill    : True                  ,
				                                       redirect: False                 ,
				                                       epoch   : commitEpoch[feID][0]+1,
				                                       nextPc  : ?                     });
			end else begin
				toWBstRedirect [1][feID].enq(Redirect{ lock    : False,
				                                       dry     : False,
				                                       kill    : False,
				                                       redirect: False,
				                                       epoch   : ?    ,
				                                       nextPc  : ?    });
			end

		end

		numCommit[0] <= numCommit[0]+1;

		`ifdef DEBUG_CMR
		commitReportQ.port[0].enq(generateOldCMR(numCycles, mapID[feID], cToken, loadRes));
		`endif

		// Perf debug
		`ifdef DEBUG_CYC
			deb_cyc_lat_notEmpty.wset(True          );
			deb_cyc_lat_feID    .wset(cToken.feID   );
			deb_cyc_lat_rawInst .wset(cToken.rawInst);
		`endif

	endrule

	//////////// WRBACK ////////////
	for(Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin

		rule do_wb;

			     if(toWBrfWriteBack[0][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[0][i].first); toWBrfWriteBack[0][i].deq(); end
			else if(toWBrfWriteBack[1][i].notEmpty) begin rfWriteBackQ[i].enq(toWBrfWriteBack[1][i].first); toWBrfWriteBack[1][i].deq(); end

			     if(toWBstEpoch    [0][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [0][i].first ; toWBstEpoch    [0][i].deq(); end
			else if(toWBstEpoch    [1][i].notEmpty) begin commitEpoch [i][0] <= toWBstEpoch  [1][i].first ; toWBstEpoch    [1][i].deq(); end

			     if(toWBstRedirect [0][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [0][i].first); toWBstRedirect [0][i].deq(); end
			else if(toWBstRedirect [1][i].notEmpty) begin redirectQ   [i].enq(toWBstRedirect [1][i].first); toWBstRedirect [1][i].deq(); end

		endrule

	end

	//////////// INTERFACE ////////////

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

	`ifdef DEBUG_CYC
 	Vector#(BackWidth, DEB_CYC_exe) deb_cyc_exeIfc = newVector;
 	for(Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
		deb_cyc_exeIfc[i] =
			(interface DEB_CYC_exe;
				method Bool    notEmpty; if (deb_cyc_exe_notEmpty[i].wget matches tagged Valid .d) return d; else return False; endmethod
				method Addr    nextPC  ; if (deb_cyc_exe_nextPC  [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method FrontID feID    ; if (deb_cyc_exe_feID    [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
			endinterface);
	end

 	Vector#(BackWidth, DEB_CYC_mem) deb_cyc_memIfc = newVector;
 	for(Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
		deb_cyc_memIfc[i] =
			(interface DEB_CYC_mem;
				method Bool    notEmpty; if (deb_cyc_mem_notEmpty[i].wget matches tagged Valid .d) return d; else return False; endmethod
				method Addr    nextPC  ; if (deb_cyc_mem_nextPC  [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method FrontID feID    ; if (deb_cyc_mem_feID    [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
			endinterface);
	end

 	Vector#(BackWidth, DEB_CYC_com) deb_cyc_comIfc = newVector;
 	for(Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
		deb_cyc_comIfc[i] =
			(interface DEB_CYC_com;
				method Bool    notEmpty; if (deb_cyc_com_notEmpty[i].wget matches tagged Valid .d) return d; else return False; endmethod
				method Addr    nextPC  ; if (deb_cyc_com_nextPC  [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method FrontID feID    ; if (deb_cyc_com_feID    [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method Bool    valid   ; if (deb_cyc_com_valid   [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method Bool    miss    ; if (deb_cyc_com_miss    [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
				method Data    rawInst ; if (deb_cyc_com_rawInst [i].wget matches tagged Valid .d) return d; else return ?    ; endmethod
			endinterface);
	end

 	DEB_CYC_lat deb_cyc_latIfc;
	deb_cyc_latIfc =
		(interface DEB_CYC_lat;
			method Bool    notEmpty; if (deb_cyc_lat_notEmpty.wget matches tagged Valid .d) return d; else return False; endmethod
			method FrontID feID    ; if (deb_cyc_lat_feID    .wget matches tagged Valid .d) return d; else return ?    ; endmethod
			method Data    rawInst ; if (deb_cyc_lat_rawInst .wget matches tagged Valid .d) return d; else return ?    ; endmethod
		endinterface);
	`endif

	// DMEM
	interface mem = l1D.mem;

	method Action enq(Vector#(BackWidth, Maybe#(ExecToken)) inst);

		Vector#(BackWidth, Maybe#(MemToken) ) toMem  = replicate(tagged Invalid);

		let toExec = inst;

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

			if (eToken.iType == Ld) begin
				l1D.req(L1DReq{ op     : Ld           ,
				                ldFunc : eToken.ldFunc,
				                stFunc : eToken.stFunc,
				                addr   : exec.add     ,
				                data   : exec.res     ,
				                transId: eToken.feID  });
			end else if (eToken.iType == St) begin
				l1D.req(L1DReq{ op     : St           ,
				                ldFunc : eToken.ldFunc,
				                stFunc : eToken.stFunc,
				                addr   : exec.add     ,
				                data   : exec.res     ,
				                transId: eToken.feID  });
			end else if(eToken.iType == Join) begin
				l1D.req(L1DReq{ op     : Join         ,
				                ldFunc : eToken.ldFunc,
				                stFunc : eToken.stFunc,
				                addr   : exec.add     ,
				                data   : exec.res     ,
				                transId: eToken.feID  });
			end

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
		for (Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
			if(toExec[i] matches tagged Valid .inst) begin
				deb_cyc_exe_notEmpty[i].wset(True     );
				deb_cyc_exe_nextPC  [i].wset(inst.pc  );
				deb_cyc_exe_feID    [i].wset(inst.feID);
			end
		end
		`endif

	endmethod

	// To upstream
	interface deqRFwriteBack = deqRFwriteBackIfc;
	interface deqRedirect    = deqRedirectIfc;

	// To NTTX
	method ActionValue#(NTTXreq) getFork();
		eforkQ.deq(); return eforkQ.first();
	endmethod

	// To sched
	method PerfCnt getNumCommit();
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

	`ifdef DEBUG_CMR
	method ActionValue#(CommitReport) getCMR();
		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;
	endmethod
	`endif

	`ifdef MMIO
	method ActionValue#(StatReq) getMSG(); mmioMSGQ.deq(); return mmioMSGQ.first(); endmethod
	method ActionValue#(StatReq) getHEX(); mmioHEXQ.deq(); return mmioHEXQ.first(); endmethod
	method ActionValue#(StatReq) getMSR(); mmioMSRQ.deq(); return mmioMSRQ.first(); endmethod
	`endif

	`ifdef DEBUG_CYC
	interface cycExe = deb_cyc_exeIfc;
	interface cycMem = deb_cyc_memIfc;
	interface cycCom = deb_cyc_comIfc;
	interface cycLat = deb_cyc_latIfc;

	method PerfCnt cycNumCommit();
		return numCommit[2];
	endmethod

	`endif

	`ifdef DEBUG_STATS
	method L1DStat getL1DStat() = l1D.getStat();
	`endif

endmodule
