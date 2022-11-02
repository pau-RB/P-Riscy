#ifndef _TESTBENCH_TYPES_H
#define _TESTBENCH_TYPES_H

#define CacheLineWords 16
#define CacheLineBytes 64
#define WMBAddrSz 12
#define MEM_MAX_ADDR (1<<WMBAddrSz)*CacheLineBytes

#define StartPC 0x1000

typedef uint32_t Data;
typedef uint32_t Addr;
typedef uint32_t VerifID;
typedef uint8_t  IType;
typedef uint8_t  RIndx;

// opcode
#define opLoad    0b0000011
#define opFork    0b0001011
#define opMiscMem 0b0001111
#define opOpImm   0b0010011
#define opAuipc   0b0010111
#define opStore   0b0100011
#define opJoin    0b0101011
#define opAmo     0b0101111
#define opOp      0b0110011
#define opLui     0b0110111
#define opBranch  0b1100011
#define opJalr    0b1100111
#define opJal     0b1101111
#define opSystem  0b1110011

//Itypes
#define iTypeUnsup 0
#define iTypeAlu   1
#define iTypeMul   2
#define iTypeLd    3
#define iTypeSt    4
#define iTypeFork  5
#define iTypeJoin  6
#define iTypeJ     7
#define iTypeJr    8
#define iTypeBr    9
#define iTypeAuipc 10

typedef struct {
	Data    cycle;
	VerifID verifID;
	Addr    pc;
	Data    rawInst;
	IType   iType;
	RIndx   wbDst;   // 0 if no wb
	Data    wbRes;   // ALU/Load result, childverifID for fork
	Addr    addr;    // nextpc for branch, addr for LSU, nextpc for Fork
} CommitReport;

#endif