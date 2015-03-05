.global dis_cpsr

dis_cpsr:
	mov r9,lr
	mov r11,sp

	mrs r1,cpsr
	ldr r0,=fmt1
	bl printf

	mrs r1,cpsr
	bic r1,r1,#0x80
	msr cpsr_c,r1

	mrs r1,cpsr
	ldr r0,=fmt1
	bl  printf

	mov sp,r11
	mov lr,r9
	bx  lr

fmt1:
	.asciz "cpsr = %x\n"
