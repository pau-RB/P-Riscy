import Types::*;
import ProcTypes::*;

function Data mul(Data a, Data b, MulFunc func);

  Int#(TAdd#(DataSz,DataSz))  a_int_s = unpack(signExtend(a));
  Int#(TAdd#(DataSz,DataSz))  b_int_s = unpack(signExtend(b));

  Int#(TAdd#(DataSz,DataSz))  a_int_z = unpack(zeroExtend(a));
  Int#(TAdd#(DataSz,DataSz))  b_int_z = unpack(zeroExtend(b));

  Data res = case(func)
    Mul    : truncate   (pack(a_int_s*b_int_s));
    Mulh   : truncateLSB(pack(a_int_s*b_int_s));
    Mulhsu : truncateLSB(pack(a_int_s*b_int_z));
    Mulhu  : truncateLSB(pack(a_int_z*b_int_z));
    Div    : truncate   (pack(a_int_s/b_int_s));
    Divu   : truncate   (pack(a_int_z/b_int_z));
    Rem    : truncate   (pack(a_int_s%b_int_s));
    Remu   : truncate   (pack(a_int_z%b_int_z));
  endcase;

  return res;

endfunction