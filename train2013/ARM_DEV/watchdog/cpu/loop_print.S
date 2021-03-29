
.extern printf

.global loop_print

loop_print:	
	mov r9,lr

	mov r6,#3

loop:
	ldr r0,=fmt
	bl  printf

	bl delay

	cmp r6,#0
	bne loop
       	
	mov lr,r9
	bx  lr

fmt:
	.asciz ">>>>>> gec210 <<<<<<\n"
