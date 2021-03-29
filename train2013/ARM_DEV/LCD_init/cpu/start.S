
.text

.extern uart_init
.extern printf
.extern delay
.extern C_program
.extern dis_cpsr
.extern dis_cp15
.extern stack
.extern loop_print


.global printf
.global _start

_start:
	mov r7,lr	

	bl  uart_init
	
#	bl  loop_print
	
	bl  dis_cpsr

#	bl  dis_cp15
	
#	bl  stack

	bl  ExcVecTable_init

	bl  C_program 

#	b   _start

	mov lr,r7
	bx  lr


ExcVecTable_init:
	ldr r0,=HandlerIRQ
	ldr r1,=0xd0037418
	str r0,[r1]
	bx  lr

HandlerIRQ:
#	进入中断
	sub   lr,lr,#4
	stmfd sp!,{r0-r12,lr}

#	供中断程序运行后返回
	ldr   lr,=return_irq
	ldr   pc,=isr

return_irq:
	ldmfd sp!,{r0-r12,pc}^

isr:
	ldr   r0,=0xf2000000
	ldr   r1,[r0]

#	判断IRQ_STATUS是否标记地址
	cmp   r1,#0
	bne   VIC0

	ldr   r0,=0xf2200000
	ldr   r1,[r0]
	cmp   r1,#0
	bne   VIC2

	b     return_irq


VIC0:
#	加载VIC0ADDRESS中断程序
	ldr   r0,=0xf2000f00
	ldr   pc,[r0]

VIC2:
#	加载VIC2ADDRESS中断程序
	ldr   r0,=0xf2200f00
	ldr   pc,[r0]

.end
