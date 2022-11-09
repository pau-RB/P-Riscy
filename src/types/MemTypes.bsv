import Types::*;
import Memory::*;
import Vector::*;


//////////// CACHE WIDEMEM REQUESTS ////////////


typedef 8 CacheRows; // small size to improve compile times

typedef Bit#( TSub#(TSub#(TSub#(AddrSz, 2), TLog#(CacheRows)), TLog#(CacheLineWords)) ) CacheTag;
typedef Bit#( TLog#(CacheRows) ) CacheIndex;

typedef struct{
    CacheTag  tag;
    CacheLine data;
} CacheEntry deriving(Eq,Bits);




//////////// BRAM ////////////

typedef 12 WMBAddrSz;
typedef Bit#(WMBAddrSz) WMBAddr;