import Types::*;
import ProcTypes::*;
import Mul::*;
import Alu::*;
import Vector::*;

(* noinline *)
function ExecInst exec(DecodedInst dInst, Data rVal1, Data rVal2, Addr pc, Addr ppc);
  ExecInst eInst = ?;

  // do ALU operation: use imm instead of rs2 if imm is valid (consider LW and SW)
  Data aluVal2 = isValid(dInst.imm) ? fromMaybe(?, dInst.imm) : rVal2;
  let aluRes = alu(rVal1, aluVal2, dInst.aluFunc);
  let mulRes = mul(rVal1, rVal2,   dInst.mulFunc);
  
  // set eInst
  eInst.iType = dInst.iType;
  eInst.ldFunc = dInst.ldFunc;
  eInst.stFunc = dInst.stFunc;
  eInst.dst = dInst.dst;
  
  eInst.data = 
               dInst.iType==St ?
                 rVal2 :
               (dInst.iType==J || dInst.iType == Jr || dInst.iType == Fork || dInst.iType == Forkr) ?
                 (pc+4) :
               dInst.iType==Auipc ?
                 (pc + fromMaybe(?, dInst.imm)) :
               dInst.iType==Join ?
                 'd1 :
               dInst.iType==Mul ?
                 mulRes : 
                 aluRes;

  let brTaken = aluBr(rVal1, rVal2, dInst.brFunc);
  let brAddr = brAddrCalc(pc, rVal1, dInst.iType, fromMaybe(?, dInst.imm), brTaken);

  eInst.addr = (dInst.iType == Ld || dInst.iType == St || dInst.iType == Join) ? aluRes : brAddr;
  eInst.mispredict = brAddr != ppc;
  eInst.brTaken = brTaken;
  
  return eInst;
endfunction

