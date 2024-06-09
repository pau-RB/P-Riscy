// General BSV utilities
import FShow::*;
import FIFOF::*;
import SpecialFIFOs::*;
import Connectable::*;
import ClientServer::*;
import GetPut::*;

// Bridge Ifc
import TL2WMBridgeIfc::*;


// Platform types
import Types::*;
import WideMemTypes::*;

// TL types
import TileLinkTypes::*;
import TileLinkIfc::*;

module mkTL2WMBridge (TL2WMBridgeIfc ifc);

    //////////// BRIDGE FIFOS ////////////

    FIFOF#(TLreqA) tl_reqA <- mkPipelineFIFOF();
    FIFOF#(TLreqB) tl_reqB <- mkPipelineFIFOF();
    FIFOF#(TLreqC) tl_reqC <- mkPipelineFIFOF();
    FIFOF#(TLreqD) tl_reqD <- mkPipelineFIFOF();
    FIFOF#(TLreqE) tl_reqE <- mkPipelineFIFOF();

    FIFOF#(TLreqD) wm_req_2_tl_reqD <- mkPipelineFIFOF();
    FIFOF#(TLreqD) wm_res_2_tl_reqD <- mkPipelineFIFOF();

    FIFOF#(WideMemReq#(Bit#(3))) wm_req <- mkBypassFIFOF();
    FIFOF#(WideMemRes#(Bit#(3))) wm_res <- mkBypassFIFOF();

    Reg#(Bool) wm_req_round_robin  <- mkReg(False);
    Reg#(Bool) tl_reqD_round_robin <- mkReg(False);

    //////////// LOGIC ////////////    

    rule do_wm_req;

        if(tl_reqA.notEmpty() && (wm_req_round_robin || !tl_reqC.notEmpty())) begin

            // TLA to WM req

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_wm_req - do_wm_req from channel A!");
            `endif

            TLreqA beat = tl_reqA.first();
            tl_reqA.deq();
            wm_req_round_robin <= False;

            if(beat.size != 6) begin
                $error("mkTL2WMBridge A - Only expected 64-bit requests!");
            end

            case (beat.opcode)

                TileLinkTypes::PutFullData   :
                begin

                    wm_req.enq(WideMemReq { tag        : {1'b0, beat.source},
                                            write      : True               ,
                                            addr       : beat.address[31:6] ,
                                            data       : unpack(beat.data)  ,
                                            byte_enable: '1                 });

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::AccessAck,
                                                  param  : TileLinkTypes::ToT      ,
                                                  size   : 6                       ,
                                                  source : beat.source             ,
                                                  sink   : 0                       ,
                                                  denied : 0                       ,
                                                  data   : 0                       ,
                                                  corrupt: 0                       });

                end
                
                TileLinkTypes::PutPartialData:
                begin

                    wm_req.enq(WideMemReq { tag        : {1'b0, beat.source},
                                            write      : True               ,
                                            addr       : beat.address[31:6] ,
                                            data       : unpack(beat.data)  ,
                                            byte_enable: beat.mask          });

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::AccessAck,
                                                  param  : TileLinkTypes::ToT      ,
                                                  size   : 6                       ,
                                                  source : beat.source             ,
                                                  sink   : 0                       ,
                                                  denied : 0                       ,
                                                  data   : 0                       ,
                                                  corrupt: 0                       });

                end
                
                TileLinkTypes::ArithmeticData:
                begin

                    $error("mkTL2WMBridge A - Did not expect ArithmeticData!");

                end
                
                TileLinkTypes::LogicalData   :
                begin

                    $error("mkTL2WMBridge A - Did not expect LogicalData!");

                end
                
                TileLinkTypes::Get           :
                begin

                    wm_req.enq(WideMemReq { tag        : {1'b0, beat.source}, // 0 -> AccessAckData resp
                                            write      : False              ,
                                            addr       : beat.address[31:6] ,
                                            data       : ?                  ,
                                            byte_enable: 0                  });

                end
                
                TileLinkTypes::Hint          :
                begin

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::HintAck  ,
                                                  param  : TileLinkTypes::ToT      ,
                                                  size   : 6                       ,
                                                  source : beat.source             ,
                                                  sink   : 0                       ,
                                                  denied : 0                       ,
                                                  data   : 0                       ,
                                                  corrupt: 0                       });

                end
                
                TileLinkTypes::AcquireBlock  :
                begin

                    if((beat.param == TileLinkTypes::NtoB) || (beat.param == TileLinkTypes::NtoT)) begin
                        
                        // Data response

                        wm_req.enq(WideMemReq { tag        : {1'b1, beat.source}, // 1 -> GrantData resp
                                                write      : False              ,
                                                addr       : beat.address[31:6] ,
                                                data       : ?                  ,
                                                byte_enable: 0                  });

                    end else begin

                        // Dataless response

                        wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::Grant    ,
                                                      param  : TileLinkTypes::ToT      ,
                                                      size   : 6                       ,
                                                      source : beat.source             ,
                                                      sink   : 0                       ,
                                                      denied : 0                       ,
                                                      data   : 0                       ,
                                                      corrupt: 0                       });

                    end

                end
                
                TileLinkTypes::AcquirePerm   :
                begin

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::Grant    ,
                                                  param  : TileLinkTypes::ToT      ,
                                                  size   : 6                       ,
                                                  source : beat.source             ,
                                                  sink   : 0                       ,
                                                  denied : 0                       ,
                                                  data   : 0                       ,
                                                  corrupt: 0                       });

                end
            endcase

        end else if(tl_reqC.notEmpty()) begin

            // TLC to WM req

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_wm_req - do_wm_req from channel C!");
            `endif

            TLreqC beat = tl_reqC.first();
            tl_reqC.deq();
            wm_req_round_robin <= True;

            if(beat.size != 6) begin
                $error("mkTL2WMBridge A - Only expected 64-bit requests!");
            end

            case (beat.opcode)

                TileLinkTypes::AccessAck    :
                begin

                    $error("mkTL2WMBridge C - Did not expect AccessAck!");

                end

                TileLinkTypes::AccessAckData:
                begin

                    $error("mkTL2WMBridge C - Did not expect AccessAckData!");

                end

                TileLinkTypes::HintAck      :
                begin

                    $error("mkTL2WMBridge C - Did not expect HintAck!");

                end

                TileLinkTypes::Illegal3     :
                begin

                    $error("mkTL2WMBridge C - Did not expect Illegal3!");

                end

                TileLinkTypes::ProbeAck     :
                begin

                    $error("mkTL2WMBridge C - Did not expect ProbeAck!");

                end

                TileLinkTypes::ProbeAckData :
                begin

                    $error("mkTL2WMBridge C - Did not expect ProbeAckData!");

                end

                TileLinkTypes::Release      :
                begin

                    TLparamD param = TileLinkTypes::ToN;

                    case (beat.param)
                        TtoB    : param = TileLinkTypes::ToB;
                        TtoN    : param = TileLinkTypes::ToN;
                        BtoN    : param = TileLinkTypes::ToN;
                        TtoT    : param = TileLinkTypes::ToT;
                        BtoB    : param = TileLinkTypes::ToB;
                        NtoN    : param = TileLinkTypes::ToN;
                        Illegal6: $error("mkTL2WMBridge C - Illegal param in release!");
                        Illegal7: $error("mkTL2WMBridge C - Illegal param in release!");
                    endcase

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::ReleaseAck,
                                                  param  : param                    ,
                                                  size   : 6                        ,
                                                  source : beat.source              ,
                                                  sink   : 0                        ,
                                                  denied : 0                        ,
                                                  data   : 0                        ,
                                                  corrupt: 0                        });

                end

                TileLinkTypes::ReleaseData  :
                begin

                    TLparamD param = TileLinkTypes::ToN;

                    case (beat.param)
                        TtoB    : param = TileLinkTypes::ToB;
                        TtoN    : param = TileLinkTypes::ToN;
                        BtoN    : param = TileLinkTypes::ToN;
                        TtoT    : param = TileLinkTypes::ToT;
                        BtoB    : param = TileLinkTypes::ToB;
                        NtoN    : param = TileLinkTypes::ToN;
                        Illegal6: $error("mkTL2WMBridge C - Illegal param in release!");
                        Illegal7: $error("mkTL2WMBridge C - Illegal param in release!");
                    endcase

                    wm_req_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::ReleaseAck,
                                                  param  : param                    ,
                                                  size   : 6                        ,
                                                  source : beat.source              ,
                                                  sink   : 0                        ,
                                                  denied : 0                        ,
                                                  data   : 0                        ,
                                                  corrupt: 0                        });

                    wm_req.enq(WideMemReq { tag        : {1'b0, beat.source},
                                            write      : True               ,
                                            addr       : beat.address[31:6] ,
                                            data       : unpack(beat.data)  ,
                                            byte_enable: '1                 });

                end

            endcase

        end

    endrule

    rule do_wm_res;

        WideMemRes#(Bit#(3)) res = wm_res.first();
        wm_res.deq();

        if(res.tag[2] == 1'b0) begin

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_wm_res - do_wm_res AccessAckData!");
            `endif

            wm_res_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::AccessAckData,
                                          param  : TileLinkTypes::ToT          ,
                                          size   : 6                           ,
                                          source : res.tag[1:0]                ,
                                          sink   : 0                           ,
                                          denied : 0                           ,
                                          data   : pack(res.data)              ,
                                          corrupt: 0                           });

        end else begin

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_wm_res - do_wm_res GrantData!");
            `endif

            wm_res_2_tl_reqD.enq(TLreqD { opcode : TileLinkTypes::GrantData    ,
                                          param  : TileLinkTypes::ToT          ,
                                          size   : 6                           ,
                                          source : res.tag[1:0]                ,
                                          sink   : 0                           ,
                                          denied : 0                           ,
                                          data   : pack(res.data)              ,
                                          corrupt: 0                           });

        end

    endrule

    rule do_mux_tl_reqD;

        if(wm_req_2_tl_reqD.notEmpty() && (tl_reqD_round_robin || !wm_res_2_tl_reqD.notEmpty())) begin

            // WM req to TLD (write acknowledgement)

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_mux_tl_reqD - do_mux_tl_reqD from REQ!");
            `endif

            TLreqD beat = wm_req_2_tl_reqD.first();
            wm_req_2_tl_reqD.deq();
            tl_reqD.enq(beat);
            tl_reqD_round_robin <= False;

        end else if(wm_res_2_tl_reqD.notEmpty()) begin

            // WM resp to TLD (read data)

            `ifdef DEBUG_TL2WM_BRIDGE
            $display("mkTL2WMBridge do_mux_tl_reqD - do_mux_tl_reqD from RES!");
            `endif

            TLreqD beat = wm_res_2_tl_reqD.first();
            wm_res_2_tl_reqD.deq();
            tl_reqD.enq(beat);
            tl_reqD_round_robin <= True;

        end

    endrule

    rule do_deq_tl_reqE;

        tl_reqE.deq();

    endrule

    //////////// INTERFACE ////////////

    interface TileLinkSlaveCached tl_slave;

        // Slave to master

        method ActionValue#(TLreqBpacked) getB();
            TLreqB beat = tl_reqB.first();
            tl_reqB.deq();
            return pack(beat);
        endmethod

        method ActionValue#(TLreqDpacked) getD();
            TLreqD beat = tl_reqD.first();
            tl_reqD.deq();
            return pack(beat);
        endmethod

        // Master to Slave

        method Action putA(TLreqApacked beat);
            tl_reqA.enq(unpack(beat));
        endmethod

        method Action putC(TLreqCpacked beat);
            tl_reqC.enq(unpack(beat));
        endmethod

        method Action putE(TLreqEpacked beat);
            tl_reqE.enq(unpack(beat));
        endmethod

    endinterface

    interface WideMemClient wm_client;

        interface request = (interface Get#(WideMemReq#(Bit#(3)));

            method ActionValue#(WideMemReq#(Bit#(3))) get();
                wm_req.deq();
                return wm_req.first();
            endmethod

        endinterface);

        interface response = (interface Put#(WidememRes#(Tuple2#(srcT,tagT)));

            method Action put(WideMemRes#(Bit#(3)) resp);
                wm_res.enq(resp);
            endmethod

        endinterface);

    endinterface

endmodule : mkTL2WMBridge
