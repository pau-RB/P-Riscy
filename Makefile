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
CPPFILES += \
	main.cpp \
	/home/pau/Desktop/RVTOOLS/riscv-isa-sim/build/isa_parser.o \
	/home/pau/Desktop/RVTOOLS/riscv-isa-sim/build/libriscv.so  \
	Interpreter.cc \
	CustomSpike.cc

CONNECTALFLAGS += --mainclockperiod=50
#CONNECTALFLAGS += --verilog=ddr3_v2_0/
CONNECTALFLAGS += --bscflags " -show-schedule"
CONNECTALFLAGS += --cxxflags="-std=gnu++11                                               \
							  -Wno-unused-variable -Wno-unused-function                  \
							  -I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/                \
							  -I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/fesvr/          \
							  -I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/riscv/          \
							  -I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/softfloat/"

include $(CONNECTALDIR)/Makefile.connectal


clean:
	rm -rf ./verilator/*

build:
	make build.verilator

sim:
	rm -rf TMP/report.txt && ./verilator/bin/ubuntu.exe addi >> TMP/report.txt

less:
	less TMP/report.txt

color:
	./verilator/bin/ubuntu.exe addi --color=always | less -r

spike: Makefile CustomSpike.cc CustomSpike.h
	g++                                                        \
	-I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/                \
	-I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/fesvr/          \
	-I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/riscv/          \
	-I /home/pau/Desktop/RVTOOLS/riscv-isa-sim/softfloat/      \
	/home/pau/Desktop/RVTOOLS/riscv-isa-sim/build/isa_parser.o \
	/home/pau/Desktop/RVTOOLS/riscv-isa-sim/build/libriscv.so  \
	Interpreter.cc CustomSpike.cc mainSpike.cc -o mainSpike.exe