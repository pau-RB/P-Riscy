#ifndef TESTBENCH_TYPES
#define TESTBENCH_TYPES

#define CacheLineWords 16
#define CacheLineBytes 64
#define WMBAddrSz 12

typedef uint32_t Data;
typedef uint32_t Addr;
typedef uint8_t  IType;
typedef uint8_t  RIndx;

typedef struct {
	Data  cycle;
	Addr  pc;
	Data  rawInst;
	IType iType;
	RIndx wbDst;   // 0 if no wb
	Data  wbRes;   // ALU/Load result
	Addr  addr;    // nextpc for branch, addr for LSU
} CommitReport;

#endif