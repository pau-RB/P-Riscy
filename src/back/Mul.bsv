import Types::*;
import ProcTypes::*;

function Long mul1(Data a, Data b, MulFunc func);

    Int#(TAdd#(DataSz,DataSz))  a_int_s = unpack(signExtend(a));
    Int#(TAdd#(DataSz,DataSz))  b_int_s = unpack(signExtend(b));

    Int#(TAdd#(DataSz,DataSz))  a_int_z = unpack(zeroExtend(a));
    Int#(TAdd#(DataSz,DataSz))  b_int_z = unpack(zeroExtend(b));

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
        Div    : pack(a_int_s/b_int_s);
        Divu   : pack(a_int_z/b_int_z);
        Rem    : pack(a_int_s%b_int_s);
        Remu   : pack(a_int_z%b_int_z);
    endcase;

    return res;

endfunction

function Data mul2(Data a, Data b, Long partial, MulFunc func);

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

    Long mulRes = mul32(partial,opA>>valueOf(DataSz),opB<<valueOf(DataSz));

    Data res = case(func)
        Mul    : truncate   (mulRes);
        Mulh   : truncateLSB(mulRes);
        Mulhsu : truncateLSB(mulRes);
        Mulhu  : truncateLSB(mulRes);
        Div    : truncate   (partial);
        Divu   : truncate   (partial);
        Rem    : truncate   (partial);
        Remu   : truncate   (partial);
    endcase;

    return res;

endfunction

function Long mul32(Long res, Long a, Long b);

    for (Integer i = 0; i < valueOf(DataSz); i=i+1) begin
        res = res+(a[0]==1 ? b : 0);
        a = a>>1;
        b = b<<1;
    end

    return res;

endfunction