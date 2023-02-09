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
	src/memory  \
	src/front   \
	src/back    \
	src/DDR4    \
	src/DDR4/xilinx_ddr4_v2_2 \
	src/DDR4/sim \
	src/DDR4/bsvlib \
	$(CONNECTALDIR)/bsv
CPPFILES +=                          \
	main.cpp                         \
	riscv-isa-sim/build/isa_parser.o \
	riscv-isa-sim/build/libriscv.so  \
	testbench/CustomSpike.cc         \
	testbench/Tandem.cc              \
	testbench/Interpreter.cc

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
	(cd $(BOARD); vivado -mode batch -source src/DDR4/core-scripts/synth-ddr4.tcl)

$(SYNCFIFO_784_32): src/DDR4/core-scripts/synth_sync_bram_fifo.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $^ -tclargs 784 32)

$(SYNCFIFO_640_32): src/DDR4/core-scripts/synth_sync_bram_fifo.tcl
	(cd $(PROJECTDIR); vivado -mode batch -source $^ -tclargs 640 32)

endif

CONNECTALFLAGS += --mainclockperiod=60
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
PIN_TYPE_INCLUDE = ConnectalWrapper
AUTOTOP = --interface pins:ConnectalWrapper.pins

include $(CONNECTALDIR)/Makefile.connectal

clean:
	rm -rf ./verilator
	rm -rf ./vcu108
	rm -rf ./connectal/out

slow:
	./verilator/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-mxm-ikj-f 1 2000 --color=always | less -r

fast:
	./verilator/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-mxm-ikj-f 1 600

vcu:
	./vcu108/bin/ubuntu.exe ./P-RISC-TEST/build/rv32-mxm-ikj-f 1 600
