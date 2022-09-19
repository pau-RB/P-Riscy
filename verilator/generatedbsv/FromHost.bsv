package FromHost;

import FIFO::*;
import FIFOF::*;
import GetPut::*;
import Connectable::*;
import Clocks::*;
import FloatingPoint::*;
import Adapter::*;
import Leds::*;
import Vector::*;
import SpecialFIFOs::*;
import ConnectalConfig::*;
import ConnectalMemory::*;
import Portal::*;
import CtrlMux::*;
import ConnectalMemTypes::*;
import Pipe::*;
import HostInterface::*;
import LinkerLib::*;
import Ifc::*;
import GetPut::*;
import Vector::*;




typedef struct {
    Bit#(32) pc;
} StartPC_Message deriving (Bits);

// exposed wrapper portal interface
interface FromHostInputPipes;
    interface PipeOut#(StartPC_Message) startPC_PipeOut;

endinterface
typedef PipePortal#(1, 0, SlaveDataBusWidth) FromHostPortalInput;
interface FromHostInput;
    interface FromHostPortalInput portalIfc;
    interface FromHostInputPipes pipes;
endinterface
interface FromHostWrapperPortal;
    interface FromHostPortalInput portalIfc;
endinterface
// exposed wrapper MemPortal interface
interface FromHostWrapper;
    interface StdPortal portalIfc;
endinterface

instance Connectable#(FromHostInputPipes,FromHost);
   module mkConnection#(FromHostInputPipes pipes, FromHost ifc)(Empty);

    rule handle_startPC_request;
        let request <- toGet(pipes.startPC_PipeOut).get();
        ifc.startPC(request.pc);
    endrule

   endmodule
endinstance

// exposed wrapper Portal implementation
(* synthesize *)
module mkFromHostInput(FromHostInput);
    Vector#(1, PipeIn#(Bit#(SlaveDataBusWidth))) requestPipeIn;

    AdapterFromBus#(SlaveDataBusWidth,StartPC_Message) startPC_requestAdapter <- mkAdapterFromBus();
    requestPipeIn[0] = startPC_requestAdapter.in;

    interface PipePortal portalIfc;
        interface PortalSize messageSize;
        method Bit#(16) size(Bit#(16) methodNumber);
            case (methodNumber)
            0: return fromInteger(valueOf(SizeOf#(StartPC_Message)));
            endcase
        endmethod
        endinterface
        interface Vector requests = requestPipeIn;
        interface Vector indications = nil;
        interface PortalInterrupt intr;
           method Bool status();
              return False;
           endmethod
           method Bit#(dataWidth) channel();
              return -1;
           endmethod
        endinterface
    endinterface
    interface FromHostInputPipes pipes;
        interface startPC_PipeOut = startPC_requestAdapter.out;
    endinterface
endmodule

module mkFromHostWrapperPortal#(FromHost ifc)(FromHostWrapperPortal);
    let dut <- mkFromHostInput;
    mkConnection(dut.pipes, ifc);
    interface PipePortal portalIfc = dut.portalIfc;
endmodule

interface FromHostWrapperMemPortalPipes;
    interface FromHostInputPipes pipes;
    interface MemPortal#(12,32) portalIfc;
endinterface

(* synthesize *)
module mkFromHostWrapperMemPortalPipes#(Bit#(SlaveDataBusWidth) id)(FromHostWrapperMemPortalPipes);

  let dut <- mkFromHostInput;
  PortalCtrlMemSlave#(SlaveControlAddrWidth,SlaveDataBusWidth) ctrlPort <- mkPortalCtrlMemSlave(id, dut.portalIfc.intr);
  let memslave  <- mkMemMethodMuxIn(ctrlPort.memSlave,dut.portalIfc.requests);
  interface FromHostInputPipes pipes = dut.pipes;
  interface MemPortal portalIfc = (interface MemPortal;
      interface PhysMemSlave slave = memslave;
      interface ReadOnly interrupt = ctrlPort.interrupt;
      interface WriteOnly num_portals = ctrlPort.num_portals;
    endinterface);
endmodule

// exposed wrapper MemPortal implementation
module mkFromHostWrapper#(idType id, FromHost ifc)(FromHostWrapper)
   provisos (Bits#(idType, a__),
	     Add#(b__, a__, SlaveDataBusWidth));
  let dut <- mkFromHostWrapperMemPortalPipes(zeroExtend(pack(id)));
  mkConnection(dut.pipes, ifc);
  interface MemPortal portalIfc = dut.portalIfc;
endmodule

// exposed proxy interface
typedef PipePortal#(0, 1, SlaveDataBusWidth) FromHostPortalOutput;
interface FromHostOutput;
    interface FromHostPortalOutput portalIfc;
    interface Ifc::FromHost ifc;
endinterface
interface FromHostProxy;
    interface StdPortal portalIfc;
    interface Ifc::FromHost ifc;
endinterface

interface FromHostOutputPipeMethods;
    interface PipeIn#(StartPC_Message) startPC;

endinterface

interface FromHostOutputPipes;
    interface FromHostOutputPipeMethods methods;
    interface FromHostPortalOutput portalIfc;
endinterface

function Bit#(16) getFromHostMessageSize(Bit#(16) methodNumber);
    case (methodNumber)
            0: return fromInteger(valueOf(SizeOf#(StartPC_Message)));
    endcase
endfunction

(* synthesize *)
module mkFromHostOutputPipes(FromHostOutputPipes);
    Vector#(1, PipeOut#(Bit#(SlaveDataBusWidth))) indicationPipes;

    AdapterToBus#(SlaveDataBusWidth,StartPC_Message) startPC_responseAdapter <- mkAdapterToBus();
    indicationPipes[0] = startPC_responseAdapter.out;

    PortalInterrupt#(SlaveDataBusWidth) intrInst <- mkPortalInterrupt(indicationPipes);
    interface FromHostOutputPipeMethods methods;
    interface startPC = startPC_responseAdapter.in;

    endinterface
    interface PipePortal portalIfc;
        interface PortalSize messageSize;
            method size = getFromHostMessageSize;
        endinterface
        interface Vector requests = nil;
        interface Vector indications = indicationPipes;
        interface PortalInterrupt intr = intrInst;
    endinterface
endmodule

(* synthesize *)
module mkFromHostOutput(FromHostOutput);
    let indicationPipes <- mkFromHostOutputPipes;
    interface Ifc::FromHost ifc;

    method Action startPC(Bit#(32) pc);
        indicationPipes.methods.startPC.enq(StartPC_Message {pc: pc});
        //$display("indicationMethod 'startPC' invoked");
    endmethod
    endinterface
    interface PipePortal portalIfc = indicationPipes.portalIfc;
endmodule
instance PortalMessageSize#(FromHostOutput);
   function Bit#(16) portalMessageSize(FromHostOutput p, Bit#(16) methodNumber);
      return getFromHostMessageSize(methodNumber);
   endfunction
endinstance


interface FromHostInverse;
    method ActionValue#(StartPC_Message) startPC;

endinterface

interface FromHostInverter;
    interface Ifc::FromHost ifc;
    interface FromHostInverse inverseIfc;
endinterface

instance Connectable#(FromHostInverse, FromHostOutputPipeMethods);
   module mkConnection#(FromHostInverse in, FromHostOutputPipeMethods out)(Empty);
    mkConnection(in.startPC, out.startPC);

   endmodule
endinstance

(* synthesize *)
module mkFromHostInverter(FromHostInverter);
    FIFOF#(StartPC_Message) fifo_startPC <- mkFIFOF();

    interface Ifc::FromHost ifc;

    method Action startPC(Bit#(32) pc);
        fifo_startPC.enq(StartPC_Message {pc: pc});
    endmethod
    endinterface
    interface FromHostInverse inverseIfc;

    method ActionValue#(StartPC_Message) startPC;
        fifo_startPC.deq;
        return fifo_startPC.first;
    endmethod
    endinterface
endmodule

(* synthesize *)
module mkFromHostInverterV(FromHostInverter);
    PutInverter#(StartPC_Message) inv_startPC <- mkPutInverter();

    interface Ifc::FromHost ifc;

    method Action startPC(Bit#(32) pc);
        inv_startPC.mod.put(StartPC_Message {pc: pc});
    endmethod
    endinterface
    interface FromHostInverse inverseIfc;

    method ActionValue#(StartPC_Message) startPC;
        let v <- inv_startPC.inverse.get;
        return v;
    endmethod
    endinterface
endmodule

// synthesizeable proxy MemPortal
(* synthesize *)
module mkFromHostProxySynth#(Bit#(SlaveDataBusWidth) id)(FromHostProxy);
  let dut <- mkFromHostOutput();
  PortalCtrlMemSlave#(SlaveControlAddrWidth,SlaveDataBusWidth) ctrlPort <- mkPortalCtrlMemSlave(id, dut.portalIfc.intr);
  let memslave  <- mkMemMethodMuxOut(ctrlPort.memSlave,dut.portalIfc.indications);
  interface MemPortal portalIfc = (interface MemPortal;
      interface PhysMemSlave slave = memslave;
      interface ReadOnly interrupt = ctrlPort.interrupt;
      interface WriteOnly num_portals = ctrlPort.num_portals;
    endinterface);
  interface Ifc::FromHost ifc = dut.ifc;
endmodule

// exposed proxy MemPortal
module mkFromHostProxy#(idType id)(FromHostProxy)
   provisos (Bits#(idType, a__),
	     Add#(b__, a__, SlaveDataBusWidth));
   let rv <- mkFromHostProxySynth(extend(pack(id)));
   return rv;
endmodule
endpackage: FromHost
