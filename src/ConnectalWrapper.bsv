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
import WideMemTester::*;
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

	`ifdef MEMTEST
	Reg#(Bool) tstInit <- mkReg(False);
	`endif
	Reg#(Bool) memInit <- mkReg(False);
	Reg#(Bool) cpuInit <- mkReg(False);

	WideMemDDR4#(SimDDRLatency, VCUDDRLatency, Tuple2#(Bit#(TLog#(2)),FrontID))                    mainDDR4 <- mkWideMemDDR4(host);
	`ifdef L2SC
	WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, Tuple2#(Bit#(TLog#(2)),FrontID)) mainL2SC <- mkWideMemCache();
	`endif
	WideMemSplit#(2,TMul#(2,FrontWidth), FrontID)                                                  mainL2SB <- mkSplitWideMem();

	`ifdef MEMTEST
	WideMemTester#(Tuple2#(Bit#(TLog#(2)),FrontID))                                                memTest  <- mkWideMemTester();
	`endif

	Core core <- mkCore7SS();

	`ifdef L2SC
	mkConnection(mainL2SC.mem, mainDDR4.portA  );
	mkConnection(mainL2SB.mem, mainL2SC.portA  );
	`else
	mkConnection(mainL2SB.mem, mainDDR4.portA  );
	`endif

	mkConnection(core.instMem, mainL2SB.port[0]);
	mkConnection(core.dataMem, mainL2SB.port[1]);

	`ifdef MEMTEST
	mkConnection(memTest.mem, mainDDR4.portB);
	`endif

	FIFOF#(ContToken) mainTokenQ <- mkSizedBRAMFIFOF(valueOf(MTQ_LEN));

	`ifdef MEMTEST
	FIFOF#(TestRes)      mainTSTQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
	`endif
	`ifdef DEBUG_CMR
	FIFOF#(CommitReport) mainCMRQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
	`endif
	`ifdef MMIO
	FIFOF#(Message)      mainMSGQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
	FIFOF#(Message)      mainHEXQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
	FIFOF#(MemStat)      mainMSRQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
	`endif

	//////////// MTQ ////////////

	rule do_core_to_MTQ;
		mainTokenQ.enq(core.toMTQ.first()); core.toMTQ.deq();
	endrule

	rule do_MTQ_to_core;
		core.toMTQ.enq(mainTokenQ.first()); mainTokenQ.deq();
	endrule

	//////////// RELAY REPORTS ////////////

	`ifdef MEMTEST
	rule getTST;
		memTest.deq();
		if(memTest.first.testtyp == TTEND)
			tstInit <= True;
		else
			mainTSTQ.enq(memTest.first());
	endrule
	`endif

	`ifdef DEBUG_CMR
	rule getCMR;
		let latest <- core.getCMR();
		mainCMRQ.enq(latest);
	endrule
	`endif

	`ifdef MMIO
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
		`ifdef L2SC
		latest.l2s = mainL2SC.getStat();
		`else
		latest.l2s = unpack('0);
		`endif
		mainMSRQ.enq(latest);
	endrule
	`endif

	`ifdef MEMTEST
	rule relayTST;
		TestRes latest = mainTSTQ.first(); mainTSTQ.deq();
		Bit#(8)  testtyp = zeroExtend(pack(latest.testtyp));
		Bit#(32) teststr = zeroExtend(pack(latest.teststr));
		ind.testMem(latest.testlen, testtyp, teststr,latest.latency, latest.delayTX, latest.delayRX);
	endrule
	`endif

	`ifdef DEBUG_CMR
	rule relayCMR;
		CommitReport cmr = mainCMRQ.first(); mainCMRQ.deq();
		Bit#(8) iType = zeroExtend(pack(cmr.iType));
		Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
		ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
	endrule
	`endif

	`ifdef MMIO
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
	`endif

	//////////// INTERFACE ////////////

	Reg#(CacheLine) lineSend <- mkReg(replicate('0));

	interface FromHost connectProc;

		method Action tstMem (Bit#(64) testlen, Bit#(8) testtyp, Bit#(32) teststr);

			`ifdef MEMTEST
				memTest.enq(TestReq{testlen: testlen, testtyp: unpack(truncate(testtyp)), teststr: truncate(teststr)});
			`endif

		endmethod

		`ifdef MEMTEST
		method Action setMem (Bit#(32) addr, Bit#(32) word) if(tstInit);
		`else
		method Action setMem (Bit#(32) addr, Bit#(32) word);
		`endif

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

		`ifdef MEMTEST
		method Action startPC(Bit#(32) startpc) if(tstInit && memInit && !cpuInit);
		`else
		method Action startPC(Bit#(32) startpc) if(memInit && !cpuInit);
		`endif

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