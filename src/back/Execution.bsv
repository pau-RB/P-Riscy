import Types::*;
import ProcTypes::*;
import Alu::*;
import Vector::*;

(* noinline *)
function ExecInst exec(DecodedInst dInst, Data arg1, Data arg2, Addr pc, Addr ppc);

    ExecInst eInst = ?;

    // do ALU operation: use imm instead of rs2 if imm is valid (consider LW and SW)
    Data aluRes = alu(arg1, isValid(dInst.imm) ? fromMaybe(?, dInst.imm) : arg2, dInst.aluFunc);

    // set eInst
    eInst.iType  = dInst.iType;
    eInst.ldFunc = dInst.ldFunc;
    eInst.stFunc = dInst.stFunc;
    eInst.dst    = dInst.dst;

    eInst.data = 
               dInst.iType==St ?
                 arg2 :
               (dInst.iType==J || dInst.iType == Jr || dInst.iType == Fork || dInst.iType == Forkr) ?
                 (pc+4) :
               dInst.iType==Auipc ?
                 (pc + fromMaybe(?, dInst.imm)) :
               dInst.iType==Join ?
                 'd1 : aluRes;

    let brTaken = aluBr(arg1, arg2, dInst.brFunc);
    let brAddr  = brAddrCalc(pc, arg1, dInst.iType, fromMaybe(?, dInst.imm), brTaken);

    eInst.addr = (dInst.iType == Ld || dInst.iType == St || dInst.iType == Join) ? aluRes : brAddr;
    eInst.mispredict = brAddr != ppc;
    eInst.brTaken = brTaken;

    return eInst;

endfunction

