.global led_arm

led_arm:

led_init:
	ldr r0,=0xe0200280
	ldr r1,[r0]

	orr r1,r1,#0x1

	str r1,[r0]

	ldr r0,=0xe0200284
	ldr r1,[r0]

	bic r1,r1,#0xf
	str r1,[r0]

led_off:
	bl delay
	
	ldr r0,=0xe0200284
	ldr r1,[r0]

	orr r1,r1,#0xf
	bic r1,r1,#0x3
	str r1,[r0]

led_on:
	bl delay

	ldr r0,=0xe0200284
	ldr r1,[r0]

	orr r1,r1,#0xf
	bic r1,r1,#0xc
	str r1,[r0]

	b  led_off

	bx lr



