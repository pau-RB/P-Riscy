import Ifc::*;
import HostInterface::*;
import Core::*;
import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import Connectable::*;
import GetPut::*;
import ProcTypes::*;
import CMRTypes::*;
import Memory::*;
import DDR4Common::*;
import DDR4Controller::*;
import WideMemDDR4::*;
import WideMemBRAM::*;
import WideMemCache::*;
import WideMemSplit::*;
import FIFOF::*;
import FIFO::*;
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

	Reg#(Bool) memInit <- mkReg(False);
	Reg#(Bool) cpuInit <- mkReg(False);

	WideMemDDR4#(RAMLatency, Tuple2#(Bit#(TLog#(2)),FrontID))                                      mainDDR4 <- mkWideMemDDR4(host);
	WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, Tuple2#(Bit#(TLog#(2)),FrontID)) mainL2SC <- mkWideMemCache();
	WideMemSplit#(2,TMul#(2,FrontWidth), FrontID)                                                  mainL2SB <- mkSplitWideMem();

	Core core <- mkCore7SS();

	mkConnection(mainL2SC.mem, mainDDR4.portA  );
	mkConnection(mainL2SB.mem, mainL2SC.portA  );
	mkConnection(core.instMem, mainL2SB.port[0]);
	mkConnection(core.dataMem, mainL2SB.port[1]);

	FIFOF#(ContToken) mainTokenQ <- mkSizedBRAMFIFOF(valueOf(MTQ_LEN));

	FIFOF#(CommitReport) mainCMRQ <- mkSizedBRAMFIFOF(cmr_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(Message)      mainMSGQ <- mkSizedBRAMFIFOF(msg_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(Message)      mainHEXQ <- mkSizedBRAMFIFOF(hex_ext_DEBUG?valueOf(MTHQ_LEN):4);
	FIFOF#(MemStat)      mainMSRQ <- mkSizedBRAMFIFOF(mem_ext_DEBUG?valueOf(MTHQ_LEN):4);

	//////////// MTQ ////////////

	rule do_core_to_MTQ;
		mainTokenQ.enq(core.toMTQ.first()); core.toMTQ.deq();
	endrule

	rule do_MTQ_to_core;
		core.toMTQ.enq(mainTokenQ.first()); mainTokenQ.deq();
	endrule

	//////////// RELAY REPORTS ////////////

	rule getCMR if(cmr_ext_DEBUG);
		let latest <- core.getCMR();
		mainCMRQ.enq(latest);
	endrule

	rule getMSG if(msg_ext_DEBUG);
		let latest <- core.getMSG();
		mainMSGQ.enq(latest);
	endrule

	rule getHEX if(hex_ext_DEBUG);
		let latest <- core.getHEX();
		mainHEXQ.enq(latest);
	endrule

	rule getMSR if(mem_ext_DEBUG);
		let latest <- core.getMSR();
		latest.l2s = mainL2SC.getStat();
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
		              msr.l2s.hWR,        msr.l2s.mWR,
		              msr.l2s.hRD,        msr.l2s.mRD,
		              msr.l2s.tWB );
	endrule

	//////////// INTERFACE ////////////

	Reg#(CacheLine) lineSend <- mkReg(replicate('0));

	interface FromHost connectProc;

		method Action setMem (Bit#(32) addr, Bit#(32) word);

			CacheLine line = lineSend;
			line[offsetOf(addr)] = word;
			lineSend <= line;

			if(addr == max_ADDR) begin
				memInit <= True;
			end else if(offsetOf(addr) == '1) begin
				mainDDR4.portA.request.put(WideMemReq { tag  : ?,
				                                        write: True,
				                                        num  : lineNumOf(addr),
				                                        line : line });
			end

		endmethod

		method Action startPC(Bit#(32) startpc) if(memInit && !cpuInit);

			cpuInit <= True;

			mainTokenQ.enq(ContToken{
			                  verifID: '0,
			                  pc     : startpc,
			                  rfL    : replicate('0),
			                  rfH    : replicate('0)  });

		endmethod

	endinterface

	interface Top_Pins pins = mainDDR4.pins;

endmodule