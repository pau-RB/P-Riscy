// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See vlsim.h for the primary calling header

#include "vlsim.h"
#include "vlsim__Syms.h"

#include "verilated_dpi.h"

VL_INLINE_OPT void vlsim::_sequent__TOP__1153__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1153__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq) 
              & (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_error))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq) 
                            & (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1154__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1154__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data0_reg 
        = (0x1fU & (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg))) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg))))) 
                      & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg) 
                     | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg))))) 
                        & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data1_reg))) 
                    | (VL_NEGATE_I((IData)((1U & ((
                                                   ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)) 
                                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg)))))) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data0_reg))));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data1_reg 
        = (0x1fU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg))
                     ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg
                     : (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data1_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1155__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1155__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data0_reg 
        = (0x1fU & (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg))) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg))))) 
                      & vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U]) 
                     | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg))))) 
                        & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data1_reg))) 
                    | (VL_NEGATE_I((IData)((1U & ((
                                                   ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg)))))) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data0_reg))));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data1_reg 
        = (0x1fU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg))
                     ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U]
                     : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data1_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1156__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1156__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1157__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1157__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq) 
              & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportStateDbg))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq) 
                            & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1158__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1158__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportMemoryTraffic))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq) 
                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1159__PROF__RegFile__l65(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1159__PROF__RegFile__l65\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
         | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0 
            = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)
                ? (((2U == (0x3ffU & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen_D_OUT_1))) 
                    << 0xaU) | (0x3ffU & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen_D_OUT_1) 
                                          - (IData)(1U))))
                : (((1U == (0x7fU & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                                      << 0x16U) | (
                                                   vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                                                   >> 0xaU)))) 
                    << 0xaU) | (0x7fU & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                                          << 0x16U) 
                                         | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                                            >> 0xaU)))));
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0 
            = (0x1fU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)
                         ? ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
                             << 0x1fU) | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
                                          >> 1U)) : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data0_reg)));
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1160__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1160__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOA_R;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOA_R;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1161__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1161__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data0_reg 
        = (0x1fU & (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg))) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg))))) 
                      & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
                          << 0x1fU) | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
                                       >> 1U))) | (
                                                   VL_NEGATE_I((IData)(
                                                                       ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg) 
                                                                        & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg))))) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data1_reg))) 
                    | (VL_NEGATE_I((IData)((1U & ((
                                                   ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg)))))) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data0_reg))));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data1_reg 
        = (0x1fU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg))
                     ? ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
                         << 0x1fU) | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
                                      >> 1U)) : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data1_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1162__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1162__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg 
        = (((VL_NEGATE_Q((QData)((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg))) 
                                          | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg)))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0_D_IN) 
            | (VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg)))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data1_reg)) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((
                                                   (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)) 
                                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg))) 
                                                 | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg))))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1163__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1163__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOA_R;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1164__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1164__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited)) 
                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_positive_reg)) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr_D_IN;
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1165__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1165__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_addrResponse))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq) 
                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1166__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1166__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1167__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1167__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1168__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1168__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags 
        = ((IData)(vlTOPp->RST_N) ? ((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg) 
                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited)) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_positive_reg))
                                      ? (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__t___05Fh1387 
                                         | ((IData)(1U) 
                                            << (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr)))
                                      : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__t___05Fh1387)
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1169__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1169__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_fired 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_set_pw_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1170__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1170__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_fired 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_set_pw_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1171__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1171__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg_1 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_wire_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1172__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1172__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg_1 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_wire_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1173__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1173__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_writeWithResp_whas)
                                      ? (2U | (1U & 
                                               ((~ 
                                                 (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                                                    ? 0U
                                                    : 2U) 
                                                  >> 1U)) 
                                                | ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                                                    ? 0U
                                                    : 2U))))
                                      : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1174__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1174__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data0_reg 
        = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry) 
                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__full_reg))))) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data1_reg) 
           | (VL_NEGATE_I((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__empty_reg))) 
                                         | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__full_reg))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data1_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data1_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1175__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1175__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_fsm_start))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request) 
                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1176__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1176__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_fsm_start))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request) 
                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1177__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1177__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_fired 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_set_pw_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1178__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1178__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_fired 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_set_pw_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1179__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1179__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg_1 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_wire_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1180__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1180__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg_1 
        = ((IData)(vlTOPp->RST_N) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_wire_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1181__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1181__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_fsm_start))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request) 
                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1182__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1182__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_fsm_start))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request) 
                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1183__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1183__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOB_R;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOB_R;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1184__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1184__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOB_R;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1185__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1185__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1186__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1186__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr)) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg))))) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data1_reg))) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg)))))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data0_reg)));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg))
            ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr)
            : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data1_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1187__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1187__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader) 
              & (0U != (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh90027))) 
             | ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
                & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg))))) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_bpState 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader) 
                   & (0U != (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh90027)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1188__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1188__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader) 
              & (0U != (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh88187))) 
             | ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
                & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg))))) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_bpState 
                = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader) 
                   & (0U != (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh88187)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1189__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1189__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage) 
              & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_bpState 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage) 
                            & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1190__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1190__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr)) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg))))) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data1_reg))) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg)))))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data0_reg)));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg))
            ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr)
            : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data1_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1191__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1191__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
              & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_bpState 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
                            & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1192__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1192__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr)) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg))))) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data1_reg))) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg)))))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data0_reg)));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg))
            ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr)
            : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data1_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1193__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1193__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)) 
             | (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1194__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1194__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate)) 
             | (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1195__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1195__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_f_init_l241c7))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1196__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1196__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate)) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_action_f_init_l157c7))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1197__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1197__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)) 
                    & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_positive_reg)) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr_D_IN;
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1198__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1198__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg) 
                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited)) 
                    & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_positive_reg)) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr_D_IN;
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1199__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1199__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags 
        = ((IData)(vlTOPp->RST_N) ? ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg) 
                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_positive_reg))
                                      ? (vlTOPp->mkXsimTop__DOT__t___05Fh49481 
                                         | ((IData)(1U) 
                                            << (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr)))
                                      : vlTOPp->mkXsimTop__DOT__t___05Fh49481)
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1200__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1200__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags 
        = ((IData)(vlTOPp->RST_N) ? ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg) 
                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited)) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_positive_reg))
                                      ? (vlTOPp->mkXsimTop__DOT__t___05Fh10829 
                                         | ((IData)(1U) 
                                            << (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr)))
                                      : vlTOPp->mkXsimTop__DOT__t___05Fh10829)
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1246__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1246__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1256__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1256__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1257__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1257__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1258__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1258__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1259__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1259__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1260__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1260__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1261__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1261__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1262__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1262__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1263__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1263__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1264__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1264__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1265__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1265__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1270__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1270__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1271__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1271__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1272__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1272__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1273__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1273__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1274__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1274__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1297__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1297__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1298__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1298__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1299__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1299__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1300__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1300__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1301__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1301__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1302__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1302__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1303__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1303__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1307__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1307__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1308__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1308__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1309__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1309__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1310__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1310__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1311__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1311__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1313__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1313__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1316__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1316__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1317__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1317__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1318__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1318__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1319__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1319__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1320__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1320__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1356__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1356__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1357__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1357__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1378__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1378__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1379__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1379__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1382__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1382__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1383__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1383__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1384__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1384__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1385__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1385__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1386__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1386__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1400__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1400__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1401__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1401__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1403__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1403__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1404__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1404__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1406__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1406__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1407__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1407__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1408__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1408__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1409__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1409__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1410__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1410__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1411__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1411__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1452__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1452__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1455__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1455__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1456__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1456__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1457__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1457__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1458__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1458__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1459__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1459__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1465__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1465__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1466__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1466__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1476__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1476__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1488__PROF__RegFile__l68(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1488__PROF__RegFile__l68\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1491__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1491__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1498__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1498__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1502__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1502__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1503__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1503__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1504__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1504__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1505__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1505__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1506__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1506__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1507__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1507__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1508__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1508__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1509__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1509__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1510__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1510__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1511__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1511__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1535__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1535__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1537__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1537__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1538__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1538__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1539__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1539__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1540__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1540__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1541__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1541__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1574__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1574__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput_EN_portalIfc_requests_0_enq) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo_DEQ) {
                vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1575__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1575__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_idResponsePipe_deq) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1576__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1576__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_errorPipe_deq) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1577__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1577__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) {
                vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1578__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1578__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo_DEQ) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1579__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1579__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_2_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idRequest_PipeOut_deq) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1580__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1580__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_3_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idReturn_PipeOut_deq) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1581__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1581__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_2) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1582__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1582__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1583__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1583__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__empty_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1584__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1584__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_sglist_PipeOut_deq) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1585__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1585__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__empty_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1586__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1586__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_2_enq) {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1587__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1587__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[0U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[1U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[0U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[2U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[1U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[3U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[2U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[4U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[3U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1588__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1588__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_region_PipeOut_deq) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1589__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1589__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_configResponsePipe_deq) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1590__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1590__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_3_enq) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request) {
                vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1591__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1591__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_2_enq) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request) {
                vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1592__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1592__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[0U] 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
            [(0x1fU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
                               >> 0x28U)))][0U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[1U] 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
            [(0x1fU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
                               >> 0x28U)))][1U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[2U] 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
            [(0x1fU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
                               >> 0x28U)))][2U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[3U] 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
            [(0x1fU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
                               >> 0x28U)))][3U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[4U] 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
            [(0x1fU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
                               >> 0x28U)))][4U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1593__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1593__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ENA) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOA_R 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ADDRA]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_DIA);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1594__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1594__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOB_R 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM
            [((0x1f00U & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg) 
                          << 8U)) | ((0U == (7U & (IData)(
                                                          (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                                           >> 0x2dU))))
                                      ? 0U : (0xffU 
                                              & ((IData)(
                                                         (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                                          >> 0xdU)) 
                                                 + (IData)(
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                                            >> 5U))))))];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1595__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1595__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ENB) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[0U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB][0U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[0U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[1U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB][1U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[1U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[2U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB][2U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[2U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[3U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB][3U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[3U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[4U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB][4U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[4U]);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1596__PROF__mkXsimTop__l3369(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1596__PROF__mkXsimTop__l3369\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__dumpstarted_EN = (1U & 
                                              (~ (IData)(vlTOPp->mkXsimTop__DOT__dumpstarted)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1597__PROF__mkXsimTop__l3986(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1597__PROF__mkXsimTop__l3986\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount_D_IN 
        = ((IData)(1U) + vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1598__PROF__mkXsimTop__l3524(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1598__PROF__mkXsimTop__l3524\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount_D_IN 
        = ((IData)(1U) + vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1599__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1599__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1600__PROF__mkXsimTop__l5364(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1600__PROF__mkXsimTop__l5364\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__readOffset___05Fh93284 
        = ((0U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readLenReg))
            ? 0U : vlTOPp->mkXsimTop__DOT__slave_2_0_readOffsetReg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1601__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1601__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1602__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1602__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1603__PROF__mkXsimTop__l4928(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1603__PROF__mkXsimTop__l4928\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full) 
           & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_s1)) 
                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full)) 
               & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_s1) 
                  >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1604__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1604__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1605__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1605__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1606__PROF__mkXsimTop__l4617(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1606__PROF__mkXsimTop__l4617\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full) 
           & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_s1)) 
                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full)) 
               & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_s1) 
                  >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1607__PROF__mkXsimTop__l4174(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1607__PROF__mkXsimTop__l4174\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_cycles_D_IN = 
        (VL_ULL(1) + vlTOPp->mkXsimTop__DOT__slave_2_0_cycles);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1608__PROF__mkMemServerRequestInput__l1049(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1608__PROF__mkMemServerRequestInput__l1049\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count_D_IN 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1609__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1609__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1610__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1610__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1611__PROF__mkXsimTop__l3247(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1611__PROF__mkXsimTop__l3247\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outData_enqData_whas 
        = (1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_s1)) 
                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                  & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_s1) 
                     >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1612__PROF__mkMMUSynth__l1839(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1612__PROF__mkMMUSynth__l1839\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1_D_IN 
        = (((QData)((IData)((7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                                   >> 0x1bU)))) << 0x28U) 
           | ((1U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                            >> 0x18U))) ? (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg)) 
                                            << 0xcU) 
                                           | (QData)((IData)(
                                                             (0xfffU 
                                                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT))))
               : ((2U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                                >> 0x18U))) ? (((QData)((IData)(
                                                                (0xffffffU 
                                                                 & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg))) 
                                                << 0x10U) 
                                               | (QData)((IData)(
                                                                 (0xffffU 
                                                                  & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT))))
                   : ((3U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                                    >> 0x18U))) ? (
                                                   ((QData)((IData)(
                                                                    (0xfffffU 
                                                                     & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg))) 
                                                    << 0x14U) 
                                                   | (QData)((IData)(
                                                                     (0xfffffU 
                                                                      & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT))))
                       : (((QData)((IData)((0xffffU 
                                            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg))) 
                           << 0x18U) | (QData)((IData)(
                                                       (0xffffffU 
                                                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT))))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1613__PROF__mkXsimTop__l5416(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1613__PROF__mkXsimTop__l5416\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__writeOffset___05Fh95460 
        = ((0U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeLenReg))
            ? 0U : vlTOPp->mkXsimTop__DOT__slave_2_0_writeOffsetReg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1614__PROF__mkMMURequestInput__l1433(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1614__PROF__mkMMURequestInput__l1433\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count_D_IN 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1615__PROF__mkMMURequestInput__l1445(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1615__PROF__mkMMURequestInput__l1445\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count_D_IN 
        = ((4U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1616__PROF__mkMMURequestInput__l1422(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1616__PROF__mkMMURequestInput__l1422\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count_D_IN 
        = ((0xcU == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count))
            ? 0U : (0xfU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1617__PROF__mkMMUSynth__l2012(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1617__PROF__mkMMUSynth__l2012\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_D_IN 
        = (((QData)((IData)(((0x10000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                              ? 4U : ((0x8000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                       ? 3U : ((0x4000U 
                                                & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                ? 2U
                                                : (
                                                   (0x2000U 
                                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                    ? 1U
                                                    : 0U)))))) 
            << 0x2dU) | (((QData)((IData)(((0xffffff00U 
                                            & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
                                               << 8U)) 
                                           | (0xffU 
                                              & ((0x10000U 
                                                  & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                  ? 
                                                 ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                   << 8U) 
                                                  | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
                                                     >> 0x18U))
                                                  : 
                                                 ((0x8000U 
                                                   & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                   ? 
                                                  ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                    << 0xcU) 
                                                   | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
                                                      >> 0x14U))
                                                   : 
                                                  ((0x4000U 
                                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                    ? 
                                                   ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                     << 0x10U) 
                                                    | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
                                                       >> 0x10U))
                                                    : 
                                                   ((0x2000U 
                                                     & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                     ? 
                                                    ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                      << 0x14U) 
                                                     | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
                                                        >> 0xcU))
                                                     : 0U)))))))) 
                          << 0xdU) | (QData)((IData)(
                                                     ((0x1fe0U 
                                                       & (((0x10000U 
                                                            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                            ? 
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
                                                            >> 5U)
                                                            : 
                                                           ((0x8000U 
                                                             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                             ? 
                                                            ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
                                                              << 3U) 
                                                             | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                                >> 0x1dU))
                                                             : 
                                                            ((0x4000U 
                                                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                              ? 
                                                             ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
                                                               << 0xbU) 
                                                              | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                                 >> 0x15U))
                                                              : 
                                                             ((0x2000U 
                                                               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U])
                                                               ? 
                                                              ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
                                                                << 0x13U) 
                                                               | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                                  >> 0xdU))
                                                               : 0U)))) 
                                                          << 5U)) 
                                                      | (0x1fU 
                                                         & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
                                                             << 0x18U) 
                                                            | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
                                                               >> 8U))))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1618__PROF__mkMMUSynth__l1696(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1618__PROF__mkMMUSynth__l1696\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1619__PROF__mkXsimTop__l4164(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1619__PROF__mkXsimTop__l4164\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1620__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1620__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1621__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1621__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1622__PROF__mkMMUSynth__l1831(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1622__PROF__mkMMUSynth__l1831\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0_D_IN 
        = (((QData)((IData)((7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                                   >> 0x1bU)))) << 0x28U) 
           | ((1U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                            >> 0x18U))) ? (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg)) 
                                            << 0xcU) 
                                           | (QData)((IData)(
                                                             (0xfffU 
                                                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT))))
               : ((2U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                                >> 0x18U))) ? (((QData)((IData)(
                                                                (0xffffffU 
                                                                 & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg))) 
                                                << 0x10U) 
                                               | (QData)((IData)(
                                                                 (0xffffU 
                                                                  & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT))))
                   : ((3U == (7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                                    >> 0x18U))) ? (
                                                   ((QData)((IData)(
                                                                    (0xfffffU 
                                                                     & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg))) 
                                                    << 0x14U) 
                                                   | (QData)((IData)(
                                                                     (0xfffffU 
                                                                      & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT))))
                       : (((QData)((IData)((0xffffU 
                                            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg))) 
                           << 0x18U) | (QData)((IData)(
                                                       (0xffffffU 
                                                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT))))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1623__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1623__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_tail 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1624__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1624__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_tail 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1625__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1625__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_head 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1626__PROF__mkXsimTop__l4953(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1626__PROF__mkXsimTop__l4953\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_IN 
        = ((0xfc0000U & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                         << 3U)) | ((0x3ff00U & ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U] 
                                                  << 0x13U) 
                                                 | (0x7ff00U 
                                                    & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                       >> 0xdU)))) 
                                    | ((0xfeU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U] 
                                                 << 1U)) 
                                       | (8U == (0x3ffU 
                                                 & ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U] 
                                                     << 0xbU) 
                                                    | (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                       >> 0x15U)))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1627__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1627__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1628__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1628__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1629__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1629__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1630__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1630__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1631__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1631__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1632__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1632__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_tail 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1633__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1633__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_head 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1634__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1634__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1635__PROF__mkToHostOutputPipes__l256(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1635__PROF__mkToHostOutputPipes__l256\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput_EN_portalIfc_indications_0_deq) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput_EN_portalIfc_indications_0_deq)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1636__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1636__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1637__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1637__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessage))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1638__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1638__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1639__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1639__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1640__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1640__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1641__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1641__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1642__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1642__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule)))) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1643__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1643__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1644__PROF__mkCnocTop__l890(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1644__PROF__mkCnocTop__l890\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT___theResult___05F___05Fh1407 
        = (0xffU & ((1U == (0xffU & vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg))
                     ? vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg
                     : (vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1645__PROF__XsimSink__l41(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1645__PROF__XsimSink__l41\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    QData/*63:0*/ __Vfunc_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat__3__Vfuncout;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((IData)(vlTOPp->mkXsimTop__DOT__sink_0_EN_beat) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__sink_0__DOT__valid_reg))))) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat_TOP(6U, __Vfunc_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat__3__Vfuncout);
            vlTOPp->mkXsimTop__DOT__sink_0__DOT__unnamedblk1__DOT__v 
                = __Vfunc_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat__3__Vfuncout;
            vlTOPp->mkXsimTop__DOT__sink_0__DOT__valid_reg 
                = (1U & (IData)((vlTOPp->mkXsimTop__DOT__sink_0__DOT__unnamedblk1__DOT__v 
                                 >> 0x20U)));
            vlTOPp->mkXsimTop__DOT__sink_0__DOT__beat_reg 
                = (IData)(vlTOPp->mkXsimTop__DOT__sink_0__DOT__unnamedblk1__DOT__v);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__sink_0__DOT__valid_reg = 0U;
        vlTOPp->mkXsimTop__DOT__sink_0__DOT__beat_reg = 0xaaaaaaaaU;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1646__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1646__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq)))) {
                vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1647__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1647__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1648__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1648__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_3_enq) {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1649__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1649__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1650__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1650__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_tail 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1651__PROF__mkMMUSynth__l1999(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1651__PROF__mkMMUSynth__l1999\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_D_IN 
        = (((QData)((IData)(((0x10000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                              ? 4U : ((0x8000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                       ? 3U : ((0x4000U 
                                                & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                ? 2U
                                                : (
                                                   (0x2000U 
                                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                    ? 1U
                                                    : 0U)))))) 
            << 0x2dU) | (((QData)((IData)(((0xffffff00U 
                                            & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
                                               << 8U)) 
                                           | (0xffU 
                                              & ((0x10000U 
                                                  & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                  ? 
                                                 ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                   << 8U) 
                                                  | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
                                                     >> 0x18U))
                                                  : 
                                                 ((0x8000U 
                                                   & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                   ? 
                                                  ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                    << 0xcU) 
                                                   | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
                                                      >> 0x14U))
                                                   : 
                                                  ((0x4000U 
                                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                    ? 
                                                   ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                     << 0x10U) 
                                                    | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
                                                       >> 0x10U))
                                                    : 
                                                   ((0x2000U 
                                                     & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                     ? 
                                                    ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                      << 0x14U) 
                                                     | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
                                                        >> 0xcU))
                                                     : 0U)))))))) 
                          << 0xdU) | (QData)((IData)(
                                                     ((0x1fe0U 
                                                       & (((0x10000U 
                                                            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                            ? 
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
                                                            >> 5U)
                                                            : 
                                                           ((0x8000U 
                                                             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                             ? 
                                                            ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
                                                              << 3U) 
                                                             | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                                >> 0x1dU))
                                                             : 
                                                            ((0x4000U 
                                                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                              ? 
                                                             ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
                                                               << 0xbU) 
                                                              | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                                 >> 0x15U))
                                                              : 
                                                             ((0x2000U 
                                                               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U])
                                                               ? 
                                                              ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
                                                                << 0x13U) 
                                                               | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                                  >> 0xdU))
                                                               : 0U)))) 
                                                          << 5U)) 
                                                      | (0x1fU 
                                                         & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
                                                             << 0x18U) 
                                                            | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
                                                               >> 8U))))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1652__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1652__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1653__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1653__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1654__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1654__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1655__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1655__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1656__PROF__XsimSink__l41(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1656__PROF__XsimSink__l41\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    QData/*63:0*/ __Vfunc_mkXsimTop__DOT__sink_2__DOT__dpi_msgSink_beat__5__Vfuncout;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((IData)(vlTOPp->mkXsimTop__DOT__sink_2_EN_beat) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__sink_2__DOT__valid_reg))))) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat_TOP(1U, __Vfunc_mkXsimTop__DOT__sink_2__DOT__dpi_msgSink_beat__5__Vfuncout);
            vlTOPp->mkXsimTop__DOT__sink_2__DOT__unnamedblk1__DOT__v 
                = __Vfunc_mkXsimTop__DOT__sink_2__DOT__dpi_msgSink_beat__5__Vfuncout;
            vlTOPp->mkXsimTop__DOT__sink_2__DOT__valid_reg 
                = (1U & (IData)((vlTOPp->mkXsimTop__DOT__sink_2__DOT__unnamedblk1__DOT__v 
                                 >> 0x20U)));
            vlTOPp->mkXsimTop__DOT__sink_2__DOT__beat_reg 
                = (IData)(vlTOPp->mkXsimTop__DOT__sink_2__DOT__unnamedblk1__DOT__v);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__sink_2__DOT__valid_reg = 0U;
        vlTOPp->mkXsimTop__DOT__sink_2__DOT__beat_reg = 0xaaaaaaaaU;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1657__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1657__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1658__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1658__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1659__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1659__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1660__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1660__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1661__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1661__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1662__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1662__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1663__PROF__XsimSink__l41(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1663__PROF__XsimSink__l41\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    QData/*63:0*/ __Vfunc_mkXsimTop__DOT__sink_1__DOT__dpi_msgSink_beat__4__Vfuncout;
    // Body
    if (vlTOPp->RST_N) {
        if ((1U & ((IData)(vlTOPp->mkXsimTop__DOT__sink_1_EN_beat) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__sink_1__DOT__valid_reg))))) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat_TOP(2U, __Vfunc_mkXsimTop__DOT__sink_1__DOT__dpi_msgSink_beat__4__Vfuncout);
            vlTOPp->mkXsimTop__DOT__sink_1__DOT__unnamedblk1__DOT__v 
                = __Vfunc_mkXsimTop__DOT__sink_1__DOT__dpi_msgSink_beat__4__Vfuncout;
            vlTOPp->mkXsimTop__DOT__sink_1__DOT__valid_reg 
                = (1U & (IData)((vlTOPp->mkXsimTop__DOT__sink_1__DOT__unnamedblk1__DOT__v 
                                 >> 0x20U)));
            vlTOPp->mkXsimTop__DOT__sink_1__DOT__beat_reg 
                = (IData)(vlTOPp->mkXsimTop__DOT__sink_1__DOT__unnamedblk1__DOT__v);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__sink_1__DOT__valid_reg = 0U;
        vlTOPp->mkXsimTop__DOT__sink_1__DOT__beat_reg = 0xaaaaaaaaU;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1664__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1664__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1665__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1665__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1666__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1666__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_tail 
        = ((0x1eU == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1667__PROF__mkXsimTop__l5231(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1667__PROF__mkXsimTop__l5231\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__burstLen___05Fh51885 = 
        ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg)
          ? (0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                      >> 0xbU)) : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_burstReg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1668__PROF__mkXsimTop__l5492(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1668__PROF__mkXsimTop__l5492\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((2U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)) {
        if ((2U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)) {
            vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1 
                = (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[2U])) 
                    << 0x39U) | (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[1U])) 
                                  << 0x19U) | ((QData)((IData)(
                                                               vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[0U])) 
                                               >> 7U)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1 
            = (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[2U])) 
                << 0x39U) | (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[1U])) 
                              << 0x19U) | ((QData)((IData)(
                                                           vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[0U])) 
                                           >> 7U)));
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1669__PROF__mkXsimTop__l5210(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1669__PROF__mkXsimTop__l5210\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__IF_lMemServer_writer_writers_0_firstReg_93_THE_ETC___05F_d818 
        = (1U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg)
                  ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT
                  : (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_lastReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1670__PROF__mkXsimTop__l5471(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1670__PROF__mkXsimTop__l5471\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786 
        = (1U & ((0x800000U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)
                  ? ((0x400000U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_3))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_2)))
                  : ((0x400000U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_1))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_0)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1671__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1671__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_head 
        = ((0x1eU == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head))
            ? 0U : (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1672__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1672__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_tail 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1673__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1673__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1674__PROF__mkXsimTop__l5368(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1674__PROF__mkXsimTop__l5368\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__readyChannel___05Fh87211 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg)
            ? 0U : ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)
                     ? 1U : ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)
                              ? 2U : 0xffU)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1675__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1675__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1676__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1676__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1677__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1677__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1678__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1678__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1679__PROF__mkMMUSynth__l1888(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1679__PROF__mkMMUSynth__l1888\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[0U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[1U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[1U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[1U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[2U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[2U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[2U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[3U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[3U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[3U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[4U] 
        = (0x1ffffU & ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U])
                        ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U]
                        : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[4U]));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1680__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1680__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[0U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[1U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[2U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[3U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[4U] 
        = ((IData)(vlTOPp->RST_N) ? (0xaaaaU | (0xfffc0000U 
                                                & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                                   << 0x12U)))
            : 0x2aaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1681__PROF__mkMMUSynth__l2056(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1681__PROF__mkMMUSynth__l2056\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_D_IN 
        = (0xfffffffU & ((0x10000000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_1)
                          ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_1
                          : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOB_R2));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1682__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1682__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data1_1 
        = ((IData)(vlTOPp->RST_N) ? (0xaaaaaaaU | ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                                   << 0x1dU))
            : 0xaaaaaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1683__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1683__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
            = (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff)) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg)));
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1684__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1684__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1685__PROF__mkMMUSynth__l2044(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1685__PROF__mkMMUSynth__l2044\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_D_IN 
        = (0xfffffffU & ((0x10000000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_0)
                          ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_0
                          : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOA_R2));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1686__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1686__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data1_0 
        = ((IData)(vlTOPp->RST_N) ? (0xaaaaaaaU | ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                                   << 0x1dU))
            : 0xaaaaaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1687__PROF__mkMMUSynth__l1898(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1687__PROF__mkMMUSynth__l1898\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[0U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[1U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[1U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[1U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[2U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[2U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[2U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[3U] 
        = ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U])
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[3U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[3U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[4U] 
        = (0x1ffffU & ((0x20000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U])
                        ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U]
                        : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[4U]));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1688__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1688__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[0U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[1U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[2U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[3U] = 0xaaaaaaaaU;
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[4U] 
        = ((IData)(vlTOPp->RST_N) ? (0xaaaaU | (0xfffc0000U 
                                                & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                   << 0x12U)))
            : 0x2aaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1689__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1689__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_1_enq) {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT 
            = (0xfU & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1690__PROF__FIFO1__l73(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1690__PROF__FIFO1__l73\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_1_enq) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_DEQ) {
                vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg = 0U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1691__PROF__mkXsimTop__l5450(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1691__PROF__mkXsimTop__l5450\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_reader_readers_0_killv___05FETC___05F_d435 
        = (1U & ((2U & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compTileReg))
                  ? ((1U & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compTileReg))
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_3))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_2)))
                  : ((1U & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compTileReg))
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_1))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1692__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1692__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo_D_OUT 
            = (0x1fU & vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[0xcU]);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1693__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1693__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1694__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1694__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][0U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][1U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][2U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[3U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][3U]
                : 0U);
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[3U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[3U];
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][0U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][1U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][2U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[3U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head][3U]
                        : 0U);
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[0U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[1U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[2U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[3U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[3U];
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1695__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1695__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][0U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][1U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][2U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[3U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][3U]
                : 0U);
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[3U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[3U];
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][0U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][1U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][2U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[3U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head][3U]
                        : 0U);
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[0U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[1U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[2U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[3U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[3U];
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1696__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1696__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_tail 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1697__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1697__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_head 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1698__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1698__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1699__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1699__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[0U] 
            = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                & (0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                        >> 0x2dU)))))
                ? (IData)((QData)((IData)((0xffffffU 
                                           & (IData)(
                                                     (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                                      >> 0x15U))))))
                : (IData)((QData)((IData)((0xffffffU 
                                           & (IData)(
                                                     (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                                      >> 0x15U)))))));
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[1U] 
            = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                & (0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                        >> 0x2dU)))))
                ? ((0x1f00U & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg) 
                               << 8U)) | (IData)(((QData)((IData)(
                                                                  (0xffffffU 
                                                                   & (IData)(
                                                                             (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                                                              >> 0x15U))))) 
                                                  >> 0x20U)))
                : ((0x1f00U & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg) 
                               << 8U)) | (IData)(((QData)((IData)(
                                                                  (0xffffffU 
                                                                   & (IData)(
                                                                             (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                                                              >> 0x15U))))) 
                                                  >> 0x20U))));
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[2U] = 0x500U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1700__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1700__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[0U] 
            = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                & (~ (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
                      >> 0x10U))) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT)
                : (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT));
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[1U] 
            = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                & (~ (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
                      >> 0x10U))) ? (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                                             >> 0x20U))
                : (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                           >> 0x20U)));
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[2U] = 0x600U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1701__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1701__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_tail 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1702__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1702__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1703__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1703__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1704__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1704__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1705__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1705__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][0U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][1U]
                : 0U);
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U] 
            = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
               [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][2U]
                : 0U);
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[2U];
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][0U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][1U]
                        : 0U);
                vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U] 
                    = ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head][2U]
                        : 0U);
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[0U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[1U];
                    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U] 
                        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[2U];
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1706__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1706__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1707__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1707__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1708__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1708__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1709__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1709__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                       << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][0U];
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][1U];
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][2U];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] = 0x55555555U;
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] = 0x55555555U;
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] = 0x1555555U;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                             << 1U) 
                                            | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][0U];
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][1U];
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head][2U];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] = 0x55555555U;
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] = 0x55555555U;
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] = 0x1555555U;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1710__PROF__RegFile__l71(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1710__PROF__RegFile__l71\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen_D_OUT_1 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr
        [(0x1fU & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
                    << 0x1fU) | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
                                 >> 1U)))];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1711__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1711__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1712__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1712__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1713__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1713__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOA_R 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM
            [(0x1fU & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg) 
                       >> 1U))];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1714__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1714__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1715__PROF__mkXsimTop__l5376(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1715__PROF__mkXsimTop__l5376\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg)
            ? 0U : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)
                     ? 1U : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)
                              ? 2U : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)
                                       ? 3U : 0xffU))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1716__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1716__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1717__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1717__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1718__PROF__mkXsimTop__l3284(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1718__PROF__mkXsimTop__l3284\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas 
        = (1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_s1)) 
                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                  & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_s1) 
                     >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1719__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1719__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1720__PROF__mkXsimTop__l3202(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1720__PROF__mkXsimTop__l3202\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outData_enqData_whas 
        = (1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_s1)) 
                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full)) 
                  & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_s1) 
                     >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1721__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1721__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1722__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1722__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_cnt_PLUS_IF_sglId_gen_counte_ETC___05F_d9)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1723__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1723__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas)))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1724__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1724__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited_EN) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited 
                = (0x1fU == (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1725__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1725__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__empty_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__full_reg)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1726__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1726__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_3_enq) {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT 
            = (1U & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1727__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1727__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_2_enq) {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT 
            = (1U & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1728__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1728__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_writeWithResp_whas) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOB_R 
            = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM
               [vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_ADDRB]
                : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_DIB);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1729__PROF__SizedFIFO__l79(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1729__PROF__SizedFIFO__l79\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_tail 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1730__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1730__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1731__PROF__mkXsimTop__l3214(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1731__PROF__mkXsimTop__l3214\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_enqData_whas 
        = (1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_s1)) 
                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                  & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_s1) 
                     >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_s1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1732__PROF__mkXsimTop__l4969(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1732__PROF__mkXsimTop__l4969\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[0U] 
        = ((0xffffff80U & ((IData)((VL_ULL(0xffffffffff) 
                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg)) 
                           << 7U)) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__data0_reg) 
                                       << 1U) | (1U 
                                                 & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U])));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[1U] 
        = ((0x7fU & ((IData)((VL_ULL(0xffffffffff) 
                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg)) 
                     >> 0x19U)) | (0xffffff80U & ((0xffff8000U 
                                                   & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] 
                                                      << 0xeU)) 
                                                  | ((IData)(
                                                             ((VL_ULL(0xffffffffff) 
                                                               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg) 
                                                              >> 0x20U)) 
                                                     << 7U))));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[2U] 
        = ((0x7fU & ((0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] 
                               >> 0x12U)) | ((IData)(
                                                     ((VL_ULL(0xffffffffff) 
                                                       & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg) 
                                                      >> 0x20U)) 
                                             >> 0x19U))) 
           | (0xffffff80U & ((0x7f80U & ((0x4000U & 
                                          (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
                                           << 0xeU)) 
                                         | (0x3f80U 
                                            & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] 
                                               >> 0x12U)))) 
                             | (0xffff8000U & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
                                               << 0xeU)))));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[3U] 
        = ((0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
                     >> 0x12U)) | (0xffffff80U & ((0x7f80U 
                                                   & ((0x4000U 
                                                       & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] 
                                                          << 0xeU)) 
                                                      | (0x3f80U 
                                                         & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
                                                            >> 0x12U)))) 
                                                  | (0xffff8000U 
                                                     & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] 
                                                        << 0xeU)))));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[4U] 
        = (0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] 
                    >> 0x12U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1733__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1733__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage))) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1734__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1734__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage))) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1735__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1735__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1736__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1736__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1737__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1737__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1738__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1738__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1739__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1739__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1740__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1740__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1741__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1741__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1742__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1742__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1743__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1743__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_cn_ETC___05F_d702)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1744__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1744__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1745__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1745__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited 
                = (0x1fU == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1746__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1746__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_cn_ETC___05F_d292)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1747__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1747__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg)));
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas)))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg = 1U;
            }
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1748__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1748__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited_EN) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited 
                = (0x1fU == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1773__PROF__BRAM2__l67(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1773__PROF__BRAM2__l67\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1775__PROF__BRAM2__l80(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1775__PROF__BRAM2__l80\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0][0U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[0U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0][1U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[1U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0][2U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[2U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0][3U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[3U];
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0][4U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[4U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1777__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1777__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1778__PROF__mkXsimTop__l4628(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1778__PROF__mkXsimTop__l4628\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outData_enqData_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1780__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1780__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1782__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1782__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1784__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1784__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1786__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1786__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1788__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1788__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1790__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1790__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1793__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1793__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1797__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1797__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1799__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1799__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1803__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1803__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1809__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1809__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1811__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1811__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1814__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1814__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1816__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1816__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1820__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1820__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1822__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1822__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1826__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1826__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1834__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1834__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1835__PROF__mkXsimTop__l4898(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1835__PROF__mkXsimTop__l4898\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[0U] 
        = ((0xffffff80U & ((IData)(((IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786)
                                     ? vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1
                                     : VL_ULL(0))) 
                           << 7U)) | ((0x7eU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                                                >> 1U)) 
                                      | (IData)(vlTOPp->mkXsimTop__DOT__IF_lMemServer_writer_writers_0_firstReg_93_THE_ETC___05F_d818)));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[1U] 
        = ((0x7fU & ((IData)(((IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786)
                               ? vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1
                               : VL_ULL(0))) >> 0x19U)) 
           | (0xffffff80U & ((IData)((((IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786)
                                        ? vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1
                                        : VL_ULL(0)) 
                                      >> 0x20U)) << 7U)));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[2U] 
        = (0x7fU & ((IData)((((IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786)
                               ? vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq1
                               : VL_ULL(0)) >> 0x20U)) 
                    >> 0x19U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1837__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1837__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1838__PROF__mkMMUIndicationOutputPipes__l641(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1838__PROF__mkMMUIndicationOutputPipes__l641\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size 
        = (((0U == (IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh87211)) 
            | (1U == (IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh87211)))
            ? 0x20U : 0xc0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1841__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1841__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1843__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1843__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1845__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1845__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1851__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1851__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1859__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1859__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1860__PROF__mkXsimTop__l5117(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1860__PROF__mkXsimTop__l5117\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[0U] 
        = (IData)(((VL_ULL(0xffffffffff0000) & (((QData)((IData)(
                                                                 vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U])) 
                                                 << 0x29U) 
                                                | (VL_ULL(0xffffffffffff0000) 
                                                   & ((QData)((IData)(
                                                                      vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U])) 
                                                      << 9U)))) 
                   | (QData)((IData)(((0xffc0U & ((
                                                   vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U] 
                                                   << 0x11U) 
                                                  | (0x1ffc0U 
                                                     & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                        >> 0xfU)))) 
                                      | (0x3fU & ((
                                                   vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                   << 0x1fU) 
                                                  | (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U] 
                                                     >> 1U))))))));
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[1U] 
        = ((0xff000000U & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                           << 0x18U)) | (IData)((((VL_ULL(0xffffffffff0000) 
                                                   & (((QData)((IData)(
                                                                       vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U])) 
                                                       << 0x29U) 
                                                      | (VL_ULL(0xffffffffffff0000) 
                                                         & ((QData)((IData)(
                                                                            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U])) 
                                                            << 9U)))) 
                                                  | (QData)((IData)(
                                                                    ((0xffc0U 
                                                                      & ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U] 
                                                                          << 0x11U) 
                                                                         | (0x1ffc0U 
                                                                            & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                                               >> 0xfU)))) 
                                                                     | (0x3fU 
                                                                        & ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
                                                                            << 0x1fU) 
                                                                           | (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U] 
                                                                              >> 1U))))))) 
                                                 >> 0x20U)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[2U] 
        = ((0xffffffU & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                         >> 8U)) | (0xff000000U & ((IData)(
                                                           (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                                            >> 0x20U)) 
                                                   << 0x18U)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[3U] 
        = (0xffffffU & ((IData)((vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                 >> 0x20U)) >> 8U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1862__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1862__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1863__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1863__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0][0U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0][1U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0][2U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[2U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0][3U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[3U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1864__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1864__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1865__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1865__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1866__PROF__mkXsimTop__l5037(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1866__PROF__mkXsimTop__l5037\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[0U] 
        = (IData)(((VL_ULL(0xffffffffff0000) & (((QData)((IData)(
                                                                 vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U])) 
                                                 << 0x29U) 
                                                | (VL_ULL(0xffffffffffff0000) 
                                                   & ((QData)((IData)(
                                                                      vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U])) 
                                                      << 9U)))) 
                   | (QData)((IData)(((0xffc0U & ((
                                                   vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U] 
                                                   << 0x11U) 
                                                  | (0x1ffc0U 
                                                     & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                                        >> 0xfU)))) 
                                      | (0x3fU & ((
                                                   vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                                   << 0x1fU) 
                                                  | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U] 
                                                     >> 1U))))))));
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[1U] 
        = ((0xff000000U & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                           << 0x18U)) | (IData)((((VL_ULL(0xffffffffff0000) 
                                                   & (((QData)((IData)(
                                                                       vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U])) 
                                                       << 0x29U) 
                                                      | (VL_ULL(0xffffffffffff0000) 
                                                         & ((QData)((IData)(
                                                                            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U])) 
                                                            << 9U)))) 
                                                  | (QData)((IData)(
                                                                    ((0xffc0U 
                                                                      & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U] 
                                                                          << 0x11U) 
                                                                         | (0x1ffc0U 
                                                                            & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                                                               >> 0xfU)))) 
                                                                     | (0x3fU 
                                                                        & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                                                            << 0x1fU) 
                                                                           | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U] 
                                                                              >> 1U))))))) 
                                                 >> 0x20U)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[2U] 
        = ((0xffffffU & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                         >> 8U)) | (0xff000000U & ((IData)(
                                                           (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                                            >> 0x20U)) 
                                                   << 0x18U)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[3U] 
        = (0xffffffU & ((IData)((vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                 >> 0x20U)) >> 8U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1868__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1868__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1869__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1869__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0][0U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0][1U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0][2U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[2U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0][3U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[3U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1870__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1870__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1871__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1871__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1873__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1873__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1875__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1875__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1876__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1876__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1878__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1878__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1882__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1882__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1885__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1885__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1887__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1887__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1888__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1888__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0][0U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0][1U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0][2U] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[2U];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1889__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1889__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1890__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1890__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1892__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1892__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1896__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1896__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1897__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1897__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1898__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1898__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1900__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1900__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1902__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1902__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1904__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1904__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1906__PROF__mkMemServerIndicationOutputPipes__l949(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1906__PROF__mkMemServerIndicationOutputPipes__l949\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size 
        = (((0U == (IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937)) 
            | (2U == (IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937)))
            ? 0x40U : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937))
                        ? 0x80U : 0xc0U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1907__PROF__mkXsimTop__l2707(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1907__PROF__mkXsimTop__l2707\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_setFirstEnq 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1908__PROF__mkXsimTop__l2580(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1908__PROF__mkXsimTop__l2580\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outData_setFirstEnq 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outData_enqData_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1911__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1911__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1913__PROF__mkMMUSynth__l2330(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1913__PROF__mkMMUSynth__l2330\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1917__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1917__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1920__PROF__BRAM2__l80(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1920__PROF__BRAM2__l80\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1921__PROF__mkXsimTop__l2603(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1921__PROF__mkXsimTop__l2603\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_setFirstEnq 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_enqData_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1927__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1927__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1935__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1935__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1937__PROF__mkXsimTop__l6218(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1937__PROF__mkXsimTop__l6218\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1940__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1940__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1942__PROF__mkXsimTop__l6080(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1942__PROF__mkXsimTop__l6080\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1943__PROF__mkFromHostInput__l260(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1943__PROF__mkFromHostInput__l260\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1944__PROF__mkXsimTop__l4240(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1944__PROF__mkXsimTop__l4240\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_idResponse 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1945__PROF__mkXsimTop__l4397(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1945__PROF__mkXsimTop__l4397\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_idResponsePipe_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1946__PROF__mkXsimTop__l4248(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1946__PROF__mkXsimTop__l4248\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_error 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1947__PROF__mkXsimTop__l4405(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1947__PROF__mkXsimTop__l4405\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_errorPipe_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1948__PROF__mkMMURequestInput__l1484(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1948__PROF__mkMMURequestInput__l1484\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1949__PROF__mkMMUSynth__l1499(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1949__PROF__mkMMUSynth__l1499\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__CAN_FIRE_RL_mkConnectionGetPut_1 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1950__PROF__mkMMUSynth__l1552(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1950__PROF__mkMMUSynth__l1552\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1951__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1951__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__empty_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1952__PROF__mkXsimTop__l4291(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1952__PROF__mkXsimTop__l4291\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_sglist_PipeOut_deq 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_positive_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1953__PROF__mkXsimTop__l4378(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1953__PROF__mkXsimTop__l4378\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_sglist 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_positive_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1954__PROF__mkXsimTop__l2571(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1954__PROF__mkXsimTop__l2571\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_burst_remainder 
        = (((~ (IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_reader_readers_0_killv___05FETC___05F_d435)) 
            | ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__full_reg) 
               & (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt))))) 
           & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compCountReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1955__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1955__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect_ENQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__empty_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1956__PROF__mkMMURequestInput__l1505(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1956__PROF__mkMMURequestInput__l1505\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_0_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[0U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[1U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[2U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[3U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[3U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[4U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[4U];
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[0U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[1U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[2U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[3U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[4U] = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1957__PROF__mkXsimTop__l4244(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1957__PROF__mkXsimTop__l4244\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_configResp 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1958__PROF__mkXsimTop__l4401(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1958__PROF__mkXsimTop__l4401\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_configResponsePipe_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1959__PROF__mkMMUSynth__l1084(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1959__PROF__mkMMUSynth__l1084\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_region 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_positive_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1960__PROF__mkMMUSynth__l2060(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1960__PROF__mkMMUSynth__l2060\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ 
        = ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_1 
            >> 0x1dU) & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1961__PROF__mkMMUSynth__l2048(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1961__PROF__mkMMUSynth__l2048\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ 
        = ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_0 
            >> 0x1dU) & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1962__PROF__mkCnocTop__l886(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1962__PROF__mkCnocTop__l886\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_DEQ 
        = vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1963__PROF__mkMMUSynth__l1922(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1963__PROF__mkMMUSynth__l1922\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1964__PROF__mkXsimTop__l4959(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1964__PROF__mkXsimTop__l4959\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1965__PROF__mkXsimTop__l4976(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1965__PROF__mkXsimTop__l4976\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1966__PROF__mkXsimTop__l5122(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1966__PROF__mkXsimTop__l5122\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1967__PROF__mkCnocTop__l771(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1967__PROF__mkCnocTop__l771\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg) 
             & ((0U != (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_methodIdReg)) 
                | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg))) 
            & ((0U != (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_methodIdReg)) 
               | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1968__PROF__mkCnocTop__l765(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1968__PROF__mkCnocTop__l765\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader 
        = (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg) 
            & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_bpState))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1969__PROF__mkXsimTop__l2700(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1969__PROF__mkXsimTop__l2700\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg) 
           & (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_cnt))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1970__PROF__mkMMUSynth__l1994(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1970__PROF__mkMMUSynth__l1994\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1971__PROF__mkMMUSynth__l2019(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1971__PROF__mkMMUSynth__l2019\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1972__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1972__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1973__PROF__mkXsimTop__l2890(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1973__PROF__mkXsimTop__l2890\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__CAN_FIRE_RL_lMemServer_writer_writers_0_dmaError 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1974__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1974__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1975__PROF__mkXsimTop__l5013(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1975__PROF__mkXsimTop__l5013\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__sink_0_EN_beat = ((IData)(vlTOPp->mkXsimTop__DOT__sink_0__DOT__valid_reg) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1976__PROF__mkXsimTop__l5156(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1976__PROF__mkXsimTop__l5156\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__sink_0__DOT__valid_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1977__PROF__mkCnocTop__l780(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1977__PROF__mkCnocTop__l780\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_bpState)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1978__PROF__mkCnocTop__l785(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1978__PROF__mkCnocTop__l785\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessage 
        = (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg) 
            & ((0U != (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_methodIdReg)) 
               | (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg)))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1979__PROF__mkMMUSynth__l1902(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1979__PROF__mkMMUSynth__l1902\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ 
        = ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U] 
            >> 0x12U) & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1980__PROF__mkXsimTop__l4303(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1980__PROF__mkXsimTop__l4303\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idReturn_PipeOut_deq 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1981__PROF__mkXsimTop__l4390(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1981__PROF__mkXsimTop__l4390\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1982__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1982__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1983__PROF__mkMMUSynth__l1600(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1983__PROF__mkMMUSynth__l1600\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1984__PROF__mkXsimTop__l2822(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1984__PROF__mkXsimTop__l2822\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg) 
            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_bpState))) 
           & (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg) 
               | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1985__PROF__mkXsimTop__l2830(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1985__PROF__mkXsimTop__l2830\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg) 
            & (((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                 ? (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg)
                 : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                     ? (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)
                     : ((2U != (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg)) 
                        | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)))) 
               & ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                   ? (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg)
                   : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                       ? (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg)
                       : ((2U != (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg)) 
                          | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)))))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1986__PROF__mkXsimTop__l4260(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1986__PROF__mkXsimTop__l4260\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1987__PROF__mkXsimTop__l4539(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1987__PROF__mkXsimTop__l4539\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__sink_2__DOT__valid_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1988__PROF__mkXsimTop__l5020(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1988__PROF__mkXsimTop__l5020\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__sink_2_EN_beat = ((IData)(vlTOPp->mkXsimTop__DOT__sink_2__DOT__valid_reg) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1989__PROF__mkXsimTop__l2918(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1989__PROF__mkXsimTop__l2918\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_bpState)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1990__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1990__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1991__PROF__mkXsimTop__l5721(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1991__PROF__mkXsimTop__l5721\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((2U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)) {
        if ((2U & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT)) {
            vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq4 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq4 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1992__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1992__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1993__PROF__mkXsimTop__l4313(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1993__PROF__mkXsimTop__l4313\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__sink_1__DOT__valid_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1994__PROF__mkXsimTop__l5016(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1994__PROF__mkXsimTop__l5016\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__sink_1_EN_beat = ((IData)(vlTOPp->mkXsimTop__DOT__sink_1__DOT__valid_reg) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1995__PROF__mkXsimTop__l2836(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1995__PROF__mkXsimTop__l2836\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_bpState)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1996__PROF__mkXsimTop__l2841(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1996__PROF__mkXsimTop__l2841\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg) 
            & ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg))
                ? ((4U > (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count)) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg)))
                : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg))
                    ? ((0xcU > (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count)) 
                       | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg)))
                    : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg))
                        ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg))
                        : ((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg))
                            ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg))
                            : ((4U != (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)) 
                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count)) 
                                  | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg))))))))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1997__PROF__mkXsimTop__l5350(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1997__PROF__mkXsimTop__l5350\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__numWords___05Fh87584 = 
        (0xffffU & ((0x7ffU & ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size) 
                               >> 5U)) + ((0U == (0x1fU 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size)))
                                           ? 0U : 1U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1998__PROF__mkMMUIndicationOutputPipes__l744(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1998__PROF__mkMMUIndicationOutputPipes__l744\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count_D_IN 
        = ((5U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1999__PROF__mkMMUSynth__l1892(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1999__PROF__mkMMUSynth__l1892\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ 
        = ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U] 
            >> 0x12U) & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2000__PROF__mkMMUSynth__l1974(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2000__PROF__mkMMUSynth__l1974\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2001__PROF__mkMMUSynth__l2006(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2001__PROF__mkMMUSynth__l2006\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2002__PROF__mkMemServerRequestInput__l1111(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2002__PROF__mkMemServerRequestInput__l1111\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_0_enq) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff 
                = vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff = VL_ULL(0);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2003__PROF__mkXsimTop__l2929(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2003__PROF__mkXsimTop__l2929\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg)) 
           & ((0U != (0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                         >> 0x30U)))) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2004__PROF__mkXsimTop__l3600(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2004__PROF__mkXsimTop__l3600\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN 
        = ((2U != (3U & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT))) 
           & (1U != (3U & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2005__PROF__mkMemServerRequestInput__l1096(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2005__PROF__mkMemServerRequestInput__l1096\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2006__PROF__mkXsimTop__l2923(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2006__PROF__mkXsimTop__l2923\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg) 
            & ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg))
                ? ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count)) 
                   | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg)))
                : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg))
                    ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg))
                    : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg))
                        ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg))
                        : ((3U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg)) 
                           | (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg))))))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2007__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2007__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[0U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[1U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[2U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[1U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[3U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[2U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[4U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[3U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[5U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[4U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[6U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[5U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[7U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[6U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[8U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[7U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[9U] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[8U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[0xaU] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[9U];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[0xbU] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xaU];
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_D_OUT[0xcU] 
            = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xbU];
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2008__PROF__mkXsimTop__l2847(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2008__PROF__mkXsimTop__l2847\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg) 
            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_bpState))) 
           & ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg) 
                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)) 
               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2009__PROF__mkXsimTop__l2911(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2009__PROF__mkXsimTop__l2911\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg) 
             & ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                 ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg)
                 : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                     ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)
                     : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                         ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)
                         : ((3U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)) 
                            | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)))))) 
            & ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg)
                : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                    ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)
                    : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                        ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)
                        : ((3U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)) 
                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)))))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_bpState));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2010__PROF__mkXsimTop__l4501(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2010__PROF__mkXsimTop__l4501\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2011__PROF__mkXsimTop__l5024(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2011__PROF__mkXsimTop__l5024\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[0U] 
        = ((0xffffffc0U & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                           << 6U)) | (0x3fU & vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U]));
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[1U] 
        = ((0x3fU & ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_cycles) 
                     >> 0x1aU)) | (0xffffffc0U & ((IData)(
                                                          (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                                           >> 0x20U)) 
                                                  << 6U)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[2U] 
        = (0x3fU & ((IData)((vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                             >> 0x20U)) >> 0x1aU));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2012__PROF__mkXsimTop__l5412(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2012__PROF__mkXsimTop__l5412\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__writeLen___05F_2___05Fh95459 
        = ((0U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeLenReg))
            ? (0x7fU & ((vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                         << 0x17U) | (vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
                                      >> 9U))) : (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeLenReg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2013__PROF__mkXsimTop__l5389(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2013__PROF__mkXsimTop__l5389\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifoD_OUT_BITS_47_TO_16_P_ETC___05Fq5 
        = (((vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
             << 0x10U) | (vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[0U] 
                          >> 0x10U)) + vlTOPp->mkXsimTop__DOT__writeOffset___05Fh95460);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2014__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2014__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_head 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2015__PROF__mkXsimTop__l5360(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2015__PROF__mkXsimTop__l5360\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__readLen___05Fh93283 = (
                                                   (0U 
                                                    == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readLenReg))
                                                    ? 
                                                   (0x7fU 
                                                    & ((vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                                                        << 0x17U) 
                                                       | (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                                                          >> 9U)))
                                                    : (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readLenReg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2016__PROF__mkXsimTop__l5229(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2016__PROF__mkXsimTop__l5229\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__addr___05Fh93295 = (((vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                                                  << 0x10U) 
                                                 | (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                                                    >> 0x10U)) 
                                                + vlTOPp->mkXsimTop__DOT__readOffset___05Fh93284);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2017__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2017__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_head 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2018__PROF__mkXsimTop__l2659(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2018__PROF__mkXsimTop__l2659\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_valid_reg) 
              & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_valid_reg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)) 
           & (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_cnt))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2019__PROF__mkMMUSynth__l1821(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2019__PROF__mkMMUSynth__l1821\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_IN 
        = ((((0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                   >> 0x2dU)))) ? 5U
              : (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                               >> 0x30U)))) << 0x1bU) 
           | (0x7ffffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                    >> 0x15U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2020__PROF__mkMMUSynth__l1811(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2020__PROF__mkMMUSynth__l1811\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_IN 
        = ((((0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                   >> 0x2dU)))) ? 5U
              : (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                               >> 0x30U)))) << 0x1bU) 
           | (0x7ffffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                    >> 0x15U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2021__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2021__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2022__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2022__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2023__PROF__mkXsimTop__l2987(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2023__PROF__mkXsimTop__l2987\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut 
        = (((7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt))) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2024__PROF__mkMemServerIndicationOutputPipes__l1107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2024__PROF__mkMemServerIndicationOutputPipes__l1107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count_D_IN 
        = ((5U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2025__PROF__mkMMUSynth__l1928(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2025__PROF__mkMMUSynth__l1928\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2026__PROF__mkMMUSynth__l2126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2026__PROF__mkMMUSynth__l2126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__t___05Fh1387 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)
            ? (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags 
               & (~ ((IData)(1U) << (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__data0_reg))))
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2027__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2027__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_head 
        = ((0x94U == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))
            ? 0U : (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2028__PROF__mkXsimTop__l4999(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2028__PROF__mkXsimTop__l4999\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2029__PROF__mkXsimTop__l5395(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2029__PROF__mkXsimTop__l5395\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__t___05Fh49481 = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)
                                              ? (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags 
                                                 & (~ 
                                                    ((IData)(1U) 
                                                     << (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__data0_reg))))
                                              : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2030__PROF__mkMemServerIndicationOutputPipes__l1166(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2030__PROF__mkMemServerIndicationOutputPipes__l1166\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count_D_IN 
        = ((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count))
            ? 0U : (3U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2031__PROF__mkMemServerIndicationOutputPipes__l1136(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2031__PROF__mkMemServerIndicationOutputPipes__l1136\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count_D_IN 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2032__PROF__mkXsimTop__l4752(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2032__PROF__mkXsimTop__l4752\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[0U] 
        = ((0xffffff80U & ((IData)((VL_ULL(0xffffffffff) 
                                    & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg)) 
                           << 7U)) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__data0_reg) 
                                       << 1U) | (1U 
                                                 & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U])));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[1U] 
        = ((0x7fU & ((IData)((VL_ULL(0xffffffffff) 
                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg)) 
                     >> 0x19U)) | (0xffffff80U & ((0xffff8000U 
                                                   & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                                                      << 0xeU)) 
                                                  | ((IData)(
                                                             ((VL_ULL(0xffffffffff) 
                                                               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg) 
                                                              >> 0x20U)) 
                                                     << 7U))));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[2U] 
        = ((0x7fU & ((0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                               >> 0x12U)) | ((IData)(
                                                     ((VL_ULL(0xffffffffff) 
                                                       & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg) 
                                                      >> 0x20U)) 
                                             >> 0x19U))) 
           | (0xffffff80U & ((0x7f80U & ((0x4000U & 
                                          (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                                           << 0xeU)) 
                                         | (0x3f80U 
                                            & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[0U] 
                                               >> 0x12U)))) 
                             | (0xffff8000U & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                                               << 0xeU)))));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[3U] 
        = ((0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                     >> 0x12U)) | (0xffffff80U & ((0x7f80U 
                                                   & ((0x4000U 
                                                       & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
                                                          << 0xeU)) 
                                                      | (0x3f80U 
                                                         & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[1U] 
                                                            >> 0x12U)))) 
                                                  | (0xffff8000U 
                                                     & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
                                                        << 0xeU)))));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[4U] 
        = (0x7fU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
                    >> 0x12U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2033__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2033__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_head 
        = ((7U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head))
            ? 0U : (7U & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2034__PROF__mkXsimTop__l4787(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2034__PROF__mkXsimTop__l4787\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_DEQ 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2035__PROF__mkXsimTop__l5391(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2035__PROF__mkXsimTop__l5391\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__t___05Fh10829 = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)
                                              ? (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags 
                                                 & (~ 
                                                    ((IData)(1U) 
                                                     << (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__data0_reg))))
                                              : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2036__PROF__mkMMUSynth__l1596(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2036__PROF__mkMMUSynth__l1596\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2037__PROF__mkXsimTop__l4690(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2037__PROF__mkXsimTop__l4690\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[0U] 
        = ((0xffffff80U & ((IData)((((QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg)) 
                                     << 0x20U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg)))) 
                           << 7U)) | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[1U] 
        = ((0x7fU & ((IData)((((QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg)) 
                               << 0x20U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg)))) 
                     >> 0x19U)) | (0xffffff80U & ((IData)(
                                                          ((((QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg)) 
                                                             << 0x20U) 
                                                            | (QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg))) 
                                                           >> 0x20U)) 
                                                  << 7U)));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[2U] 
        = (0x7fU & ((IData)(((((QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg)) 
                               << 0x20U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg))) 
                             >> 0x20U)) >> 0x19U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2038__PROF__mkMemServerIndicationOutputPipes__l1077(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2038__PROF__mkMemServerIndicationOutputPipes__l1077\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count_D_IN 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2039__PROF__mkXsimTop__l5353(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2039__PROF__mkXsimTop__l5353\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__numWords___05Fh89404 = 
        (0xffffU & ((0x7ffU & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size) 
                               >> 5U)) + ((0U == (0x1fU 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes_portalIfc_messageSize_size)))
                                           ? 0U : 1U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2040__PROF__mkMMUSynth__l1089(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2040__PROF__mkMMUSynth__l1089\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_idRequest 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2041__PROF__mkMMUSynth__l1689(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2041__PROF__mkMMUSynth__l1689\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited_EN 
        = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2042__PROF__mkMMUSynth__l1590(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2042__PROF__mkMMUSynth__l1590\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_positive_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2043__PROF__mkMMUSynth__l1681(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2043__PROF__mkMMUSynth__l1681\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2044__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2044__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__full_reg = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__full_reg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2045__PROF__mkXsimTop__l5225(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2045__PROF__mkXsimTop__l5225\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh90027 
        = (0xffU & ((1U == (0xffU & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg))
                     ? vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg
                     : (vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2046__PROF__mkXsimTop__l3219(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2046__PROF__mkXsimTop__l3219\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_outData_wget 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_setFirstEnq)
            ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__DOB_R
            : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_D_OUT);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2047__PROF__mkXsimTop__l3773(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2047__PROF__mkXsimTop__l3773\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2048__PROF__mkXsimTop__l3977(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2048__PROF__mkXsimTop__l3977\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr_D_IN 
        = ((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate))
            ? (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr)))
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2049__PROF__mkXsimTop__l2744(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2049__PROF__mkXsimTop__l2744\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l253c10 
        = ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr)) 
           & ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)) 
              | (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2050__PROF__mkXsimTop__l5316(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2050__PROF__mkXsimTop__l5316\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_abort_whas___05F14_AN_ETC___05F_d970 
        = (((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)) 
            | (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate))) 
           & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg_1)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_fired)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2051__PROF__mkXsimTop__l3844(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2051__PROF__mkXsimTop__l3844\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr_D_IN 
        = ((3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate))
            ? (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr)))
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2052__PROF__mkXsimTop__l2653(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2052__PROF__mkXsimTop__l2653\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l169c10 
        = ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr)) 
           & ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate)) 
              | (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2053__PROF__mkXsimTop__l2875(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2053__PROF__mkXsimTop__l2875\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l173c17 
        = (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)) 
            & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficPtr))) 
           & ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate)) 
              | (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2054__PROF__mkXsimTop__l5303(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2054__PROF__mkXsimTop__l5303\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_abort_whas___05F27_AN_ETC___05F_d585 
        = (((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate)) 
            | (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_mkFSMstate))) 
           & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg_1)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_state_fired)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2055__PROF__mkXsimTop__l3903(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2055__PROF__mkXsimTop__l3903\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr_D_IN 
        = ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate))
            ? (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr)))
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2056__PROF__mkXsimTop__l5308(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2056__PROF__mkXsimTop__l5308\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_abort_whas___05F46_AND_lM_ETC___05F_d908 
        = ((((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)) 
             | ((0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr)) 
                & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)))) 
            | ((0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr)) 
               & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)))) 
           & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg_1)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_fired)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2057__PROF__mkXsimTop__l3515(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2057__PROF__mkXsimTop__l3515\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr_D_IN 
        = ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate))
            ? (0xffU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr)))
            : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2058__PROF__mkXsimTop__l2868(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2058__PROF__mkXsimTop__l2868\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_action_l158c10 
        = (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)) 
            & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr))) 
           & ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate)) 
              | (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2059__PROF__mkXsimTop__l5238(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2059__PROF__mkXsimTop__l5238\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_abort_whas___05F59_AND_lM_ETC___05F_d521 
        = ((((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate)) 
             | ((0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr)) 
                & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate)))) 
            | ((0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgPtr)) 
               & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_mkFSMstate)))) 
           & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg_1)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_state_fired)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2060__PROF__mkXsimTop__l4155(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2060__PROF__mkXsimTop__l4155\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited_EN 
        = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2061__PROF__mkXsimTop__l4994(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2061__PROF__mkXsimTop__l4994\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
             & (VL_ULL(0x96) <= (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                 - (((QData)((IData)(
                                                     vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U])) 
                                     << 0x3aU) | (((QData)((IData)(
                                                                   vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U])) 
                                                   << 0x1aU) 
                                                  | ((QData)((IData)(
                                                                     vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U])) 
                                                     >> 6U)))))) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2062__PROF__mkXsimTop__l5029(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2062__PROF__mkXsimTop__l5029\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ = (
                                                   (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                     & (VL_ULL(0x96) 
                                                        <= 
                                                        (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                                         - 
                                                         (((QData)((IData)(
                                                                           vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[2U])) 
                                                           << 0x3aU) 
                                                          | (((QData)((IData)(
                                                                              vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[1U])) 
                                                              << 0x1aU) 
                                                             | ((QData)((IData)(
                                                                                vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_OUT[0U])) 
                                                                >> 6U)))))) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2063__PROF__mkXsimTop__l3296(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2063__PROF__mkXsimTop__l3296\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_inited)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_positive_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2064__PROF__mkXsimTop__l4144(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2064__PROF__mkXsimTop__l4144\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2065__PROF__mkXsimTop__l3764(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2065__PROF__mkXsimTop__l3764\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited_EN 
        = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2066__PROF__mkXsimTop__l3264(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2066__PROF__mkXsimTop__l3264\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_inited)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_positive_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2067__PROF__mkXsimTop__l3753(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2067__PROF__mkXsimTop__l3753\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr_D_IN 
        = (0x1fU & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2068__PROF__mkMMUSynth__l1554(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2068__PROF__mkMMUSynth__l1554\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_2 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__CAN_FIRE_RL_mkConnectionGetPut_1) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2069__PROF__mkMMUSynth__l1756(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2069__PROF__mkMMUSynth__l1756\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1) 
           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__CAN_FIRE_RL_mkConnectionGetPut_1));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2071__PROF__mkXsimTop__l3324(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2071__PROF__mkXsimTop__l3324\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas)) 
            & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_setFirstEnq) 
               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata))) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__full_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2072__PROF__mkMMUSynth__l1508(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2072__PROF__mkMMUSynth__l1508\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_positive_reg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full)) 
            & ((0U != (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                     >> 0x2dU)))) | 
               (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg)))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_sglist)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2075__PROF__mkXsimTop__l4295(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2075__PROF__mkXsimTop__l4295\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_region_PipeOut_deq 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_region) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2076__PROF__mkXsimTop__l4382(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2076__PROF__mkXsimTop__l4382\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_region) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2077__PROF__mkCnocTop__l873(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2077__PROF__mkCnocTop__l873\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput_EN_portalIfc_indications_0_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2078__PROF__mkCnocTop__l838(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2078__PROF__mkCnocTop__l838\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader)
            ? 1U : (0xffffU & ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg) 
                               - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2079__PROF__mkCnocTop__l883(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2079__PROF__mkCnocTop__l883\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader) 
           | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2080__PROF__mkCnocTop__l879(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2080__PROF__mkCnocTop__l879\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader)
            ? (2U | (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg)
                       ? 0U : 0xffU) << 0x10U)) : vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_bits);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2083__PROF__mkCnocTop__l815(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2083__PROF__mkCnocTop__l815\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg_D_IN 
        = (0xffU & ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader)
                     ? (IData)(vlTOPp->mkXsimTop__DOT__top__DOT___theResult___05F___05Fh1407)
                     : ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg) 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2084__PROF__mkCnocTop__l855(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2084__PROF__mkCnocTop__l855\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput_EN_portalIfc_requests_0_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2085__PROF__mkCnocTop__l864(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2085__PROF__mkCnocTop__l864\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessage) 
           | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2087__PROF__mkXsimTop__l2863(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2087__PROF__mkXsimTop__l2863\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError 
        = ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2088__PROF__mkXsimTop__l4231(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2088__PROF__mkXsimTop__l4231\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_0_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2089__PROF__mkXsimTop__l4234(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2089__PROF__mkXsimTop__l4234\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_1_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2090__PROF__mkXsimTop__l4257(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2090__PROF__mkXsimTop__l4257\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2091__PROF__mkXsimTop__l4237(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2091__PROF__mkXsimTop__l4237\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendMessage) 
           & (2U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2093__PROF__mkXsimTop__l2750(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2093__PROF__mkXsimTop__l2750\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)) 
           & (((~ (IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786)) 
               | (IData)(vlTOPp->mkXsimTop__DOT__CASE_lMemServer_writer_writers_0_serverProcess_ETC___05Fq4)) 
              & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg)) 
                 | (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_cnt))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2095__PROF__mkXsimTop__l4282(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2095__PROF__mkXsimTop__l4282\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_2_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           & (2U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2096__PROF__mkXsimTop__l4285(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2096__PROF__mkXsimTop__l4285\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_3_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2097__PROF__mkXsimTop__l4315(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2097__PROF__mkXsimTop__l4315\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2098__PROF__mkXsimTop__l4276(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2098__PROF__mkXsimTop__l4276\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_0_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2099__PROF__mkXsimTop__l4288(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2099__PROF__mkXsimTop__l4288\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_4_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           & (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2100__PROF__mkXsimTop__l3380(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2100__PROF__mkXsimTop__l3380\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg_D_IN 
        = (0xffffU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader)
                       ? (IData)(vlTOPp->mkXsimTop__DOT__numWords___05Fh87584)
                       : ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_messageWordsReg) 
                          - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2101__PROF__mkXsimTop__l4253(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2101__PROF__mkXsimTop__l4253\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader)
            ? (((IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh87211) 
                << 0x10U) | (0xffffU & ((IData)(1U) 
                                        + (IData)(vlTOPp->mkXsimTop__DOT__numWords___05Fh87584))))
            : ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_bits
                : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                    ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_bits
                    : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg))
                        ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U]
                        : 0xaaaaaaaaU))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2103__PROF__mkXsimTop__l4423(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2103__PROF__mkXsimTop__l4423\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
           & (0U == (0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                        >> 0x30U)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2104__PROF__mkXsimTop__l4519(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2104__PROF__mkXsimTop__l4519\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_1_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2105__PROF__mkXsimTop__l4522(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2105__PROF__mkXsimTop__l4522\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_2_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
           & (2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2106__PROF__mkXsimTop__l4525(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2106__PROF__mkXsimTop__l4525\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_3_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
           & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2107__PROF__mkXsimTop__l4541(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2107__PROF__mkXsimTop__l4541\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2108__PROF__mkXsimTop__l4516(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2108__PROF__mkXsimTop__l4516\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_0_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2110__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2110__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2112__PROF__mkXsimTop__l4498(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2112__PROF__mkXsimTop__l4498\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2113__PROF__mkXsimTop__l4470(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2113__PROF__mkXsimTop__l4470\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2114__PROF__mkXsimTop__l4467(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2114__PROF__mkXsimTop__l4467\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2115__PROF__mkXsimTop__l4473(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2115__PROF__mkXsimTop__l4473\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
           & (2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2116__PROF__mkXsimTop__l4476(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2116__PROF__mkXsimTop__l4476\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendMessage) 
           & (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2117__PROF__mkXsimTop__l2541(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2117__PROF__mkXsimTop__l2541\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
              & (VL_ULL(0x96) <= (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                                  - (((QData)((IData)(
                                                      vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[3U])) 
                                      << 0x28U) | (
                                                   ((QData)((IData)(
                                                                    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U])) 
                                                    << 8U) 
                                                   | ((QData)((IData)(
                                                                      vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U])) 
                                                      >> 0x18U)))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata)) 
           & ((1U != (IData)(vlTOPp->mkXsimTop__DOT__writeLen___05F_2___05Fh95459)) 
              | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2118__PROF__mkXsimTop__l5108(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2118__PROF__mkXsimTop__l5108\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo_D_IN 
        = ((0x7eU & (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[0U] 
                     << 1U)) | (1U == (IData)(vlTOPp->mkXsimTop__DOT__readLen___05Fh93283)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2119__PROF__mkXsimTop__l2977(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2119__PROF__mkXsimTop__l2977\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule 
        = (((((((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_valid_reg)) 
                & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_valid_reg))) 
               | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
              & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata)) 
           & (VL_ULL(0x96) <= (vlTOPp->mkXsimTop__DOT__slave_2_0_cycles 
                               - (((QData)((IData)(
                                                   vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[3U])) 
                                   << 0x28U) | (((QData)((IData)(
                                                                 vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U])) 
                                                 << 8U) 
                                                | ((QData)((IData)(
                                                                   vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U])) 
                                                   >> 0x18U))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2121__PROF__mkMMUSynth__l1593(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2121__PROF__mkMMUSynth__l1593\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__empty_reg) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_0_positive_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2122__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2122__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2123__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2123__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2124__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2124__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2125__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2125__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2126__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2126__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2128__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2128__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2129__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2129__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2130__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2130__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr[vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0] 
            = vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2131__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2131__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2132__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2132__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata 
        = vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2133__PROF__mkXsimTop__l2564(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2133__PROF__mkXsimTop__l2564\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg) 
             & (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt)))) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2134__PROF__mkMMUSynth__l2124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2134__PROF__mkMMUSynth__l2124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags_port1___05Fread___05F2_BIT_sglId_gen_ta_ETC___05F_d14 
        = (1U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__t___05Fh1387 
                 >> (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2135__PROF__mkXsimTop__l5342(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2135__PROF__mkXsimTop__l5342\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags_port1_ETC___05F_d707 
        = (1U & (vlTOPp->mkXsimTop__DOT__t___05Fh49481 
                 >> (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2136__PROF__mkXsimTop__l5301(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2136__PROF__mkXsimTop__l5301\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags_port1_ETC___05F_d297 
        = (1U & (vlTOPp->mkXsimTop__DOT__t___05Fh10829 
                 >> (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tail_ptr)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2137__PROF__mkXsimTop__l3426(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2137__PROF__mkXsimTop__l3426\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg_D_IN 
        = (0xffffU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader)
                       ? (IData)(vlTOPp->mkXsimTop__DOT__numWords___05Fh89404)
                       : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_messageWordsReg) 
                          - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2138__PROF__mkXsimTop__l4494(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2138__PROF__mkXsimTop__l4494\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader)
            ? (((IData)(vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937) 
                << 0x10U) | (0xffffU & ((IData)(1U) 
                                        + (IData)(vlTOPp->mkXsimTop__DOT__numWords___05Fh89404))))
            : ((0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                ? (IData)((vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits 
                           >> 0x20U)) : ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                                          ? vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[3U]
                                          : ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                                              ? (IData)(
                                                        (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits 
                                                         >> 0x20U))
                                              : ((3U 
                                                  == (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg))
                                                  ? 
                                                 vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U]
                                                  : 0xaaaaaaaaU)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2139__PROF__mkXsimTop__l4299(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2139__PROF__mkXsimTop__l4299\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idRequest_PipeOut_deq 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_idRequest) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2140__PROF__mkXsimTop__l4386(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2140__PROF__mkXsimTop__l4386\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_RDY_request_idRequest) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2142__PROF__mkXsimTop__l2856(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2142__PROF__mkXsimTop__l2856\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry 
        = (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__empty_reg)) 
           & ((0U != (0xffffU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__data0_reg 
                                 >> 0x10U))) | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2143__PROF__mkXsimTop__l3450(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2143__PROF__mkXsimTop__l3450\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg_D_IN 
        = (0xffU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader)
                     ? (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh90027)
                     : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_messageWordsReg) 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2144__PROF__mkXsimTop__l5734(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2144__PROF__mkXsimTop__l5734\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_reader_readers_0_killv___05FETC___05F_d415 
        = (1U & ((0x800000U & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_outData_wget)
                  ? ((0x400000U & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_outData_wget)
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_3))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_2)))
                  : ((0x400000U & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_outData_wget)
                      ? (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_1))
                      : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2145__PROF__mkXsimTop__l3912(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2145__PROF__mkXsimTop__l3912\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l253c10)
            ? (vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum 
               + (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount)))
            : VL_ULL(0));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2146__PROF__mkXsimTop__l3779(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2146__PROF__mkXsimTop__l3779\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l169c10)
            ? (vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum 
               + (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount)))
            : VL_ULL(0));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2147__PROF__mkXsimTop__l2903(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2147__PROF__mkXsimTop__l2903\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l257c17 
        = ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_notEmptyReg)) 
             & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficPtr))) 
            & ((2U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)) 
               | (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_state_mkFSMstate)))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l173c17)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2148__PROF__mkXsimTop__l2949(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2148__PROF__mkXsimTop__l2949\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg) 
           & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo_D_OUT)
               ? ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_abort_whas___05F14_AN_ETC___05F_d970) 
                  & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg)))
               : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_abort_whas___05F27_AN_ETC___05F_d585) 
                  & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2149__PROF__mkXsimTop__l2895(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2149__PROF__mkXsimTop__l2895\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10 
        = ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_notEmptyReg)) 
             & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgPtr))) 
            & ((1U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)) 
               | (3U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_state_mkFSMstate)))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_action_l158c10)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2150__PROF__mkXsimTop__l2943(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2150__PROF__mkXsimTop__l2943\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg) 
           & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo_D_OUT)
               ? ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_abort_whas___05F46_AND_lM_ETC___05F_d908) 
                  & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg)))
               : ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_abort_whas___05F59_AND_lM_ETC___05F_d521) 
                  & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2151__PROF__mkXsimTop__l5326(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2151__PROF__mkXsimTop__l5326\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAd_ETC___05F_d672 
        = (7U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_cnt) 
                  + ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways)
                      ? 1U : 0U)) + ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas)
                                      ? 7U : 0U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2152__PROF__mkXsimTop__l2712(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2152__PROF__mkXsimTop__l2712\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqAndDeq 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas)) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2153__PROF__mkMMUSynth__l2031(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2153__PROF__mkMMUSynth__l2031\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_DIA 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)
            ? 0xaaaaaaaU : (0xfffffffU & vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[1U]));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2154__PROF__mkMMUSynth__l2039(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2154__PROF__mkMMUSynth__l2039\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ENA 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_sglist));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2155__PROF__mkMMUSynth__l2025(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2155__PROF__mkMMUSynth__l2025\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ADDRA 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)
            ? ((0x1f00U & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg) 
                           << 8U)) | ((0U == (7U & (IData)(
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                                            >> 0x2dU))))
                                       ? 0U : (0xffU 
                                               & ((IData)(
                                                          (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                                           >> 0xdU)) 
                                                  + (IData)(
                                                            (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                                             >> 5U))))))
            : ((0x1f00U & (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[4U] 
                           << 8U)) | (0xffU & vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[3U])));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2156__PROF__mkMMUSynth__l2130(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2156__PROF__mkMMUSynth__l2130\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_cnt_08_PLUS_I_ETC___05F_d116 
        = (3U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_cnt) 
                  + ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)
                      ? 1U : 0U)) - ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)
                                      ? 1U : 0U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2157__PROF__mkMMUSynth__l1522(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2157__PROF__mkMMUSynth__l1522\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_positive_reg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full)) 
            & ((0U != (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                     >> 0x2dU)))) | 
               (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg)))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2158__PROF__mkMMUSynth__l1511(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2158__PROF__mkMMUSynth__l1511\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_positive_reg)) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2159__PROF__mkXsimTop__l3018(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2159__PROF__mkXsimTop__l3018\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2 
        = ((IData)(vlTOPp->mkXsimTop__DOT__CAN_FIRE_RL_lMemServer_writer_writers_0_dmaError) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2160__PROF__mkXsimTop__l4488(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2160__PROF__mkXsimTop__l4488\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_error 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError) 
           | (IData)(vlTOPp->mkXsimTop__DOT__CAN_FIRE_RL_lMemServer_writer_writers_0_dmaError));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2161__PROF__mkMMUIndicationOutputPipes__l710(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2161__PROF__mkMMUIndicationOutputPipes__l710\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq) 
           & (5U != (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2162__PROF__mkXsimTop__l3281(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2162__PROF__mkXsimTop__l3281\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_writeWithResp_whas 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2163__PROF__mkXsimTop__l4963(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2163__PROF__mkXsimTop__l4963\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
           & (IData)(vlTOPp->mkXsimTop__DOT__IF_lMemServer_writer_writers_0_firstReg_93_THE_ETC___05F_d818));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2164__PROF__mkXsimTop__l4863(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2164__PROF__mkXsimTop__l4863\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
            & (~ (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                  >> 1U))) & (IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2165__PROF__mkXsimTop__l4875(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2165__PROF__mkXsimTop__l4875\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
            & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
               >> 1U)) & (IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_writer_writers_0_killv___05FETC___05F_d786));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2166__PROF__mkMMURequestInput__l1492(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2166__PROF__mkMMURequestInput__l1492\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_0_enq) 
           & (4U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2167__PROF__mkMMURequestInput__l1481(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2167__PROF__mkMMURequestInput__l1481\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_4_enq) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2168__PROF__mkMemServerRequestInput__l1054(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2168__PROF__mkMemServerRequestInput__l1054\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff_D_IN 
        = (((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fbnbuff)) 
            << 0x20U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2169__PROF__mkMemServerRequestInput__l1079(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2169__PROF__mkMemServerRequestInput__l1079\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_0_enq) 
           & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2170__PROF__mkMMURequestInput__l1450(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2170__PROF__mkMMURequestInput__l1450\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[0U] 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[1U] 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[0U];
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[2U] 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[1U];
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[3U] 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[2U];
    vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff_D_IN[4U] 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fbnbuff[3U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2171__PROF__mkXsimTop__l5221(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2171__PROF__mkXsimTop__l5221\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh88187 
        = (0xffU & ((1U == (0xffU & vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg))
                     ? vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg
                     : (vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2172__PROF__mkMMURequestInput__l1505(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2172__PROF__mkMMURequestInput__l1505\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_1_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[1U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[2U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[3U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[3U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[4U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[4U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[5U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[5U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[6U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[6U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[7U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[7U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[8U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[8U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[9U] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[9U];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xaU] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[0xaU];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xbU] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[0xbU];
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xcU] 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff_D_IN[0xcU];
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[1U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[2U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[3U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[4U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[5U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[6U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[7U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[8U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[9U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xaU] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xbU] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fbnbuff[0xcU] = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2173__PROF__mkMemServerIndicationOutputPipes__l1051(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2173__PROF__mkMemServerIndicationOutputPipes__l1051\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportStateDbg_responseAdapter_bits_write_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq) 
           & (3U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2174__PROF__mkMemServerIndicationOutputPipes__l1033(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2174__PROF__mkMemServerIndicationOutputPipes__l1033\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_addrResponse_responseAdapter_bits_write_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2175__PROF__mkMemServerIndicationOutputPipes__l1045(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2175__PROF__mkMemServerIndicationOutputPipes__l1045\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportMemoryTraffic_responseAdapter_bits_write_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2176__PROF__mkMemServerIndicationOutputPipes__l1039(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2176__PROF__mkMemServerIndicationOutputPipes__l1039\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq) 
           & (5U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2177__PROF__mkXsimTop__l5026(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2177__PROF__mkXsimTop__l5026\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                                                   & (1U 
                                                      == (IData)(vlTOPp->mkXsimTop__DOT__writeLen___05F_2___05Fh95459)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2178__PROF__mkXsimTop__l5126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2178__PROF__mkXsimTop__l5126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__writeLen___05F_2___05Fh95459)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2179__PROF__mkXsimTop__l5043(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2179__PROF__mkXsimTop__l5043\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__readLen___05Fh93283)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2180__PROF__mkMMUSynth__l1959(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2180__PROF__mkMMUSynth__l1959\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp282[3];
    // Body
    __Vtemp282[2U] = ((0xffff8000U & (((0xfffffU & (IData)(
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                                                            >> 0x14U))) 
                                       < (0xfffffU 
                                          & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
                                              << 0x10U) 
                                             | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
                                                >> 0x10U)))) 
                                      << 0xfU)) | (
                                                   (0xffffc000U 
                                                    & (((0xffffffU 
                                                         & (IData)(
                                                                   (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                                                                    >> 0x10U))) 
                                                        < 
                                                        (0xffffffU 
                                                         & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
                                                             << 0x14U) 
                                                            | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
                                                               >> 0xcU)))) 
                                                       << 0xeU)) 
                                                   | ((0xffffe000U 
                                                       & (((0xfffffffU 
                                                            & (IData)(
                                                                      (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                                                                       >> 0xcU))) 
                                                           < 
                                                           (0xfffffffU 
                                                            & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
                                                                << 0x18U) 
                                                               | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U] 
                                                                  >> 8U)))) 
                                                          << 0xdU)) 
                                                      | (0x1fffU 
                                                         & ((0x1fe0U 
                                                             & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
                                                                >> 7U)) 
                                                            | (0x1fU 
                                                               & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
                                                                  >> 0xbU)))))));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[0U] 
        = (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[1U] 
        = ((0xffffe000U & ((0xe0000000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
                                           << 0x15U)) 
                           | ((0x1fe00000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
                                              << 0x11U)) 
                              | (0x1fe000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U] 
                                              << 0xdU))))) 
           | (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                      >> 0x20U)));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[2U] 
        = ((0xffff0000U & (((0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0_D_OUT 
                                                >> 0x18U))) 
                            < (0xffffU & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
                                           << 0xcU) 
                                          | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
                                             >> 0x14U)))) 
                           << 0x10U)) | __Vtemp282[2U]);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2181__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2181__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2182__PROF__mkMMUSynth__l1541(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2182__PROF__mkMMUSynth__l1541\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
           & ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg) 
              & ((0x10000U & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U])
                  ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)
                  : (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg)))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2183__PROF__mkMMUSynth__l1979(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2183__PROF__mkMMUSynth__l1979\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp287[3];
    // Body
    __Vtemp287[2U] = ((0xffff8000U & (((0xfffffU & (IData)(
                                                           (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                                                            >> 0x14U))) 
                                       < (0xfffffU 
                                          & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[3U] 
                                              << 0x10U) 
                                             | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U] 
                                                >> 0x10U)))) 
                                      << 0xfU)) | (
                                                   (0xffffc000U 
                                                    & (((0xffffffU 
                                                         & (IData)(
                                                                   (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                                                                    >> 0x10U))) 
                                                        < 
                                                        (0xffffffU 
                                                         & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U] 
                                                             << 0x14U) 
                                                            | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[1U] 
                                                               >> 0xcU)))) 
                                                       << 0xeU)) 
                                                   | ((0xffffe000U 
                                                       & (((0xfffffffU 
                                                            & (IData)(
                                                                      (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                                                                       >> 0xcU))) 
                                                           < 
                                                           (0xfffffffU 
                                                            & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[1U] 
                                                                << 0x18U) 
                                                               | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[0U] 
                                                                  >> 8U)))) 
                                                          << 0xdU)) 
                                                      | (0x1fffU 
                                                         & ((0x1fe0U 
                                                             & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[3U] 
                                                                >> 7U)) 
                                                            | (0x1fU 
                                                               & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U] 
                                                                  >> 0xbU)))))));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[0U] 
        = (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[1U] 
        = ((0xffffe000U & ((0xe0000000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U] 
                                           << 0x15U)) 
                           | ((0x1fe00000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[1U] 
                                              << 0x11U)) 
                              | (0x1fe000U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[0U] 
                                              << 0xdU))))) 
           | (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                      >> 0x20U)));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[2U] 
        = ((0xffff0000U & (((0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1_D_OUT 
                                                >> 0x18U))) 
                            < (0xffffU & ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[4U] 
                                           << 0xcU) 
                                          | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[3U] 
                                             >> 0x14U)))) 
                           << 0x10U)) | __Vtemp287[2U]);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2184__PROF__SizedFIFO__l78(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2184__PROF__SizedFIFO__l78\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_head 
        = (1U & ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head)) 
                 & ((IData)(1U) + (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2185__PROF__mkXsimTop__l3235(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2185__PROF__mkXsimTop__l3235\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_writeWithResp_whas 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2186__PROF__mkXsimTop__l4707(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2186__PROF__mkXsimTop__l4707\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_DIB 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
            ? 0xaaaaaaU : ((0xfc0000U & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                         << 3U)) | 
                           ((0x3ff00U & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U] 
                                          << 0x13U) 
                                         | (0x7ff00U 
                                            & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                               >> 0xdU)))) 
                            | ((0xfeU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U] 
                                         << 1U)) | 
                               (8U == (0x3ffU & ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U] 
                                                  << 0xbU) 
                                                 | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                                                    >> 0x15U))))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2187__PROF__mkXsimTop__l4701(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2187__PROF__mkXsimTop__l4701\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_ADDRB 
        = (0x1fU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                     ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__data0_reg)
                     : ((vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
                         << 0x1fU) | (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U] 
                                      >> 1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2188__PROF__mkXsimTop__l3226(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2188__PROF__mkXsimTop__l3226\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt_1_whas 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
            | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
           & ((~ (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                    ? 0U : 2U) >> 1U)) | ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)
                                           ? 0U : 2U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2189__PROF__mkMMUSynth__l1534(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2189__PROF__mkMMUSynth__l1534\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_sglId_gen_complete_rule1 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags_port1___05Fread___05F2_BIT_sglId_gen_ta_ETC___05F_d14) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg)) 
            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_state) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2190__PROF__mkXsimTop__l2719(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2190__PROF__mkXsimTop__l2719\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_tag_gen_complete_rule1 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags_port1_ETC___05F_d707) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg)) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_state) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2191__PROF__mkXsimTop__l2628(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2191__PROF__mkXsimTop__l2628\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_gen_complete_rule1 
        = ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags_port1_ETC___05F_d297) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg)) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_state) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2192__PROF__mkXsimTop__l2882(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2192__PROF__mkXsimTop__l2882\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry 
        = ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_notEmptyReg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg)) 
            & ((0U != (0xffffU & (vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data0_reg 
                                  >> 0x10U))) | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2193__PROF__mkXsimTop__l2559(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2193__PROF__mkXsimTop__l2559\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)) 
            & ((0U != (0xffffU & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest_D_OUT[2U] 
                                  >> 9U))) | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_D_OUT)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg)) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata)))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2194__PROF__mkXsimTop__l2608(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2194__PROF__mkXsimTop__l2608\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a 
        = (((((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata) 
              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_enqData_whas)) 
             & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_setFirstEnq) 
                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata))) 
            & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg) 
               & ((~ (IData)(vlTOPp->mkXsimTop__DOT__SEL_ARR_NOT_lMemServer_reader_readers_0_killv___05FETC___05F_d415)) 
                  | ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__full_reg) 
                     & (7U > (4U ^ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt))))))) 
           & (0U == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compCountReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2195__PROF__mkXsimTop__l4485(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2195__PROF__mkXsimTop__l4485\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportMemoryTraffic 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l173c17) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l257c17));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2196__PROF__mkXsimTop__l2669(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2196__PROF__mkXsimTop__l2669\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_fsm_start 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_abort_whas___05F27_AN_ETC___05F_d585) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficFSM_start_reg)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2197__PROF__mkXsimTop__l2756(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2197__PROF__mkXsimTop__l2756\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_fsm_start 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_abort_whas___05F14_AN_ETC___05F_d970) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficFSM_start_reg)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2198__PROF__mkXsimTop__l4482(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2198__PROF__mkXsimTop__l4482\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportStateDbg 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10) 
           | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_action_l158c10));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2199__PROF__mkXsimTop__l2635(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2199__PROF__mkXsimTop__l2635\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_dbgFSM_fsm_start 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_abort_whas___05F59_AND_lM_ETC___05F_d521) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_dbgFSM_start_reg)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2200__PROF__mkXsimTop__l2726(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2200__PROF__mkXsimTop__l2726\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_fsm_start 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_abort_whas___05F46_AND_lM_ETC___05F_d908) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_dbgFSM_start_reg)) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2201__PROF__mkXsimTop__l4939(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2201__PROF__mkXsimTop__l4939\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqAndDeq) 
           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full) 
               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2202__PROF__mkXsimTop__l4944(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2202__PROF__mkXsimTop__l4944\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqAndDeq) 
           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas)) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_enqData_whas))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2203__PROF__mkMMUSynth__l2134(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2203__PROF__mkMMUSynth__l2134\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_cnt_19_PLUS_I_ETC___05F_d127 
        = (3U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_cnt) 
                  + ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)
                      ? 1U : 0U)) - ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)
                                      ? 1U : 0U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2204__PROF__mkMMUSynth__l1780(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2204__PROF__mkMMUSynth__l1780\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_ENQ 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
            & (0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
                                    >> 0x2dU))))) | 
           ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
            & (0U == (7U & (IData)((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
                                    >> 0x2dU))))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2205__PROF__mkMMUSynth__l1526(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2205__PROF__mkMMUSynth__l1526\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule 
        = ((((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_inited) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_positive_reg)) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg)) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg)) 
            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1))) 
           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2206__PROF__mkMMUIndicationOutputPipes__l734(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2206__PROF__mkMMUIndicationOutputPipes__l734\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[0U] = 0U;
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[1U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[0U]
            : 0U);
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[2U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[1U]
            : (IData)((VL_ULL(0xffffffffff) & (((QData)((IData)(
                                                                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[0U]))))));
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[3U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[2U]
            : (IData)(((VL_ULL(0xffffffffff) & (((QData)((IData)(
                                                                 vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[1U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[0U])))) 
                       >> 0x20U)));
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[4U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[3U]
            : (IData)((((QData)((IData)((7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[2U] 
                                               >> 8U)))) 
                        << 0x20U) | (QData)((IData)(
                                                    ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[2U] 
                                                      << 0x18U) 
                                                     | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[1U] 
                                                        >> 8U)))))));
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[5U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__MUX_error_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[4U]
            : (IData)(((((QData)((IData)((7U & (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[2U] 
                                                >> 8U)))) 
                         << 0x20U) | (QData)((IData)(
                                                     ((vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[2U] 
                                                       << 0x18U) 
                                                      | (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[1U] 
                                                         >> 8U))))) 
                       >> 0x20U)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2207__PROF__mkXsimTop__l3403(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2207__PROF__mkXsimTop__l3403\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg_D_IN 
        = (0xffU & ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader)
                     ? (IData)(vlTOPp->mkXsimTop__DOT___theResult___05F___05Fh88187)
                     : ((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_messageWordsReg) 
                        - (IData)(1U))));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2209__PROF__mkXsimTop__l4279(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2209__PROF__mkXsimTop__l4279\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_1_enq 
        = ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessage) 
           & (1U == (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2210__PROF__mkMemServerIndicationOutputPipes__l1156(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2210__PROF__mkMemServerIndicationOutputPipes__l1156\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[0U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportStateDbg_responseAdapter_bits_write_1___05FSEL_1)
            ? 0U : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10)
                     ? 0xaaaaaaaaU : 0U));
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[1U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportStateDbg_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[0U]
            : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10)
                ? 0xaaaaaaaaU : 0U));
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[2U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportStateDbg_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[1U]
            : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10)
                ? 0xaaaaaaaaU : 0U));
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[3U] 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportStateDbg_responseAdapter_bits_write_1___05FSEL_1)
            ? vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[2U]
            : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_dbgFSM_action_l242c10)
                ? 2U : 0U));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2211__PROF__mkMemServerIndicationOutputPipes__l1067(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2211__PROF__mkMemServerIndicationOutputPipes__l1067\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_addrResponse_responseAdapter_bits_write_1___05FSEL_1)
            ? ((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits)) 
               << 0x20U) : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)
                             ? (VL_ULL(0xffffffffff) 
                                & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__data0_reg)
                             : (VL_ULL(0xffffffffff) 
                                & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__2212__PROF__mkMemServerIndicationOutputPipes__l1126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__2212__PROF__mkMemServerIndicationOutputPipes__l1126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits_D_IN 
        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__MUX_reportMemoryTraffic_responseAdapter_bits_write_1___05FSEL_1)
            ? ((QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits)) 
               << 0x20U) : ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l173c17)
                             ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum
                             : vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum));
}
