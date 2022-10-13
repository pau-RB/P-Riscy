CONNECTALDIR ?= connectal
S2H_INTERFACES = \
	FromHost:ConnectalWrapper.connectProc
H2S_INTERFACES = \
	ConnectalWrapper:ToHost
BSVFILES += \
	src/Ifc.bsv
BSVPATH += / \
	src/ \
	src/include \
	src/types \
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
CONNECTALFLAGS += --bscflags " -show-schedule"
CONNECTALFLAGS += --cxxflags="-std=gnu++11                                    \
							  -Wno-unused-variable -Wno-unused-function       \
							  -I $(PWD)/testbench                             \
							  -I $(PWD)/spike_install/include/                \
							  -I $(PWD)/spike_install/include/fesvr/          \
							  -I $(PWD)/spike_install/include/riscv/          \
							  -I $(PWD)/spike_install/include/softfloat/"

include $(CONNECTALDIR)/Makefile.connectal


clean:
	rm -rf ./verilator/*

build:
	make build.verilator

sim:
	./verilator/bin/ubuntu.exe sw 10 --color=always | less -r