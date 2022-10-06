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
	main.cpp

CONNECTALFLAGS += --mainclockperiod=50
#CONNECTALFLAGS += --verilog=ddr3_v2_0/
CONNECTALFLAGS += --bscflags " -show-schedule"
#CONNECTALFLAGS += --cxxflags="-g -std=gnu++11"

include $(CONNECTALDIR)/Makefile.connectal


clean:
	rm -rf ./verilator/*

build:
	make build.verilator

sim:
	rm -rf TMP/report.txt && ./verilator/bin/ubuntu.exe addi >> TMP/report.txt

less:
	less TMP/report.txt

spike:
	g++ -I /usr/local/include/fesvr/ -I /usr/local/include/riscv/  -I /usr/local/include/softfloat/ CustomSpike.cc 