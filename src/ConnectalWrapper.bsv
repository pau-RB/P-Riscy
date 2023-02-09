import Ifc::*;
import HostInterface::*;
import Core::*; 
import VerifMaster::*;
import Types::*;
import ProcTypes::*;
import CMRTypes::*;
import Memory::*;
import DDR4Common::*;
import DDR4Controller::*;
import WideMemDDR4::*;
import WideMemCache::*;
import WideMemSplit::*;
import WideMemDelay::*;
import FIFOF::*;
import BRAMFIFO::*;
import Config::*;
import Vector::*;

typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

function CacheOffset offsetOf(Addr addr);
	return truncate(addr >> 2);
endfunction

function CacheLineNum lineNumOf(Addr addr);
    CacheLineNum num = truncateLSB(addr);
    return num;
endfunction

interface ConnectalWrapper;
	interface FromHost connectProc;
	interface Top_Pins pins;
endinterface

module mkConnectalWrapper#(HostInterface host, ToHost ind)(ConnectalWrapper);

	WideMemDDR4                                                                        mainDDR4  <- mkWideMemDDR4(host);
	WideMemDelay#(TSub#(RAMLatency,2))                                                 mainMem   <- mkWideMemDelay(mainDDR4.portA);
	WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, TMul#(2,FrontWidth)) mainL2    <- mkWideMemCache(mainMem.delayed);
	WideMemSplit#(2,TMul#(2,FrontWidth))                                               mainSplit <- mkSplitWideMem(mainL2.cache);

	VerifMaster                          verif        <- mkVerifMaster();
	Core                                 dut          <- mkCore7SS(mainSplit.port[0], mainSplit.port[1], verif);

	Reg#(Bool)                           memInit      <- mkReg(False);
	FIFOF#(ContToken)                    mainTokenQ   <- mkSizedBRAMFIFOF(valueOf(MTQ_LEN));
	Reg#(Data)                           commitTarget <- mkReg(80);
	Reg#(FrontID)                        evictTarget  <- mkReg(0);

	FIFOF#(CommitReport)                 mainCMRQ     <- mkSizedBRAMFIFOF(cmr_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(Message)                      mainMSGQ     <- mkSizedBRAMFIFOF(msg_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(Message)                      mainHEXQ     <- mkSizedBRAMFIFOF(hex_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(MemStat)                      mainMSRQ     <- mkSizedBRAMFIFOF(mem_ext_DEBUG?valueOf(MTHQ_LEN):4);

	//////////// RELAY REPORTS ////////////

	rule getCMR if(cmr_ext_DEBUG);
		let latest <- dut.getCMR();
		mainCMRQ.enq(latest);
	endrule

	rule getMSG if(msg_ext_DEBUG);
		let latest <- dut.getMSG();
		mainMSGQ.enq(latest);
	endrule

	rule getHEX if(hex_ext_DEBUG);
		let latest <- dut.getHEX();
		mainHEXQ.enq(latest);
	endrule

	rule getMSR if(mem_ext_DEBUG);
		let latest <- dut.getMSR();
		latest.l2s = mainL2.getStat();
		mainMSRQ.enq(latest);
	endrule

	rule relayCMR if(cmr_ext_DEBUG);
		CommitReport cmr = mainCMRQ.first(); mainCMRQ.deq();
		Bit#(8) iType = zeroExtend(pack(cmr.iType));
		Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
		ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
	endrule

	rule relayMSG if(msg_ext_DEBUG);
		Message msg = mainMSGQ.first(); mainMSGQ.deq();
		ind.reportMSG(msg.verifID, msg.cycle, msg.commit, msg.data);
	endrule

	rule relayHEX if(hex_ext_DEBUG);
		Message msg = mainHEXQ.first(); mainHEXQ.deq();
		ind.reportHEX(msg.verifID, msg.cycle, msg.commit, msg.data);
	endrule

	rule relayMSR if(mem_ext_DEBUG);
		MemStat msr = mainMSRQ.first(); mainMSRQ.deq();
		ind.reportMSR(msr.verifID,
		              msr.cycle,          msr.commit,           msr.data,
		              msr.fetch.hit,      msr.fetch.miss,       msr.fetch.empty,
		              msr.arbiter.memOvb, msr.arbiter.arithOvb, msr.arbiter.empty,
		              msr.lsu.hLd,        msr.lsu.hSt,          msr.lsu.hJoin,
		              msr.lsu.mLd,        msr.lsu.mSt,          msr.lsu.mJoin,
		              msr.lsu.dLd,        msr.lsu.dSt,          msr.lsu.dJoin,
		              msr.l2s.tWR,        msr.l2s.tWB,          msr.l2s.hRD,       msr.l2s.mRD);
	endrule

	//////////// HANDLE THREADS ////////////

	rule doEvict if(roundRobin && dut.getNumCommit() == commitTarget);

		if(mainTokenQ.notEmpty) begin
		   dut.evict(evictTarget);
		   evictTarget  <=  (evictTarget == lastFrontID) ? '0 : evictTarget+1;
		end

		commitTarget <= commitTarget+fromInteger(valueOf(RR_INT));

	endrule

	rule getContToken;

		let t <- dut.getContToken();
		mainTokenQ.enq(t);

	endrule

	rule putContToken;

		FrontID hart = 0;

		if(valueOf(FrontWidth) != 1) begin
			for (Integer i = 0; i < valueOf(FrontWidth); i=i+1) begin
				if(!dut.available(hart)) begin
					hart = (hart == lastFrontID) ? '0 : hart+1;
				end
			end
		end

		let t = mainTokenQ.first(); mainTokenQ.deq();
		dut.start(hart,t);

	endrule

	//////////// INTERFACE ////////////

	Reg#(CacheLine) lineSend <- mkReg(replicate('0));

	interface FromHost connectProc;

		method Action setMem (Bit#(32) addr, Bit#(32) word);

			CacheLine line = lineSend;
			line[offsetOf(addr)] = word;

			if(offsetOf(addr) == '1) begin
				mainMem.direct.req(WideMemReq { write: True,
				                                num  : lineNumOf(addr),
				                                line : line });
			end

			lineSend <= line;

			if(addr == max_ADDR) begin
				memInit <= True;
			end

		endmethod

		method Action startPC(Bit#(32) startpc) if(memInit);

			VerifID verifID <- verif.newVerifID();

			mainTokenQ.enq(ContToken{
			                  verifID: verifID,
			                  pc     : startpc,
			                  rfL    : replicate('0),
			                  rfH    : replicate('0)  });

		endmethod

	endinterface

	interface Top_Pins pins = mainDDR4.pins;

endmodule
