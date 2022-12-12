import Types::*;
import ProcTypes::*;

(* noinline *)
function MultInst mulStage1(Data a, Data b, MulFunc func);

    Int #(DataSz) siA = unpack(a);
    Int #(DataSz) siB = unpack(b);
    UInt#(DataSz) uiA = unpack(a);
    UInt#(DataSz) uiB = unpack(b);

    Long opA = case(func)
        Mul    : signExtend(a);
        Mulh   : signExtend(a);
        Mulhsu : signExtend(a);
        Mulhu  : zeroExtend(a);
        default: '0;
    endcase;

    Long opB = case(func)
        Mul    : signExtend(b);
        Mulh   : signExtend(b);
        Mulhsu : zeroExtend(b);
        Mulhu  : zeroExtend(b);
        default: '0;
    endcase;

    Long mulRes = mul32('0,opA,opB);

    Long res = case(func)
        Mul    : mulRes;
        Mulh   : mulRes;
        Mulhsu : mulRes;
        Mulhu  : mulRes;
        Div    : {'0,pack(siA/siB)};
        Divu   : {'0,pack(uiA/uiB)};
        Rem    : {'0,pack(siA%siB)};
        Remu   : {'0,pack(uiA%uiB)};
    endcase;

    return MultInst { arg1   : a,
                      arg2   : b,
                      partial: res,
                      mulFunc: func};

endfunction

(* noinline *)
function Data mulStage2(MultInst inst);

    Data    a       = inst.arg1;
    Data    b       = inst.arg2;
    Long    partial = inst.partial;
    MulFunc func    = inst.mulFunc;

    Long opA = case(func)
        Mul    : (signExtend(a)>>valueOf(DataSz));
        Mulh   : (signExtend(a)>>valueOf(DataSz));
        Mulhsu : (signExtend(a)>>valueOf(DataSz));
        Mulhu  : (zeroExtend(a)>>valueOf(DataSz));
        default: '0;
    endcase;

    Long opB = {b,'0};

    Long mulRes = mul32(partial,opA,opB);

    Data res = case(func)
        Mul    : truncate   (mulRes );
        Mulh   : truncateLSB(mulRes );
        Mulhsu : truncateLSB(mulRes );
        Mulhu  : truncateLSB(mulRes );
        Div    : truncate   (partial);
        Divu   : truncate   (partial);
        Rem    : truncate   (partial);
        Remu   : truncate   (partial);
    endcase;

    return res;

endfunction

(* noinline *)
function Long mul32(Long res, Long a, Long b);

    for (Integer i = 0; i < valueOf(DataSz); i=i+1) begin
        res = res+(a[0]==1 ? b : 0);
        a = a>>1;
        b = b<<1;
    end

    return res;

endfunction