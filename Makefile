CONNECTALDIR ?= connectal
S2H_INTERFACES = \
	FromHost:ConnectalWrapper.connectProc
H2S_INTERFACES = \
	ConnectalWrapper:ToHost:host
BSVFILES += \
	src/Ifc.bsv
BSVPATH += /    \
	src/        \
	src/include \
	src/types   \
	src/core    \
	src/widemem \
	src/frontend\
	src/backend \
	src/MulDiv  \
	src/DDR4    \
	src/DDR4/xilinx_ddr4_v2_2 \
	src/DDR4/sim \
	src/DDR4/bsvlib \
	$(CONNECTALDIR)/bsv\
    $(PWD)/bsc-contrib/Libraries/FPGA/Xilinx/\
    $(PWD)/bsc-contrib/Libraries/FPGA/Misc/

CPPFILES +=                          \
	main.cpp                         \
	riscv-isa-sim/build/isa_parser.o \
	riscv-isa-sim/build/libriscv.so  \
	testbench/CustomSpike.cc         \
	testbench/Tandem.cc              \
	testbench/Interpreter.cc

XILINX_INT_MUL_LATENCY = 1 # The BSV wrapper adds 1 cycle
XILINX_INT_DIV_LATENCY = 8 # The BSV wrapper adds 1 cycle

######### Xilinx DDR4 #########

CONNECTALFLAGS += -D IMPORT_HOSTIF -D XILINX_SYS_CLK

ifeq ($(BOARD), $(filter $(BOARD), vcu108))

CONNECTALFLAGS += \
		--verilog src/DDR4/xilinx_ddr4_v2_2/ddr4_wrapper.v \
		--xci $(CONNECTALDIR)/out/$(BOARD)/ddr4_0/ddr4_0.xci
CONNECTALFLAGS += --implconstraint src/DDR4/xilinx_ddr4_v2_2/ddr4_vcu108.xdc

DDR4_V = $(CONNECTALDIR)/out/$(BOARD)/ddr4_0/ddr4_0_stub.v

SYNCFIFO_784_32 = $(CONNECTALDIR)/out/$(BOARD)/sync_bram_fifo_w784_d32/sync_bram_fifo_w784_d32.xci
SYNCFIFO_640_32 = $(CONNECTALDIR)/out/$(BOARD)/sync_bram_fifo_w640_d32/sync_bram_fifo_w640_d32.xci

CONNECTALFLAGS += \
		--xci $(SYNCFIFO_784_32) \
		--xci $(SYNCFIFO_640_32)

prebuild:: $(DDR4_V) $(SYNCFIFO_784_32) $(SYNCFIFO_640_32)

$(DDR4_V): src/DDR4/core-scripts/synth-ddr4.tcl
	(cd $(BOARD); vivado -mode batch -source $(PWD)/src/DDR4/core-scripts/synth-ddr4.tcl)

$(SYNCFIFO_784_32): src/DDR4/core-scripts/synth_sync_bram_fifo.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $(PWD)/src/DDR4/core-scripts/synth_sync_bram_fifo.tcl -tclargs 784 32)

$(SYNCFIFO_640_32): src/DDR4/core-scripts/synth_sync_bram_fifo.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $(PWD)/src/DDR4/core-scripts/synth_sync_bram_fifo.tcl -tclargs 640 32)

endif

######### Xilinx int mul/div #########

CONNECTALFLAGS += -D XILINX_INT_MUL_LATENCY=$(XILINX_INT_MUL_LATENCY)

ifeq ($(BOARD), $(filter $(BOARD), vcu108))

INT_MUL_SIGNED_XCI = $(CONNECTALDIR)/out/$(BOARD)/int_mul_signed_32/int_mul_signed_32.xci
INT_MUL_UNSIGNED_XCI = $(CONNECTALDIR)/out/$(BOARD)/int_mul_unsigned_32/int_mul_unsigned_32.xci
INT_MUL_SIGNED_UNSIGNED_XCI = $(CONNECTALDIR)/out/$(BOARD)/int_mul_signed_unsigned_32/int_mul_signed_unsigned_32.xci
INT_DIV_UNSIGNED_XCI = $(CONNECTALDIR)/out/$(BOARD)/int_div_unsigned_32/int_div_unsigned_32.xci

INT_MUL_LATENCY = $(XILINX_INT_MUL_LATENCY)
INT_DIV_LATENCY = $(XILINX_INT_DIV_LATENCY)
CONNECTALFLAGS += --xci $(INT_MUL_SIGNED_XCI) \
				  --xci $(INT_MUL_UNSIGNED_XCI) \
				  --xci $(INT_MUL_SIGNED_UNSIGNED_XCI) \
				  --xci $(INT_DIV_UNSIGNED_XCI)

prebuild:: $(INT_MUL_SIGNED_XCI) $(INT_DIV_UNSIGNED_XCI)

$(INT_MUL_SIGNED_XCI): src/MulDiv/core-scripts/synth_int_mul.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $(PWD)/src/MulDiv/core-scripts/synth_int_mul.tcl -tclargs $(INT_MUL_LATENCY) 32)

$(INT_DIV_UNSIGNED_XCI): src/MulDiv/core-scripts/synth_int_div.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $(PWD)/src/MulDiv/core-scripts/synth_int_div.tcl -tclargs $(INT_DIV_LATENCY) 32)

.PHONY: $(INT_MUL_SIGNED_XCI) $(INT_DIV_UNSIGNED_XCI)

endif

######### connectal project #########

 CONNECTALFLAGS += -D MMIO      -D DEBUG_STATS    # FPGA and simulation - Report MMIO messages to host server through Connectal
#CONNECTALFLAGS += -D DEBUG_CMR -D DEBUG_RAW_INST # FPGA and simulation - Report commits to host server through Connectal for tandem verification
#CONNECTALFLAGS += -D DEBUG_CYC -D DEBUG_RAW_INST # simulation only     - Report cycle-accurate status of the pipeline 

 CONNECTALFLAGS += -D L2SC                        # FPGA and simulation - Add L2 cache to the memory hierarchy
 CONNECTALFLAGS += -D VCUDDRDELAY                 # FPGA only           - Add latency to DDR4 artificially
#CONNECTALFLAGS += -D MEMTEST                     # FPGA and simulation - Test main memory performance before start

CONNECTALFLAGS += --mainclockperiod=16
CONNECTALFLAGS += --bscflags="-show-schedule"
CONNECTALFLAGS += --bscflags="-aggressive-conditions"
CONNECTALFLAGS += --bscflags="-steps-warn-interval 1000000"
CONNECTALFLAGS += --bscflags="-steps-max-intervals 10000000"
CONNECTALFLAGS += --bscflags="+RTS -K250000000 -RTS"
CONNECTALFLAGS += --cxxflags="-std=gnu++17                                    \
							  -Wno-unused-variable -Wno-unused-function       \
							  -I $(PWD)/testbench                             \
							  -I $(PWD)/spike_install/include/                \
							  -I $(PWD)/spike_install/include/fesvr/          \
							  -I $(PWD)/spike_install/include/riscv/          \
							  -I $(PWD)/spike_install/include/softfloat/"     \
							  -I $(PWD)/riscv-isa-sim/riscv/                  \

PIN_TYPE = Top_Pins
PIN_TYPE_INCLUDE = WideMemDDR4
AUTOTOP = --interface pins:ConnectalWrapper.pins

include $(CONNECTALDIR)/Makefile.connectal

clean:
	rm -rf ./verilator
	rm -rf ./vcu108
	rm -rf ./connectal/out

slow:
	./verilator/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-c-matmul 1 2000 --color=always | less -r

fast:
	./verilator/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-c-matmul 1 600

vcu:
	./vcu108/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-c-matmul 1 600
