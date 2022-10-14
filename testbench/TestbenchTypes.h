#ifndef _TESTBENCH_TYPES_H
#define _TESTBENCH_TYPES_H

#define CacheLineWords 16
#define CacheLineBytes 64
#define WMBAddrSz 12
#define MEM_MAX_ADDR (1<<WMBAddrSz)*CacheLineBytes

#define StartPC 0x200

#define FrontWidth 4

typedef uint32_t Data;
typedef uint32_t Addr;
typedef uint8_t  FrontID;
typedef uint8_t  IType;
typedef uint8_t  RIndx;

typedef struct {
	Data    cycle;
	FrontID feID;
	Addr    pc;
	Data    rawInst;
	IType   iType;
	RIndx   wbDst;   // 0 if no wb
	Data    wbRes;   // ALU/Load result
	Addr    addr;    // nextpc for branch, addr for LSU
} CommitReport;

#endif