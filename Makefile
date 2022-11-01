CONNECTALDIR ?= connectal
S2H_INTERFACES = \
	FromHost:ConnectalWrapper.connectProc
H2S_INTERFACES = \
	ConnectalWrapper:ToHost
BSVFILES += \
	src/Ifc.bsv
BSVPATH += /    \
	src/        \
	src/include \
	src/types   \
	src/memory  \
	src/front   \
	src/back    \
	$(CONNECTALDIR)/bsv
CPPFILES +=                          \
	main.cpp                         \
	riscv-isa-sim/build/isa_parser.o \
	riscv-isa-sim/build/libriscv.so  \
	testbench/CustomSpike.cc         \
	testbench/Tandem.cc              \
	testbench/Interpreter.cc
	

CONNECTALFLAGS += --mainclockperiod=50
#CONNECTALFLAGS += --verilog=ddr3_v2_0/
CONNECTALFLAGS += --bscflags="-show-schedule"
CONNECTALFLAGS += --bscflags="-steps-warn-interval 1000000"
CONNECTALFLAGS += --bscflags="-steps-max-intervals 10000000"
CONNECTALFLAGS += --bscflags="+RTS -K250000000 -RTS"
CONNECTALFLAGS += --cxxflags="-std=gnu++17                                    \
							  -Wno-unused-variable -Wno-unused-function       \
							  -I $(PWD)/testbench                             \
							  -I $(PWD)/spike_install/include/                \
							  -I $(PWD)/spike_install/include/fesvr/          \
							  -I $(PWD)/spike_install/include/riscv/          \
							  -I $(PWD)/spike_install/include/softfloat/"

include $(CONNECTALDIR)/Makefile.connectal


clean:
	rm -rf ./verilator/*

slow:
	./verilator/bin/ubuntu.exe ./test/build/rv32-reverse 6 2000 --color=always | less -r

fast:
	./verilator/bin/ubuntu.exe ./test/build/rv32-reverse 6 15