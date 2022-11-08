.align 2
.text
.globl fork
fork:
	mv 		t0,sp
	mv		t1,ra
	mv		sp,a3
1:
	auipc	ra,%pcrel_hi(child_return)
	addi	ra,ra,%pcrel_lo(1b)
	sw		zero,0(a3)
	.word	0x0006008b					#forkr a2
	mv		sp,t0
	mv		ra,t1
	ret
child_return:
	sw		a0,4*10(sp)
	sw		a1,4*11(sp)
	.word	0x0001002b					#join 0(sp)
	lw		x1,4*1(sp)

	lw		x3,4*3(sp)
	lw		x4,4*4(sp)
	lw		x5,4*5(sp)
	lw		x6,4*6(sp)
	lw		x7,4*7(sp)
	lw		x8,4*8(sp)
	lw		x9,4*9(sp)


	lw		x12,4*12(sp)
	lw		x13,4*13(sp)
	lw		x14,4*14(sp)
	lw		x15,4*15(sp)
	lw		x16,4*16(sp)
	lw		x17,4*17(sp)
	lw		x18,4*18(sp)
	lw		x19,4*19(sp)
	lw		x20,4*20(sp)
	lw		x21,4*21(sp)
	lw		x22,4*22(sp)
	lw		x23,4*23(sp)
	lw		x24,4*24(sp)
	lw		x25,4*25(sp)
	lw		x26,4*26(sp)
	lw		x27,4*27(sp)
	lw		x28,4*28(sp)
	lw		x29,4*29(sp)
	lw		x30,4*30(sp)
	lw		x31,4*31(sp)
	lw		sp,4*2(sp)
	ret