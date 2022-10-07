#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <string>
#include "TestbenchTypes.h"


// opcode
#define opLoad    0b0000011
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

// function code
// ALU
#define fnADD  0b000
#define fnSLL  0b001
#define fnSLT  0b010
#define fnSLTU 0b011
#define fnXOR  0b100
#define fnSR   0b101
#define fnOR   0b110
#define fnAND  0b111
// Branch
#define fnBEQ  0b000
#define fnBNE  0b001
#define fnBLT  0b100
#define fnBGE  0b101
#define fnBLTU 0b110
#define fnBGEU 0b111
// Load
#define fnLW  0b010
#define fnLB  0b000
#define fnLH  0b001
#define fnLBU 0b100
#define fnLHU 0b101
// Store
#define fnSW 0b010
#define fnSB 0b000
#define fnSH 0b001
// Amo
#define fnLR 0b00010
#define fnSC 0b00011
//MiscMem
#define fnFENCE  0b000
#define fnFENCEI 0b001
// System
#define fnPRIV    0b000
#define privSCALL 0x000

//Itypes
#define iTypeUnsup 0
#define iTypeAlu   1
#define iTypeLd    2
#define iTypeSt    3
#define iTypeJ     4
#define iTypeJr    5
#define iTypeBr    6
#define iTypeAuipc 7

union Inst
{
	uint32_t u;
	 int32_t s;
};

std::string uint_to_hex(uint32_t w);

std::string int_to_hex(int32_t w);

// Overwrite part of a base string
void overwrite (std::string &base, const std::string &text, int position, int max);

// Prints the instruction type
std::string printIType (const IType iType);

// Get IType
IType getIType(const Data uinst);

// Pretty print of an instruction
std::string interpreter(const Data uinst);

void printCMR(const CommitReport cmr);

#endif