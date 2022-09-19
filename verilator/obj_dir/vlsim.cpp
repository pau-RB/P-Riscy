// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See vlsim.h for the primary calling header

#include "vlsim.h"
#include "vlsim__Syms.h"

#include "verilated_dpi.h"

//==========

void vlsim::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate vlsim::eval\n"); );
    vlsim__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/pau/Desktop/TFG/P-Risky/verilator/verilog/mkXsimTop.v", 34, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void vlsim::_eval_initial_loop(vlsim__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/pau/Desktop/TFG/P-Risky/verilator/verilog/mkXsimTop.v", 34, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_init_TOP(const IData/*31:0*/ id, const IData/*31:0*/ handle, const IData/*31:0*/ size) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_init_TOP\n"); );
    // Body
    int id__Vcvt;
    id__Vcvt = id;
    int handle__Vcvt;
    handle__Vcvt = handle;
    int size__Vcvt;
    size__Vcvt = size;
    simDma_init(id__Vcvt, handle__Vcvt, size__Vcvt);
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_initfd_TOP(const IData/*31:0*/ id, const IData/*31:0*/ fd) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_initfd_TOP\n"); );
    // Body
    int id__Vcvt;
    id__Vcvt = id;
    int fd__Vcvt;
    fd__Vcvt = fd;
    simDma_initfd(id__Vcvt, fd__Vcvt);
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_idreturn_TOP(const IData/*31:0*/ aid) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_idreturn_TOP\n"); );
    // Body
    int aid__Vcvt;
    aid__Vcvt = aid;
    simDma_idreturn(aid__Vcvt);
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__write_simDma32_TOP(const IData/*31:0*/ handle, const IData/*31:0*/ addr, const IData/*31:0*/ data, const IData/*31:0*/ byteenable) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__write_simDma32_TOP\n"); );
    // Body
    int handle__Vcvt;
    handle__Vcvt = handle;
    int addr__Vcvt;
    addr__Vcvt = addr;
    int data__Vcvt;
    data__Vcvt = data;
    int byteenable__Vcvt;
    byteenable__Vcvt = byteenable;
    write_simDma32(handle__Vcvt, addr__Vcvt, data__Vcvt, byteenable__Vcvt);
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__read_simDma32_TOP(const IData/*31:0*/ handle, const IData/*31:0*/ addr, IData/*31:0*/(&  read_simDma32__Vfuncrtn)) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__read_simDma32_TOP\n"); );
    // Body
    int handle__Vcvt;
    handle__Vcvt = handle;
    int addr__Vcvt;
    addr__Vcvt = addr;
    int read_simDma32__Vfuncrtn__Vcvt = read_simDma32(handle__Vcvt, addr__Vcvt);
    read_simDma32__Vfuncrtn = read_simDma32__Vfuncrtn__Vcvt;
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat_TOP(const IData/*31:0*/ portal, QData/*63:0*/(&  dpi_msgSink_beat__Vfuncrtn)) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__sink_0__DOT__dpi_msgSink_beat_TOP\n"); );
    // Body
    int portal__Vcvt;
    portal__Vcvt = portal;
    long long dpi_msgSink_beat__Vfuncrtn__Vcvt = dpi_msgSink_beat(portal__Vcvt);
    dpi_msgSink_beat__Vfuncrtn = dpi_msgSink_beat__Vfuncrtn__Vcvt;
}

VL_INLINE_OPT void vlsim::__Vdpiimwrap_mkXsimTop__DOT__tmp_1_0__DOT__dpi_msgSource_beat_TOP(const IData/*31:0*/ portal, const IData/*31:0*/ beat) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::__Vdpiimwrap_mkXsimTop__DOT__tmp_1_0__DOT__dpi_msgSource_beat_TOP\n"); );
    // Body
    int portal__Vcvt;
    portal__Vcvt = portal;
    int beat__Vcvt;
    beat__Vcvt = beat;
    dpi_msgSource_beat(portal__Vcvt, beat__Vcvt);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__551__PROF__BRAM2__l80(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__551__PROF__BRAM2__l80\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__553__PROF__BRAM2__l67(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__553__PROF__BRAM2__l67\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__554__PROF__BRAM2__l80(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__554__PROF__BRAM2__l80\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__577__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__577__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__581__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__581__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__588__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__588__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__589__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__589__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__590__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__590__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__591__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__591__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__594__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__594__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__595__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__595__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__596__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__596__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__597__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__597__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__598__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__598__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__599__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__599__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__603__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__603__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__604__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__604__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__606__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__606__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__607__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__607__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__608__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__608__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__621__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__621__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__625__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__625__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__626__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__626__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__627__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__627__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__628__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__628__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__629__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__629__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__632__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__632__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__633__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__633__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__634__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__634__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__635__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__635__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__637__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__637__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__638__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__638__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__639__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__639__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__640__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__640__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__643__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__643__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__644__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__644__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__646__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__646__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__648__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__648__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__649__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__649__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__650__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__650__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__651__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__651__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__652__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__652__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__653__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__653__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__654__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__654__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__655__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__655__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__656__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__656__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__657__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__657__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__658__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__658__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__660__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__660__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__661__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__661__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__663__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__663__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__664__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__664__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__666__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__666__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__669__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__669__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__673__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__673__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__674__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__674__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__676__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__676__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__677__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__677__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__678__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__678__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__680__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__680__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__682__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__682__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__683__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__683__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__693__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__693__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__695__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__695__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__696__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__696__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__697__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__697__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__698__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__698__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__699__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__699__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__700__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__700__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__701__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__701__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__702__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__702__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__706__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__706__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__707__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__707__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__711__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__711__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__713__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__713__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__714__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__714__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__715__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__715__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__716__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__716__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__717__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__717__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__718__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__718__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__719__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__719__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__720__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__720__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__723__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__723__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__725__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__725__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__730__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__730__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__731__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__731__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__732__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__732__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__733__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__733__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__736__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__736__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__739__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__739__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__743__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__743__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__744__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__744__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__748__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__748__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__749__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__749__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__750__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__750__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__751__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__751__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__753__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__753__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__754__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__754__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__755__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__755__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__756__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__756__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__757__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__757__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__758__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__758__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__759__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__759__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__760__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__760__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__761__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__761__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__762__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__762__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__764__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__764__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__766__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__766__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__769__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__769__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__770__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__770__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__771__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__771__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__773__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__773__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__775__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__775__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__778__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__778__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__779__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__779__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__783__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__783__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__798__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__798__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__799__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__799__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__800__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__800__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__801__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__801__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__804__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__804__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__806__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__806__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__807__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__807__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__808__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__808__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__809__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__809__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__810__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__810__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__811__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__811__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__812__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__812__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__813__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__813__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__814__PROF__FIFO2__l121(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__814__PROF__FIFO2__l121\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U];
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__816__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__816__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__828__PROF__FIFO2__l97(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__828__PROF__FIFO2__l97\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__832__PROF__RegFile__l68(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__832__PROF__RegFile__l68\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_clientBurstLen__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__837__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__837__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__838__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__838__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__839__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__839__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__840__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__840__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__841__PROF__mkMMUSynth__l2330(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__841__PROF__mkMMUSynth__l2330\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__843__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__843__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__844__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__844__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__845__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__845__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__846__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__846__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__847__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__847__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__848__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__848__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__849__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__849__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__867__PROF__SizedFIFO__l206(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__867__PROF__SizedFIFO__l206\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__arr__v0 = 0U;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__868__PROF__SizedFIFO__l125(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__868__PROF__SizedFIFO__l125\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__ring_empty;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__869__PROF__SizedFIFO__l124(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__869__PROF__SizedFIFO__l124\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__tail;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__870__PROF__SizedFIFO__l123(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__870__PROF__SizedFIFO__l123\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__head;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__871__PROF__SizedFIFO__l127(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__871__PROF__SizedFIFO__l127\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__872__PROF__SizedFIFO__l126(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__872__PROF__SizedFIFO__l126\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__887__PROF__mkXsimTop__l6218(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__887__PROF__mkXsimTop__l6218\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__888__PROF__mkXsimTop__l6080(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__888__PROF__mkXsimTop__l6080\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_head_ptr;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__891__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__891__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
}

VL_INLINE_OPT void vlsim::_sequent__TOP__896__PROF__XsimSource__l36(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__896__PROF__XsimSource__l36\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg) {
        vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__tmp_1_0__DOT__dpi_msgSource_beat_TOP(5U, vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__897__PROF__XsimSource__l36(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__897__PROF__XsimSource__l36\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) {
        vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__tmp_1_0__DOT__dpi_msgSource_beat_TOP(4U, vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__898__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__898__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__899__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__899__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__900__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__900__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__901__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__901__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_mmu_servers_0_tokFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__902__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__902__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_clientRequest.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__903__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__903__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_bFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_bFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__904__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__904__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.offs1_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.offs1_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__905__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__905__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_writeDelayFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_writeDelayFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__906__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__906__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.top.lFromHostInput.startPC_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput__DOT__startPC_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInput_EN_portalIfc_requests_0_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.top.lFromHostInput.startPC_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__907__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__907__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_idResponsePipe_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.idResponseFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.idResponseFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__908__PROF__XsimSource__l36(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__908__PROF__XsimSource__l36\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) {
        vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__tmp_1_0__DOT__dpi_msgSource_beat_TOP(3U, vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data0_reg);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__909__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__909__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.translationTable_cbram_responseFifo_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.translationTable_cbram_responseFifo_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__910__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__910__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.translationTable_cbram_responseFifo_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.translationTable_cbram_responseFifo_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__911__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__911__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_errorPipe_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__912__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__912__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.reqs0_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.reqs0_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__913__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__913__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_tagFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_tagFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__914__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__914__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.offs1_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.offs1_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__915__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__915__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.setTileState_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_1_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.setTileState_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__916__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__916__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage3Params_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage3Params_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__917__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__917__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.top.lFromHostInputNoc_fifoMsgSink.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.top.lFromHostInputNoc_fifoMsgSink.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__918__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__918__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.top.lToHostOutputNoc_fifoMsgSource.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.top.lToHostOutputNoc_fifoMsgSource.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__919__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__919__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_comp_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_comp_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__920__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__920__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_serverRequest.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_serverRequest.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__921__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__921__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_tagFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_tagFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__922__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__922__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.addrTrans_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.addrTrans_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__923__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__923__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage4Params_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage4Params_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__924__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__924__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.idReturnFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.idReturnFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__925__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__925__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_dmaErrorFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__926__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__926__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.incomingReqs_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__927__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__927__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.setInterface_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_fifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.setInterface_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__928__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__928__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_comp_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_comp_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__929__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__929__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_mmu_servers_0_tokFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__930__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__930__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.reqs0_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMMU_mmu.reqs0_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__931__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__931__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.regall_cbram_responseFifo_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.regall_cbram_responseFifo_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__932__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__932__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_serverProcessing.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_serverProcessing.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__933__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__933__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idRequest_PipeOut_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.idRequest_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_2_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.idRequest_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__934__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__934__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_idReturn_PipeOut_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.idReturn_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_3_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.idReturn_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__935__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__935__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_readDelayFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.slave_2_0_readDelayFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__936__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__936__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.slave_2_0_taglastfifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.slave_2_0_taglastfifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__937__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__937__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_memDataFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_memDataFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__938__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__938__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_dmaErrorFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__939__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__939__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServerRequestInputNoc_fifoMsgSink.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServerRequestInputNoc_fifoMsgSink.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__940__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__940__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_2)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifos_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifos_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__941__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__941__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifos_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.dmaErrorFifos_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__942__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__942__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_clientRequest.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__943__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__943__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage3Params_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage3Params_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__944__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__944__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.pageResponseFifos_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.pageResponseFifos_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__945__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__945__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_clientWriteData_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__946__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__946__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_clientWriteData_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__947__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__947__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMURequestInputNoc_fifoMsgSink.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMURequestInputNoc_fifoMsgSink.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__948__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__948__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_comp_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_comp_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__949__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__949__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMUIndicationOutputNoc_fifoMsgSource.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMUIndicationOutputNoc_fifoMsgSource.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__950__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__950__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_addrReqFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_addrReqFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__951__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__951__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientResponse__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_clientResponse.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__952__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__952__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.incomingReqs_1.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.incomingReqs_1.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__953__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__953__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.regall_cbram_responseFifo_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.regall_cbram_responseFifo_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__954__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__954__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage4Params_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.stage4Params_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__955__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__955__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_sglist_PipeOut_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.sglist_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.sglist_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__956__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__956__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientSelect_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_clientSelect.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__957__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__957__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverTag.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverTag.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__958__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__958__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverData.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverData.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__959__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__959__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_tagFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_tagFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__960__PROF__XsimDmaReadWrite__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__960__PROF__XsimDmaReadWrite__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_sglist) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_init_TOP(
                                                                                (0xffffU 
                                                                                & (vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[4U] 
                                                                                >> 0x10U)), 
                                                                                (0xffffU 
                                                                                & vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[4U]), 
                                                                                vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_fifo_D_OUT[0U]);
        }
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_initfd_TOP(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg, vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idRequest_requestAdapter_fifo_D_OUT);
        }
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__simDma_idreturn_TOP(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo_D_OUT);
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__961__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__961__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_pipes_region_PipeOut_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.region_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_fifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMURequestInput.region_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__962__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__962__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServerIndicationOutputNoc_fifoMsgSource.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServerIndicationOutputNoc_fifoMsgSource.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__963__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__963__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_retFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_writer_writers_0_tag_gen_retFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__964__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__964__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_writer_writers_0_respFifos_serverAdapterB_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__965__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__965__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_retFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.sglId_gen_retFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__966__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__966__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverRequest.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_serverRequest.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__967__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__967__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_serverProcessing_serverAdapterA_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__968__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__968__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_retFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_readers_0_tag_gen_retFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__969__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__969__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_configResponsePipe_deq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.configResponseFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_region)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMMU_mmu.configResponseFifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__970__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__970__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_0_response_get)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.pageResponseFifos_0.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_0__DOT__full_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMMU_mmu.pageResponseFifos_0.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__971__PROF__FIFO2__l131(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__971__PROF__FIFO2__l131\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_addrReqFifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_mmuEntry)))) {
            VL_WRITEF("Warning: FIFO2: %NmkXsimTop.lMemServer_reader_addrReqFifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__972__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__972__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_memoryTraffic_request)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.memoryTraffic_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__memoryTraffic_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_3_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.memoryTraffic_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__973__PROF__FIFO1__l112(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__973__PROF__FIFO1__l112\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_stateDbg_request)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.stateDbg_requestAdapter_fifo.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__stateDbg_requestAdapter_fifo__DOT__empty_reg) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_2_enq)))) {
            VL_WRITEF("Warning: FIFO1: %NmkXsimTop.lMemServerRequestInput.stateDbg_requestAdapter_fifo.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__974__PROF__SizedFIFO__l212(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__974__PROF__SizedFIFO__l212\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__hasodata)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_DEQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore.error_checks -- Dequeuing from empty fifo\n",
                      vlSymsp->name());
        }
        if (VL_UNLIKELY(((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore__DOT__not_ring_full)) 
                         & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore_ENQ)))) {
            VL_WRITEF("Warning: SizedFIFO: %NmkXsimTop.lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outDataCore.error_checks -- Enqueuing to a full fifo\n",
                      vlSymsp->name());
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__975__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__975__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_writeWithResp_whas) {
        if ((1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_DIB;
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory__DOT__RAM__v0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_memory_ADDRB;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__976__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__976__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[0U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[0U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[1U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[2U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[3U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R2[4U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOA_R[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__977__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__977__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ENA) {
        if ((1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_DIA;
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__RAM__v0 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram_ADDRA;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__978__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__978__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ENB) {
        if ((1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[0U] 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[0U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[1U] 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[1U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[2U] 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[2U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[3U] 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[3U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0[4U] 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_DIB[4U];
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__RAM__v0 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram_ADDRB;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__979__PROF__BRAM2__l64(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__979__PROF__BRAM2__l64\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOA_R2 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOA_R;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__980__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__980__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOB_R2 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_bram__DOT__DOB_R;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__981__PROF__BRAM2__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__981__PROF__BRAM2__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[0U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[0U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[1U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[2U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[3U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R2[4U] 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_bram__DOT__DOB_R[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__982__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__982__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__dumpstarted_EN) {
            vlTOPp->mkXsimTop__DOT__dumpstarted = 1U;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__dumpstarted = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__983__PROF__mkToHostOutputPipes__l256(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__983__PROF__mkToHostOutputPipes__l256\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ (IData)(vlTOPp->RST_N)))) {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_bits = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__984__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__984__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_writeWithResp_whas)
                                      ? 2U : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__985__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__985__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_0_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_0_cnt_4_PLUS_IF_regall_cb_ETC___05F_d52)
            : 2U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__986__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__986__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_cnt_5_PLUS_IF_regall_cb_ETC___05F_d63)
            : 2U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__987__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__987__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_cnt_PLUS_IF_sglId_gen_counte_ETC___05F_d9)
            : 0x20U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__988__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__988__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_cnt_08_PLUS_I_ETC___05F_d116)
            : 2U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__989__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__989__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_cnt_19_PLUS_I_ETC___05F_d127)
            : 2U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__990__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__990__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_cn_ETC___05F_d292)
            : 0x20U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__991__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__991__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_cnt 
        = ((IData)(vlTOPp->RST_N) ? (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_cn_ETC___05F_d702)
            : 0x20U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__992__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__992__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_0_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_0_cnt_4_PLUS_IF_regall_cb_ETC___05F_d52)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__993__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__993__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt_1_whas)
                                      ? 3U : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__994__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__994__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_burstReg 
                = (0x3ffU & ((IData)(vlTOPp->mkXsimTop__DOT__burstLen___05Fh51885) 
                             - (IData)(1U)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_burstReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__995__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__995__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_readOffsetReg 
                = ((IData)(8U) + vlTOPp->mkXsimTop__DOT__readOffset___05Fh93284);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_readOffsetReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__996__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__996__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_beatCount = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__997__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__997__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeOffsetReg 
                = ((IData)(8U) + vlTOPp->mkXsimTop__DOT__writeOffset___05Fh95460);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeOffsetReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__998__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__998__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[0U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[1U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[2U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_D_IN[2U];
        if ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[0U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[1U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT____Vlvbound2[2U];
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_bFifo__DOT__arr__v0 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__999__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__999__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_IN;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_IN;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1000__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1000__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_beatCount = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1001__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1001__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_cnt_19_PLUS_I_ETC___05F_d127)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1002__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1002__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1_D_IN;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1003__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1003__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)
                                      ? 2U : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1004__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1004__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_idResponse) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_bits 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idResponseFifo_D_OUT;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_bits = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1005__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1005__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ (IData)(vlTOPp->RST_N)))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1006__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1006__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_lastReg 
                = (2U == (IData)(vlTOPp->mkXsimTop__DOT__burstLen___05Fh51885));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_lastReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1007__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1007__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_readLenReg 
                = (0x3ffU & ((IData)(vlTOPp->mkXsimTop__DOT__readLen___05Fh93283) 
                             - (IData)(1U)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_readLenReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1008__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1008__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                       << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_D_OUT = 0U;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                             << 1U) 
                                            | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_D_OUT = 0U;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1009__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1009__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l253c10) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_trafficFSM_action_l251c20))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_trafficAccum = VL_ULL(0);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1010__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1010__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l169c10) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_trafficFSM_action_l167c20))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_trafficAccum = VL_ULL(0);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1011__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1011__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                 << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                    << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                      << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                          << 2U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                              << 2U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore_ENQ) 
                                                  << 2U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterA_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1012__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1012__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                 << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                    << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                      << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                          << 2U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                              << 2U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore_ENQ) 
                                                  << 2U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1013__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1013__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_outData_deqCalled_whas))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_cnt 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAd_ETC___05F_d672;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1014__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1014__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_methodIdReg 
                = (0xffU & (vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg 
                            >> 0x10U));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1015__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1015__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__slave_2_0_cycles = ((IData)(vlTOPp->RST_N)
                                                 ? vlTOPp->mkXsimTop__DOT__slave_2_0_cycles_D_IN
                                                 : VL_ULL(0));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1016__PROF__mkMemServerRequestInput__l1111(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1016__PROF__mkMemServerRequestInput__l1111\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput_EN_portalIfc_requests_0_enq) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1017__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1017__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                 << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                    << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                      << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                          << 2U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                              << 2U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore_ENQ) 
                                                  << 2U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_outDataCore__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1018__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1018__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                       << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][0U];
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][1U];
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][2U];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] = 0x55555555U;
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] = 0x55555555U;
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] = 0x1555555U;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                             << 1U) 
                                            | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][0U];
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][1U];
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head][2U];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[0U] = 0x55555555U;
                    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[1U] = 0x55555555U;
                    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest_D_OUT[2U] = 0x1555555U;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1019__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1019__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg 
                = (1U == (IData)(vlTOPp->mkXsimTop__DOT__burstLen___05Fh51885));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_firstReg = 1U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1020__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1020__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_D_IN) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1021__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1021__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_D_IN) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1022__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1022__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ (IData)(vlTOPp->RST_N)))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterA_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1023__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1023__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) {
            vlTOPp->mkXsimTop__DOT__slave_2_0_writeLenReg 
                = (0x3ffU & ((IData)(vlTOPp->mkXsimTop__DOT__writeLen___05F_2___05Fh95459) 
                             - (IData)(1U)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeLenReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1024__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1024__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_cnt 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_s_ETC___05F_d102;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1025__PROF__mkMMURequestInput__l1505(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1025__PROF__mkMMURequestInput__l1505\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_4_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__setInterface_requestAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1026__PROF__mkMMURequestInput__l1505(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1026__PROF__mkMMURequestInput__l1505\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_0_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__sglist_requestAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1027__PROF__mkMMURequestInput__l1505(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1027__PROF__mkMMURequestInput__l1505\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMURequestInput_EN_portalIfc_requests_1_enq) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count 
                = vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__region_requestAdapter_count = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1028__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1028__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[0U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[1U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[2U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[2U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[3U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_IN[3U];
        if ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[0U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[1U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[2U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0[3U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT____Vlvbound2[3U];
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__arr__v0 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1029__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1029__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerRequestInputNoc_receiveMessageHeader) {
            vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg 
                = (0xffU & (vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg 
                            >> 0x10U));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1030__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1030__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp63[3];
    WData/*95:0*/ __Vtemp71[3];
    // Body
    __Vtemp63[1U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[1U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[1U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U]));
    __Vtemp63[2U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[2U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[2U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[1U] 
        = __Vtemp63[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data0_reg[2U] 
        = __Vtemp63[2U];
    __Vtemp71[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[1U]
                      : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[1U]);
    __Vtemp71[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[2U]
                      : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[2U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[1U] 
        = __Vtemp71[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__data1_reg[2U] 
        = __Vtemp71[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1031__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1031__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tail_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1032__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1032__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tail_ptr = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1033__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1033__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1034__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1034__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_responseFifo_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1035__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1035__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_IN;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_IN;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1036__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1036__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_D_IN) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_D_IN
            : vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1037__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1037__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_bFifo__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_bFifo__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1038__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1038__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1039__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1039__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*159:0*/ __Vtemp75[5];
    WData/*159:0*/ __Vtemp83[5];
    // Body
    __Vtemp75[1U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[1U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[1U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U]));
    __Vtemp75[2U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[2U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[2U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U]));
    __Vtemp75[3U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[3U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[3U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[3U]));
    __Vtemp75[4U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[4U]) 
                      | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[4U])) 
                     | (VL_NEGATE_I((IData)((1U & (
                                                   (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                     & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp))) 
                                                    | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                                   | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[4U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[1U] 
        = __Vtemp75[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[2U] 
        = __Vtemp75[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[3U] 
        = __Vtemp75[3U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data0_reg[4U] 
        = __Vtemp75[4U];
    __Vtemp83[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[1U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[1U]);
    __Vtemp83[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[2U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[2U]);
    __Vtemp83[3U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[3U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[3U]);
    __Vtemp83[4U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[4U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[4U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[1U] 
        = __Vtemp83[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[2U] 
        = __Vtemp83[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[3U] 
        = __Vtemp83[3U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__data1_reg[4U] 
        = __Vtemp83[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1040__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1040__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1041__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1041__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1042__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1042__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_1__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1043__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1043__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lToHostOutputNoc_fifoMsgSource__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1044__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1044__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0_D_IN;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1045__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1045__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1046__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1046__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_sglId_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1047__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1047__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMUIndicationOutputNoc_sendHeader) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg 
                = vlTOPp->mkXsimTop__DOT__readyChannel___05Fh87211;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1048__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1048__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_clientRequest__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1049__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1049__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverRequest__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1050__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1050__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_methodIdReg 
                = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutput__DOT__indicationPipes__DOT__print_responseAdapter_notEmptyReg)
                    ? 0U : 0xffU);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1051__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1051__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1052__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1052__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_checkMmuResp) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_counter_dec_wire_whas)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tagFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1053__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1053__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1054__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1054__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMMURequestInputNoc_receiveMessageHeader) {
            vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg 
                = (0xffU & (vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg 
                            >> 0x10U));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1055__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1055__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt_1_whas) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverA_ETC___05F_d262;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientData_serverAdapterB_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1056__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1056__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_writer_writers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1057__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1057__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader) 
              & (0U != (IData)(vlTOPp->mkXsimTop__DOT__top__DOT___theResult___05F___05Fh1407))) 
             | ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessage) 
                & (1U == (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_messageWordsReg))))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_bpState 
                = ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lFromHostInputNoc_receiveMessageHeader) 
                   & (0U != (IData)(vlTOPp->mkXsimTop__DOT__top__DOT___theResult___05F___05Fh1407)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1058__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1058__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp93[3];
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[1U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[1U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[2U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[2U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U]));
    __Vtemp93[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[1U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[1U]);
    __Vtemp93[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))
                      ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[2U]
                      : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[2U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[1U] 
        = __Vtemp93[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data1_reg[2U] 
        = __Vtemp93[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1059__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1059__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1060__PROF__mkCnocTop__l910(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1060__PROF__mkCnocTop__l910\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage) 
              & (1U == (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendHeader))) {
            vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_bpState 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__WILL_FIRE_RL_lToHostOutputNoc_sendMessage) 
                            & (1U == (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_messageWordsReg)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__top__DOT__lToHostOutputNoc_bpState = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1061__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1061__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo_D_IN)) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg))))) 
               & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data1_reg))) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg)))))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data0_reg)));
    vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
            & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg))
            ? (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo_D_IN)
            : (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__data1_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1062__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1062__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1063__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1063__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg 
        = (((VL_NEGATE_Q((QData)((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg))) 
                                          | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg)))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_D_IN) 
            | (VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg)))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data1_reg)) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((
                                                   (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)) 
                                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4_1)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg))) 
                                                 | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ)) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__full_reg))))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_1__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1064__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1064__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_memdata)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1065__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1065__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg 
        = ((VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                         & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__full_reg)))))) 
            & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data1_reg) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas)) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__empty_reg))) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data1_reg 
        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_0__DOT__data1_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1066__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1066__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_taglastfifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1067__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1067__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__data0_reg 
        = ((VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2) 
                                         & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__full_reg)))))) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__data1_reg) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2)) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServerIndicationOutput_ifc_error_1___05FSEL_2)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__empty_reg))) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__data1_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_dmaErrorFifo__DOT__data1_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1068__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1068__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt_1_whas) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_s_ETC___05F_d156;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_cnt = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1069__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1069__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_1_deq) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_configResp))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_1_deq)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1070__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1070__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_0_deq) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_idResponse))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg 
                = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_0_deq)));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__idResponse_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1071__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1071__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__sink_0__DOT__beat_reg) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__top_EN_requests_0_message_enq) 
            & (IData)(vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__sink_0__DOT__beat_reg
            : vlTOPp->mkXsimTop__DOT__top__DOT__lFromHostInputNoc_fifoMsgSink__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1072__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1072__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*159:0*/ __Vtemp102[5];
    WData/*159:0*/ __Vtemp110[5];
    // Body
    __Vtemp102[1U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[1U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[1U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[1U]));
    __Vtemp102[2U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[2U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[2U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U]));
    __Vtemp102[3U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[3U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[3U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[3U]));
    __Vtemp102[4U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[4U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[4U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[4U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[1U] 
        = __Vtemp102[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[2U] 
        = __Vtemp102[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[3U] 
        = __Vtemp102[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data0_reg[4U] 
        = __Vtemp102[4U];
    __Vtemp110[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[1U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[1U]);
    __Vtemp110[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[2U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[2U]);
    __Vtemp110[3U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[3U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[3U]);
    __Vtemp110[4U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[4U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[4U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[1U] 
        = __Vtemp110[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[2U] 
        = __Vtemp110[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[3U] 
        = __Vtemp110[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_1__DOT__data1_reg[4U] 
        = __Vtemp110[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1073__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1073__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a) 
             | (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_burst_remainder))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compCountReg 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compCountReg_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compCountReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1074__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1074__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1075__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1075__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1076__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1076__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo_D_OUT) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idReturn) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMURequestInput__DOT__idReturn_requestAdapter_fifo_D_OUT
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__idReturnFifo__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1077__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1077__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_writeDelayFifo__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1078__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1078__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1079__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1079__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp113[3];
    WData/*95:0*/ __Vtemp121[3];
    // Body
    __Vtemp113[1U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[1U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[1U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U]));
    __Vtemp113[2U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[2U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[2U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[1U] 
        = __Vtemp113[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data0_reg[2U] 
        = __Vtemp113[2U];
    __Vtemp121[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[1U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[1U]);
    __Vtemp121[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[2U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[2U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[1U] 
        = __Vtemp121[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage3Params_0__DOT__data1_reg[2U] 
        = __Vtemp121[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1080__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1080__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_cnt_08_PLUS_I_ETC___05F_d116)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1081__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1081__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full))))) {
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[0U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[0U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[1U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[1U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[2U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[2U];
        vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[3U] 
            = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_IN[3U];
        if ((0x94U >= (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[0U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[0U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[1U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[1U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[2U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[2U];
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0[3U] 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT____Vlvbound2[3U];
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__arr__v0 
                = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1082__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1082__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full))))) {
        vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg;
        vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0 = 1U;
        vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__arr__v0 
            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1083__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1083__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__data0_reg 
        = ((VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError) 
                                         & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__full_reg)))))) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__data1_reg) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError)) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_dmaError)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__empty_reg))) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__data1_reg 
        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_dmaErrorFifo__DOT__data1_reg;
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1084__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1084__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__MUX_lMemServer_reader_readers_0_tag_gen_comp_state_write_1___05FSEL_1)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_fifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1085__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1085__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg 
        = (((VL_NEGATE_Q((QData)((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg))) 
                                          | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg)))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1_D_IN) 
            | (VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg)))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data1_reg)) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((
                                                   (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)) 
                                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg))) 
                                                 | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg))))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1086__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1086__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_response_get) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_1_inc_wire_whas)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__pageResponseFifos_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1087__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1087__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_D_IN) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMUIndicationOutputNoc_fifoMsgSource__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1088__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1088__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1089__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1089__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (0U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_0 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1090__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1090__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (1U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_1 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_1 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1091__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1091__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (2U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_2 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_2 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1092__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1092__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (3U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_3 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_killv_3 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1093__PROF__SizedFIFO__l190(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1093__PROF__SizedFIFO__l190\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
         & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))) 
            | (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ)) 
                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata)) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT____Vlvbound2 
            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_IN;
        if ((0x1eU >= (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail))) {
            vlTOPp->__Vdlyvval__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT____Vlvbound2;
            vlTOPp->__Vdlyvset__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0 = 1U;
            vlTOPp->__Vdlyvdim0__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr__v0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail;
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1094__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1094__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__sink_2__DOT__beat_reg) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__sink_2__DOT__beat_reg
            : vlTOPp->mkXsimTop__DOT__lMemServerRequestInputNoc_fifoMsgSink__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1095__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1095__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1096__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1096__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data0_0_whas) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_0__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1097__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1097__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq) 
              & (5U != (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_error))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[0U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[1U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[2U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[3U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[3U];
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[4U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[4U];
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U] 
                = vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[5U];
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[0U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[1U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[2U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[3U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[4U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U] = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1098__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1098__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_tag_gen_complete_rule1) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_tags_port1_ETC___05F_d707))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_state 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_state_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_comp_state = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1099__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1099__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_counter_0_inc_wire_whas) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__offs1_0__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1100__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1100__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_sglId_gen_complete_rule1) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tags_port1___05Fread___05F2_BIT_sglId_gen_ta_ETC___05F_d14))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg))) {
            vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_state 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_state_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_comp_state = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1101__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1101__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compTileReg 
                = (3U & (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterB_outData_outData_wget 
                         >> 0x16U));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_compTileReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1102__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1102__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1103__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1103__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_gen_complete_rule1) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tags_port1_ETC___05F_d297))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_state 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_state_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_comp_state = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1104__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1104__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1105__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1105__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1106__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1106__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp130[3];
    WData/*95:0*/ __Vtemp135[3];
    // Body
    __Vtemp130[1U] = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[1U]) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg))) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[1U]));
    __Vtemp130[2U] = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[2U]) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg))) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[2U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[0U] 
        = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ) 
                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[0U]) 
           | (VL_NEGATE_I((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__empty_reg))) 
                                         | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__full_reg))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[1U] 
        = __Vtemp130[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data0_reg[2U] 
        = __Vtemp130[2U];
    __Vtemp135[1U] = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[1U];
    __Vtemp135[2U] = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[0U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[0U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[1U] 
        = __Vtemp135[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_1__DOT__data1_reg[2U] 
        = __Vtemp135[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1107__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1107__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp136[3];
    WData/*95:0*/ __Vtemp141[3];
    // Body
    __Vtemp136[1U] = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[1U]) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg))) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[1U]));
    __Vtemp136[2U] = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[2U]) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg))) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[2U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[0U] 
        = ((VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ) 
                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
            & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[0U]) 
           | (VL_NEGATE_I((IData)((1U & (((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__empty_reg))) 
                                         | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__full_reg))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[1U] 
        = __Vtemp136[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data0_reg[2U] 
        = __Vtemp136[2U];
    __Vtemp141[1U] = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[1U];
    __Vtemp141[2U] = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[0U] 
        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[0U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[1U] 
        = __Vtemp141[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_clientWriteData_0__DOT__data1_reg[2U] 
        = __Vtemp141[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1108__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1108__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__sink_1__DOT__beat_reg) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_DEQ)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__sink_1__DOT__beat_reg
            : vlTOPp->mkXsimTop__DOT__lMMURequestInputNoc_fifoMsgSink__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1109__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1109__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServerIndicationOutputNoc_sendHeader) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg 
                = vlTOPp->mkXsimTop__DOT__readyChannel___05Fh88937;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_methodIdReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1110__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1110__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2_1) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__reqs0_1__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1111__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1111__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1112__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1112__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_respFifos_serverAdapterB_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_writers_0_respFifos_serverAdapterB_stageReadResponseAlways)
                                      ? 3U : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1113__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1113__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1114__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1114__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                       << 2U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
            = ((0x1eU >= (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head))
                ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr
               [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head]
                : 0U);
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_IN;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                             << 2U) 
                                            | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                << 1U) 
                                               | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                    = ((0x1eU >= (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head))
                        ? vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__arr
                       [vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__head]
                        : 0U);
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_ENQ) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing__DOT__ring_empty))))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_OUT 
                        = vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_serverProcessing_D_IN;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1115__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1115__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                            << 2U) 
                                           | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                               << 2U) 
                                              | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                  << 1U) 
                                                 | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                           << 2U) | 
                                          (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                                 << 2U) 
                                                | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                    << 1U) 
                                                   | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                                     << 2U) 
                                                    | (((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata) 
                                                        << 1U) 
                                                       | (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty))))))) {
                                if (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__slave_2_0_readDelayFifo__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1116__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1116__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1117__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1117__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_complete_burst1a) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_tag_completed)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverTag__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1118__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1118__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq) 
              & (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_error))) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg 
                = (1U & (~ ((IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_portalIfc_indications_2_deq) 
                            & (5U == (IData)(vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count)))));
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_notEmptyReg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1119__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1119__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*159:0*/ __Vtemp151[5];
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[0U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[1U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[1U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[1U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[2U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[2U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[2U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[3U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[3U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[3U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[4U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[4U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage2)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data0_reg[4U]));
    __Vtemp151[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[1U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[1U]);
    __Vtemp151[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[2U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[2U]);
    __Vtemp151[3U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[3U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[3U]);
    __Vtemp151[4U] = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[4U]
                       : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[4U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[1U] 
        = __Vtemp151[1U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[2U] 
        = __Vtemp151[2U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[3U] 
        = __Vtemp151[3U];
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_responseFifo_0__DOT__data1_reg[4U] 
        = __Vtemp151[4U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1120__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1120__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg 
        = (((VL_NEGATE_Q((QData)((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg))) 
                                          | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg)))))) 
             & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
                 & (0U == (0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                              >> 0x30U)))))
                 ? (((QData)((IData)((0x1fU & (IData)(
                                                      (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                                       >> 0x20U))))) 
                     << 0x28U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT)))
                 : VL_ULL(0xaaaaaaaaaaa))) | (VL_NEGATE_Q((QData)((IData)(
                                                                          ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1) 
                                                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg)))))) 
                                              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data1_reg)) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((
                                                   (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)) 
                                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage1_1)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg))) 
                                                 | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put)) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__full_reg))))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_addr_1_request_put) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__empty_reg))
            ? (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
                & (0U == (0xffffU & (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                             >> 0x30U)))))
                ? (((QData)((IData)((0x1fU & (IData)(
                                                     (vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                                                      >> 0x20U))))) 
                    << 0x28U) | (QData)((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT)))
                : VL_ULL(0xaaaaaaaaaaa)) : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__incomingReqs_1__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1121__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1121__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverProcessing_serverAdapterA_s1 
        = ((IData)(vlTOPp->RST_N) ? ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)
                                      ? 3U : 0U) : 0U);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1122__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1122__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg 
        = (((VL_NEGATE_Q((QData)((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg))) 
                                          | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ) 
                                              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg)))))) 
             & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_D_IN) 
            | (VL_NEGATE_Q((QData)((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4) 
                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg)))))) 
               & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data1_reg)) 
           | (VL_NEGATE_Q((QData)((IData)((1U & (((
                                                   (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)) 
                                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ))) 
                                                  | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_stage4)) 
                                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg))) 
                                                 | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ)) 
                                                    & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__full_reg))))))) 
              & vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0_D_IN
            : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__stage4Params_0__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1123__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1123__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_counter_dec_wire_whas)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_tagFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1124__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1124__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[0U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[0U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[1U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[1U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[2U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[2U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[3U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[3U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_0[4U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_0[4U]
            : 0x2aaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1125__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1125__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_1 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data1_1
            : 0xaaaaaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1126__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1126__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg))))) 
             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr)) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg))))) 
               & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data1_reg))) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu_EN_request_idRequest)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__full_reg)))))) 
              & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data0_reg)));
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_counter_dec_wire_whas) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__empty_reg))
            ? (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_head_ptr)
            : (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_tagFifo__DOT__data1_reg));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1127__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1127__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg))))) 
             & (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                        >> 0x20U))) | (VL_NEGATE_I((IData)(
                                                           ((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry) 
                                                            & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg))))) 
                                       & vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_writer_mmuEntry)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_handle_addrTrans_request) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__empty_reg))
            ? (IData)((vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__addrTrans_requestAdapter_fifo_D_OUT 
                       >> 0x20U)) : vlTOPp->mkXsimTop__DOT__lMemServer_writer_addrReqFifo__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1128__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1128__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data2_0 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__translationTable_cbram_data1_0
            : 0xaaaaaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1129__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1129__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[0U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[0U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[1U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[1U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[2U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[2U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[3U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[3U]
            : 0xaaaaaaaaU);
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data2_1[4U] 
        = ((IData)(vlTOPp->RST_N) ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_data1_1[4U]
            : 0x2aaaaU);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1130__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1130__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (0U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1131__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1131__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (1U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_1 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_1 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1132__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1132__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (2U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_2 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_2 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1133__PROF__mkXsimTop__l5758(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1133__PROF__mkXsimTop__l5758\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo__DOT__empty_reg) 
             & (3U == (3U & ((IData)(vlTOPp->mkXsimTop__DOT__lMemServerRequestInput__DOT__setTileState_requestAdapter_fifo_D_OUT) 
                             >> 2U))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_3 
                = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_0_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_killv_3 = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1134__PROF__SizedFIFO__l167(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1134__PROF__SizedFIFO__l167\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                            << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                       << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
        vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_D_OUT 
            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__arr
            [vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head];
    } else {
        if ((0xdU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
            vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_D_OUT = 0U;
        } else {
            if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                  << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                             << 1U) 
                                            | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_D_OUT 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__arr
                    [vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head];
            } else {
                if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                    vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_D_OUT = 0U;
                }
            }
        }
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1135__PROF__mkMMUIndicationOutputPipes__l781(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1135__PROF__mkMMUIndicationOutputPipes__l781\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput_EN_ifc_configResp) {
            vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_bits 
                = vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__configResponseFifo_D_OUT;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMMUIndicationOutput__DOT__indicationPipes__DOT__configResp_responseAdapter_bits = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1136__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1136__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data0_reg 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_D_IN) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data1_reg)) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data0_reg));
    vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data1_reg 
        = (((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_ENQ) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource_D_IN
            : vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutputNoc_fifoMsgSource__DOT__data1_reg);
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1137__PROF__mkMMUSynth__l2255(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1137__PROF__mkMMUSynth__l2255\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_positive_reg 
        = ((IData)(vlTOPp->RST_N) & (0U != (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__regall_cbram_counter_1_cnt_5_PLUS_IF_regall_cb_ETC___05F_d63)));
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1138__PROF__XsimDmaReadWrite__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1138__PROF__XsimDmaReadWrite__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    IData/*31:0*/ __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__read_simDma32__8__Vfuncout;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__read_simDma32_TOP(
                                                                                (0xffU 
                                                                                & ((vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                                                                                >> 0x10U))), 
                                                                                ((IData)(4U) 
                                                                                + vlTOPp->mkXsimTop__DOT__addr___05Fh93295), __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__read_simDma32__8__Vfuncout);
            vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg 
                = __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__read_simDma32__8__Vfuncout;
            vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_valid_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_valid_reg = 0U;
                vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg = 0xbbbbbbbbU;
            }
        }
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__write_simDma32_TOP(
                                                                                (0xffU 
                                                                                & ((vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                                                                                >> 0x10U))), 
                                                                                (4U 
                                                                                | (0xfffffff8U 
                                                                                & vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifoD_OUT_BITS_47_TO_16_P_ETC___05Fq5)), 
                                                                                ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[2U] 
                                                                                << 0x19U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U] 
                                                                                >> 7U)), 0xfU);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_data_reg = 0xaaaaaaaaU;
        vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_1__DOT__readresponse_valid_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1139__PROF__XsimDmaReadWrite__l77(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1139__PROF__XsimDmaReadWrite__l77\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    IData/*31:0*/ __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__read_simDma32__6__Vfuncout;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_slave_2_0_read_rule) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__read_simDma32_TOP(
                                                                                (0xffU 
                                                                                & ((vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__slave_2_0_readDelayFifo_D_OUT[1U] 
                                                                                >> 0x10U))), vlTOPp->mkXsimTop__DOT__addr___05Fh93295, __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__read_simDma32__6__Vfuncout);
            vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg 
                = __Vfunc_mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__read_simDma32__6__Vfuncout;
            vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_valid_reg = 1U;
        } else {
            if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) {
                vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_valid_reg = 0U;
                vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg = 0xbbbbbbbbU;
            }
        }
        if (vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut_3) {
            vlTOPp->__Vdpiimwrap_mkXsimTop__DOT__lMMU_mmu__DOT__simDma_rws_0__DOT__write_simDma32_TOP(
                                                                                (0xffU 
                                                                                & ((vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[2U] 
                                                                                << 0x10U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifo_D_OUT[1U] 
                                                                                >> 0x10U))), 
                                                                                (0xfffffff8U 
                                                                                & vlTOPp->mkXsimTop__DOT__slave_2_0_writeDelayFifoD_OUT_BITS_47_TO_16_P_ETC___05Fq5), 
                                                                                ((vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[1U] 
                                                                                << 0x19U) 
                                                                                | (vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_memDataFifo__DOT__data0_reg[0U] 
                                                                                >> 7U)), 0xfU);
        }
    } else {
        vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_data_reg = 0xaaaaaaaaU;
        vlTOPp->mkXsimTop__DOT__slave_2_0_rw_rws_0__DOT__readresponse_valid_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1140__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1140__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_writer_writers_0_tag_gen_retFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1141__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1141__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__WILL_FIRE_RL_idReturnRule)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMMU_mmu__DOT__sglId_gen_retFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1142__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1142__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1143__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1143__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo_DEQ) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_mmu_servers_0_tokFifo__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1144__PROF__FIFO2__l81(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1144__PROF__FIFO2__l81\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ) 
             & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_DEQ)))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg = 1U;
        } else {
            if (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_DEQ) 
                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo_ENQ)))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg 
                    = (1U & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__full_reg)));
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_tag_gen_retFifo__DOT__empty_reg = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1145__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1145__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp172[3];
    // Body
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[0U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[1U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[1U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[1U]));
    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[2U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[2U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_read_data)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data0_reg[2U]));
    __Vtemp172[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[1U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[1U]);
    __Vtemp172[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[2U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[2U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_serverProcessing_serverAdapterA_stageReadResponseAlways) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[1U] 
        = __Vtemp172[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverData__DOT__data1_reg[2U] 
        = __Vtemp172[2U];
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1146__PROF__FIFO1__l96(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1146__PROF__FIFO1__l96\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_ENQ) {
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[0U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[0U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[0U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[1U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[1U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[1U]);
        vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifo_D_OUT[2U] 
            = ((IData)(vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__MUX_dmaErrorFifo_enq_1___05FSEL_1)
                ? vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_0_D_OUT[2U]
                : vlTOPp->mkXsimTop__DOT__lMMU_mmu__DOT__dmaErrorFifos_1_D_OUT[2U]);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1147__PROF__SizedFIFO__l107(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1147__PROF__SizedFIFO__l107\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((0x10U == (0x10U & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                 << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                            << 1U) 
                                           | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail = 0U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full = 1U;
            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata = 0U;
        } else {
            if ((0xcU == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                    << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                               << 1U) 
                                              | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_tail;
                vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head 
                    = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_head;
            } else {
                if ((9U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                      << 3U) | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata = 0U;
                } else {
                    if ((8U == (0x1dU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                          << 3U) | 
                                         (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                           << 1U) | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head 
                            = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_head;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full = 1U;
                        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty 
                            = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_head) 
                               == (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail));
                    } else {
                        if ((4U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                              << 3U) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                                 << 1U) 
                                                | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                            vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata = 1U;
                        } else {
                            if ((6U == (0x1eU & (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                                  << 3U) 
                                                 | (((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata) 
                                                     << 1U) 
                                                    | (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty)))))) {
                                if (vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full) {
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail 
                                        = vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_tail;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty = 0U;
                                    vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full 
                                        = ((IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__next_tail) 
                                           != (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head));
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__head = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__tail = 0U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__ring_empty = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__not_ring_full = 1U;
        vlTOPp->__Vdly__mkXsimTop__DOT__lMemServer_reader_readers_0_clientRequest__DOT__hasodata = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1148__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1148__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_1_deq) 
              & (3U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportStateDbg))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[0U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[1U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[2U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[3U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits_D_IN[3U];
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[0U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[1U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[2U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportStateDbg_responseAdapter_bits[3U] = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1149__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1149__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_3_deq) 
              & (5U != (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_error))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[0U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[0U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[1U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[1U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[2U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[2U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[3U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[3U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[4U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[4U];
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U] 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits_D_IN[5U];
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[0U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[1U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[2U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[3U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[4U] = 0U;
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__error_responseAdapter_bits[5U] = 0U;
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1150__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1150__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_0_deq) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_addrResponse))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__addrResponse_responseAdapter_bits = VL_ULL(0);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1151__PROF__mkMemServerIndicationOutputPipes__l1203(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1151__PROF__mkMemServerIndicationOutputPipes__l1203\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if ((((IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_portalIfc_indications_2_deq) 
              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_count))) 
             | (IData)(vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput_EN_ifc_reportMemoryTraffic))) {
            vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits 
                = vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits_D_IN;
        }
    } else {
        vlTOPp->mkXsimTop__DOT__lMemServerIndicationOutput__DOT__indicationPipes__DOT__reportMemoryTraffic_responseAdapter_bits = VL_ULL(0);
    }
}

VL_INLINE_OPT void vlsim::_sequent__TOP__1152__PROF__FIFO2__l110(vlsim__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    vlsim::_sequent__TOP__1152__PROF__FIFO2__l110\n"); );
    vlsim* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*159:0*/ __Vtemp175[5];
    WData/*159:0*/ __Vtemp183[5];
    // Body
    __Vtemp175[1U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[1U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[1U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U]));
    __Vtemp175[2U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[2U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[2U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U]));
    __Vtemp175[3U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[3U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[3U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[3U]));
    __Vtemp175[4U] = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                              & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                             | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                                 & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                        & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[4U]) 
                       | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                               & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
                          & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[4U])) 
                      | (VL_NEGATE_I((IData)((1U & 
                                              ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                 & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) 
                                                | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                                   & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                               | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                                  & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)))))) 
                         & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[4U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U] 
        = (((VL_NEGATE_I((IData)((((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                   & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                  | (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                                      & (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                     & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
             & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[0U]) 
            | (VL_NEGATE_I((IData)(((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut) 
                                    & (~ (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg))))) 
               & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[0U])) 
           | (VL_NEGATE_I((IData)((1U & ((((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                           & (~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp))) 
                                          | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_mkConnectionGetPut)) 
                                             & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))) 
                                         | ((~ (IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp)) 
                                            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__full_reg)))))) 
              & vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[0U]));
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[1U] 
        = __Vtemp175[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[2U] 
        = __Vtemp175[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[3U] 
        = __Vtemp175[3U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data0_reg[4U] 
        = __Vtemp175[4U];
    __Vtemp183[1U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[1U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[1U]);
    __Vtemp183[2U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[2U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[2U]);
    __Vtemp183[3U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[3U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[3U]);
    __Vtemp183[4U] = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
                       & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))
                       ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[4U]
                       : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[4U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[0U] 
        = (((IData)(vlTOPp->mkXsimTop__DOT__WILL_FIRE_RL_lMemServer_reader_readers_0_checkMmuResp) 
            & (IData)(vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__empty_reg))
            ? vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest_D_IN[0U]
            : vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[0U]);
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[1U] 
        = __Vtemp183[1U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[2U] 
        = __Vtemp183[2U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[3U] 
        = __Vtemp183[3U];
    vlTOPp->mkXsimTop__DOT__lMemServer_reader_readers_0_serverRequest__DOT__data1_reg[4U] 
        = __Vtemp183[4U];
}
