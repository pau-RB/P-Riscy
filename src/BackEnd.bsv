import FShow::*;
import VerifMaster::*;
import Config::*;

// types
import Types::*;
import ProcTypes::*;
import LSUTypes::*;
import CMRTypes::*;

// include
import Fifo::*;
import MFifo::*;
import Vector::*;
import Ehr::*;

// back
import Scoreboard::*;
import RFile::*;
import Execution::*;
import NTTX::*;

interface Writeback;

	// To upstream
	method ActionValue#(Redirect)     getRedirect();
	method ActionValue#(void)         getBackendDry();

endinterface

interface BackEnd;

	// Execute
	method Action execute(Vector#(BackWidth, Maybe#(ExecToken)) inst);

	// To upstream
	interface Vector#(FrontWidth, Writeback) hart;

	// CMR
	method ActionValue#(CommitReport) getCMR();
	method ActionValue#(Message)      getMSG();
	method ActionValue#(MemStat)      getMSR();

	// Performance Debug
	method Vector#(BackWidth,Maybe#(ExecToken)) get_exec_inst  ;
	method Vector#(BackWidth,Maybe#(MemToken) ) get_mem_inst   ;
	method Vector#(BackWidth,Maybe#(WBToken)  ) get_wb_inst    ;
	method Vector#(BackWidth,Bool             ) get_wb_valid   ;
	method Vector#(BackWidth,Bool             ) get_wb_miss    ;

	method Maybe#(WBToken)                      get_old_wb_inst;

endinterface

module mkBackEnd (LSU#(WBToken)                       lsu        ,
	              VerifMaster                         verif      ,
	              NTTX                                nttx       ,
	              Vector#(FrontWidth, RFile)          regFile    ,
	              Vector#(FrontWidth, Scoreboard#(8)) scoreboard ,
	              Vector#(FrontWidth, Ehr#(2,Epoch))  wbEpoch    ,
	              Bool                                coreStarted,
	              Data                                numCycles  ,
	              BackEnd ifc);

	// Stages
	Fifo#(1,Vector#(BackWidth,Maybe#(ExecToken)))  executeQ        <- mkBypassFifo();
	Fifo#(1,Vector#(BackWidth,Maybe#(MemToken)))   memoryQ         <- mkStageFifo();
	Fifo#(1,Vector#(BackWidth,Maybe#(WBToken)))    commitQ         <- mkStageFifo();

	Vector#(FrontWidth, Ehr#(3, Maybe#(void    ))) toWBsbRemove    <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(RFwb    ))) toWBrfWriteBack <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(void    ))) toWBstDry       <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Epoch   ))) toWBstEpoch     <- replicateM(mkEhr(tagged Invalid));
	Vector#(FrontWidth, Ehr#(3, Maybe#(Redirect))) toWBstRedirect  <- replicateM(mkEhr(tagged Invalid));

	// Upstream
	Vector#(FrontWidth, Fifo#(1,Redirect))         redirectQ       <- replicateM(mkBypassFifo());
	Vector#(FrontWidth, Fifo#(1,void))             backendDryQ     <- replicateM(mkBypassFifo());

	// CMR
	MFifo#(THQ_LEN,BackWidth,CommitReport)         commitReportQ   <- mkPipelineMFifo();
	Fifo# (THQ_LEN,Message)                        messageReportQ  <- mkPipelineFifo();
	Fifo# (THQ_LEN,MemStat)                        memStatReportQ  <- mkPipelineFifo();

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

		// Instruction Execute
		for (Integer i = 0; i < valueOf(BackWidth); i=i+1) begin
			if(isValid(toExec[i])) begin
				let eToken = fromMaybe(?,toExec[i]);
				let execInst = exec(eToken.inst, eToken.arg1, eToken.arg2, eToken.pc, eToken.pc+4);
				let mToken   = MemToken{
								inst   : execInst,
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

		if(isValid(toMem[0])) begin

			let mToken = fromMaybe(?, toMem[0]);
			let wToken = WBToken{ inst   : mToken.inst,
			                      pc     : mToken.pc,
			                      feID   : mToken.feID,
			                      epoch  : mToken.epoch,
			                      rawInst: mToken.rawInst};
			toCommit[0] = tagged Valid wToken;

			// Send LSU req, if the instruction is valid
			Maybe#(MemOp) memOp = case (mToken.inst.iType)
				Ld  : tagged Valid Ld;
				St  : tagged Valid St;
				Join: tagged Valid Join;
				default: tagged Invalid;
			endcase;

			if (mToken.epoch == wbEpoch[mToken.feID][1] && isValid(memOp)) begin

	    		lsu.req(LSUReq{ op     : fromMaybe(?,memOp),
	    		                ldFunc : mToken.inst.ldFunc,
	    		                stFunc : mToken.inst.stFunc,
	    		                addr   : mToken.inst.addr,
	    		                data   : mToken.inst.data,
	    		                transId: wToken });

	    	end

	    end

	    for(Integer i = 1; i < valueOf(BackWidth); i=i+1) begin
	    	if(isValid(toMem[i])) begin

	    		let mToken = fromMaybe(?, toMem[i]);
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
		Vector#(FrontWidth, Maybe#(void    )) stDry        = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Epoch   )) stEpoch      = replicate(tagged Invalid);
		Vector#(FrontWidth, Maybe#(Redirect)) stRedirect   = replicate(tagged Invalid);

		// WB
		Vector#(BackWidth, Maybe#(WBToken))   toCommit     = commitQ.first(); commitQ.deq();
		Vector#(BackWidth,Bool            )   commit_valid = replicate(False);
		Vector#(BackWidth,Bool            )   commit_miss  = replicate(False);
		Data numWB = 0;

		// LSU Pipeline WB
		if(isValid(toCommit[0])) begin

			let wToken = fromMaybe(?, toCommit[0]);
			let feID   = wToken.feID;

			sbRemove[feID] = tagged Valid(?);

			if (wToken.epoch == wbEpoch[feID][0])  begin

				let commitInst = wToken.inst;

				if(commitInst.iType == Ghost) begin

					nttx.evict(feID, wToken.pc);
					stDry[feID] = tagged Valid(?);

				end else begin

					Data    loadRes      = '1;
					Bool    memValid     = True;
					VerifID childVerifID = '0;

					if(commitInst.iType == Ld) begin

						let resp <- lsu.resp();
						if(resp.valid) begin
							loadRes = resp.data;
		        	    	rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: loadRes};
						end else begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else if(commitInst.iType == St) begin

						let resp <- lsu.resp();
						if(!resp.valid) begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
								                                      kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else if(commitInst.iType == Fork || commitInst.iType == Forkr) begin

						childVerifID <- nttx.efork(feID, commitInst.addr);

					end else if(commitInst.iType == Join) begin

						let resp <- lsu.resp();
						if(resp.valid) begin
							loadRes = resp.data;
							if(resp.data == '0) begin
								stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
								stRedirect[feID] = tagged Valid Redirect{ lock    : False,
	    	    	                                                      kill    : True,
				                                                          redirect: False,
				                                                          epoch   : wbEpoch[feID][0]+1,
				                                                          nextPc  : ? };
							end
						end else begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : True,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : wToken.pc+4 };
							memValid = False;
						end

		        	end else begin

		        		if(isValid(commitInst.dst)) begin
							rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: commitInst.data};
						end

						if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
							stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
							stRedirect[feID] = tagged Valid Redirect{ lock    : False,
							                                          kill    : False,
							                                          redirect: True,
							                                          epoch   : wbEpoch[feID][0]+1,
							                                          nextPc  : commitInst.addr };
						end else if (commitInst.iType == Br) begin
							stRedirect[feID] = tagged Valid Redirect{ lock    : False,
							                                          kill    : False,
							                                          redirect: False,
							                                          epoch   : ?,
							                                          nextPc  : ?};
						end

					end

					if (memValid) begin
						numWB = numWB+1;
					end

					if (wb_ext_DEBUG == True && memValid) begin
						commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(feID), childVerifID, wToken, loadRes));
					end

					if (msg_ext_DEBUG == True) begin
						if(commitInst.iType == St && commitInst.addr == msg_ADDR) begin
							messageReportQ.enq(Message { verifID: verif.getVerifID(feID),
														 cycle:   numCycles,
														 commit:  numCommit[0],
														 data:    commitInst.data });
						end
					end

					if (mem_ext_DEBUG == True) begin
						if(commitInst.iType == St && commitInst.addr == lsu_ADDR) begin
							FetchStat fsr = ?; //frontEnd.getStat();
							LSUStat   lsr = lsu.getStat();
							MemStat   msr = MemStat{ verifID: verif.getVerifID(feID),
							                         cycle  : numCycles,
							                         commit : numCommit[0],
							                         data   : commitInst.data,
							                         fetch  : fsr,
							                         lsu    : lsr };
							memStatReportQ.enq(msr);
						end
					end

					if(perf_DEBUG == True) begin
						commit_valid[0] = True;
						commit_miss [0] = !memValid;
					end

				end

			end

		end

		// GP Pipeline WB
		for (Integer i = 1; i < valueOf(BackWidth); i=i+1) begin

			if(isValid(toCommit[i])) begin

				let wToken = fromMaybe(?, toCommit[i]);
				let feID   = wToken.feID;

				sbRemove[feID] = tagged Valid(?);

				if (wToken.epoch == wbEpoch[feID][0])  begin

					let commitInst = wToken.inst;

					if(isValid(commitInst.dst)) begin
						rfWriteBack[feID] = tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: commitInst.data};
					end

					if(commitInst.brTaken || commitInst.iType == J || commitInst.iType == Jr) begin
						stEpoch   [feID] = tagged Valid (wbEpoch[feID][0]+1);
						stRedirect[feID] = tagged Valid Redirect{ lock    : False,
						                                          kill    : False,
						                                          redirect: True,
						                                          epoch   : wbEpoch[feID][0]+1,
						                                          nextPc  : commitInst.addr };
					end else if (commitInst.iType == Br) begin
						stRedirect[feID] = tagged Valid Redirect{ lock    : False,
						                                          kill    : False,
						                                          redirect: False,
						                                          epoch   : ?,
						                                          nextPc  : ?};
					end

					numWB = numWB+1;

					if (wb_ext_DEBUG == True) begin
						commitReportQ.port[i].enq(generateCMR(numCycles, verif.getVerifID(feID), ?, wToken, ?));
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
			toWBstDry      [i][0] <= stDry      [i];
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
		ExecInst          commitInst = wToken.inst;
		FrontID           feID       = wToken.feID;
		Data              loadRes    = 'hdeadbeef;

		if(commitInst.iType == Ld) begin

			loadRes = resp.data;
    	    toWBrfWriteBack[feID][1] <= tagged Valid RFwb{dst: fromMaybe(?, commitInst.dst), res: loadRes};
    	    toWBstRedirect [feID][1] <= tagged Valid Redirect{ lock    : False,
    	    	                                               kill    : False,
			                                                   redirect: False,
			                                                   epoch   : ?,
			                                                   nextPc  : ? };

    	end else if(commitInst.iType == St) begin

    	    toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
    	    	                                    kill    : False,
			                                        redirect: False,
			                                        epoch   : ?,
			                                        nextPc  : ? };

    	end else if(commitInst.iType == Join) begin

    		loadRes = resp.data;
			if(resp.data == '0) begin
				toWBstEpoch   [feID][1] <= tagged Valid (wbEpoch[feID][0]+1);
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
    		                                            kill    : True,
			                                            redirect: False,
			                                            epoch   : wbEpoch[feID][0]+1,
			                                            nextPc  : ? };
			end else begin
				toWBstRedirect[feID][1] <= tagged Valid Redirect{ lock    : False,
					                                    kill    : False,
				                                        redirect: False,
				                                        epoch   : ?,
				                                        nextPc  : ? };
			end

    	end

    	numCommit[1] <= numCommit[1]+1;

		if (wb_ext_DEBUG == True) begin
			commitReportQ.port[0].enq(generateCMR(numCycles, verif.getVerifID(feID), ?, wToken, loadRes));
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

			if(isValid(toWBstDry[i][2])) begin
				backendDryQ[i].enq(?);
			end

			wbEpoch[i][0] <= fromMaybe(wbEpoch[i][0], toWBstEpoch[i][2]);

			if(isValid(toWBstRedirect[i][2])) begin
				redirectQ[i].enq(fromMaybe(?,toWBstRedirect[i][2]));
			end

			toWBsbRemove   [i][2] <= tagged Invalid;
			toWBrfWriteBack[i][2] <= tagged Invalid;
			toWBstDry      [i][2] <= tagged Invalid;
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

				method ActionValue#(void) getBackendDry();
					let latest = backendDryQ[i].first(); backendDryQ[i].deq();
					return latest;
				endmethod

			endinterface);
	end

	// Execute
	method Action execute(Vector#(BackWidth, Maybe#(ExecToken)) inst);
		executeQ.enq(inst);
	endmethod

	// To upstream
	interface hart = wbIfc;

	// CMR
	method ActionValue#(CommitReport) getCMR();
		let latest = commitReportQ.first(); commitReportQ.deq();
		return latest;
	endmethod

	method ActionValue#(Message) getMSG();
		let latest = messageReportQ.first(); messageReportQ.deq();
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

	method Maybe#(WBToken) get_old_wb_inst();
		return perf_old_wb_inst[1];
	endmethod

endmodule