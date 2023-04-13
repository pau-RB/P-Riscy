import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import GetPut::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Ehr::*;

typedef enum {
	RDLAT,
	MXLAT,
	RDTHP,
	WRTHP,
	MXTHP,
	TTEND
} TestType deriving(Bits, Eq, FShow);

typedef struct {
	PerfCnt      testlen; // Length of the test
	TestType     testtyp; // Type of the test
	CacheLineNum teststr; // Test stride
} TestReq deriving(Bits, FShow);

typedef struct {
	PerfCnt  testlen;     // Length of the test
	TestType testtyp;     // Type of the test
	CacheLineNum teststr; // Test stride
	PerfCnt  latency;     // Sum of latencies
	PerfCnt  delayTX;     // Send delay
	PerfCnt  delayRX;     // Recieve delay
} TestRes deriving(Bits, FShow);

interface WideMemTester#(type tagT);
	interface WideMemClient#(tagT) mem;
	method Action enq(TestReq r);
	method TestRes first();
	method Action deq();
endinterface

module mkWideMemTester(WideMemTester#(tagT) ifc) provisos(Bits#(tagT, t__));

	FIFOF#(TestReq) testreq <- mkFIFOF();
	FIFOF#(TestRes) testres <- mkFIFOF();

	FIFOF#(WideMemReq#(tagT)) memreq <- mkBypassFIFOF();
	FIFOF#(WideMemRes#(tagT)) memres <- mkBypassFIFOF();

	Reg#(Bool)         testbusy <- mkReg(False);
	Reg#(Bool)         testwait <- mkReg(False);

	Reg#(PerfCnt)      testlen <- mkReg( ?);
	Reg#(TestType)     testtyp <- mkReg( ?);
	Reg#(CacheLineNum) teststr <- mkReg( ?);

	Reg#(CacheLineNum) baseadd <- mkReg('0);
	Reg#(PerfCnt)      exptx   <- mkReg('0);
	Reg#(PerfCnt)      exprx   <- mkReg('0);
	Reg#(PerfCnt)      numtx   <- mkReg('0);
	Reg#(PerfCnt)      numrx   <- mkReg('0);

	Ehr#(2,PerfCnt)    timmer0 <- mkEhr('0);
	Ehr#(2,PerfCnt)    timmer1 <- mkEhr('0);

	Reg#(PerfCnt)      latency <- mkReg('0);
	Reg#(PerfCnt)      delayTX <- mkReg('0);
	Reg#(PerfCnt)      delayRX <- mkReg('0);

	rule do_start if(!testbusy);

		TestReq r = testreq.first; testreq.deq;

		if(r.testtyp == TTEND) begin
			testres.enq(TestRes{ testtyp: TTEND  ,
			                     testlen: ?      ,
			                     teststr: ?      ,
			                     latency: ?      ,
			                     delayTX: ?      ,
			                     delayRX: ?      });
		end else begin
			testbusy <= True;
			testwait <= False;

			testlen  <= r.testlen;
			teststr  <= r.teststr;
			testtyp  <= r.testtyp;

			baseadd  <= '0;

			case(r.testtyp)
				RDLAT: begin exptx <=   r.testlen; exprx <= r.testlen; end
				MXLAT: begin exptx <= 2*r.testlen; exprx <= r.testlen; end
				RDTHP: begin exptx <=   r.testlen; exprx <= r.testlen; end
				WRTHP: begin exptx <=   r.testlen; exprx <= r.testlen; end
				MXTHP: begin exptx <= 2*r.testlen; exprx <= r.testlen; end
			endcase

			numtx    <= '0;
			numrx    <= '0;

			latency  <= '0;
			delayTX  <= '0;
			delayRX  <= '0;
		end
	endrule

	rule do_send if(testbusy && !testwait && numtx != exptx);
		case(testtyp)
			RDLAT: begin
				memreq.enq(WideMemReq{ tag  : ?      ,
				                       write: False  ,
				                       num  : baseadd,
				                       line : ?      });
				testwait   <= True           ;
				baseadd    <= baseadd+teststr;
				numtx      <= numtx+1        ;
				timmer0[0] <= '0             ;
			end
			MXLAT: begin
				if(numtx[0] == 1'b0) begin
					memreq.enq(WideMemReq{ tag  : ?      ,
					                       write: True   ,
					                       num  : baseadd,
					                       line : ?      });
				end else begin
					memreq.enq(WideMemReq{ tag  : ?      ,
					                       write: False  ,
					                       num  : baseadd,
					                       line : ?      });
					testwait   <= True           ;
					baseadd    <= baseadd+teststr;
					timmer0[0] <= '0             ;
				end
				numtx <= numtx+1;
			end
			RDTHP: begin
				memreq.enq(WideMemReq{ tag  : ?      ,
				                       write: False  ,
				                       num  : baseadd,
				                       line : ?      });
				baseadd  <= baseadd+teststr;
				numtx    <= numtx+1        ;
				if(numtx == '0)
					timmer0[0] <= '0;
				if(numtx+1 == exptx)
					delayTX <= timmer0[0]+1;
			end
			WRTHP: begin
				memreq.enq(WideMemReq{ tag  : ?      ,
				                       write: True   ,
				                       num  : baseadd,
				                       line : ?      });
				baseadd  <= baseadd+teststr;
				numtx    <= numtx+1        ;
				if(numtx == '0)
					timmer0[0] <= '0;
				if(numtx+1 == exptx) begin
					delayTX <= timmer0[0]+1;
					numrx <= exprx;
				end
			end
			MXTHP: begin
				if(numtx[0] == 1'b0) begin
					memreq.enq(WideMemReq{ tag  : ?      ,
					                       write: True   ,
					                       num  : baseadd,
					                       line : ?      });
				end else begin
					memreq.enq(WideMemReq{ tag  : ?      ,
					                       write: False  ,
					                       num  : baseadd,
					                       line : ?      });
					baseadd  <= baseadd+teststr;
				end
				numtx <= numtx+1;
				if(numtx == '0)
					timmer0[0] <= '0;
				if(numtx+1 == exptx) begin
					delayTX <= timmer0[0]+1;
				end
			end
		endcase
	endrule

	rule do_recieve;
		memres.deq();
		case(testtyp)
			RDLAT: begin
				testwait <= False             ;
				numrx    <= numrx+1           ;
				latency  <= latency+timmer0[0];
			end
			MXLAT: begin
				testwait <= False             ;
				numrx    <= numrx+1           ;
				latency  <= latency+timmer0[0];
			end
			RDTHP: begin
				numrx <= numrx+1  ;
				if(numrx == '0)
					timmer1[0] <= '0;
				if(numrx+1 == exprx)
					delayRX <= timmer1[0]+1;
			end
			WRTHP: begin
				numrx <= numrx+1  ;
				if(numrx == '0)
					timmer1[0] <= '0;
				if(numrx+1 == exprx)
					delayRX <= timmer1[0]+1;
			end
			MXTHP: begin
				numrx <= numrx+1  ;
				if(numrx == '0)
					timmer1[0] <= '0;
				if(numrx+1 == exprx)
					delayRX <= timmer1[0]+1;
			end
		endcase
	endrule

	rule do_cycle;
		timmer0[1] <= timmer0[1]+1;
		timmer1[1] <= timmer1[1]+1;
	endrule

	rule do_end if(testbusy && numrx == exprx);
		testbusy <= False;
		testres.enq(TestRes{ testtyp: testtyp,
		                     testlen: testlen,
		                     teststr: teststr,
		                     latency: latency,
		                     delayTX: delayTX,
		                     delayRX: delayRX});

	endrule

	interface WideMemClient mem;
		interface request = (interface Get#(WideMemReq#(tagT));
			method ActionValue#(WideMemReq#(tagT)) get();
				memreq.deq();
				return memreq.first();
			endmethod
		endinterface);
		interface response = (interface Put#(WideMemRes#(tagT));
			method Action put(WideMemRes#(tagT) r);
				memres.enq(r);
			endmethod
		endinterface);
	endinterface

	method Action enq(TestReq r) = testreq.enq(r);
	method TestRes first() = testres.first();
	method Action deq() = testres.deq();

endmodule