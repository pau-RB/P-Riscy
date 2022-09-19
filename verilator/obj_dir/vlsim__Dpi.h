// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    // DPI IMPORTS
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimSink.sv:36
    extern long long dpi_msgSink_beat(int portal);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimSource.sv:34
    extern void dpi_msgSource_beat(int portal, int beat);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimDmaReadWrite.sv:71
    extern int read_simDma32(int handle, int addr);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimDmaReadWrite.sv:69
    extern void simDma_idreturn(int aid);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimDmaReadWrite.sv:67
    extern void simDma_init(int id, int handle, int size);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimDmaReadWrite.sv:68
    extern void simDma_initfd(int id, int fd);
    // DPI import at /home/pau/Desktop/TFG/P-Risky/connectal/verilog/XsimDmaReadWrite.sv:70
    extern void write_simDma32(int handle, int addr, int data, int byteenable);
    
#ifdef __cplusplus
}
#endif
