// opcode
typedef Bit#(7) Opcode;
Opcode opLoad    = 7'b0000011;
Opcode opFork    = 7'b0001011;
Opcode opMiscMem = 7'b0001111;
Opcode opOpImm   = 7'b0010011;
Opcode opAuipc   = 7'b0010111;
Opcode opStore   = 7'b0100011;
Opcode opAmo     = 7'b0101111;
Opcode opOp      = 7'b0110011;
Opcode opLui     = 7'b0110111;
Opcode opBranch  = 7'b1100011;
Opcode opJalr    = 7'b1100111;
Opcode opJal     = 7'b1101111;
Opcode opSystem  = 7'b1110011;

// function code
// ALU
Bit#(3) fnADD   = 3'b000;
Bit#(3) fnSLL   = 3'b001;
Bit#(3) fnSLT   = 3'b010;
Bit#(3) fnSLTU  = 3'b011;
Bit#(3) fnXOR   = 3'b100;
Bit#(3) fnSR    = 3'b101;
Bit#(3) fnOR    = 3'b110;
Bit#(3) fnAND   = 3'b111;
// FORK/JOIN
Bit#(5) fnFork  = 5'b00000;
Bit#(5) fnForkr = 5'b00001;
Bit#(5) fnJoin  = 5'b00010;
// M
Bit#(3) fnMUL   = 3'b000;
Bit#(3) fnMULH  = 3'b001;
Bit#(3) fnMULHSU= 3'b010;
Bit#(3) fnMULHU = 3'b011;
Bit#(3) fnDIV   = 3'b100;
Bit#(3) fnDIVU  = 3'b101;
Bit#(3) fnREM   = 3'b110;
Bit#(3) fnREMU  = 3'b111;
// Branch
Bit#(3) fnBEQ   = 3'b000;
Bit#(3) fnBNE   = 3'b001;
Bit#(3) fnBLT   = 3'b100;
Bit#(3) fnBGE   = 3'b101;
Bit#(3) fnBLTU  = 3'b110;
Bit#(3) fnBGEU  = 3'b111;
// Load
Bit#(3) fnLW    = 3'b010;
Bit#(3) fnLB    = 3'b000;
Bit#(3) fnLH    = 3'b001;
Bit#(3) fnLBU   = 3'b100;
Bit#(3) fnLHU   = 3'b101;
// Store
Bit#(3) fnSW    = 3'b010;
Bit#(3) fnSB    = 3'b000;
Bit#(3) fnSH    = 3'b001;
// Amo
Bit#(5) fnLR    = 5'b00010;
Bit#(5) fnSC    = 5'b00011;
//MiscMem
Bit#(3) fnFENCE  = 3'b000;
//Bit#(3) fnFENCEI = 3'b001;
// System
Bit#(3) fnPRIV   = 3'b000;
Bit#(12) privSCALL    = 12'h000;