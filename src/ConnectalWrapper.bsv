import Ifc::*;
import HostInterface::*;
import Core::*;
import Types::*;
import WideMemTypes::*;
import WMRocketTileIfc::*;
import WMRocketTile::*;
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
import FShow::*;

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

	//WideMemDDR4#(SimDDRLatency, VCUDDRLatency, Tuple2#(Bit#(TLog#(2)),FrontID))                    mainDDR4 <- mkWideMemDDR4(host);
	WideMemDDR4#(SimDDRLatency, VCUDDRLatency, Bit#(3)) mainDDR4 <- mkWideMemDDR4(host);
	`ifdef L2SC
	//WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, Tuple2#(Bit#(TLog#(2)),FrontID)) mainL2SC <- mkWideMemCache();
	WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, Bit#(3)) mainL2SC <- mkWideMemCache();
	`endif
	//WideMemSplit#(2,TMul#(2,FrontWidth), FrontID)                                                  mainL2SB <- mkSplitWideMem();

	`ifdef MEMTEST
	//WideMemTester#(Tuple2#(Bit#(TLog#(2)),FrontID))                                                memTest  <- mkWideMemTester();
	WideMemTester#(Bit#(3))                                                memTest  <- mkWideMemTester();
	`endif

	// Core core <- mkCore7SS();


	WMRocketTileIfc wm_rocket_tile <- mkWMRocketTile();


	`ifdef L2SC
	mkConnection(mainL2SC.mem, mainDDR4.portA  );
	//mkConnection(mainL2SB.mem, mainL2SC.portA  );
	mkConnection(wm_rocket_tile.wm_client, mainL2SC.portA);
	`else
	//mkConnection(mainL2SB.mem, mainDDR4.portA  );
	mkConnection(wm_rocket_tile.wm_client, mainDDR4.portA);
	`endif

	//mkConnection(core.instMem, mainL2SB.port[0]);
	//mkConnection(core.dataMem, mainL2SB.port[1]);

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

	//////////// MTQ ////////////

	//rule do_core_to_MTQ;
	//	mainTokenQ.enq(core.toMTQ.first()); core.toMTQ.deq();
	//endrule

	//rule do_MTQ_to_core;
	//	core.toMTQ.enq(mainTokenQ.first()); mainTokenQ.deq();
	//endrule

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

	//`ifdef DEBUG_CMR
	//rule getCMR;
	//	let latest <- core.getCMR();
	//	mainCMRQ.enq(latest);
	//endrule
	//`endif

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

	`ifdef DEBUG_RCKT_CMR
	rule relayCMR;
		CommitReport cmr <- wm_rocket_tile.getCMR();
		Bit#(8) iType = zeroExtend(pack(cmr.iType));
		Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
		ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
	endrule
	`endif

	`ifdef MMIO
	//rule relayMSG if(msg_ext_DEBUG);
	//	StatReq latest <- core.getMSG();
	//	ind.reportMSG(latest.verifID, latest.cycle, latest.commit, latest.data);
	//endrule
	//rule relayHEX if(hex_ext_DEBUG);
	//	StatReq latest <- core.getHEX();
	//	ind.reportHEX(latest.verifID, latest.cycle, latest.commit, latest.data);
	//endrule
	//rule relayMSR if(msr_ext_DEBUG);
	//	StatReq latest  <- core.getMSR();
	//	L1IStat l1IStat  = core.getL1IStat();
	//	L1DStat l1DStat  = core.getL1DStat();
	//	`ifdef L2SC
	//	WMCStat l2SStat  = mainL2SC.getStat();
	//	`else
	//	WMCStat l2SStat  = unpack('0);
	//	`endif
	//	ind.reportMSR(latest.verifID,
	//	              latest.cycle  , latest.commit, latest.data  ,
	//	              l1IStat.hRD   ,
	//	              l1IStat.mRD   ,
	//	              l1DStat.hLd   , l1DStat.hSt  , l1DStat.hJoin,
	//	              l1DStat.mLd   , l1DStat.mSt  , l1DStat.mJoin,
	//	              l2SStat.hRD   , l2SStat.hWR  , l2SStat.tWB  ,
	//	              l2SStat.mRD   , l2SStat.mWR                   );
	//endrule

	Reg#(CoreStat) coreStatPending <- mkReg(?);
	Reg#(StatReq ) coreStatReq <- mkReg(?);
	Reg#(Maybe#(Bit#(TAdd#(FrontWidth,1)))) coreStatIndex <- mkReg(tagged Invalid);
	//rule relayCTR if(msr_ext_DEBUG &&& coreStatIndex matches tagged Invalid);
	//	StatReq latest  <- core.getCTR();
	//	coreStatPending <= core.getCoreStat;
	//	coreStatReq     <= latest;
	//	coreStatIndex   <= tagged Valid 0;
	//endrule
	rule relayCTRPartial if(msr_ext_DEBUG &&& coreStatIndex matches tagged Valid .idx);
		let latest = coreStatReq;
		ind.reportCTR(latest.verifID, zeroExtend(idx), latest.cycle, latest.commit, latest.data,
		              coreStatPending.frontStat.distFull   [idx],
		              coreStatPending.frontStat.distFetch  [idx],
		              coreStatPending.frontStat.distDecode [idx],
		              coreStatPending.frontStat.distWrong  [idx],
		              coreStatPending.frontStat.distRedir  [idx],
		              coreStatPending.frontStat.distLock   [idx],
		              coreStatPending.frontStat.distStall  [idx],
		              coreStatPending.arbiterStat.distWrong[idx],
		              coreStatPending.arbiterStat.distAri  [idx],
		              coreStatPending.arbiterStat.distMem  [idx],
		              coreStatPending.backStat.distWrong   [idx],
		              coreStatPending.backStat.distCommit  [idx]);
		if(idx == fromInteger(valueOf(FrontWidth)))
			coreStatIndex <= tagged Invalid;
		else
			coreStatIndex <= tagged Valid (idx+1);
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

			CacheLine data = lineSend;
			data[offsetOf(addr)] = word;
			lineSend <= data;

			if(addr == max_ADDR) begin
				memInit <= True;
			end else if(offsetOf(addr) == '1) begin
				mainDDR4.portA.request.put(WideMemReq { tag        : ?              ,
				                                        write      : True           ,
				                                        addr       : lineNumOf(addr),
				                                        data       : data           ,
				                                        byte_enable: '1             });

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

			wm_rocket_tile.startBridge();

		endmethod

	endinterface

	interface Top_Pins pins = mainDDR4.pins;

endmodule