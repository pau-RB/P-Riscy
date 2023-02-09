import Types::*;
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
import Clocks          :: *;
import DefaultValue    :: *;
`endif

import GetPut::*;
import ClientServerHelper::*;
import DRAMControllerTypes::*;


module mkWideMemDDR4(WideMem);

	FIFO#(WideMemReq ) reqQ <- mkFIFO();
	FIFO#(WideMemResp) resQ <- mkFIFO();

	Vector#(1,FIFO#(DDRRequest )) ddr4_req <- replicateM(mkFIFO());
	Vector#(1,FIFO#(DDRResponse)) ddr4_res <- replicateM(mkFIFO());
	Vector#(1,DDR4Client) ddr_clients = zipWith(toClient, ddr4_req, ddr4_res);

	Vector#(1, DDR4_User_VCU108) ddr4_ctrl_users <- replicateM(mkDDR4Simulator);
	zipWithM_(mkConnection, ddr_clients, ddr4_ctrl_users);

	rule do_ddr4_req;
		WideMemReq req = reqQ.first(); reqQ.deq();
		if(req.write)
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: {16'b0,-1}, datain: {?,pack(req.line)} });
		else
			ddr4_req[0].enq(DDRRequest{address: extend(req.num<<3), writeen: 80'b0, datain:?});
	endrule

	rule do_ddr4_res;
		DDRResponse res = ddr4_res[0].first(); ddr4_res[0].deq();
		resQ.enq(unpack(truncate(res)));
	endrule

	method Action req(WideMemReq r);
		reqQ.enq(r);
	endmethod

	method ActionValue#(CacheLine) resp;
		resQ.deq(); return resQ.first();
	endmethod

endmodule