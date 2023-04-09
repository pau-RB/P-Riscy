import Types::*;
import ProcTypes::*;
import Vector::*;

(* noinline *)
function Data alu(Data a, Data b, AluFunc func);

    Data res = case(func)
        Add   : (a + b);
        Sub   : (a - b);
        And   : (a & b);
        Or    : (a | b);
        Xor   : (a ^ b);
        Slt   : zeroExtend( pack( signedLT(a, b) ) );
        Sltu  : zeroExtend( pack( a < b ) );
        // 5-bit shift width for 32-bit data
        Sll   : (a << b[4:0]);
        Srl   : (a >> b[4:0]);
        Sra   : signedShiftRight(a, b[4:0]);
    endcase;

    return res;

endfunction

(* noinline *)
function Bool aluBr(Data a, Data b, BrFunc brFunc);

    Bool brTaken = case(brFunc)
        Eq  : (a == b);
        Neq : (a != b);
        Lt  : signedLT(a, b);
        Ltu : (a < b);
        Ge  : signedGE(a, b);
        Geu : (a >= b);
        AT  : True;
        NT  : False;
    endcase;

    return brTaken;

endfunction

(* noinline *)
function Addr brAddrCalc(IType iType, Addr pc, Data val, Data imm, Bool taken);

    Addr pcPlus4 = pc + 4;
    Addr targetAddr = case (iType)
        J   : (pc + imm);
        Fork: (pc + imm);
        Jr  : {truncateLSB(val + imm), 1'b0};
        Forkr: {truncateLSB(val + imm), 1'b0};
        Br  : (taken ? pc + imm : pcPlus4);
        default: pcPlus4;
    endcase;

    return targetAddr;

endfunction

(* noinline *)
function ExecInst exec(IType         iType               ,
                       AluFunc       aluFunc             ,
                       MulFunc       mulFunc             ,
                       BrFunc        brFunc              ,
                       LoadFunc      ldFunc              ,
                       StoreFunc     stFunc              ,
                       Data          arg1                ,
                       Data          arg2                ,
                       Maybe#(Data)  imm                 ,
                       Maybe#(RIndx) dst                 ,
                       Addr          pc                  );

    Data aluRes  = alu       (arg1, fromMaybe(arg2, imm), aluFunc);
    Bool brTaken = aluBr     (arg1, arg2, brFunc );
    Addr brAddr  = brAddrCalc(iType, pc, arg1, fromMaybe('0, imm) , brTaken);

    ExecInst eInst = ?;

    eInst.iType   = iType;
    eInst.mulFunc = mulFunc;
    eInst.ldFunc  = ldFunc;
    eInst.stFunc  = stFunc;
    eInst.dst     = dst;

    eInst.data    = (case(iType)
                    J      : (pc+4                 );
                    Jr     : (pc+4                 );
                    Auipc  : (pc+fromMaybe('0, imm));
                    default: (aluRes               );
                    endcase);

    eInst.addr    = brAddr;

    eInst.brTaken = brTaken;

    return eInst;

endfunction

(* noinline *)
function ExecInst addr(IType         iType               ,
                       AluFunc       aluFunc             ,
                       MulFunc       mulFunc             ,
                       BrFunc        brFunc              ,
                       LoadFunc      ldFunc              ,
                       StoreFunc     stFunc              ,
                       Data          arg1                ,
                       Data          arg2                ,
                       Maybe#(Data)  imm                 ,
                       Maybe#(RIndx) dst                 ,
                       Addr          pc                  );

    ExecInst eInst = ?;

    eInst.iType   = iType  ;
    eInst.mulFunc = mulFunc;
    eInst.ldFunc  = ldFunc ;
    eInst.stFunc  = stFunc ;
    eInst.dst     = dst    ;

    eInst.data    = (case(iType)
                    St     : (arg2);
                    Join   : ('d1 );
                    default: '0;
                    endcase);

    eInst.addr    = (case (iType)
                    Ld     : (arg1+fromMaybe('0, imm));
                    St     : (arg1+fromMaybe('0, imm));
                    Fork   : (pc  +fromMaybe('0, imm));
                    Forkr  : {truncateLSB(arg1 + fromMaybe('0, imm)), 1'b0};
                    Join   : (arg1+fromMaybe('0, imm));
                    default: '0;
                    endcase);

    eInst.brTaken = False;

    return eInst;

endfunction