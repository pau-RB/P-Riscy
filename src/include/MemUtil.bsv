import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Fifo::*;
import Vector::*;
import Memory::*;

function Data extendLoad( Data value, Addr addr, LoadFunc func );

    Bit#(32) wordValue = value;
    
    Bit#(5)  halfsel   = {(addr[1:0] & 2'b10),3'b000};
    Bit#(16) halfValue = truncate(value>>halfsel);

    Bit#(5)  bytesel   = {(addr[1:0] & 2'b11),3'b000};
    Bit#(8)  byteValue = truncate(value>>bytesel);

    case(func)
        LB:  return signExtend(byteValue);
        LH:  return signExtend(halfValue);
        LW:  return signExtend(wordValue);
        LBU: return zeroExtend(byteValue);
        LHU: return zeroExtend(halfValue);
        default: return value;
    endcase

endfunction

function Bit#(CacheLineBytes) writeEnReq (MemReq req);
    
    Bit#(CacheLineBytes) write_en = 0;

    CacheByteSelect wordsel = truncate( req.addr & 32'hfffffffc );
    CacheByteSelect halfsel = truncate( req.addr & 32'hfffffffe );
    CacheByteSelect bytesel = truncate( req.addr & 32'hffffffff );

    if( req.op == St ) begin
        case(req.func)
            SB:  write_en = 'b1111 << wordsel;
            SH:  write_en = 'b11   << halfsel;
            SW:  write_en = 'b1    << bytesel;
        endcase
    end

    return write_en;

endfunction

function CacheLine embedReq (MemReq req);

    Data word = '0;

    if( req.op == St ) begin
        case(req.func)
            SB:  word = {req.data[ 7:0],req.data[ 7:0],req.data[ 7:0],req.data[ 7:0]};
            SH:  word = {req.data[15:0],req.data[15:0]};
            SW:  word = {req.data};
        endcase
    end

    CacheLine line = replicate(word);

    return line;

endfunction

function WideMemReq toWideMemReadReq( MemReq req );

    Addr addr = req.addr;
    for( Integer i = 0 ; i < valueOf(TLog#(CacheLineBytes)) ; i = i+1 ) begin
        addr[i] = 0;
    end

    return WideMemReq {
                write_en: '0,
                addr: addr,
                data: ?
            };

endfunction

function WideMemReq toWideMemReq( MemReq req );
    
    Bit#(CacheLineBytes) write_en = writeEnReq(req);

    Addr addr = req.addr;
    for( Integer i = 0 ; i < valueOf(TLog#(CacheLineBytes)) ; i = i+1 ) begin
        addr[i] = 0;
    end

    CacheLine data = embedReq( req );

    return WideMemReq {
                write_en: write_en,
                addr: addr,
                data: data
            };

endfunction