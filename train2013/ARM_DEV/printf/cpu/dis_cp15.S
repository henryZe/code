
.extern printf

.global dis_cp15

dis_cp15:
	mov r9,lr	

	mrc p15,0,r1,c0,c0,0
	ldr r0,=fmt2
	bl printf

	mrc p15,0,r1,c1,c0,0
	ldr r0,=fmt3
	bl  printf

	mrc p15,0,r1,c1,c0,0
	bic r1,#0x800
	mcr p15,0,r1,c1,c0,0

	mrc p15,0,r1,c1,c0,0
	ldr r0,=fmt3
	bl  printf

	mov lr,r9
	bx  lr

fmt2:
	.asciz "CP15 C0:R0 = %x\n"

fmt3:
	.asciz "CP15 C1:R0 = %x\n"




