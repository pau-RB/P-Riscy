# BSV dependences
#  -DConnectalVersion=22.05.23b
#  -DNumberOfMasters=1
#  -DPinType=Empty
#  -DPinTypeInclude=Misc
#  -DNumberOfUserTiles=1
#  -DSlaveDataBusWidth=32
#  -DSlaveControlAddrWidth=5
#  -DBurstLenSize=10
#  -Dproject_dir=/home/pau/Desktop/TFG/P-Risky/verilator
#  -DMainClockPeriod=20
#  -DDerivedClockPeriod=10.000000
#  -DCnocTop
#  -DXsimHostInterface
#  -DPhysAddrWidth=40
#  -DSIMULATION
#  -DSVDPI
#  -DCONNECTAL_BITS_DEPENDENCES=vlsim
#  -DBOARD_verilator
OBJMAKEFILE_DEP = $(wildcard /home/pau/Desktop/TFG/P-Risky/src/*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/connectal/bsv/*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/*.bsv) $(wildcard //*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/*.bsv) $(wildcard /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/*.bsv)


XsimTop_BO  = obj/XsimTop.bo
XsimTop_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/Top.bo obj/HostInterface.bo obj/Pipe.bo obj/CnocPortal.bo obj/ConnectalMemTypes.bo obj/ConnectalMMU.bo obj/MemServer.bo obj/MMURequest.bo obj/MMUIndication.bo obj/MemServerIndication.bo obj/MemServerRequest.bo obj/SimDma.bo obj/IfcNames.bo
XsimTop_INC = 
XsimTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/XsimTop.bsv

$(eval $(call BSV_BO_RULE, $(XsimTop_BO), $(XsimTop_BSV), $(XsimTop_DEP), $(XsimTop_INC)))

Cache_BO  = obj/Cache.bo
Cache_DEP = obj/Types.bo obj/MemTypes.bo obj/CacheTypes.bo obj/MemUtil.bo
Cache_INC = 
Cache_BSV = /home/pau/Desktop/TFG/P-Risky/src/Cache.bsv

$(eval $(call BSV_BO_RULE, $(Cache_BO), $(Cache_BSV), $(Cache_DEP), $(Cache_INC)))

Core_BO  = obj/Core.bo
Core_DEP = obj/Types.bo obj/ProcTypes.bo obj/Scoreboard.bo obj/decoder.bo obj/execution.bo obj/CacheTypes.bo obj/MemTypes.bo obj/MemUtil.bo obj/Cache.bo obj/RFile.bo obj/Fifo.bo obj/Ehr.bo
Core_INC = 
Core_BSV = /home/pau/Desktop/TFG/P-Risky/src/Core.bsv

$(eval $(call BSV_BO_RULE, $(Core_BO), $(Core_BSV), $(Core_DEP), $(Core_INC)))

Scoreboard_BO  = obj/Scoreboard.bo
Scoreboard_DEP = obj/SFifo.bo obj/ProcTypes.bo
Scoreboard_INC = 
Scoreboard_BSV = /home/pau/Desktop/TFG/P-Risky/src/Scoreboard.bsv

$(eval $(call BSV_BO_RULE, $(Scoreboard_BO), $(Scoreboard_BSV), $(Scoreboard_DEP), $(Scoreboard_INC)))

RFile_BO  = obj/RFile.bo
RFile_DEP = obj/Types.bo obj/ProcTypes.bo obj/Ehr.bo
RFile_INC = 
RFile_BSV = /home/pau/Desktop/TFG/P-Risky/src/RFile.bsv

$(eval $(call BSV_BO_RULE, $(RFile_BO), $(RFile_BSV), $(RFile_DEP), $(RFile_INC)))

RFile_MOD = mkRFile
RFile_V   = verilog/mkRFile.v
RFile_BO  = obj/RFile.bo
RFile_BSV = /home/pau/Desktop/TFG/P-Risky/src/RFile.bsv
RFile_DEP = obj/Types.bo obj/ProcTypes.bo obj/Ehr.bo
RFile_INC = 

$(eval $(call BSV_V_RULE, $(RFile_MOD), $(RFile_V), $(RFile_BSV), $(RFile_DEP), $(RFile_INC)))

RFile_MOD = mkBypassRFile
RFile_V   = verilog/mkBypassRFile.v
RFile_BO  = obj/RFile.bo
RFile_BSV = /home/pau/Desktop/TFG/P-Risky/src/RFile.bsv
RFile_DEP = obj/Types.bo obj/ProcTypes.bo obj/Ehr.bo
RFile_INC = 

$(eval $(call BSV_V_RULE, $(RFile_MOD), $(RFile_V), $(RFile_BSV), $(RFile_DEP), $(RFile_INC)))

execution_BO  = obj/execution.bo
execution_DEP = obj/Types.bo obj/ProcTypes.bo
execution_INC = 
execution_BSV = /home/pau/Desktop/TFG/P-Risky/src/execution.bsv

$(eval $(call BSV_BO_RULE, $(execution_BO), $(execution_BSV), $(execution_DEP), $(execution_INC)))

ProcTypes_BO  = obj/ProcTypes.bo
ProcTypes_DEP = obj/Types.bo
ProcTypes_INC = 
ProcTypes_BSV = /home/pau/Desktop/TFG/P-Risky/src/ProcTypes.bsv

$(eval $(call BSV_BO_RULE, $(ProcTypes_BO), $(ProcTypes_BSV), $(ProcTypes_DEP), $(ProcTypes_INC)))

Ehr_BO  = obj/Ehr.bo
Ehr_DEP = 
Ehr_INC = 
Ehr_BSV = /home/pau/Desktop/TFG/P-Risky/src/Ehr.bsv

$(eval $(call BSV_BO_RULE, $(Ehr_BO), $(Ehr_BSV), $(Ehr_DEP), $(Ehr_INC)))

SFifo_BO  = obj/SFifo.bo
SFifo_DEP = obj/Ehr.bo
SFifo_INC = 
SFifo_BSV = /home/pau/Desktop/TFG/P-Risky/src/SFifo.bsv

$(eval $(call BSV_BO_RULE, $(SFifo_BO), $(SFifo_BSV), $(SFifo_DEP), $(SFifo_INC)))

Types_BO  = obj/Types.bo
Types_DEP = 
Types_INC = 
Types_BSV = /home/pau/Desktop/TFG/P-Risky/src/Types.bsv

$(eval $(call BSV_BO_RULE, $(Types_BO), $(Types_BSV), $(Types_DEP), $(Types_INC)))

MemTypes_BO  = obj/MemTypes.bo
MemTypes_DEP = obj/Types.bo
MemTypes_INC = 
MemTypes_BSV = /home/pau/Desktop/TFG/P-Risky/src/MemTypes.bsv

$(eval $(call BSV_BO_RULE, $(MemTypes_BO), $(MemTypes_BSV), $(MemTypes_DEP), $(MemTypes_INC)))

CacheTypes_BO  = obj/CacheTypes.bo
CacheTypes_DEP = obj/MemTypes.bo obj/Types.bo
CacheTypes_INC = 
CacheTypes_BSV = /home/pau/Desktop/TFG/P-Risky/src/CacheTypes.bsv

$(eval $(call BSV_BO_RULE, $(CacheTypes_BO), $(CacheTypes_BSV), $(CacheTypes_DEP), $(CacheTypes_INC)))

Fifo_BO  = obj/Fifo.bo
Fifo_DEP = obj/Ehr.bo
Fifo_INC = 
Fifo_BSV = /home/pau/Desktop/TFG/P-Risky/src/Fifo.bsv

$(eval $(call BSV_BO_RULE, $(Fifo_BO), $(Fifo_BSV), $(Fifo_DEP), $(Fifo_INC)))

Ifc_BO  = obj/Ifc.bo
Ifc_DEP = 
Ifc_INC = 
Ifc_BSV = /home/pau/Desktop/TFG/P-Risky/src/Ifc.bsv

$(eval $(call BSV_BO_RULE, $(Ifc_BO), $(Ifc_BSV), $(Ifc_DEP), $(Ifc_INC)))

MemUtil_BO  = obj/MemUtil.bo
MemUtil_DEP = obj/Types.bo obj/ProcTypes.bo obj/MemTypes.bo obj/CacheTypes.bo obj/Fifo.bo
MemUtil_INC = 
MemUtil_BSV = /home/pau/Desktop/TFG/P-Risky/src/MemUtil.bsv

$(eval $(call BSV_BO_RULE, $(MemUtil_BO), $(MemUtil_BSV), $(MemUtil_DEP), $(MemUtil_INC)))

decoder_BO  = obj/decoder.bo
decoder_DEP = obj/Types.bo obj/ProcTypes.bo
decoder_INC = 
decoder_BSV = /home/pau/Desktop/TFG/P-Risky/src/decoder.bsv

$(eval $(call BSV_BO_RULE, $(decoder_BO), $(decoder_BSV), $(decoder_DEP), $(decoder_INC)))

MemReadEngine_BO  = obj/MemReadEngine.bo
MemReadEngine_DEP = obj/ConfigCounter.bo obj/ConnectalMemory.bo obj/ConnectalBramFifo.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/ConnectalMemUtils.bo obj/ConnectalConfig.bo
MemReadEngine_INC = 
MemReadEngine_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemReadEngine.bsv

$(eval $(call BSV_BO_RULE, $(MemReadEngine_BO), $(MemReadEngine_BSV), $(MemReadEngine_DEP), $(MemReadEngine_INC)))

Adapter_BO  = obj/Adapter.bo
Adapter_DEP = obj/Pipe.bo
Adapter_INC = 
Adapter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Adapter.bsv

$(eval $(call BSV_BO_RULE, $(Adapter_BO), $(Adapter_BSV), $(Adapter_DEP), $(Adapter_INC)))

GearboxGetPut_BO  = obj/GearboxGetPut.bo
GearboxGetPut_DEP = 
GearboxGetPut_INC = 
GearboxGetPut_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/GearboxGetPut.bsv

$(eval $(call BSV_BO_RULE, $(GearboxGetPut_BO), $(GearboxGetPut_BSV), $(GearboxGetPut_DEP), $(GearboxGetPut_INC)))

ZynqUltraTop_BO  = obj/ZynqUltraTop.bo
ZynqUltraTop_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectableWithTrace.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/AxiMasterSlave.bo obj/ConnectalXilinxCells.bo obj/PS8LIB.bo obj/ZYNQ_ULTRA.bo obj/CtrlMux.bo obj/AxiDma.bo obj/Top.bo obj/Bscan.bo obj/HostInterface.bo obj/Platform.bo
ZynqUltraTop_INC = 
ZynqUltraTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ZynqUltraTop.bsv

$(eval $(call BSV_BO_RULE, $(ZynqUltraTop_BO), $(ZynqUltraTop_BSV), $(ZynqUltraTop_DEP), $(ZynqUltraTop_INC)))

LinkerLib_BO  = obj/LinkerLib.bo
LinkerLib_DEP = 
LinkerLib_INC = 
LinkerLib_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/LinkerLib.bsv

$(eval $(call BSV_BO_RULE, $(LinkerLib_BO), $(LinkerLib_BSV), $(LinkerLib_DEP), $(LinkerLib_INC)))

ConnectalFIFO_BO  = obj/ConnectalFIFO.bo
ConnectalFIFO_DEP = obj/ConnectalEHR.bo
ConnectalFIFO_INC = 
ConnectalFIFO_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalFIFO.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalFIFO_BO), $(ConnectalFIFO_BSV), $(ConnectalFIFO_DEP), $(ConnectalFIFO_INC)))

PcieStateChanges_BO  = obj/PcieStateChanges.bo
PcieStateChanges_DEP = obj/Pipe.bo
PcieStateChanges_INC = 
PcieStateChanges_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieStateChanges.bsv

$(eval $(call BSV_BO_RULE, $(PcieStateChanges_BO), $(PcieStateChanges_BSV), $(PcieStateChanges_DEP), $(PcieStateChanges_INC)))

AxiDma_BO  = obj/AxiDma.bo
AxiDma_DEP = obj/ConnectalConfig.bo obj/AxiMasterSlave.bo obj/Axi4MasterSlave.bo obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo
AxiDma_INC = 
AxiDma_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiDma.bsv

$(eval $(call BSV_BO_RULE, $(AxiDma_BO), $(AxiDma_BSV), $(AxiDma_DEP), $(AxiDma_INC)))

Pcie3RootPortX7_BO  = obj/Pcie3RootPortX7.bo
Pcie3RootPortX7_DEP = obj/CFFIFO.bo obj/XilinxVirtex7PCIE.bo obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/ROOTPCIEWRAPPER3.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/Pipe.bo
Pcie3RootPortX7_INC = 
Pcie3RootPortX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie3RootPortX7.bsv

$(eval $(call BSV_BO_RULE, $(Pcie3RootPortX7_BO), $(Pcie3RootPortX7_BSV), $(Pcie3RootPortX7_DEP), $(Pcie3RootPortX7_INC)))

Pcie3RootPortX7_MOD = mkPcieRootPortX7
Pcie3RootPortX7_V   = verilog/mkPcieRootPortX7.v
Pcie3RootPortX7_BO  = obj/Pcie3RootPortX7.bo
Pcie3RootPortX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie3RootPortX7.bsv
Pcie3RootPortX7_DEP = obj/CFFIFO.bo obj/XilinxVirtex7PCIE.bo obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/ROOTPCIEWRAPPER3.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/Pipe.bo
Pcie3RootPortX7_INC = 

$(eval $(call BSV_V_RULE, $(Pcie3RootPortX7_MOD), $(Pcie3RootPortX7_V), $(Pcie3RootPortX7_BSV), $(Pcie3RootPortX7_DEP), $(Pcie3RootPortX7_INC)))

Portal_BO  = obj/Portal.bo
Portal_DEP = obj/ConnectalConfig.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/ConnectalMemory.bo obj/HostInterface.bo
Portal_INC = 
Portal_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Portal.bsv

$(eval $(call BSV_BO_RULE, $(Portal_BO), $(Portal_BSV), $(Portal_DEP), $(Portal_INC)))

PS7Trace_BO  = obj/PS7Trace.bo
PS7Trace_DEP = obj/ConnectalConfig.bo obj/ConnectableWithTrace.bo obj/HostInterface.bo obj/PS7LIB.bo obj/Portal.bo obj/AxiMasterSlave.bo obj/AxiDma.bo obj/AxiBits.bo obj/AxiGather.bo obj/Platform.bo
PS7Trace_INC = 
PS7Trace_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS7Trace.bsv

$(eval $(call BSV_BO_RULE, $(PS7Trace_BO), $(PS7Trace_BSV), $(PS7Trace_DEP), $(PS7Trace_INC)))

AvalonGather_BO  = obj/AvalonGather.bo
AvalonGather_DEP = obj/AvalonBits.bo obj/AvalonMasterSlave.bo
AvalonGather_INC = 
AvalonGather_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonGather.bsv

$(eval $(call BSV_BO_RULE, $(AvalonGather_BO), $(AvalonGather_BSV), $(AvalonGather_DEP), $(AvalonGather_INC)))

ConnectalMimo_BO  = obj/ConnectalMimo.bo
ConnectalMimo_DEP = obj/ConnectalBramFifo.bo
ConnectalMimo_INC = 
ConnectalMimo_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMimo.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalMimo_BO), $(ConnectalMimo_BSV), $(ConnectalMimo_DEP), $(ConnectalMimo_INC)))

PcieHost_BO  = obj/PcieHost.bo
PcieHost_DEP = obj/ConnectalConfig.bo obj/PcieSplitter.bo obj/PcieTracer.bo obj/ConnectalXilinxCells.bo obj/Bscan.bo obj/Portal.bo obj/MemToPcie.bo obj/PcieToMem.bo obj/PcieCsr.bo obj/ConnectalMemTypes.bo obj/HostInterface.bo
PcieHost_INC = 
PcieHost_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieHost.bsv

$(eval $(call BSV_BO_RULE, $(PcieHost_BO), $(PcieHost_BSV), $(PcieHost_DEP), $(PcieHost_INC)))

PcieHost_MOD = mkMemToPcieSynth
PcieHost_V   = verilog/mkMemToPcieSynth.v
PcieHost_BO  = obj/PcieHost.bo
PcieHost_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieHost.bsv
PcieHost_DEP = obj/ConnectalConfig.bo obj/PcieSplitter.bo obj/PcieTracer.bo obj/ConnectalXilinxCells.bo obj/Bscan.bo obj/Portal.bo obj/MemToPcie.bo obj/PcieToMem.bo obj/PcieCsr.bo obj/ConnectalMemTypes.bo obj/HostInterface.bo
PcieHost_INC = 

$(eval $(call BSV_V_RULE, $(PcieHost_MOD), $(PcieHost_V), $(PcieHost_BSV), $(PcieHost_DEP), $(PcieHost_INC)))

AxiStream_BO  = obj/AxiStream.bo
AxiStream_DEP = obj/GetPutM.bo
AxiStream_INC = 
AxiStream_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiStream.bsv

$(eval $(call BSV_BO_RULE, $(AxiStream_BO), $(AxiStream_BSV), $(AxiStream_DEP), $(AxiStream_INC)))

ConnectalMemUtils_BO  = obj/ConnectalMemUtils.bo
ConnectalMemUtils_DEP = obj/ConnectalConfig.bo obj/ConnectalMemTypes.bo obj/ConfigCounter.bo obj/BRAMFIFOFLevel.bo
ConnectalMemUtils_INC = 
ConnectalMemUtils_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMemUtils.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalMemUtils_BO), $(ConnectalMemUtils_BSV), $(ConnectalMemUtils_DEP), $(ConnectalMemUtils_INC)))

Axi4MasterSlave_BO  = obj/Axi4MasterSlave.bo
Axi4MasterSlave_DEP = obj/ConnectalMemTypes.bo
Axi4MasterSlave_INC = 
Axi4MasterSlave_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Axi4MasterSlave.bsv

$(eval $(call BSV_BO_RULE, $(Axi4MasterSlave_BO), $(Axi4MasterSlave_BSV), $(Axi4MasterSlave_DEP), $(Axi4MasterSlave_INC)))

CnocPortal_BO  = obj/CnocPortal.bo
CnocPortal_DEP = obj/ConnectalConfig.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/Portal.bo obj/HostInterface.bo
CnocPortal_INC = 
CnocPortal_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/CnocPortal.bsv

$(eval $(call BSV_BO_RULE, $(CnocPortal_BO), $(CnocPortal_BSV), $(CnocPortal_DEP), $(CnocPortal_INC)))

ConnectalEHR_BO  = obj/ConnectalEHR.bo
ConnectalEHR_DEP = 
ConnectalEHR_INC = 
ConnectalEHR_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalEHR.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalEHR_BO), $(ConnectalEHR_BSV), $(ConnectalEHR_DEP), $(ConnectalEHR_INC)))

BpiFlash_BO  = obj/BpiFlash.bo
BpiFlash_DEP = obj/ConnectalXilinxCells.bo obj/I28F512P33.bo
BpiFlash_INC = 
BpiFlash_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/BpiFlash.bsv

$(eval $(call BSV_BO_RULE, $(BpiFlash_BO), $(BpiFlash_BSV), $(BpiFlash_DEP), $(BpiFlash_INC)))

ConnectalBramFifo_BO  = obj/ConnectalBramFifo.bo
ConnectalBramFifo_DEP = obj/Arith.bo obj/ConnectalClocks.bo
ConnectalBramFifo_INC = 
ConnectalBramFifo_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalBramFifo.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalBramFifo_BO), $(ConnectalBramFifo_BSV), $(ConnectalBramFifo_DEP), $(ConnectalBramFifo_INC)))

TraceMemClient_BO  = obj/TraceMemClient.bo
TraceMemClient_DEP = obj/Pipe.bo obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo
TraceMemClient_INC = 
TraceMemClient_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/TraceMemClient.bsv

$(eval $(call BSV_BO_RULE, $(TraceMemClient_BO), $(TraceMemClient_BSV), $(TraceMemClient_DEP), $(TraceMemClient_INC)))

SyncAxisFifo32x8_BO  = obj/SyncAxisFifo32x8.bo
SyncAxisFifo32x8_DEP = obj/ConnectalFIFO.bo obj/AxiBits.bo obj/AxiStream.bo
SyncAxisFifo32x8_INC = 
SyncAxisFifo32x8_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/SyncAxisFifo32x8.bsv

$(eval $(call BSV_BO_RULE, $(SyncAxisFifo32x8_BO), $(SyncAxisFifo32x8_BSV), $(SyncAxisFifo32x8_DEP), $(SyncAxisFifo32x8_INC)))

AvalonDma_BO  = obj/AvalonDma.bo
AvalonDma_DEP = obj/ConnectalConfig.bo obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo obj/AvalonMasterSlave.bo obj/AvalonBits.bo obj/AddressGenerator.bo obj/AvalonSplitter.bo
AvalonDma_INC = 
AvalonDma_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonDma.bsv

$(eval $(call BSV_BO_RULE, $(AvalonDma_BO), $(AvalonDma_BSV), $(AvalonDma_DEP), $(AvalonDma_INC)))

AxiMasterSlave_BO  = obj/AxiMasterSlave.bo
AxiMasterSlave_DEP = obj/GetPutWithClocks.bo
AxiMasterSlave_INC = 
AxiMasterSlave_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiMasterSlave.bsv

$(eval $(call BSV_BO_RULE, $(AxiMasterSlave_BO), $(AxiMasterSlave_BSV), $(AxiMasterSlave_DEP), $(AxiMasterSlave_INC)))

PcieToMem_BO  = obj/PcieToMem.bo
PcieToMem_DEP = obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo
PcieToMem_INC = 
PcieToMem_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieToMem.bsv

$(eval $(call BSV_BO_RULE, $(PcieToMem_BO), $(PcieToMem_BSV), $(PcieToMem_DEP), $(PcieToMem_INC)))

PcieToMem_MOD = mkPcieToMem
PcieToMem_V   = verilog/mkPcieToMem.v
PcieToMem_BO  = obj/PcieToMem.bo
PcieToMem_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieToMem.bsv
PcieToMem_DEP = obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo
PcieToMem_INC = 

$(eval $(call BSV_V_RULE, $(PcieToMem_MOD), $(PcieToMem_V), $(PcieToMem_BSV), $(PcieToMem_DEP), $(PcieToMem_INC)))

PcieToMem_MOD = mkMemInterrupt
PcieToMem_V   = verilog/mkMemInterrupt.v
PcieToMem_BO  = obj/PcieToMem.bo
PcieToMem_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieToMem.bsv
PcieToMem_DEP = obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo
PcieToMem_INC = 

$(eval $(call BSV_V_RULE, $(PcieToMem_MOD), $(PcieToMem_V), $(PcieToMem_BSV), $(PcieToMem_DEP), $(PcieToMem_INC)))

HostInterface_BO  = obj/HostInterface.bo
HostInterface_DEP = obj/ConnectalConfig.bo obj/AxiMasterSlave.bo obj/ConnectalMemTypes.bo
HostInterface_INC = 
HostInterface_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/HostInterface.bsv

$(eval $(call BSV_BO_RULE, $(HostInterface_BO), $(HostInterface_BSV), $(HostInterface_DEP), $(HostInterface_INC)))

MemServerPortal_BO  = obj/MemServerPortal.bo
MemServerPortal_DEP = obj/ConfigCounter.bo obj/ConnectalFIFO.bo obj/ConnectalConfig.bo obj/ConnectalMemTypes.bo
MemServerPortal_INC = 
MemServerPortal_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemServerPortal.bsv

$(eval $(call BSV_BO_RULE, $(MemServerPortal_BO), $(MemServerPortal_BSV), $(MemServerPortal_DEP), $(MemServerPortal_INC)))

PcieRootPortX7_BO  = obj/PcieRootPortX7.bo
PcieRootPortX7_DEP = obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER.bo obj/Bufgctrl.bo
PcieRootPortX7_INC = 
PcieRootPortX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieRootPortX7.bsv

$(eval $(call BSV_BO_RULE, $(PcieRootPortX7_BO), $(PcieRootPortX7_BSV), $(PcieRootPortX7_DEP), $(PcieRootPortX7_INC)))

PcieRootPortX7_MOD = mkPcieRootPortX7
PcieRootPortX7_V   = verilog/mkPcieRootPortX7.v
PcieRootPortX7_BO  = obj/PcieRootPortX7.bo
PcieRootPortX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieRootPortX7.bsv
PcieRootPortX7_DEP = obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER.bo obj/Bufgctrl.bo
PcieRootPortX7_INC = 

$(eval $(call BSV_V_RULE, $(PcieRootPortX7_MOD), $(PcieRootPortX7_V), $(PcieRootPortX7_BSV), $(PcieRootPortX7_DEP), $(PcieRootPortX7_INC)))

ConnectalClocks_BO  = obj/ConnectalClocks.bo
ConnectalClocks_DEP = 
ConnectalClocks_INC = 
ConnectalClocks_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalClocks.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalClocks_BO), $(ConnectalClocks_BSV), $(ConnectalClocks_DEP), $(ConnectalClocks_INC)))

Pcie1EndpointX7_BO  = obj/Pcie1EndpointX7.bo
Pcie1EndpointX7_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/PcieStateChanges.bo obj/Pipe.bo
Pcie1EndpointX7_INC = 
Pcie1EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie1EndpointX7.bsv

$(eval $(call BSV_BO_RULE, $(Pcie1EndpointX7_BO), $(Pcie1EndpointX7_BSV), $(Pcie1EndpointX7_DEP), $(Pcie1EndpointX7_INC)))

Pcie1EndpointX7_MOD = mkPcieEndpointX7
Pcie1EndpointX7_V   = verilog/mkPcieEndpointX7.v
Pcie1EndpointX7_BO  = obj/Pcie1EndpointX7.bo
Pcie1EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie1EndpointX7.bsv
Pcie1EndpointX7_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/PcieStateChanges.bo obj/Pipe.bo
Pcie1EndpointX7_INC = 

$(eval $(call BSV_V_RULE, $(Pcie1EndpointX7_MOD), $(Pcie1EndpointX7_V), $(Pcie1EndpointX7_BSV), $(Pcie1EndpointX7_DEP), $(Pcie1EndpointX7_INC)))

PS5LIB_BO  = obj/PS5LIB.bo
PS5LIB_DEP = obj/ConnectalAlteraCells.bo obj/ConnectalClocks.bo obj/ALTERA_XCVR_RECONFIG_WRAPPER.bo obj/ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER.bo obj/ALTERA_PCIE_SV_WRAPPER.bo
PS5LIB_INC = 
PS5LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS5LIB.bsv

$(eval $(call BSV_BO_RULE, $(PS5LIB_BO), $(PS5LIB_BSV), $(PS5LIB_DEP), $(PS5LIB_INC)))

PS5LIB_MOD = mkAlteraPcieHipRs
PS5LIB_V   = verilog/mkAlteraPcieHipRs.v
PS5LIB_BO  = obj/PS5LIB.bo
PS5LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS5LIB.bsv
PS5LIB_DEP = obj/ConnectalAlteraCells.bo obj/ConnectalClocks.bo obj/ALTERA_XCVR_RECONFIG_WRAPPER.bo obj/ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER.bo obj/ALTERA_PCIE_SV_WRAPPER.bo
PS5LIB_INC = 

$(eval $(call BSV_V_RULE, $(PS5LIB_MOD), $(PS5LIB_V), $(PS5LIB_BSV), $(PS5LIB_DEP), $(PS5LIB_INC)))

PcieEndpointS5Test_BO  = obj/PcieEndpointS5Test.bo
PcieEndpointS5Test_DEP = obj/ConnectalAlteraCells.bo obj/ALTERA_PCIE_ED_WRAPPER.bo obj/PS5LIB.bo
PcieEndpointS5Test_INC = 
PcieEndpointS5Test_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieEndpointS5Test.bsv

$(eval $(call BSV_BO_RULE, $(PcieEndpointS5Test_BO), $(PcieEndpointS5Test_BSV), $(PcieEndpointS5Test_DEP), $(PcieEndpointS5Test_INC)))

PcieTop_BO  = obj/PcieTop.bo
PcieTop_DEP = obj/ConnectalConfig.bo obj/PcieSplitter.bo obj/Portal.bo obj/Top.bo obj/PcieCsr.bo obj/ConnectalMemTypes.bo obj/Bscan.bo obj/ConnectalClocks.bo obj/GetPutWithClocks.bo obj/PcieHost.bo obj/HostInterface.bo obj/Platform.bo
PcieTop_INC = 
PcieTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieTop.bsv

$(eval $(call BSV_BO_RULE, $(PcieTop_BO), $(PcieTop_BSV), $(PcieTop_DEP), $(PcieTop_INC)))

PcieEndpointS5_BO  = obj/PcieEndpointS5.bo
PcieEndpointS5_DEP = obj/ConnectalConfig.bo
PcieEndpointS5_INC = 
PcieEndpointS5_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieEndpointS5.bsv

$(eval $(call BSV_BO_RULE, $(PcieEndpointS5_BO), $(PcieEndpointS5_BSV), $(PcieEndpointS5_DEP), $(PcieEndpointS5_INC)))

PcieEndpointS5_MOD = mkPcieEndpointS5
PcieEndpointS5_V   = verilog/mkPcieEndpointS5.v
PcieEndpointS5_BO  = obj/PcieEndpointS5.bo
PcieEndpointS5_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieEndpointS5.bsv
PcieEndpointS5_DEP = obj/ConnectalConfig.bo
PcieEndpointS5_INC = 

$(eval $(call BSV_V_RULE, $(PcieEndpointS5_MOD), $(PcieEndpointS5_V), $(PcieEndpointS5_BSV), $(PcieEndpointS5_DEP), $(PcieEndpointS5_INC)))

BramMux_BO  = obj/BramMux.bo
BramMux_DEP = 
BramMux_INC = 
BramMux_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/BramMux.bsv

$(eval $(call BSV_BO_RULE, $(BramMux_BO), $(BramMux_BSV), $(BramMux_DEP), $(BramMux_INC)))

ConnectalAlteraCells_BO  = obj/ConnectalAlteraCells.bo
ConnectalAlteraCells_DEP = obj/ConnectalClocks.bo
ConnectalAlteraCells_INC = 
ConnectalAlteraCells_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalAlteraCells.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalAlteraCells_BO), $(ConnectalAlteraCells_BSV), $(ConnectalAlteraCells_DEP), $(ConnectalAlteraCells_INC)))

PcieGearbox_BO  = obj/PcieGearbox.bo
PcieGearbox_DEP = 
PcieGearbox_INC = 
PcieGearbox_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieGearbox.bsv

$(eval $(call BSV_BO_RULE, $(PcieGearbox_BO), $(PcieGearbox_BSV), $(PcieGearbox_DEP), $(PcieGearbox_INC)))

Pcie3EndpointX7_BO  = obj/Pcie3EndpointX7.bo
Pcie3EndpointX7_DEP = obj/ConnectalFIFO.bo obj/XilinxVirtex7PCIE.bo obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER3.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/Pipe.bo
Pcie3EndpointX7_INC = 
Pcie3EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie3EndpointX7.bsv

$(eval $(call BSV_BO_RULE, $(Pcie3EndpointX7_BO), $(Pcie3EndpointX7_BSV), $(Pcie3EndpointX7_DEP), $(Pcie3EndpointX7_INC)))

Pcie3EndpointX7_MOD = mkPcieEndpointX7
Pcie3EndpointX7_V   = verilog/mkPcieEndpointX7.v
Pcie3EndpointX7_BO  = obj/Pcie3EndpointX7.bo
Pcie3EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie3EndpointX7.bsv
Pcie3EndpointX7_DEP = obj/ConnectalFIFO.bo obj/XilinxVirtex7PCIE.bo obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER3.bo obj/Bufgctrl.bo obj/PcieGearbox.bo obj/Pipe.bo
Pcie3EndpointX7_INC = 

$(eval $(call BSV_V_RULE, $(Pcie3EndpointX7_MOD), $(Pcie3EndpointX7_V), $(Pcie3EndpointX7_BSV), $(Pcie3EndpointX7_DEP), $(Pcie3EndpointX7_INC)))

AxiDdr3Controller_BO  = obj/AxiDdr3Controller.bo
AxiDdr3Controller_DEP = obj/AxiDdr3Wrapper.bo obj/AxiBits.bo obj/AxiGather.bo obj/Axi4MasterSlave.bo obj/ConnectalClocks.bo
AxiDdr3Controller_INC = 
AxiDdr3Controller_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiDdr3Controller.bsv

$(eval $(call BSV_BO_RULE, $(AxiDdr3Controller_BO), $(AxiDdr3Controller_BSV), $(AxiDdr3Controller_DEP), $(AxiDdr3Controller_INC)))

AxiDdr3Controller_MOD = mkDdr3
AxiDdr3Controller_V   = verilog/mkDdr3.v
AxiDdr3Controller_BO  = obj/AxiDdr3Controller.bo
AxiDdr3Controller_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiDdr3Controller.bsv
AxiDdr3Controller_DEP = obj/AxiDdr3Wrapper.bo obj/AxiBits.bo obj/AxiGather.bo obj/Axi4MasterSlave.bo obj/ConnectalClocks.bo
AxiDdr3Controller_INC = 

$(eval $(call BSV_V_RULE, $(AxiDdr3Controller_MOD), $(AxiDdr3Controller_V), $(AxiDdr3Controller_BSV), $(AxiDdr3Controller_DEP), $(AxiDdr3Controller_INC)))

ParallellaTop_BO  = obj/ParallellaTop.bo
ParallellaTop_DEP = obj/ConnectableWithTrace.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/AxiMasterSlave.bo obj/ConnectalXilinxCells.bo obj/PS7LIB.bo obj/PS7Trace.bo obj/PPS7LIB.bo obj/CtrlMux.bo obj/AxiDma.bo obj/Top.bo obj/Bscan.bo obj/HostInterface.bo
ParallellaTop_INC = 
ParallellaTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ParallellaTop.bsv

$(eval $(call BSV_BO_RULE, $(ParallellaTop_BO), $(ParallellaTop_BSV), $(ParallellaTop_DEP), $(ParallellaTop_INC)))

SimLink_BO  = obj/SimLink.bo
SimLink_DEP = obj/Pipe.bo
SimLink_INC = 
SimLink_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/SimLink.bsv

$(eval $(call BSV_BO_RULE, $(SimLink_BO), $(SimLink_BSV), $(SimLink_DEP), $(SimLink_INC)))

GetPutWithClocks_BO  = obj/GetPutWithClocks.bo
GetPutWithClocks_DEP = obj/ConnectalMemTypes.bo obj/ConnectalBramFifo.bo obj/Pipe.bo obj/SyncAxisFifo32x8.bo obj/AxiStream.bo
GetPutWithClocks_INC = 
GetPutWithClocks_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/GetPutWithClocks.bsv

$(eval $(call BSV_BO_RULE, $(GetPutWithClocks_BO), $(GetPutWithClocks_BSV), $(GetPutWithClocks_DEP), $(GetPutWithClocks_INC)))

ConnectalBram_BO  = obj/ConnectalBram.bo
ConnectalBram_DEP = obj/OldEHR.bo obj/ConfigCounter.bo
ConnectalBram_INC = 
ConnectalBram_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalBram.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalBram_BO), $(ConnectalBram_BSV), $(ConnectalBram_DEP), $(ConnectalBram_INC)))

AvalonMasterSlave_BO  = obj/AvalonMasterSlave.bo
AvalonMasterSlave_DEP = 
AvalonMasterSlave_INC = 
AvalonMasterSlave_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonMasterSlave.bsv

$(eval $(call BSV_BO_RULE, $(AvalonMasterSlave_BO), $(AvalonMasterSlave_BSV), $(AvalonMasterSlave_DEP), $(AvalonMasterSlave_INC)))

PS7LIB_BO  = obj/PS7LIB.bo
PS7LIB_DEP = obj/ConnectableWithTrace.bo obj/Bscan.bo obj/PPS7LIB.bo obj/AxiMasterSlave.bo obj/AxiDma.bo obj/ConnectalXilinxCells.bo obj/ConnectalClocks.bo obj/AxiBits.bo obj/AxiGather.bo
PS7LIB_INC = 
PS7LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS7LIB.bsv

$(eval $(call BSV_BO_RULE, $(PS7LIB_BO), $(PS7LIB_BSV), $(PS7LIB_DEP), $(PS7LIB_INC)))

MemServerInternal_BO  = obj/MemServerInternal.bo
MemServerInternal_DEP = obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo obj/ConnectalClocks.bo obj/ConnectalMMU.bo obj/ConnectalCompletionBuffer.bo obj/ConnectalConfig.bo
MemServerInternal_INC = 
MemServerInternal_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemServerInternal.bsv

$(eval $(call BSV_BO_RULE, $(MemServerInternal_BO), $(MemServerInternal_BSV), $(MemServerInternal_DEP), $(MemServerInternal_INC)))

OldEHR_BO  = obj/OldEHR.bo
OldEHR_DEP = 
OldEHR_INC = 
OldEHR_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/OldEHR.bsv

$(eval $(call BSV_BO_RULE, $(OldEHR_BO), $(OldEHR_BSV), $(OldEHR_DEP), $(OldEHR_INC)))

OldEHR_MOD = mkEHR2BSV
OldEHR_V   = verilog/mkEHR2BSV.v
OldEHR_BO  = obj/OldEHR.bo
OldEHR_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/OldEHR.bsv
OldEHR_DEP = 
OldEHR_INC = 

$(eval $(call BSV_V_RULE, $(OldEHR_MOD), $(OldEHR_V), $(OldEHR_BSV), $(OldEHR_DEP), $(OldEHR_INC)))

AsicTop_BO  = obj/AsicTop.bo
AsicTop_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/Top.bo obj/HostInterface.bo obj/Pipe.bo obj/CnocPortal.bo obj/ConnectalMemTypes.bo obj/ConnectalMMU.bo obj/MemServer.bo obj/MMURequest.bo obj/MMUIndication.bo obj/MemServerIndication.bo obj/MemServerRequest.bo obj/SimDma.bo obj/IfcNames.bo
AsicTop_INC = 
AsicTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AsicTop.bsv

$(eval $(call BSV_BO_RULE, $(AsicTop_BO), $(AsicTop_BSV), $(AsicTop_DEP), $(AsicTop_INC)))

SimDma_BO  = obj/SimDma.bo
SimDma_DEP = obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo
SimDma_INC = 
SimDma_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/SimDma.bsv

$(eval $(call BSV_BO_RULE, $(SimDma_BO), $(SimDma_BSV), $(SimDma_DEP), $(SimDma_INC)))

AxiGather_BO  = obj/AxiGather.bo
AxiGather_DEP = obj/PPS7LIB.bo obj/AxiMasterSlave.bo obj/Axi4MasterSlave.bo obj/AxiBits.bo obj/GetPutM.bo
AxiGather_INC = 
AxiGather_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiGather.bsv

$(eval $(call BSV_BO_RULE, $(AxiGather_BO), $(AxiGather_BSV), $(AxiGather_DEP), $(AxiGather_INC)))

ConnectalCompletionBuffer_BO  = obj/ConnectalCompletionBuffer.bo
ConnectalCompletionBuffer_DEP = obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo obj/ConfigCounter.bo
ConnectalCompletionBuffer_INC = 
ConnectalCompletionBuffer_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalCompletionBuffer.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalCompletionBuffer_BO), $(ConnectalCompletionBuffer_BSV), $(ConnectalCompletionBuffer_DEP), $(ConnectalCompletionBuffer_INC)))

MemWriteEngine_BO  = obj/MemWriteEngine.bo
MemWriteEngine_DEP = obj/ConfigCounter.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/ConnectalConfig.bo
MemWriteEngine_INC = 
MemWriteEngine_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemWriteEngine.bsv

$(eval $(call BSV_BO_RULE, $(MemWriteEngine_BO), $(MemWriteEngine_BSV), $(MemWriteEngine_DEP), $(MemWriteEngine_INC)))

AvalonDdr3Controller_BO  = obj/AvalonDdr3Controller.bo
AvalonDdr3Controller_DEP = obj/ConnectalClocks.bo obj/ALTERA_DDR3_WRAPPER.bo
AvalonDdr3Controller_INC = 
AvalonDdr3Controller_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonDdr3Controller.bsv

$(eval $(call BSV_BO_RULE, $(AvalonDdr3Controller_BO), $(AvalonDdr3Controller_BSV), $(AvalonDdr3Controller_DEP), $(AvalonDdr3Controller_INC)))

AvalonDdr3Controller_MOD = mkDdr3
AvalonDdr3Controller_V   = verilog/mkDdr3.v
AvalonDdr3Controller_BO  = obj/AvalonDdr3Controller.bo
AvalonDdr3Controller_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonDdr3Controller.bsv
AvalonDdr3Controller_DEP = obj/ConnectalClocks.bo obj/ALTERA_DDR3_WRAPPER.bo
AvalonDdr3Controller_INC = 

$(eval $(call BSV_V_RULE, $(AvalonDdr3Controller_MOD), $(AvalonDdr3Controller_V), $(AvalonDdr3Controller_BSV), $(AvalonDdr3Controller_DEP), $(AvalonDdr3Controller_INC)))

AxiBits_BO  = obj/AxiBits.bo
AxiBits_DEP = obj/ConnectalFIFO.bo obj/ConnectalMemTypes.bo obj/ConnectalEHR.bo obj/Axi4MasterSlave.bo obj/ConnectalBramFifo.bo
AxiBits_INC = 
AxiBits_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AxiBits.bsv

$(eval $(call BSV_BO_RULE, $(AxiBits_BO), $(AxiBits_BSV), $(AxiBits_DEP), $(AxiBits_INC)))

DisplayInd_BO  = obj/DisplayInd.bo
DisplayInd_DEP = 
DisplayInd_INC = 
DisplayInd_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/DisplayInd.bsv

$(eval $(call BSV_BO_RULE, $(DisplayInd_BO), $(DisplayInd_BSV), $(DisplayInd_DEP), $(DisplayInd_INC)))

PcieCsr_BO  = obj/PcieCsr.bo
PcieCsr_DEP = obj/PcieTracer.bo obj/ConnectalMemTypes.bo obj/AddressGenerator.bo obj/Pipe.bo
PcieCsr_INC = 
PcieCsr_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieCsr.bsv

$(eval $(call BSV_BO_RULE, $(PcieCsr_BO), $(PcieCsr_BSV), $(PcieCsr_DEP), $(PcieCsr_INC)))

PcieCsr_MOD = mkPcieControlAndStatusRegs
PcieCsr_V   = verilog/mkPcieControlAndStatusRegs.v
PcieCsr_BO  = obj/PcieCsr.bo
PcieCsr_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieCsr.bsv
PcieCsr_DEP = obj/PcieTracer.bo obj/ConnectalMemTypes.bo obj/AddressGenerator.bo obj/Pipe.bo
PcieCsr_INC = 

$(eval $(call BSV_V_RULE, $(PcieCsr_MOD), $(PcieCsr_V), $(PcieCsr_BSV), $(PcieCsr_DEP), $(PcieCsr_INC)))

GetPutM_BO  = obj/GetPutM.bo
GetPutM_DEP = 
GetPutM_INC = 
GetPutM_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/GetPutM.bsv

$(eval $(call BSV_BO_RULE, $(GetPutM_BO), $(GetPutM_BSV), $(GetPutM_DEP), $(GetPutM_INC)))

MIFO_BO  = obj/MIFO.bo
MIFO_DEP = obj/Arith.bo obj/Pipe.bo
MIFO_INC = 
MIFO_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MIFO.bsv

$(eval $(call BSV_BO_RULE, $(MIFO_BO), $(MIFO_BSV), $(MIFO_DEP), $(MIFO_INC)))

ConnectalXilinxCells_BO  = obj/ConnectalXilinxCells.bo
ConnectalXilinxCells_DEP = 
ConnectalXilinxCells_INC = 
ConnectalXilinxCells_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalXilinxCells.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalXilinxCells_BO), $(ConnectalXilinxCells_BSV), $(ConnectalXilinxCells_DEP), $(ConnectalXilinxCells_INC)))

ConnectalMMU_BO  = obj/ConnectalMMU.bo
ConnectalMMU_DEP = obj/ConnectalBram.bo obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/ConnectalCompletionBuffer.bo obj/Pipe.bo obj/SimDma.bo
ConnectalMMU_INC = 
ConnectalMMU_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMMU.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalMMU_BO), $(ConnectalMMU_BSV), $(ConnectalMMU_DEP), $(ConnectalMMU_INC)))

ConnectalMMU_MOD = mkMMUSynth
ConnectalMMU_V   = verilog/mkMMUSynth.v
ConnectalMMU_BO  = obj/ConnectalMMU.bo
ConnectalMMU_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMMU.bsv
ConnectalMMU_DEP = obj/ConnectalBram.bo obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/ConnectalCompletionBuffer.bo obj/Pipe.bo obj/SimDma.bo
ConnectalMMU_INC = 

$(eval $(call BSV_V_RULE, $(ConnectalMMU_MOD), $(ConnectalMMU_V), $(ConnectalMMU_BSV), $(ConnectalMMU_DEP), $(ConnectalMMU_INC)))

ZynqTop_BO  = obj/ZynqTop.bo
ZynqTop_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectableWithTrace.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/AxiMasterSlave.bo obj/ConnectalXilinxCells.bo obj/PS7LIB.bo obj/PS7Trace.bo obj/PPS7LIB.bo obj/CtrlMux.bo obj/AxiDma.bo obj/Top.bo obj/Bscan.bo obj/HostInterface.bo obj/Platform.bo
ZynqTop_INC = 
ZynqTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ZynqTop.bsv

$(eval $(call BSV_BO_RULE, $(ZynqTop_BO), $(ZynqTop_BSV), $(ZynqTop_DEP), $(ZynqTop_INC)))

XsimIF_BO  = obj/XsimIF.bo
XsimIF_DEP = 
XsimIF_INC = 
XsimIF_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/XsimIF.bsv

$(eval $(call BSV_BO_RULE, $(XsimIF_BO), $(XsimIF_BSV), $(XsimIF_DEP), $(XsimIF_INC)))

Platform_BO  = obj/Platform.bo
Platform_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/HostInterface.bo obj/ConnectalMMU.bo obj/MemServer.bo obj/ConnectalMemTypes.bo obj/CtrlMux.bo obj/Pipe.bo obj/ConnectalMemory.bo obj/MMURequest.bo obj/MMUIndication.bo obj/MemServerIndication.bo obj/MemServerRequest.bo obj/IfcNames.bo
Platform_INC = 
Platform_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Platform.bsv

$(eval $(call BSV_BO_RULE, $(Platform_BO), $(Platform_BSV), $(Platform_DEP), $(Platform_INC)))

ConnectalMemory_BO  = obj/ConnectalMemory.bo
ConnectalMemory_DEP = 
ConnectalMemory_INC = 
ConnectalMemory_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMemory.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalMemory_BO), $(ConnectalMemory_BSV), $(ConnectalMemory_DEP), $(ConnectalMemory_INC)))

PS8LIB_BO  = obj/PS8LIB.bo
PS8LIB_DEP = obj/ConnectalConfig.bo obj/ConnectableWithTrace.bo obj/Bscan.bo obj/ConnectalXilinxCells.bo obj/ConnectalClocks.bo obj/AxiMasterSlave.bo obj/Axi4MasterSlave.bo obj/AxiDma.bo obj/AxiBits.bo obj/ConnectalMemTypes.bo obj/Platform.bo obj/ZYNQ_ULTRA.bo
PS8LIB_INC = 
PS8LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS8LIB.bsv

$(eval $(call BSV_BO_RULE, $(PS8LIB_BO), $(PS8LIB_BSV), $(PS8LIB_DEP), $(PS8LIB_INC)))

Pipe_BO  = obj/Pipe.bo
Pipe_DEP = obj/AxiStream.bo
Pipe_INC = 
Pipe_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pipe.bsv

$(eval $(call BSV_BO_RULE, $(Pipe_BO), $(Pipe_BSV), $(Pipe_DEP), $(Pipe_INC)))

MemServer_BO  = obj/MemServer.bo
MemServer_DEP = obj/HostInterface.bo obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/ConnectalMMU.bo obj/MemServerInternal.bo
MemServer_INC = 
MemServer_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemServer.bsv

$(eval $(call BSV_BO_RULE, $(MemServer_BO), $(MemServer_BSV), $(MemServer_DEP), $(MemServer_INC)))

Trace_BO  = obj/Trace.bo
Trace_DEP = obj/ConnectalFIFO.bo obj/ConnectalMemTypes.bo
Trace_INC = 
Trace_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Trace.bsv

$(eval $(call BSV_BO_RULE, $(Trace_BO), $(Trace_BSV), $(Trace_DEP), $(Trace_INC)))

AddressGenerator_BO  = obj/AddressGenerator.bo
AddressGenerator_DEP = obj/ConnectalMemTypes.bo obj/ConnectalConfig.bo
AddressGenerator_INC = 
AddressGenerator_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AddressGenerator.bsv

$(eval $(call BSV_BO_RULE, $(AddressGenerator_BO), $(AddressGenerator_BSV), $(AddressGenerator_DEP), $(AddressGenerator_INC)))

MemToPcie_BO  = obj/MemToPcie.bo
MemToPcie_DEP = obj/ConnectalMimo.bo obj/MIFO.bo obj/ConnectalMemTypes.bo obj/ConfigCounter.bo obj/ConnectalConfig.bo
MemToPcie_INC = 
MemToPcie_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemToPcie.bsv

$(eval $(call BSV_BO_RULE, $(MemToPcie_BO), $(MemToPcie_BSV), $(MemToPcie_DEP), $(MemToPcie_INC)))

SyncBits_BO  = obj/SyncBits.bo
SyncBits_DEP = 
SyncBits_INC = 
SyncBits_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/SyncBits.bsv

$(eval $(call BSV_BO_RULE, $(SyncBits_BO), $(SyncBits_BSV), $(SyncBits_DEP), $(SyncBits_INC)))

Dsp48E1_BO  = obj/Dsp48E1.bo
Dsp48E1_DEP = obj/ConnectalClocks.bo
Dsp48E1_INC = 
Dsp48E1_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Dsp48E1.bsv

$(eval $(call BSV_BO_RULE, $(Dsp48E1_BO), $(Dsp48E1_BSV), $(Dsp48E1_DEP), $(Dsp48E1_INC)))

AwsF1Top_BO  = obj/AwsF1Top.bo
AwsF1Top_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/Platform.bo obj/Top.bo obj/HostInterface.bo obj/Pipe.bo obj/CnocPortal.bo obj/ConnectalMemTypes.bo obj/ConnectalMMU.bo obj/MemServer.bo obj/MMURequest.bo obj/MMUIndication.bo obj/MemServerIndication.bo obj/MemServerRequest.bo obj/SimDma.bo obj/IfcNames.bo obj/Axi4MasterSlave.bo obj/AxiBits.bo obj/AxiDma.bo obj/ConnectalFIFO.bo
AwsF1Top_INC = 
AwsF1Top_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AwsF1Top.bsv

$(eval $(call BSV_BO_RULE, $(AwsF1Top_BO), $(AwsF1Top_BSV), $(AwsF1Top_DEP), $(AwsF1Top_INC)))

PhysMemSlaveFromBram_BO  = obj/PhysMemSlaveFromBram.bo
PhysMemSlaveFromBram_DEP = obj/ConnectalMemTypes.bo obj/AddressGenerator.bo
PhysMemSlaveFromBram_INC = 
PhysMemSlaveFromBram_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PhysMemSlaveFromBram.bsv

$(eval $(call BSV_BO_RULE, $(PhysMemSlaveFromBram_BO), $(PhysMemSlaveFromBram_BSV), $(PhysMemSlaveFromBram_DEP), $(PhysMemSlaveFromBram_INC)))

ConnectalConfig_BO  = obj/ConnectalConfig.bo
ConnectalConfig_DEP = 
ConnectalConfig_INC = 
ConnectalConfig_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalConfig.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalConfig_BO), $(ConnectalConfig_BSV), $(ConnectalConfig_DEP), $(ConnectalConfig_INC)))

UntetheredTop_BO  = obj/UntetheredTop.bo
UntetheredTop_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/Top.bo obj/ConnectalMemTypes.bo obj/ConnectalClocks.bo obj/GetPutWithClocks.bo obj/HostInterface.bo obj/Platform.bo
UntetheredTop_INC = 
UntetheredTop_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/UntetheredTop.bsv

$(eval $(call BSV_BO_RULE, $(UntetheredTop_BO), $(UntetheredTop_BSV), $(UntetheredTop_DEP), $(UntetheredTop_INC)))

MemPipe_BO  = obj/MemPipe.bo
MemPipe_DEP = obj/ConnectalMemTypes.bo obj/Pipe.bo obj/ConfigCounter.bo
MemPipe_INC = 
MemPipe_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/MemPipe.bsv

$(eval $(call BSV_BO_RULE, $(MemPipe_BO), $(MemPipe_BSV), $(MemPipe_DEP), $(MemPipe_INC)))

PcieRootDevice_BO  = obj/PcieRootDevice.bo
PcieRootDevice_DEP = 
PcieRootDevice_INC = 
PcieRootDevice_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieRootDevice.bsv

$(eval $(call BSV_BO_RULE, $(PcieRootDevice_BO), $(PcieRootDevice_BSV), $(PcieRootDevice_DEP), $(PcieRootDevice_INC)))

PcieSplitter_BO  = obj/PcieSplitter.bo
PcieSplitter_DEP = 
PcieSplitter_INC = 
PcieSplitter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieSplitter.bsv

$(eval $(call BSV_BO_RULE, $(PcieSplitter_BO), $(PcieSplitter_BSV), $(PcieSplitter_DEP), $(PcieSplitter_INC)))

PcieSplitter_MOD = mkTLPDispatcher
PcieSplitter_V   = verilog/mkTLPDispatcher.v
PcieSplitter_BO  = obj/PcieSplitter.bo
PcieSplitter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieSplitter.bsv
PcieSplitter_DEP = 
PcieSplitter_INC = 

$(eval $(call BSV_V_RULE, $(PcieSplitter_MOD), $(PcieSplitter_V), $(PcieSplitter_BSV), $(PcieSplitter_DEP), $(PcieSplitter_INC)))

PcieSplitter_MOD = mkTLPArbiter
PcieSplitter_V   = verilog/mkTLPArbiter.v
PcieSplitter_BO  = obj/PcieSplitter.bo
PcieSplitter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieSplitter.bsv
PcieSplitter_DEP = 
PcieSplitter_INC = 

$(eval $(call BSV_V_RULE, $(PcieSplitter_MOD), $(PcieSplitter_V), $(PcieSplitter_BSV), $(PcieSplitter_DEP), $(PcieSplitter_INC)))

PS4LIB_BO  = obj/PS4LIB.bo
PS4LIB_DEP = obj/ConnectalAlteraCells.bo obj/ConnectalClocks.bo obj/ALTERA_PCIE_SIV_WRAPPER.bo
PS4LIB_INC = 
PS4LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PS4LIB.bsv

$(eval $(call BSV_BO_RULE, $(PS4LIB_BO), $(PS4LIB_BSV), $(PS4LIB_DEP), $(PS4LIB_INC)))

Pcie2EndpointX7_BO  = obj/Pcie2EndpointX7.bo
Pcie2EndpointX7_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER2.bo obj/Pipe.bo obj/PcieStateChanges.bo obj/Bufgctrl.bo
Pcie2EndpointX7_INC = 
Pcie2EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie2EndpointX7.bsv

$(eval $(call BSV_BO_RULE, $(Pcie2EndpointX7_BO), $(Pcie2EndpointX7_BSV), $(Pcie2EndpointX7_DEP), $(Pcie2EndpointX7_INC)))

Pcie2EndpointX7_MOD = mkPcieEndpointX7
Pcie2EndpointX7_V   = verilog/mkPcieEndpointX7.v
Pcie2EndpointX7_BO  = obj/Pcie2EndpointX7.bo
Pcie2EndpointX7_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/Pcie2EndpointX7.bsv
Pcie2EndpointX7_DEP = obj/ConnectalConfig.bo obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo obj/PCIEWRAPPER2.bo obj/Pipe.bo obj/PcieStateChanges.bo obj/Bufgctrl.bo
Pcie2EndpointX7_INC = 

$(eval $(call BSV_V_RULE, $(Pcie2EndpointX7_MOD), $(Pcie2EndpointX7_V), $(Pcie2EndpointX7_BSV), $(Pcie2EndpointX7_DEP), $(Pcie2EndpointX7_INC)))

ConnectableWithTrace_BO  = obj/ConnectableWithTrace.bo
ConnectableWithTrace_DEP = obj/AxiMasterSlave.bo obj/Bscan.bo
ConnectableWithTrace_INC = 
ConnectableWithTrace_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectableWithTrace.bsv

$(eval $(call BSV_BO_RULE, $(ConnectableWithTrace_BO), $(ConnectableWithTrace_BSV), $(ConnectableWithTrace_DEP), $(ConnectableWithTrace_INC)))

CtrlMux_BO  = obj/CtrlMux.bo
CtrlMux_DEP = obj/ConnectalConfig.bo obj/HostInterface.bo obj/AddressGenerator.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/Arith.bo obj/Pipe.bo
CtrlMux_INC = 
CtrlMux_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/CtrlMux.bsv

$(eval $(call BSV_BO_RULE, $(CtrlMux_BO), $(CtrlMux_BSV), $(CtrlMux_DEP), $(CtrlMux_INC)))

PcieTracer_BO  = obj/PcieTracer.bo
PcieTracer_DEP = obj/BramMux.bo obj/ConnectalBram.bo
PcieTracer_INC = 
PcieTracer_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieTracer.bsv

$(eval $(call BSV_BO_RULE, $(PcieTracer_BO), $(PcieTracer_BSV), $(PcieTracer_DEP), $(PcieTracer_INC)))

PcieTracer_MOD = mkPcieTracer
PcieTracer_V   = verilog/mkPcieTracer.v
PcieTracer_BO  = obj/PcieTracer.bo
PcieTracer_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/PcieTracer.bsv
PcieTracer_DEP = obj/BramMux.bo obj/ConnectalBram.bo
PcieTracer_INC = 

$(eval $(call BSV_V_RULE, $(PcieTracer_MOD), $(PcieTracer_V), $(PcieTracer_BSV), $(PcieTracer_DEP), $(PcieTracer_INC)))

ConnectalPrelude_BO  = obj/ConnectalPrelude.bo
ConnectalPrelude_DEP = 
ConnectalPrelude_INC = 
ConnectalPrelude_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalPrelude.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalPrelude_BO), $(ConnectalPrelude_BSV), $(ConnectalPrelude_DEP), $(ConnectalPrelude_INC)))

ConnectalMemTypes_BO  = obj/ConnectalMemTypes.bo
ConnectalMemTypes_DEP = obj/Adapter.bo obj/ConnectalConfig.bo obj/Pipe.bo obj/ConnectalMemory.bo obj/AxiStream.bo
ConnectalMemTypes_INC = 
ConnectalMemTypes_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/ConnectalMemTypes.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalMemTypes_BO), $(ConnectalMemTypes_BSV), $(ConnectalMemTypes_DEP), $(ConnectalMemTypes_INC)))

AvalonBits_BO  = obj/AvalonBits.bo
AvalonBits_DEP = 
AvalonBits_INC = 
AvalonBits_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonBits.bsv

$(eval $(call BSV_BO_RULE, $(AvalonBits_BO), $(AvalonBits_BSV), $(AvalonBits_DEP), $(AvalonBits_INC)))

AvalonSplitter_BO  = obj/AvalonSplitter.bo
AvalonSplitter_DEP = obj/AvalonMasterSlave.bo
AvalonSplitter_INC = 
AvalonSplitter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/bsv/AvalonSplitter.bsv

$(eval $(call BSV_BO_RULE, $(AvalonSplitter_BO), $(AvalonSplitter_BSV), $(AvalonSplitter_DEP), $(AvalonSplitter_INC)))

FromHost_BO  = obj/FromHost.bo
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv

$(eval $(call BSV_BO_RULE, $(FromHost_BO), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostInput
FromHost_V   = verilog/mkFromHostInput.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostWrapperMemPortalPipes
FromHost_V   = verilog/mkFromHostWrapperMemPortalPipes.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostOutputPipes
FromHost_V   = verilog/mkFromHostOutputPipes.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostOutput
FromHost_V   = verilog/mkFromHostOutput.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostInverter
FromHost_V   = verilog/mkFromHostInverter.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostInverterV
FromHost_V   = verilog/mkFromHostInverterV.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

FromHost_MOD = mkFromHostProxySynth
FromHost_V   = verilog/mkFromHostProxySynth.v
FromHost_BO  = obj/FromHost.bo
FromHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/FromHost.bsv
FromHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
FromHost_INC = 

$(eval $(call BSV_V_RULE, $(FromHost_MOD), $(FromHost_V), $(FromHost_BSV), $(FromHost_DEP), $(FromHost_INC)))

ToHost_BO  = obj/ToHost.bo
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv

$(eval $(call BSV_BO_RULE, $(ToHost_BO), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostInput
ToHost_V   = verilog/mkToHostInput.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostWrapperMemPortalPipes
ToHost_V   = verilog/mkToHostWrapperMemPortalPipes.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostOutputPipes
ToHost_V   = verilog/mkToHostOutputPipes.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostOutput
ToHost_V   = verilog/mkToHostOutput.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostInverter
ToHost_V   = verilog/mkToHostInverter.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostInverterV
ToHost_V   = verilog/mkToHostInverterV.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

ToHost_MOD = mkToHostProxySynth
ToHost_V   = verilog/mkToHostProxySynth.v
ToHost_BO  = obj/ToHost.bo
ToHost_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ToHost.bsv
ToHost_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/Ifc.bo
ToHost_INC = 

$(eval $(call BSV_V_RULE, $(ToHost_MOD), $(ToHost_V), $(ToHost_BSV), $(ToHost_DEP), $(ToHost_INC)))

XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv

$(eval $(call BSV_BO_RULE, $(XsimMsgIndication_BO), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationInput
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationInput.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationWrapperMemPortalPipes
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationWrapperMemPortalPipes.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationOutputPipes
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationOutputPipes.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationOutput
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationOutput.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationInverter
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationInverter.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationInverterV
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationInverterV.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

XsimMsgIndication_MOD = mkXsimMsgIndicationProxySynth
XsimMsgIndication_V   = verilog/mkXsimMsgIndicationProxySynth.v
XsimMsgIndication_BO  = obj/XsimMsgIndication.bo
XsimMsgIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgIndication.bsv
XsimMsgIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgIndication_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgIndication_MOD), $(XsimMsgIndication_V), $(XsimMsgIndication_BSV), $(XsimMsgIndication_DEP), $(XsimMsgIndication_INC)))

MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv

$(eval $(call BSV_BO_RULE, $(MemServerIndication_BO), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationInput
MemServerIndication_V   = verilog/mkMemServerIndicationInput.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationWrapperMemPortalPipes
MemServerIndication_V   = verilog/mkMemServerIndicationWrapperMemPortalPipes.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationOutputPipes
MemServerIndication_V   = verilog/mkMemServerIndicationOutputPipes.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationOutput
MemServerIndication_V   = verilog/mkMemServerIndicationOutput.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationInverter
MemServerIndication_V   = verilog/mkMemServerIndicationInverter.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationInverterV
MemServerIndication_V   = verilog/mkMemServerIndicationInverterV.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

MemServerIndication_MOD = mkMemServerIndicationProxySynth
MemServerIndication_V   = verilog/mkMemServerIndicationProxySynth.v
MemServerIndication_BO  = obj/MemServerIndication.bo
MemServerIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerIndication.bsv
MemServerIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerIndication_INC = 

$(eval $(call BSV_V_RULE, $(MemServerIndication_MOD), $(MemServerIndication_V), $(MemServerIndication_BSV), $(MemServerIndication_DEP), $(MemServerIndication_INC)))

XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv

$(eval $(call BSV_BO_RULE, $(XsimMsgRequest_BO), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestInput
XsimMsgRequest_V   = verilog/mkXsimMsgRequestInput.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestWrapperMemPortalPipes
XsimMsgRequest_V   = verilog/mkXsimMsgRequestWrapperMemPortalPipes.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestOutputPipes
XsimMsgRequest_V   = verilog/mkXsimMsgRequestOutputPipes.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestOutput
XsimMsgRequest_V   = verilog/mkXsimMsgRequestOutput.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestInverter
XsimMsgRequest_V   = verilog/mkXsimMsgRequestInverter.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestInverterV
XsimMsgRequest_V   = verilog/mkXsimMsgRequestInverterV.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

XsimMsgRequest_MOD = mkXsimMsgRequestProxySynth
XsimMsgRequest_V   = verilog/mkXsimMsgRequestProxySynth.v
XsimMsgRequest_BO  = obj/XsimMsgRequest.bo
XsimMsgRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/XsimMsgRequest.bsv
XsimMsgRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo obj/XsimIF.bo
XsimMsgRequest_INC = 

$(eval $(call BSV_V_RULE, $(XsimMsgRequest_MOD), $(XsimMsgRequest_V), $(XsimMsgRequest_BSV), $(XsimMsgRequest_DEP), $(XsimMsgRequest_INC)))

MMURequest_BO  = obj/MMURequest.bo
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv

$(eval $(call BSV_BO_RULE, $(MMURequest_BO), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestInput
MMURequest_V   = verilog/mkMMURequestInput.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestWrapperMemPortalPipes
MMURequest_V   = verilog/mkMMURequestWrapperMemPortalPipes.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestOutputPipes
MMURequest_V   = verilog/mkMMURequestOutputPipes.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestOutput
MMURequest_V   = verilog/mkMMURequestOutput.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestInverter
MMURequest_V   = verilog/mkMMURequestInverter.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestInverterV
MMURequest_V   = verilog/mkMMURequestInverterV.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MMURequest_MOD = mkMMURequestProxySynth
MMURequest_V   = verilog/mkMMURequestProxySynth.v
MMURequest_BO  = obj/MMURequest.bo
MMURequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMURequest.bsv
MMURequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMURequest_INC = 

$(eval $(call BSV_V_RULE, $(MMURequest_MOD), $(MMURequest_V), $(MMURequest_BSV), $(MMURequest_DEP), $(MMURequest_INC)))

MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv

$(eval $(call BSV_BO_RULE, $(MemServerRequest_BO), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestInput
MemServerRequest_V   = verilog/mkMemServerRequestInput.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestWrapperMemPortalPipes
MemServerRequest_V   = verilog/mkMemServerRequestWrapperMemPortalPipes.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestOutputPipes
MemServerRequest_V   = verilog/mkMemServerRequestOutputPipes.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestOutput
MemServerRequest_V   = verilog/mkMemServerRequestOutput.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestInverter
MemServerRequest_V   = verilog/mkMemServerRequestInverter.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestInverterV
MemServerRequest_V   = verilog/mkMemServerRequestInverterV.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

MemServerRequest_MOD = mkMemServerRequestProxySynth
MemServerRequest_V   = verilog/mkMemServerRequestProxySynth.v
MemServerRequest_BO  = obj/MemServerRequest.bo
MemServerRequest_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MemServerRequest.bsv
MemServerRequest_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MemServerRequest_INC = 

$(eval $(call BSV_V_RULE, $(MemServerRequest_MOD), $(MemServerRequest_V), $(MemServerRequest_BSV), $(MemServerRequest_DEP), $(MemServerRequest_INC)))

IfcNames_BO  = obj/IfcNames.bo
IfcNames_DEP = 
IfcNames_INC = 
IfcNames_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/IfcNames.bsv

$(eval $(call BSV_BO_RULE, $(IfcNames_BO), $(IfcNames_BSV), $(IfcNames_DEP), $(IfcNames_INC)))

MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv

$(eval $(call BSV_BO_RULE, $(MMUIndication_BO), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationInput
MMUIndication_V   = verilog/mkMMUIndicationInput.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationWrapperMemPortalPipes
MMUIndication_V   = verilog/mkMMUIndicationWrapperMemPortalPipes.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationOutputPipes
MMUIndication_V   = verilog/mkMMUIndicationOutputPipes.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationOutput
MMUIndication_V   = verilog/mkMMUIndicationOutput.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationInverter
MMUIndication_V   = verilog/mkMMUIndicationInverter.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationInverterV
MMUIndication_V   = verilog/mkMMUIndicationInverterV.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

MMUIndication_MOD = mkMMUIndicationProxySynth
MMUIndication_V   = verilog/mkMMUIndicationProxySynth.v
MMUIndication_BO  = obj/MMUIndication.bo
MMUIndication_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/MMUIndication.bsv
MMUIndication_DEP = obj/Adapter.bo obj/Leds.bo obj/ConnectalConfig.bo obj/ConnectalMemory.bo obj/Portal.bo obj/CtrlMux.bo obj/ConnectalMemTypes.bo obj/Pipe.bo obj/HostInterface.bo obj/LinkerLib.bo
MMUIndication_INC = 

$(eval $(call BSV_V_RULE, $(MMUIndication_MOD), $(MMUIndication_V), $(MMUIndication_BSV), $(MMUIndication_DEP), $(MMUIndication_INC)))

ConnectalProjectConfig_BO  = obj/ConnectalProjectConfig.bo
ConnectalProjectConfig_DEP = 
ConnectalProjectConfig_INC = 
ConnectalProjectConfig_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/ConnectalProjectConfig.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalProjectConfig_BO), $(ConnectalProjectConfig_BSV), $(ConnectalProjectConfig_DEP), $(ConnectalProjectConfig_INC)))

Top_BO  = obj/Top.bo
Top_DEP = obj/ConnectalConfig.bo obj/Portal.bo obj/CnocPortal.bo obj/HostInterface.bo obj/ConnectalMemTypes.bo obj/IfcNames.bo obj/ToHost.bo obj/ConnectalWrapper.bo obj/FromHost.bo
Top_INC = 
Top_BSV = /home/pau/Desktop/TFG/P-Risky/verilator/generatedbsv/Top.bsv

$(eval $(call BSV_BO_RULE, $(Top_BO), $(Top_BSV), $(Top_DEP), $(Top_INC)))

ConnectalWrapper_BO  = obj/ConnectalWrapper.bo
ConnectalWrapper_DEP = obj/Ifc.bo obj/Core.bo
ConnectalWrapper_INC = 
ConnectalWrapper_BSV = /home/pau/Desktop/TFG/P-Risky/ConnectalWrapper.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalWrapper_BO), $(ConnectalWrapper_BSV), $(ConnectalWrapper_DEP), $(ConnectalWrapper_INC)))

Leds_BO  = obj/Leds.bo
Leds_DEP = 
Leds_INC = 
Leds_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/Leds.bsv

$(eval $(call BSV_BO_RULE, $(Leds_BO), $(Leds_BSV), $(Leds_DEP), $(Leds_INC)))

IserdesDatadeser_BO  = obj/IserdesDatadeser.bo
IserdesDatadeser_DEP = obj/SyncBits.bo obj/ImageonVita.bo obj/IserdesDatadeserIF.bo
IserdesDatadeser_INC = 
IserdesDatadeser_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/IserdesDatadeser.bsv

$(eval $(call BSV_BO_RULE, $(IserdesDatadeser_BO), $(IserdesDatadeser_BSV), $(IserdesDatadeser_DEP), $(IserdesDatadeser_INC)))

HDMI_BO  = obj/HDMI.bo
HDMI_DEP = obj/SyncBits.bo obj/YUV.bo obj/Arith.bo
HDMI_INC = 
HDMI_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/HDMI.bsv

$(eval $(call BSV_BO_RULE, $(HDMI_BO), $(HDMI_BSV), $(HDMI_DEP), $(HDMI_INC)))

HDMI_MOD = mkRgb888ToYyuv
HDMI_V   = verilog/mkRgb888ToYyuv.v
HDMI_BO  = obj/HDMI.bo
HDMI_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/HDMI.bsv
HDMI_DEP = obj/SyncBits.bo obj/YUV.bo obj/Arith.bo
HDMI_INC = 

$(eval $(call BSV_V_RULE, $(HDMI_MOD), $(HDMI_V), $(HDMI_BSV), $(HDMI_DEP), $(HDMI_INC)))

Dma2BRAM_BO  = obj/Dma2BRAM.bo
Dma2BRAM_DEP = obj/ConnectalMemTypes.bo obj/MemWriteEngine.bo obj/ConnectalMemUtils.bo obj/Pipe.bo
Dma2BRAM_INC = 
Dma2BRAM_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/Dma2BRAM.bsv

$(eval $(call BSV_BO_RULE, $(Dma2BRAM_BO), $(Dma2BRAM_BSV), $(Dma2BRAM_DEP), $(Dma2BRAM_INC)))

BRAMFIFOFLevel_BO  = obj/BRAMFIFOFLevel.bo
BRAMFIFOFLevel_DEP = 
BRAMFIFOFLevel_INC = 
BRAMFIFOFLevel_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/BRAMFIFOFLevel.bsv

$(eval $(call BSV_BO_RULE, $(BRAMFIFOFLevel_BO), $(BRAMFIFOFLevel_BSV), $(BRAMFIFOFLevel_DEP), $(BRAMFIFOFLevel_INC)))

HdmiDisplay_BO  = obj/HdmiDisplay.bo
HdmiDisplay_DEP = obj/ConnectalMemTypes.bo obj/MemReadEngine.bo obj/HDMI.bo obj/XADC.bo obj/YUV.bo obj/BlueScope.bo
HdmiDisplay_INC = 
HdmiDisplay_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/HdmiDisplay.bsv

$(eval $(call BSV_BO_RULE, $(HdmiDisplay_BO), $(HdmiDisplay_BSV), $(HdmiDisplay_DEP), $(HdmiDisplay_INC)))

YUV_BO  = obj/YUV.bo
YUV_DEP = obj/Arith.bo
YUV_INC = 
YUV_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/YUV.bsv

$(eval $(call BSV_BO_RULE, $(YUV_BO), $(YUV_BSV), $(YUV_DEP), $(YUV_INC)))

PipeMul_BO  = obj/PipeMul.bo
PipeMul_DEP = 
PipeMul_INC = 
PipeMul_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/PipeMul.bsv

$(eval $(call BSV_BO_RULE, $(PipeMul_BO), $(PipeMul_BSV), $(PipeMul_DEP), $(PipeMul_INC)))

BlueScopeEventPIO_BO  = obj/BlueScopeEventPIO.bo
BlueScopeEventPIO_DEP = 
BlueScopeEventPIO_INC = 
BlueScopeEventPIO_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/BlueScopeEventPIO.bsv

$(eval $(call BSV_BO_RULE, $(BlueScopeEventPIO_BO), $(BlueScopeEventPIO_BSV), $(BlueScopeEventPIO_DEP), $(BlueScopeEventPIO_INC)))

SharedMemoryFifo_BO  = obj/SharedMemoryFifo.bo
SharedMemoryFifo_DEP = obj/Pipe.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo
SharedMemoryFifo_INC = 
SharedMemoryFifo_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/SharedMemoryFifo.bsv

$(eval $(call BSV_BO_RULE, $(SharedMemoryFifo_BO), $(SharedMemoryFifo_BSV), $(SharedMemoryFifo_DEP), $(SharedMemoryFifo_INC)))

ConfigCounter_BO  = obj/ConfigCounter.bo
ConfigCounter_DEP = 
ConfigCounter_INC = 
ConfigCounter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/ConfigCounter.bsv

$(eval $(call BSV_BO_RULE, $(ConfigCounter_BO), $(ConfigCounter_BSV), $(ConfigCounter_DEP), $(ConfigCounter_INC)))

BlueScope_BO  = obj/BlueScope.bo
BlueScope_DEP = obj/ConnectalMemTypes.bo obj/MemWriteEngine.bo
BlueScope_INC = 
BlueScope_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/BlueScope.bsv

$(eval $(call BSV_BO_RULE, $(BlueScope_BO), $(BlueScope_BSV), $(BlueScope_DEP), $(BlueScope_INC)))

BlueScopeEvent_BO  = obj/BlueScopeEvent.bo
BlueScopeEvent_DEP = obj/ConnectalMemTypes.bo obj/MemWriteEngine.bo
BlueScopeEvent_INC = 
BlueScopeEvent_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/BlueScopeEvent.bsv

$(eval $(call BSV_BO_RULE, $(BlueScopeEvent_BO), $(BlueScopeEvent_BSV), $(BlueScopeEvent_DEP), $(BlueScopeEvent_INC)))

SpiRoot_BO  = obj/SpiRoot.bo
SpiRoot_DEP = obj/SpiTap.bo
SpiRoot_INC = 
SpiRoot_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/SpiRoot.bsv

$(eval $(call BSV_BO_RULE, $(SpiRoot_BO), $(SpiRoot_BSV), $(SpiRoot_DEP), $(SpiRoot_INC)))

IserdesDatadeserIF_BO  = obj/IserdesDatadeserIF.bo
IserdesDatadeserIF_DEP = 
IserdesDatadeserIF_INC = 
IserdesDatadeserIF_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/IserdesDatadeserIF.bsv

$(eval $(call BSV_BO_RULE, $(IserdesDatadeserIF_BO), $(IserdesDatadeserIF_BSV), $(IserdesDatadeserIF_DEP), $(IserdesDatadeserIF_INC)))

SpiTap_BO  = obj/SpiTap.bo
SpiTap_DEP = 
SpiTap_INC = 
SpiTap_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/SpiTap.bsv

$(eval $(call BSV_BO_RULE, $(SpiTap_BO), $(SpiTap_BSV), $(SpiTap_DEP), $(SpiTap_INC)))

SharedMemoryPortal_BO  = obj/SharedMemoryPortal.bo
SharedMemoryPortal_DEP = obj/Pipe.bo obj/Portal.bo obj/ConnectalMemTypes.bo obj/ConnectalMemory.bo obj/SharedMemoryFifo.bo
SharedMemoryPortal_INC = 
SharedMemoryPortal_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/SharedMemoryPortal.bsv

$(eval $(call BSV_BO_RULE, $(SharedMemoryPortal_BO), $(SharedMemoryPortal_BSV), $(SharedMemoryPortal_DEP), $(SharedMemoryPortal_INC)))

ImageonVita_BO  = obj/ImageonVita.bo
ImageonVita_DEP = obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo
ImageonVita_INC = 
ImageonVita_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/ImageonVita.bsv

$(eval $(call BSV_BO_RULE, $(ImageonVita_BO), $(ImageonVita_BSV), $(ImageonVita_DEP), $(ImageonVita_INC)))

ImageonVita_MOD = mkSerdesClock
ImageonVita_V   = verilog/mkSerdesClock.v
ImageonVita_BO  = obj/ImageonVita.bo
ImageonVita_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/ImageonVita.bsv
ImageonVita_DEP = obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo
ImageonVita_INC = 

$(eval $(call BSV_V_RULE, $(ImageonVita_MOD), $(ImageonVita_V), $(ImageonVita_BSV), $(ImageonVita_DEP), $(ImageonVita_INC)))

ImageonVita_MOD = mkImageClocks
ImageonVita_V   = verilog/mkImageClocks.v
ImageonVita_BO  = obj/ImageonVita.bo
ImageonVita_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/ImageonVita.bsv
ImageonVita_DEP = obj/ConnectalClocks.bo obj/ConnectalXilinxCells.bo
ImageonVita_INC = 

$(eval $(call BSV_V_RULE, $(ImageonVita_MOD), $(ImageonVita_V), $(ImageonVita_BSV), $(ImageonVita_DEP), $(ImageonVita_INC)))

XADC_BO  = obj/XADC.bo
XADC_DEP = 
XADC_INC = 
XADC_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/XADC.bsv

$(eval $(call BSV_BO_RULE, $(XADC_BO), $(XADC_BSV), $(XADC_DEP), $(XADC_INC)))

FrequencyCounter_BO  = obj/FrequencyCounter.bo
FrequencyCounter_DEP = 
FrequencyCounter_INC = 
FrequencyCounter_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/FrequencyCounter.bsv

$(eval $(call BSV_BO_RULE, $(FrequencyCounter_BO), $(FrequencyCounter_BSV), $(FrequencyCounter_DEP), $(FrequencyCounter_INC)))

Bscan_BO  = obj/Bscan.bo
Bscan_DEP = obj/BscanE2.bo obj/SyncBits.bo
Bscan_INC = 
Bscan_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/Bscan.bsv

$(eval $(call BSV_BO_RULE, $(Bscan_BO), $(Bscan_BSV), $(Bscan_DEP), $(Bscan_INC)))

StackReg_BO  = obj/StackReg.bo
StackReg_DEP = 
StackReg_INC = 
StackReg_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/StackReg.bsv

$(eval $(call BSV_BO_RULE, $(StackReg_BO), $(StackReg_BSV), $(StackReg_DEP), $(StackReg_INC)))

Stack_BO  = obj/Stack.bo
Stack_DEP = 
Stack_INC = 
Stack_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/Stack.bsv

$(eval $(call BSV_BO_RULE, $(Stack_BO), $(Stack_BSV), $(Stack_DEP), $(Stack_INC)))

XilinxVirtex7PCIE_BO  = obj/XilinxVirtex7PCIE.bo
XilinxVirtex7PCIE_DEP = 
XilinxVirtex7PCIE_INC = 
XilinxVirtex7PCIE_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/XilinxVirtex7PCIE.bsv

$(eval $(call BSV_BO_RULE, $(XilinxVirtex7PCIE_BO), $(XilinxVirtex7PCIE_BSV), $(XilinxVirtex7PCIE_DEP), $(XilinxVirtex7PCIE_INC)))

ConnectalSpi_BO  = obj/ConnectalSpi.bo
ConnectalSpi_DEP = obj/SyncBits.bo obj/ConnectalClocks.bo
ConnectalSpi_INC = 
ConnectalSpi_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/ConnectalSpi.bsv

$(eval $(call BSV_BO_RULE, $(ConnectalSpi_BO), $(ConnectalSpi_BSV), $(ConnectalSpi_DEP), $(ConnectalSpi_INC)))

Arith_BO  = obj/Arith.bo
Arith_DEP = 
Arith_INC = 
Arith_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/lib/bsv/Arith.bsv

$(eval $(call BSV_BO_RULE, $(Arith_BO), $(Arith_BSV), $(Arith_DEP), $(Arith_INC)))

PCIEWRAPPER3u_BO  = obj/PCIEWRAPPER3u.bo
PCIEWRAPPER3u_DEP = obj/AxiBits.bo
PCIEWRAPPER3u_INC = 
PCIEWRAPPER3u_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIEWRAPPER3u.bsv

$(eval $(call BSV_BO_RULE, $(PCIEWRAPPER3u_BO), $(PCIEWRAPPER3u_BSV), $(PCIEWRAPPER3u_DEP), $(PCIEWRAPPER3u_INC)))

AxiIntcBvi_BO  = obj/AxiIntcBvi.bo
AxiIntcBvi_DEP = obj/AxiBits.bo
AxiIntcBvi_INC = 
AxiIntcBvi_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/AxiIntcBvi.bsv

$(eval $(call BSV_BO_RULE, $(AxiIntcBvi_BO), $(AxiIntcBvi_BSV), $(AxiIntcBvi_DEP), $(AxiIntcBvi_INC)))

PCIEWRAPPER3_BO  = obj/PCIEWRAPPER3.bo
PCIEWRAPPER3_DEP = obj/AxiBits.bo
PCIEWRAPPER3_INC = 
PCIEWRAPPER3_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIEWRAPPER3.bsv

$(eval $(call BSV_BO_RULE, $(PCIEWRAPPER3_BO), $(PCIEWRAPPER3_BSV), $(PCIEWRAPPER3_DEP), $(PCIEWRAPPER3_INC)))

AxiEthBvi_BO  = obj/AxiEthBvi.bo
AxiEthBvi_DEP = obj/AxiBits.bo obj/AxiStream.bo
AxiEthBvi_INC = 
AxiEthBvi_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/AxiEthBvi.bsv

$(eval $(call BSV_BO_RULE, $(AxiEthBvi_BO), $(AxiEthBvi_BSV), $(AxiEthBvi_DEP), $(AxiEthBvi_INC)))

Ddr3Wrapper_BO  = obj/Ddr3Wrapper.bo
Ddr3Wrapper_DEP = obj/AxiBits.bo
Ddr3Wrapper_INC = 
Ddr3Wrapper_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/Ddr3Wrapper.bsv

$(eval $(call BSV_BO_RULE, $(Ddr3Wrapper_BO), $(Ddr3Wrapper_BSV), $(Ddr3Wrapper_DEP), $(Ddr3Wrapper_INC)))

Bufgctrl_BO  = obj/Bufgctrl.bo
Bufgctrl_DEP = 
Bufgctrl_INC = 
Bufgctrl_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/Bufgctrl.bsv

$(eval $(call BSV_BO_RULE, $(Bufgctrl_BO), $(Bufgctrl_BSV), $(Bufgctrl_DEP), $(Bufgctrl_INC)))

PCIE_2_1_BO  = obj/PCIE_2_1.bo
PCIE_2_1_DEP = 
PCIE_2_1_INC = 
PCIE_2_1_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIE_2_1.bsv

$(eval $(call BSV_BO_RULE, $(PCIE_2_1_BO), $(PCIE_2_1_BSV), $(PCIE_2_1_DEP), $(PCIE_2_1_INC)))

PCIEWRAPPER3uplus_BO  = obj/PCIEWRAPPER3uplus.bo
PCIEWRAPPER3uplus_DEP = obj/AxiBits.bo
PCIEWRAPPER3uplus_INC = 
PCIEWRAPPER3uplus_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIEWRAPPER3uplus.bsv

$(eval $(call BSV_BO_RULE, $(PCIEWRAPPER3uplus_BO), $(PCIEWRAPPER3uplus_BSV), $(PCIEWRAPPER3uplus_DEP), $(PCIEWRAPPER3uplus_INC)))

AxiDmaBvi_BO  = obj/AxiDmaBvi.bo
AxiDmaBvi_DEP = obj/ConnectalConfig.bo obj/AxiBits.bo obj/AxiStream.bo
AxiDmaBvi_INC = 
AxiDmaBvi_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/AxiDmaBvi.bsv

$(eval $(call BSV_BO_RULE, $(AxiDmaBvi_BO), $(AxiDmaBvi_BSV), $(AxiDmaBvi_DEP), $(AxiDmaBvi_INC)))

ZYNQ_ULTRA_BO  = obj/ZYNQ_ULTRA.bo
ZYNQ_ULTRA_DEP = obj/AxiBits.bo
ZYNQ_ULTRA_INC = 
ZYNQ_ULTRA_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/ZYNQ_ULTRA.bsv

$(eval $(call BSV_BO_RULE, $(ZYNQ_ULTRA_BO), $(ZYNQ_ULTRA_BSV), $(ZYNQ_ULTRA_DEP), $(ZYNQ_ULTRA_INC)))

PipeClock_BO  = obj/PipeClock.bo
PipeClock_DEP = 
PipeClock_INC = 
PipeClock_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PipeClock.bsv

$(eval $(call BSV_BO_RULE, $(PipeClock_BO), $(PipeClock_BSV), $(PipeClock_DEP), $(PipeClock_INC)))

AxiEth1000BaseX_BO  = obj/AxiEth1000BaseX.bo
AxiEth1000BaseX_DEP = obj/AxiBits.bo obj/AxiStream.bo
AxiEth1000BaseX_INC = 
AxiEth1000BaseX_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/AxiEth1000BaseX.bsv

$(eval $(call BSV_BO_RULE, $(AxiEth1000BaseX_BO), $(AxiEth1000BaseX_BSV), $(AxiEth1000BaseX_DEP), $(AxiEth1000BaseX_INC)))

BscanE2_BO  = obj/BscanE2.bo
BscanE2_DEP = 
BscanE2_INC = 
BscanE2_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/BscanE2.bsv

$(eval $(call BSV_BO_RULE, $(BscanE2_BO), $(BscanE2_BSV), $(BscanE2_DEP), $(BscanE2_INC)))

PCIEWRAPPER2_BO  = obj/PCIEWRAPPER2.bo
PCIEWRAPPER2_DEP = 
PCIEWRAPPER2_INC = 
PCIEWRAPPER2_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIEWRAPPER2.bsv

$(eval $(call BSV_BO_RULE, $(PCIEWRAPPER2_BO), $(PCIEWRAPPER2_BSV), $(PCIEWRAPPER2_DEP), $(PCIEWRAPPER2_INC)))

AxiDdr3Wrapper_BO  = obj/AxiDdr3Wrapper.bo
AxiDdr3Wrapper_DEP = obj/AxiBits.bo
AxiDdr3Wrapper_INC = 
AxiDdr3Wrapper_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/AxiDdr3Wrapper.bsv

$(eval $(call BSV_BO_RULE, $(AxiDdr3Wrapper_BO), $(AxiDdr3Wrapper_BSV), $(AxiDdr3Wrapper_DEP), $(AxiDdr3Wrapper_INC)))

PPS7LIB_BO  = obj/PPS7LIB.bo
PPS7LIB_DEP = obj/AxiBits.bo
PPS7LIB_INC = 
PPS7LIB_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PPS7LIB.bsv

$(eval $(call BSV_BO_RULE, $(PPS7LIB_BO), $(PPS7LIB_BSV), $(PPS7LIB_DEP), $(PPS7LIB_INC)))

PCIEWRAPPER_BO  = obj/PCIEWRAPPER.bo
PCIEWRAPPER_DEP = 
PCIEWRAPPER_INC = 
PCIEWRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/xilinx/PCIEWRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(PCIEWRAPPER_BO), $(PCIEWRAPPER_BSV), $(PCIEWRAPPER_DEP), $(PCIEWRAPPER_INC)))

ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_BO  = obj/ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER.bo
ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_DEP = 
ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_INC = 
ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_BO), $(ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_BSV), $(ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_DEP), $(ALTERA_ETH_PMA_RESET_CONTROL_WRAPPER_INC)))

ALTERA_PCIE_SV_WRAPPER_BO  = obj/ALTERA_PCIE_SV_WRAPPER.bo
ALTERA_PCIE_SV_WRAPPER_DEP = 
ALTERA_PCIE_SV_WRAPPER_INC = 
ALTERA_PCIE_SV_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_PCIE_SV_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_PCIE_SV_WRAPPER_BO), $(ALTERA_PCIE_SV_WRAPPER_BSV), $(ALTERA_PCIE_SV_WRAPPER_DEP), $(ALTERA_PCIE_SV_WRAPPER_INC)))

ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_BO  = obj/ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER.bo
ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_DEP = 
ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_INC = 
ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_BO), $(ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_BSV), $(ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_DEP), $(ALTERA_PCIE_RECONFIG_DRIVER_WRAPPER_INC)))

ALTERA_DDR3_WRAPPER_BO  = obj/ALTERA_DDR3_WRAPPER.bo
ALTERA_DDR3_WRAPPER_DEP = obj/AxiBits.bo
ALTERA_DDR3_WRAPPER_INC = 
ALTERA_DDR3_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_DDR3_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_DDR3_WRAPPER_BO), $(ALTERA_DDR3_WRAPPER_BSV), $(ALTERA_DDR3_WRAPPER_DEP), $(ALTERA_DDR3_WRAPPER_INC)))

ALTERA_PCIE_ED_WRAPPER_BO  = obj/ALTERA_PCIE_ED_WRAPPER.bo
ALTERA_PCIE_ED_WRAPPER_DEP = 
ALTERA_PCIE_ED_WRAPPER_INC = 
ALTERA_PCIE_ED_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_PCIE_ED_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_PCIE_ED_WRAPPER_BO), $(ALTERA_PCIE_ED_WRAPPER_BSV), $(ALTERA_PCIE_ED_WRAPPER_DEP), $(ALTERA_PCIE_ED_WRAPPER_INC)))

ALTERA_XCVR_RECONFIG_WRAPPER_BO  = obj/ALTERA_XCVR_RECONFIG_WRAPPER.bo
ALTERA_XCVR_RECONFIG_WRAPPER_DEP = 
ALTERA_XCVR_RECONFIG_WRAPPER_INC = 
ALTERA_XCVR_RECONFIG_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_XCVR_RECONFIG_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_XCVR_RECONFIG_WRAPPER_BO), $(ALTERA_XCVR_RECONFIG_WRAPPER_BSV), $(ALTERA_XCVR_RECONFIG_WRAPPER_DEP), $(ALTERA_XCVR_RECONFIG_WRAPPER_INC)))

ALTERA_ETH_PMA_RECONFIG_WRAPPER_BO  = obj/ALTERA_ETH_PMA_RECONFIG_WRAPPER.bo
ALTERA_ETH_PMA_RECONFIG_WRAPPER_DEP = 
ALTERA_ETH_PMA_RECONFIG_WRAPPER_INC = 
ALTERA_ETH_PMA_RECONFIG_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_ETH_PMA_RECONFIG_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_ETH_PMA_RECONFIG_WRAPPER_BO), $(ALTERA_ETH_PMA_RECONFIG_WRAPPER_BSV), $(ALTERA_ETH_PMA_RECONFIG_WRAPPER_DEP), $(ALTERA_ETH_PMA_RECONFIG_WRAPPER_INC)))

ALTERA_PCIE_SIV_WRAPPER_BO  = obj/ALTERA_PCIE_SIV_WRAPPER.bo
ALTERA_PCIE_SIV_WRAPPER_DEP = 
ALTERA_PCIE_SIV_WRAPPER_INC = 
ALTERA_PCIE_SIV_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_PCIE_SIV_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_PCIE_SIV_WRAPPER_BO), $(ALTERA_PCIE_SIV_WRAPPER_BSV), $(ALTERA_PCIE_SIV_WRAPPER_DEP), $(ALTERA_PCIE_SIV_WRAPPER_INC)))

ALTERA_PLL_WRAPPER_BO  = obj/ALTERA_PLL_WRAPPER.bo
ALTERA_PLL_WRAPPER_DEP = 
ALTERA_PLL_WRAPPER_INC = 
ALTERA_PLL_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_PLL_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_PLL_WRAPPER_BO), $(ALTERA_PLL_WRAPPER_BSV), $(ALTERA_PLL_WRAPPER_DEP), $(ALTERA_PLL_WRAPPER_INC)))

ALTERA_ETH_PMA_WRAPPER_BO  = obj/ALTERA_ETH_PMA_WRAPPER.bo
ALTERA_ETH_PMA_WRAPPER_DEP = 
ALTERA_ETH_PMA_WRAPPER_INC = 
ALTERA_ETH_PMA_WRAPPER_BSV = /home/pau/Desktop/TFG/P-Risky/connectal/generated/altera/ALTERA_ETH_PMA_WRAPPER.bsv

$(eval $(call BSV_BO_RULE, $(ALTERA_ETH_PMA_WRAPPER_BO), $(ALTERA_ETH_PMA_WRAPPER_BSV), $(ALTERA_ETH_PMA_WRAPPER_DEP), $(ALTERA_ETH_PMA_WRAPPER_INC)))
