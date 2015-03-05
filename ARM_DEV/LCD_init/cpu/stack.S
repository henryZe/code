.extern printf

.global stack
stack:
	mov r9,lr

	mov r3,#5
	mov r4,#0x41000000
	str r3,[r4]

	ldr r1,[r4]

	ldr r0,=fmt
	bl  printf

	mov r4,#4
	mov r5,#5
	mov r6,#6

	stmfd sp!,{r4-r6}
	ldmfd sp!,{r1-r3}

	ldr r0,=fmt1
	bl  printf

	mov lr,r9
	bx  lr

fmt:
	.asciz "ldr_data = %x\n"

fmt1:
	.asciz "r1 = %x  r2 = %x  r3 = %x\n"
