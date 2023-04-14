import Types::*;
import WideMemTypes::*;
import ClientServer::*;
import BRAM::*;

import FIFO::*;
import Vector::*;
import DRAMController::*;
import Connectable::*;
import HostInterface::*;

import DDR4Controller::*;
import DDR4Common::*;

`ifdef SIMULATION
import DDR4Sim::*;
`else
import Clocks:: *;
import DefaultValue:: *;
`endif

import WideMemDelay::*;

import GetPut::*;
import ClientServerHelper::*;
import DRAMControllerTypes::*;

interface Top_Pins;
        `ifndef SIMULATION
        interface DDR4_Pins_Dual_VCU108 pins_ddr4;
        `endif
endinterface

interface WideMemDDR4#(numeric type simLatency, numeric type vcuLatency, type tagT);
	interface WideMemServer#(tagT) portA;
	interface WideMemServer#(tagT) portB;
	interface Top_Pins pins;
endinterface

module mkWideMemDDR4(HostInterface host, WideMemDDR4#(simLatency, vcuLatency, tagT) ifc) provisos(Add#(a__, 2, simLatency), Bits#(tagT, t__));

	FIFO#(WideMemReq#(tagT)) reqAQ <- mkFIFO();
	FIFO#(WideMemReq#(tagT)) reqBQ <- mkFIFO();
	FIFO#(tagT             ) tagQ  <- mkFIFO();
	FIFO#(Bool             ) porQ  <- mkFIFO();
	FIFO#(WideMemRes#(tagT)) resAQ <- mkFIFO();
	FIFO#(WideMemRes#(tagT)) resBQ <- mkFIFO();

	Vector#(2,FIFO#(DDRRequest )) ddr4_req <- replicateM(mkFIFO());
	Vector#(2,FIFO#(DDRResponse)) ddr4_res <- replicateM(mkFIFO());
	Vector#(2,DDR4Client) ddr_clients = zipWith(toClient, ddr4_req, ddr4_res);

	`ifdef SIMULATION

		Vector#(2, DDR4_User_VCU108) ddr4_ctrl_users <- replicateM(mkDDR4Simulator);
		zipWithM_(mkConnection, ddr_clients, ddr4_ctrl_users);

	`else

		Clock curr_clk <- exposeCurrentClock();
		Reset curr_rst_n <- exposeCurrentReset();

		// DDR4 C1
		let sys_clk1 = host.tsys_clk1_300mhz;
		let sys_rst1 <- mkAsyncResetFromCR(20, sys_clk1);

		DDR4_Controller_VCU108 ddr4_ctrl_0 <- mkDDR4Controller_VCU108(defaultValue, clocked_by sys_clk1, reset_by sys_rst1);

		Clock ddr4clk0 = ddr4_ctrl_0.user.clock;
		Reset ddr4rstn0 = ddr4_ctrl_0.user.reset_n;

		let ddr_cli_300mhz_0 <- mkDDR4ClientSync(ddr_clients[0], curr_clk, curr_rst_n, ddr4clk0, ddr4rstn0);
		mkConnection(ddr_cli_300mhz_0, ddr4_ctrl_0.user);

		// DDR4 C2
		let sys_clk2 = host.tsys_clk1_300mhz_buf;
		let sys_rst2 <- mkAsyncResetFromCR(20, sys_clk2);

		DDR4_Controller_VCU108 ddr4_ctrl_1 <- mkDDR4Controller_VCU108(defaultValue, clocked_by sys_clk2, reset_by sys_rst2);

		Clock ddr4clk1 = ddr4_ctrl_1.user.clock;
		Reset ddr4rstn1 = ddr4_ctrl_1.user.reset_n;

		let ddr_cli_300mhz_1 <- mkDDR4ClientSync(ddr_clients[1], curr_clk, curr_rst_n, ddr4clk1, ddr4rstn1);
		mkConnection(ddr_cli_300mhz_1, ddr4_ctrl_1.user);

	`endif

	rule do_ddr4_reqA;
		WideMemReq#(tagT) req = reqAQ.first(); reqAQ.deq();
		if(!req.write) begin
			tagQ.enq(req.tag);
			porQ.enq(True   );
		end
		if(req.write)
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: {16'b0,-1}, datain: {?,pack(req.line)} });
		else
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: 80'b0, datain:?});
	endrule

	rule do_ddr4_reqB;
		WideMemReq#(tagT) req = reqBQ.first(); reqBQ.deq();
		if(!req.write) begin
			tagQ.enq(req.tag);
			porQ.enq(False  );
		end
		if(req.write)
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: {16'b0,-1}, datain: {?,pack(req.line)} });
		else
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: 80'b0, datain:?});
	endrule

	rule do_ddr4_res;
		DDRResponse res = ddr4_res[0].first(); ddr4_res[0].deq();
		tagT tag = tagQ.first(); tagQ.deq();
		Bool por = porQ.first(); porQ.deq();
		if(por) begin
			resAQ.enq(WideMemRes{ tag: tag, line: unpack(truncate(res)) });
		end else begin
			resBQ.enq(WideMemRes{ tag: tag, line: unpack(truncate(res)) });
		end
	endrule

	WideMemServer#(tagT) wmifcA = (interface WideMemServer#(tagT);
				interface request = (interface Put#(WideMemReq);
					method Action put(WideMemReq#(tagT) r);
						reqAQ.enq(r);
					endmethod
				endinterface);
				interface response = (interface Get#(WideMemRes);
					method ActionValue#(WideMemRes#(tagT)) get();
						resAQ.deq(); return resAQ.first();
					endmethod
				endinterface);
			 endinterface);

	WideMemServer#(tagT) wmifcB = (interface WideMemServer#(tagT);
				interface request = (interface Put#(WideMemReq);
					method Action put(WideMemReq#(tagT) r);
						reqBQ.enq(r);
					endmethod
				endinterface);
				interface response = (interface Get#(WideMemRes);
					method ActionValue#(WideMemRes#(tagT)) get();
						resBQ.deq(); return resBQ.first();
					endmethod
				endinterface);
			 endinterface);

	`ifdef SIMULATION
		WideMemDelay#(TSub#(simLatency,2), tagT) simIfcA <- mkWideMemDelay();
		WideMemDelay#(TSub#(simLatency,2), tagT) simIfcB <- mkWideMemDelay();
		mkConnection(simIfcA.mem,wmifcA);
		mkConnection(simIfcB.mem,wmifcB);
	`else
		`ifdef VCUDDRDELAY
		WideMemDelay#(TSub#(vcuLatency,2), tagT) vcuIfcA <- mkWideMemDelay();
		WideMemDelay#(TSub#(vcuLatency,2), tagT) vcuIfcB <- mkWideMemDelay();
		mkConnection(vcuIfcA.mem,wmifcA);
		mkConnection(vcuIfcB.mem,wmifcB);
		`endif
	`endif

	`ifdef SIMULATION
		interface WideMemServer portA = simIfcA.portA;
		interface WideMemServer portB = simIfcB.portA;
	`else
		`ifdef VCUDDRDELAY
		interface WideMemServer portA = vcuIfcA.portA;
		interface WideMemServer portB = vcuIfcB.portA;
		`else
		interface WideMemServer portA = wmifcA;
		interface WideMemServer portB = wmifcB;
		`endif
	`endif

	interface Top_Pins pins;
		`ifndef SIMULATION
			interface DDR4_Pins_Dual_VCU108 pins_ddr4;
				interface pins_c0 = ddr4_ctrl_0.ddr4;
				interface pins_c1 = ddr4_ctrl_1.ddr4;
			endinterface
		`endif
	endinterface

endmodule
