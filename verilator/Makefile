

##    run: run the program
##         pass parameters to software via 'make RUN_ARGS= run'
RUN_ARGS?=

export DTOP=/home/pau/Desktop/TFG/P-Risky/verilator
CONNECTALDIR=/home/pau/Desktop/TFG/P-Risky/connectal
BSVPATH = /home/pau/Desktop/TFG/P-Risky/src:/home/pau/Desktop/TFG/P-Risky/connectal/bsv:/home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv:/home/pau/Desktop/TFG/P-Risky:/:/home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv:/home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx:/home/pau/Desktop/TFG/P-Risky/connectal/generated/altera

BOARD=verilator
PROJECTDIR=/home/pau/Desktop/TFG/P-Risky/verilator
MKTOP=mkXsimTop
OS=ubuntu
TOOLCHAIN?=
DUT=mkxsimtop

export INTERFACES = MemServerRequest MMURequest MemServerIndication MMUIndication XsimMsgRequest XsimMsgIndication FromHost ToHost
BSVFILES = /home/pau/Desktop/TFG/P-Risky/src/Ifc.bsv /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMemory.bsv /home/pau/Desktop/TFG/P-Risky/connectal/bsv/XsimIF.bsv /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/IfcNames.bsv /home/pau/Desktop/TFG/P-Risky/connectal/bsv/DisplayInd.bsv
XCIFILES = 

BSCFLAGS_PROJECT =  -show-schedule
SIM_CXX_PROJECT = 
VERILATOR_PROJECT_ARGS = 
CFLAGS_PROJECT = 
CXXFLAGS_PROJECT = 
XELABFLAGS = 
XSIMFLAGS  = -R
AWSFLAGS   = 
TOPBSVFILE = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/XsimTop.bsv
BSVDEFINES =  -D ConnectalVersion=22.05.23b -D NumberOfMasters=1 -D PinType=Empty -D PinTypeInclude=Misc -D NumberOfUserTiles=1 -D SlaveDataBusWidth=32 -D SlaveControlAddrWidth=5 -D BurstLenSize=10 -D project_dir=$(DTOP) -D MainClockPeriod=20 -D DerivedClockPeriod=10.000000 -D CnocTop -D XsimHostInterface -D PhysAddrWidth=40 -D SIMULATION -D SVDPI -D CONNECTAL_BITS_DEPENDENCES=vlsim -D BOARD_verilator
QTUSED = 
export BSVDEFINES_LIST = ConnectalVersion=22.05.23b NumberOfMasters=1 PinType=Empty PinTypeInclude=Misc NumberOfUserTiles=1 SlaveDataBusWidth=32 SlaveControlAddrWidth=5 BurstLenSize=10 project_dir=$(DTOP) MainClockPeriod=20 DerivedClockPeriod=10.000000 CnocTop XsimHostInterface PhysAddrWidth=40 SIMULATION SVDPI CONNECTAL_BITS_DEPENDENCES=vlsim BOARD_verilator
export DUT_NAME = mkXsimTop





ConnectalVersion=22.05.23b
NumberOfMasters=1
PinType=Empty
PinTypeInclude=Misc
NumberOfUserTiles=1
SlaveDataBusWidth=32
SlaveControlAddrWidth=5
BurstLenSize=10
project_dir=$(DTOP)
MainClockPeriod=20
DerivedClockPeriod=10.000000
CnocTop=CnocTop
XsimHostInterface=XsimHostInterface
PhysAddrWidth=40
SIMULATION=SIMULATION
SVDPI=SVDPI
CONNECTAL_BITS_DEPENDENCES=vlsim
BOARD_verilator=BOARD_verilator


include $(CONNECTALDIR)/scripts/Makefile.connectal.build


export VERILOG_PATH=verilog /home/pau/Desktop/TFG/P-Risky/connectal/verilog $(BLUESPEC_VERILOG)
MODELSIM_FILES= 
FPGAMAKE=$(CONNECTALDIR)/../fpgamake/fpgamake
fpgamake.mk: $(VFILE) Makefile prepare_bin_target
	$(Q)if [ -f ../synth-ip.tcl ]; then vivado -mode batch -source ../synth-ip.tcl; fi
	$(Q)$(FPGAMAKE) $(FPGAMAKE_VERBOSE) -o fpgamake.mk --board=verilator --part=xc7z020clg484-1  --floorplan=      -t $(MKTOP)   -b hw/mkTop.bit   $(VERILOG_PATH)

synth.%:fpgamake.mk
	$(MAKE) -f fpgamake.mk Synth/$*/$*-synth.dcp

hw/mkTop.bit: prepare_bin_target  fpgamake.mk
	$(Q)mkdir -p hw
	$(Q)$(MAKE) -f fpgamake.mk
ifneq ($(XILINX),)
	$(Q)rsync -rav --include="*/" --include="*.rpt" --exclude="*" Impl/ bin
else ifneq ($(ALTERA),)
	$(Q)cp -f $(MKTOP).sof bin
endif




