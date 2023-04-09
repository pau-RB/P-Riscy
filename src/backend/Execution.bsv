import Types::*;
import ProcTypes::*;
import Vector::*;

(* noinline *)
function Data aluAri(Data a, Data b, AluFunc func);

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
function Bool aluBrT(Data a, Data b, BrFunc brFunc);

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
function Addr aluBrA(Data arg1, Data imm, Addr pc, Bool taken, IType iType);

    Addr pcPlus4 = pc + 4;
    Addr targetAddr = case (iType)
        J   : (pc + imm);
        Jr  : {truncateLSB(arg1 + imm), 1'b0};
        Br  : (taken ? pc + imm : pcPlus4);
        default: pcPlus4;
    endcase;

    return targetAddr;

endfunction

typedef struct{
    Data res;
    Addr add;
    Bool brt;
} Exec deriving(Bits);

(* noinline *)
function Exec execari(IType        iType  ,
                      AluFunc      aluFunc,
                      BrFunc       brFunc ,
                      Data         arg1   ,
                      Data         arg2   ,
                      Maybe#(Data) imm    ,
                      Addr         pc     );

    Data aluRes  = aluAri(arg1, fromMaybe(arg2, imm), aluFunc);
    Bool brTaken = aluBrT(arg1, arg2                , brFunc );
    Addr add     = aluBrA(arg1, fromMaybe('0  , imm), pc, brTaken, iType);

    Data res = (case(iType)
                J      : (pc+4                 );
                Jr     : (pc+4                 );
                Auipc  : (pc+fromMaybe('0, imm));
                default: (aluRes               );
                endcase);

    return Exec{res: res, add: add, brt: brTaken};

endfunction

(* noinline *)
function Exec execmem(IType        iType,
                      Data         arg1 ,
                      Data         arg2 ,
                      Maybe#(Data) imm  ,
                      Addr         pc   );

    Data res = (case(iType)
                St     : (arg2);
                Join   : ('d1 );
                default: '0;
                endcase);

    Addr add = (case (iType)
                Ld     : (arg1+fromMaybe('0, imm));
                St     : (arg1+fromMaybe('0, imm));
                Fork   : (pc  +fromMaybe('0, imm));
                Forkr  : {truncateLSB(arg1 + fromMaybe('0, imm)), 1'b0};
                Join   : (arg1+fromMaybe('0, imm));
                default: '0;
                endcase);

    return Exec{res: res, add: add, brt: False};

endfunction