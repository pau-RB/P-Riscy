#ifndef _TESTBENCH_TYPES_H
#define _TESTBENCH_TYPES_H

#define CacheLineWords 16
#define CacheLineBytes 64
#define MEM_MAX_ADDR 0x80000000

#define StartPC 0x00001000

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
#define iTypeDiv   3
#define iTypeLd    4
#define iTypeSt    5
#define iTypeFork  6
#define iTypeForkr 7
#define iTypeJoin  8
#define iTypeJ     9
#define iTypeJr    10
#define iTypeBr    11
#define iTypeAuipc 12

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

typedef struct {
	VerifID verifID;
	Data    cycle;
	Data    commit;
	Data	data;
} Message;

typedef struct {
	Data    hit;
    Data    miss;
    Data    empty;
} FetchStat;

typedef struct {
	Data    memOvb;
	Data    arithOvb;
	Data    empty;
} ArbiterStat;

typedef struct {
	Data    hLd;
    Data    hSt;
    Data    hJoin;
    Data    mLd;
    Data    mSt;
    Data    mJoin;
    Data    dLd;
    Data    dSt;
    Data    dJoin;
} LSUStat;

typedef struct {
	Data hWR; // Total hits on read
	Data mWR; // Total miss on read
	Data hRD; // Total hits on read
	Data mRD; // Total miss on read
	Data tWB; // Total writebacks
} WMCStat;

typedef struct {
	VerifID     verifID;
	Data        cycle;
	Data        commit;
	Data	    data;
	FetchStat   fetch;
	ArbiterStat arbiter;
	LSUStat     lsu;
	WMCStat     l2s;
} MemStat;

#endif