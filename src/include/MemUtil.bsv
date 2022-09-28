import Types::*;
import ProcTypes::*;
import MemTypes::*;
import Fifo::*;
import Vector::*;
import Memory::*;

function Data extendLoad( Data value, Addr addr, LoadFunc func );

    Bit#(32) wordValue = value;
    
    Bit#(2)  halfsel   = addr[1:0] & 2'b10;
    Bit#(16) halfValue = truncate( value >> halfsel );

    Bit#(2)  bytesel   = addr[1:0] & 2'b11;
    Bit#(8)  byteValue = truncate( value >> bytesel );

    case(func)
        LB:  return signExtend(byteValue);
        LH:  return signExtend(halfValue);
        LW:  return signExtend(wordValue);
        LBU: return zeroExtend(byteValue);
        LHU: return zeroExtend(halfValue);
        default: return value;
    endcase

endfunction

function WideMemReq toWideMemReadReq( MemReq req );

    Addr addr = req.addr;
    for( Integer i = 0 ; i < valueOf(TLog#(CacheLineBytes)) ; i = i+1 ) begin
        addr[i] = 0;
    end
    CacheLine data = replicate( req.data );

    return WideMemReq {
                write_en: '0,
                addr: addr,
                data: data
            };

endfunction

function WideMemReq toWideMemReq( MemReq req );
    
    Bit#(CacheLineBytes) write_en = 0;

    CacheByteSelect wordsel = truncate( req.addr & 32'hfffffffc );
    CacheByteSelect halfsel = truncate( req.addr & 32'hfffffffe );
    CacheByteSelect bytesel = truncate( req.addr & 32'hffffffff );

    if( req.op == St ) begin
        case(req.func)
            SB:  write_en = 'b1111 << wordsel;
            SH:  write_en = 'b11 << halfsel;
            SW:  write_en = 'b1 << bytesel;
        endcase
    end

    Addr addr = req.addr;
    for( Integer i = 0 ; i < valueOf(TLog#(CacheLineBytes)) ; i = i+1 ) begin
        addr[i] = 0;
    end
    CacheLine data = replicate( req.data );

    return WideMemReq {
                write_en: write_en,
                addr: addr,
                data: data
            };

endfunction

module mkSplitWideMem(  Bool initDone, WideMem mem,
                        Vector#(n, WideMem) ifc );

    Vector#(n, Fifo#(2, WideMemReq)) reqFifos <- replicateM(mkCFFifo);
    Fifo#(TAdd#(n,1), Bit#(TLog#(n))) reqSource <- mkCFFifo;
    Vector#(n, Fifo#(2, WideMemResp)) respFifos <- replicateM(mkCFFifo);

    rule doWideMemReq(initDone);
        Maybe#(Bit#(TLog#(n))) req_index = tagged Invalid;
        for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
            if( !isValid(req_index) && reqFifos[i].notEmpty ) begin
                req_index = tagged Valid (fromInteger(i));
            end
        end

        if( isValid(req_index) ) begin
            let req = reqFifos[ fromMaybe(?,req_index) ].first;
            reqFifos[ fromMaybe(?,req_index) ].deq();

            mem.req(req);
            if( req.write_en == 0 ) begin
                // req is a load, so keep track of the source
                reqSource.enq( fromMaybe(?,req_index) );
            end
        end
    endrule

    rule doWideMemResp(initDone);
        let resp <- mem.resp;

        let source = reqSource.first;
        reqSource.deq;

        respFifos[source].enq( resp );
    endrule

    Vector#(n, WideMem) wideMemIfcs = newVector;
    for( Integer i = 0 ; i < valueOf(n) ; i = i+1 ) begin
        wideMemIfcs[i] =
            (interface WideMem;
                method Action req( WideMemReq x );
                    reqFifos[i].enq(x);
                endmethod
                method ActionValue#(WideMemResp) resp;
                    let x = respFifos[i].first;
                    respFifos[i].deq;
                    return x;
                endmethod
            endinterface);
    end
    return wideMemIfcs;
endmodule
