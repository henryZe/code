.global led_arm

led_arm:

led_init:
	ldr r0,=0xe0200280
	ldr r1,[r0]

	orr r1,r1,#0x1

	str r1,[r0]

	ldr r0,=0xe0200284
	ldr r1,[r0]

	orr r1,r1,#0xf
	str r1,[r0]

	ldr r2,=0xe0200C40
	ldr r3,[r2]
	
	bic r3,r3,#0xf
	str r3,[r2]

	ldr r2,=0xe0200C44
	
_compare:	
	ldr r3,[r2]
	and r10,r3,#0x1

	cmp r10,#1
	blne _invert
	
	b   _compare

_invert:
	ldr r3,[r2]
	and r10,r3,#0x1
	cmp r10,#1

	bne _invert

	eor r1,#0xff
	str r1,[r0]

	bl  _compare


