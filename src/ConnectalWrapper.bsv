import Ifc::*;
import HostInterface::*;
import WideMemPRiscy::*;
import WideMemPRiscyIfc::*;
import Types::*;
import WideMemTypes::*;
import WMRocketTileIfc::*;
import WMRocketTile::*;
import RocketConfig::*;
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
import WideMemTester::*;
import FIFOF::*;
import FIFO::*;
import Config::*;
import Vector::*;
import FShow::*;

typedef Bit#(TLog#(CacheLineWords)) CacheOffset;

`ifdef PRISCY
	typedef Tuple2#(Bit#(TLog#(2)),Config::FrontID) MemTag;
`elsif ROCKET
	typedef Bit#(3) MemTag;
`else
	typedef Bit#(8) MemTag;
`endif

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

    //////////// Core ////////////

	`ifdef PRISCY
		WideMemPRiscy wm_priscy_i <- mkWideMemPRiscy();
	`elsif ROCKET
		WMRocketTileIfc wm_rocket_i <- mkWMRocketTile();
	`endif

    //////////// Memory hiearchy ////////////

	WideMemDDR4#(SimDDRLatency, VCUDDRLatency, MemTag) mainDDR4 <- mkWideMemDDR4(host);

	`ifdef PRISCY
		`ifdef L2SC
			WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, MemTag) mainL2SC <- mkWideMemCache();
			mkConnection(mainL2SC.mem, mainDDR4.portA  );
			mkConnection(wm_priscy_i.wm_client, mainL2SC.portA);
		`else 
			mkConnection(wm_priscy_i.wm_client, mainDDR4.portA);
		`endif
	`elsif ROCKET
		`ifdef L2SC
			WideMemCache#(L2CacheRows, L2CacheColumns, L2CacheHashBlocks, MemTag) mainL2SC <- mkWideMemCache();
			mkConnection(mainL2SC.mem, mainDDR4.portA  );
			mkConnection(wm_rocket_i.wm_client, mainL2SC.portA);
		`else 
			mkConnection(wm_rocket_i.wm_client, mainDDR4.portA);
		`endif
	`endif

	`ifdef MEMTEST
		FIFOF#(TestRes) mainTSTQ <- mkSizedBRAMFIFOF(valueOf(MTHQ_LEN));
		WideMemTester#(MemTag) memTest  <- mkWideMemTester();
		mkConnection(memTest.mem, mainDDR4.portB);
	`endif

	//////////// RELAY REPORTS ROCKET ////////////

	`ifdef PRISCY

		`ifdef DEBUG_CMR

			rule relayCMR;
				CommitReport cmr <- wm_priscy_i.getCMR();
				Bit#(8) iType = zeroExtend(pack(cmr.iType));
				Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
				ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
			endrule

		`endif

		`ifdef MMIO

			Reg#(CoreStat) coreStatPending <- mkReg(?);
			Reg#(StatReq ) coreStatReq <- mkReg(?);
			Reg#(Maybe#(Bit#(TAdd#(FrontWidth,1)))) coreStatIndex <- mkReg(tagged Invalid);

			rule relayMSG if(Config::msg_ext_DEBUG);
				StatReq latest <- wm_priscy_i.getMSG();
				ind.reportMSG(latest.verifID, latest.cycle, latest.commit, latest.data);
			endrule
			
			rule relayHEX if(Config::hex_ext_DEBUG);
				StatReq latest <- wm_priscy_i.getHEX();
				ind.reportHEX(latest.verifID, latest.cycle, latest.commit, latest.data);
			endrule
			
			rule relayMSR if(Config::msr_ext_DEBUG);
				StatReq latest  <- wm_priscy_i.getMSR();
				L1IStat l1IStat  = wm_priscy_i.getL1IStat();
				L1DStat l1DStat  = wm_priscy_i.getL1DStat();
				`ifdef L2SC
				WMCStat l2SStat  = mainL2SC.getStat();
				`else
				WMCStat l2SStat  = unpack('0);
				`endif
				ind.reportMSR(latest.verifID,
				              latest.cycle  , latest.commit, latest.data  ,
				              l1IStat.hRD   ,
				              l1IStat.mRD   ,
				              l1DStat.hLd   , l1DStat.hSt  , l1DStat.hJoin,
				              l1DStat.mLd   , l1DStat.mSt  , l1DStat.mJoin,
				              l2SStat.hRD   , l2SStat.hWR  , l2SStat.tWB  ,
				              l2SStat.mRD   , l2SStat.mWR                   );
			endrule


			rule relayCTR if(Config::msr_ext_DEBUG &&& coreStatIndex matches tagged Invalid);
				StatReq latest  <- wm_priscy_i.getCTR();
				coreStatPending <= wm_priscy_i.getCoreStat;
				coreStatReq     <= latest;
				coreStatIndex   <= tagged Valid 0;
			endrule

			rule relayCTRPartial if(Config::msr_ext_DEBUG &&& coreStatIndex matches tagged Valid .idx);
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

	`endif

	//////////// RELAY REPORTS ROCKET ////////////

	`ifdef ROCKET
	
		`ifdef DEBUG_RCKT_CMR
			rule relayCMR;
				CommitReport cmr <- wm_rocket_i.getCMR();
				Bit#(8) iType = zeroExtend(pack(cmr.iType));
				Bit#(8) wbDst = zeroExtend(pack(cmr.wbDst));
				ind.reportCMR(cmr.cycle, cmr.verifID, cmr.pc, cmr.rawInst, iType, wbDst, cmr.wbRes, cmr.addr);
			endrule
		`endif
	
		`ifdef RCKT_MMIO
	
			rule relayMSG;
				StatReq latest <- wm_rocket_i.getMSG();
				ind.reportMSG(latest.verifID, latest.cycle, latest.commit, latest.data);
			endrule
	
			rule relayHEX;
				StatReq latest <- wm_rocket_i.getHEX();
				ind.reportHEX(latest.verifID, latest.cycle, latest.commit, latest.data);
			endrule
	
			rule relayMSR;
				StatReq latest  <- wm_rocket_i.getMSR();
				L1IStat l1IStat = L1IStat{hRD:'0,mRD:'0}; // TODO: NO L1I stats for Rocket
				L1DStat l1DStat = L1DStat{hLd:'0,hSt:'0,hJoin:'0,mLd:'0,mSt:'0,mJoin:'0}; // TODO: No L1D stats for Rocket
				`ifdef L2SC
				WMCStat l2SStat  = mainL2SC.getStat();
				`else
				WMCStat l2SStat  = unpack('0);
				`endif
				ind.reportMSR(latest.verifID,
				              latest.cycle  , latest.commit, latest.data  ,
				              l1IStat.hRD   ,
				              l1IStat.mRD   ,
				              l1DStat.hLd   , l1DStat.hSt  , l1DStat.hJoin,
				              l1DStat.mLd   , l1DStat.mSt  , l1DStat.mJoin,
				              l2SStat.hRD   , l2SStat.hWR  , l2SStat.tWB  ,
				              l2SStat.mRD   , l2SStat.mWR                   );
			endrule
	
			rule relayCTR; // NO proper CTR for Rocket
				StatReq latest  <- wm_rocket_i.getCTR();
				ind.reportCTR(latest.verifID, '0, latest.cycle, latest.commit, latest.data, '0, '0, '0, '0, '0, '0, '0, '0, '0, '0, '0, '0);
			endrule
	
		`endif

	`endif

	//////////// RELAY REPORTS MEMTEST ////////////

	`ifdef MEMTEST

		rule getTST;
			memTest.deq();
			if(memTest.first.testtyp == TTEND)
				tstInit <= True;
			else
				mainTSTQ.enq(memTest.first());
		endrule

		rule relayTST;
			TestRes latest = mainTSTQ.first(); mainTSTQ.deq();
			Bit#(8)  testtyp = zeroExtend(pack(latest.testtyp));
			Bit#(32) teststr = zeroExtend(pack(latest.teststr));
			ind.testMem(latest.testlen, testtyp, teststr,latest.latency, latest.delayTX, latest.delayRX);
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

			`ifdef PRISCY
				wm_priscy_i.toMTQ.enq(ContToken{ verifID: '0           ,
				                                 pc     : startpc      ,
				                                 rfL    : replicate('0),
				                                 rfH    : replicate('0)});
			`endif

			`ifdef ROCKET
				wm_rocket_i.startBridge();
			`endif

		endmethod

	endinterface

	interface Top_Pins pins = mainDDR4.pins;

endmodule