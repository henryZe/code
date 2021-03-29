.global delay
delay:
	mov r0,#0x4000000
	sub r6,r6,#1
temp:
	subs r0,r0,#1
	cmp r0,#0
	bne temp

	bx  lr

