package ToHost;

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
    Bit#(32) word;
} Print_Message deriving (Bits);

// exposed wrapper portal interface
interface ToHostInputPipes;
    interface PipeOut#(Print_Message) print_PipeOut;

endinterface
typedef PipePortal#(1, 0, SlaveDataBusWidth) ToHostPortalInput;
interface ToHostInput;
    interface ToHostPortalInput portalIfc;
    interface ToHostInputPipes pipes;
endinterface
interface ToHostWrapperPortal;
    interface ToHostPortalInput portalIfc;
endinterface
// exposed wrapper MemPortal interface
interface ToHostWrapper;
    interface StdPortal portalIfc;
endinterface

instance Connectable#(ToHostInputPipes,ToHost);
   module mkConnection#(ToHostInputPipes pipes, ToHost ifc)(Empty);

    rule handle_print_request;
        let request <- toGet(pipes.print_PipeOut).get();
        ifc.print(request.word);
    endrule

   endmodule
endinstance

// exposed wrapper Portal implementation
(* synthesize *)
module mkToHostInput(ToHostInput);
    Vector#(1, PipeIn#(Bit#(SlaveDataBusWidth))) requestPipeIn;

    AdapterFromBus#(SlaveDataBusWidth,Print_Message) print_requestAdapter <- mkAdapterFromBus();
    requestPipeIn[0] = print_requestAdapter.in;

    interface PipePortal portalIfc;
        interface PortalSize messageSize;
        method Bit#(16) size(Bit#(16) methodNumber);
            case (methodNumber)
            0: return fromInteger(valueOf(SizeOf#(Print_Message)));
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
    interface ToHostInputPipes pipes;
        interface print_PipeOut = print_requestAdapter.out;
    endinterface
endmodule

module mkToHostWrapperPortal#(ToHost ifc)(ToHostWrapperPortal);
    let dut <- mkToHostInput;
    mkConnection(dut.pipes, ifc);
    interface PipePortal portalIfc = dut.portalIfc;
endmodule

interface ToHostWrapperMemPortalPipes;
    interface ToHostInputPipes pipes;
    interface MemPortal#(12,32) portalIfc;
endinterface

(* synthesize *)
module mkToHostWrapperMemPortalPipes#(Bit#(SlaveDataBusWidth) id)(ToHostWrapperMemPortalPipes);

  let dut <- mkToHostInput;
  PortalCtrlMemSlave#(SlaveControlAddrWidth,SlaveDataBusWidth) ctrlPort <- mkPortalCtrlMemSlave(id, dut.portalIfc.intr);
  let memslave  <- mkMemMethodMuxIn(ctrlPort.memSlave,dut.portalIfc.requests);
  interface ToHostInputPipes pipes = dut.pipes;
  interface MemPortal portalIfc = (interface MemPortal;
      interface PhysMemSlave slave = memslave;
      interface ReadOnly interrupt = ctrlPort.interrupt;
      interface WriteOnly num_portals = ctrlPort.num_portals;
    endinterface);
endmodule

// exposed wrapper MemPortal implementation
module mkToHostWrapper#(idType id, ToHost ifc)(ToHostWrapper)
   provisos (Bits#(idType, a__),
	     Add#(b__, a__, SlaveDataBusWidth));
  let dut <- mkToHostWrapperMemPortalPipes(zeroExtend(pack(id)));
  mkConnection(dut.pipes, ifc);
  interface MemPortal portalIfc = dut.portalIfc;
endmodule

// exposed proxy interface
typedef PipePortal#(0, 1, SlaveDataBusWidth) ToHostPortalOutput;
interface ToHostOutput;
    interface ToHostPortalOutput portalIfc;
    interface Ifc::ToHost ifc;
endinterface
interface ToHostProxy;
    interface StdPortal portalIfc;
    interface Ifc::ToHost ifc;
endinterface

interface ToHostOutputPipeMethods;
    interface PipeIn#(Print_Message) print;

endinterface

interface ToHostOutputPipes;
    interface ToHostOutputPipeMethods methods;
    interface ToHostPortalOutput portalIfc;
endinterface

function Bit#(16) getToHostMessageSize(Bit#(16) methodNumber);
    case (methodNumber)
            0: return fromInteger(valueOf(SizeOf#(Print_Message)));
    endcase
endfunction

(* synthesize *)
module mkToHostOutputPipes(ToHostOutputPipes);
    Vector#(1, PipeOut#(Bit#(SlaveDataBusWidth))) indicationPipes;

    AdapterToBus#(SlaveDataBusWidth,Print_Message) print_responseAdapter <- mkAdapterToBus();
    indicationPipes[0] = print_responseAdapter.out;

    PortalInterrupt#(SlaveDataBusWidth) intrInst <- mkPortalInterrupt(indicationPipes);
    interface ToHostOutputPipeMethods methods;
    interface print = print_responseAdapter.in;

    endinterface
    interface PipePortal portalIfc;
        interface PortalSize messageSize;
            method size = getToHostMessageSize;
        endinterface
        interface Vector requests = nil;
        interface Vector indications = indicationPipes;
        interface PortalInterrupt intr = intrInst;
    endinterface
endmodule

(* synthesize *)
module mkToHostOutput(ToHostOutput);
    let indicationPipes <- mkToHostOutputPipes;
    interface Ifc::ToHost ifc;

    method Action print(Bit#(32) word);
        indicationPipes.methods.print.enq(Print_Message {word: word});
        //$display("indicationMethod 'print' invoked");
    endmethod
    endinterface
    interface PipePortal portalIfc = indicationPipes.portalIfc;
endmodule
instance PortalMessageSize#(ToHostOutput);
   function Bit#(16) portalMessageSize(ToHostOutput p, Bit#(16) methodNumber);
      return getToHostMessageSize(methodNumber);
   endfunction
endinstance


interface ToHostInverse;
    method ActionValue#(Print_Message) print;

endinterface

interface ToHostInverter;
    interface Ifc::ToHost ifc;
    interface ToHostInverse inverseIfc;
endinterface

instance Connectable#(ToHostInverse, ToHostOutputPipeMethods);
   module mkConnection#(ToHostInverse in, ToHostOutputPipeMethods out)(Empty);
    mkConnection(in.print, out.print);

   endmodule
endinstance

(* synthesize *)
module mkToHostInverter(ToHostInverter);
    FIFOF#(Print_Message) fifo_print <- mkFIFOF();

    interface Ifc::ToHost ifc;

    method Action print(Bit#(32) word);
        fifo_print.enq(Print_Message {word: word});
    endmethod
    endinterface
    interface ToHostInverse inverseIfc;

    method ActionValue#(Print_Message) print;
        fifo_print.deq;
        return fifo_print.first;
    endmethod
    endinterface
endmodule

(* synthesize *)
module mkToHostInverterV(ToHostInverter);
    PutInverter#(Print_Message) inv_print <- mkPutInverter();

    interface Ifc::ToHost ifc;

    method Action print(Bit#(32) word);
        inv_print.mod.put(Print_Message {word: word});
    endmethod
    endinterface
    interface ToHostInverse inverseIfc;

    method ActionValue#(Print_Message) print;
        let v <- inv_print.inverse.get;
        return v;
    endmethod
    endinterface
endmodule

// synthesizeable proxy MemPortal
(* synthesize *)
module mkToHostProxySynth#(Bit#(SlaveDataBusWidth) id)(ToHostProxy);
  let dut <- mkToHostOutput();
  PortalCtrlMemSlave#(SlaveControlAddrWidth,SlaveDataBusWidth) ctrlPort <- mkPortalCtrlMemSlave(id, dut.portalIfc.intr);
  let memslave  <- mkMemMethodMuxOut(ctrlPort.memSlave,dut.portalIfc.indications);
  interface MemPortal portalIfc = (interface MemPortal;
      interface PhysMemSlave slave = memslave;
      interface ReadOnly interrupt = ctrlPort.interrupt;
      interface WriteOnly num_portals = ctrlPort.num_portals;
    endinterface);
  interface Ifc::ToHost ifc = dut.ifc;
endmodule

// exposed proxy MemPortal
module mkToHostProxy#(idType id)(ToHostProxy)
   provisos (Bits#(idType, a__),
	     Add#(b__, a__, SlaveDataBusWidth));
   let rv <- mkToHostProxySynth(extend(pack(id)));
   return rv;
endmodule
endpackage: ToHost
