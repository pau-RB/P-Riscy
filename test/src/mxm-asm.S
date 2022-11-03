.equ msz,4

.data
A:
	.word 4
	.word 7
	.word 9
	.word 8

	.word 4
	.word 8
	.word 7
	.word 8
	
	.word 1
	.word 0
	.word 0
	.word 8
	
	.word 4
	.word 7
	.word 0
	.word 0

B:
	.word 4
	.word 4
	.word 1
	.word 1

	.word 4
	.word 7
	.word 3
	.word 1

	.word 91
	.word -7
	.word 1
	.word 0

	.word 0
	.word -3
	.word 2
	.word 0

C:
	.word 0
	.word 0
	.word 0
	.word 0

	.word 0
	.word 0
	.word 0
	.word 0

	.word 0
	.word 0
	.word 0
	.word 0

	.word 0
	.word 0
	.word 0
	.word 0


.align 2
.text
.globl main
###### mat times mat ######
main:
	
	addi	sp,sp,-8
	sw		ra,4(sp)

## Pointers
1:
	auipc 	s0,   %pcrel_hi(A)		# s0 <- &A
	addi  	s0,s0,%pcrel_lo(1b)
2:
	auipc 	s1,   %pcrel_hi(B) 		# s1 <- &B
	addi  	s1,s1,%pcrel_lo(2b)
3:
	auipc 	s2,   %pcrel_hi(C)		# s2 <- &C
	addi  	s2,s2,%pcrel_lo(3b)

## Compute
	li		s3,msz		# i
for_i:
	mv 		a0,s0
	mv 		a1,s1
	mv 		a2,s2
	addi 	s0,s0,4*msz
	addi 	s2,s2,4*msz
	call 	rxm
	addi	s3,s3,-1
	bnez	s3,for_i

## Check
	li		s3,msz*msz	# ij
4:
	auipc 	s2,   %pcrel_hi(C)		# s2 holds &C
	addi  	s2,s2,%pcrel_lo(4b)

for_ii:
	lw 		zero,0(s2)
	addi	s2,s2,4
	addi	s3,s3,-1
	bnez	s3,for_ii


	lw		ra,4(sp)
	addi	sp,sp,+8
	li		a0,0
	ret


###### row times mat ######
rxm:
	li		t0, msz		# k

for_k:
	li		t1, msz		# j
	lw		t3,0(a0)	# Ai[k]

for_j:
	lw		t4,0(a1)	# B[k][j]
	lw		t5,0(a2)	# Ci[j]
	mul		t4,t3,t4
	add		t5,t5,t4
	sw		t5,0(a2)

	addi	a1,a1,4
	addi	a2,a2,4

	addi	t1,t1,-1
	bnez	t1,for_j

	addi	a0,a0,4
	addi	a2,a2,(-4*msz)

	addi	t0,t0,-1
	bnez	t0,for_k

	li		a0,0
	ret