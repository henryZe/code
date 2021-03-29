#include "s5pv210.h"
#include "stdio.h"
#include "delay.h"


void ext_int_init(void)
{
	//设置GPH2DAT[0]为中断功能
	rGPH2CON |= 0xf;
	
	//EXT_C设置为下降沿触发,使能外部中断16,并将其申请信号清0
	rEXT_INT_2_CON &= ~(0x7);
	rEXT_INT_2_CON |= 0x2;
	
	rEXT_INT_2_MASK &= ~(0x1);

	rEXT_INT_2_PEND |= 0x1;
}

void Extint_16(void)
{
	//由EXT_C来判断是否为外部中断16(二级中断源)
	if(rEXT_INT_2_PEND & (0x1))
	{
		//PEND清为0,反操作!
		rEXT_INT_2_PEND |= 0x1;

		//清除VIC0中断程序地址
		rVIC0ADDRESS = 0;

		rGPJ2DAT = ~(0xf);

		printf("interrupting...\n");
		delay_1sec();
	}
}

void vic0_int_init(void)
{
	//屏蔽中断16号,才可以对中断进行初始化
	rVIC0INTENCLEAR |= 0x10000;

	//将16号中断设置为IRQ模式
	rVIC0INTSELECT  &= ~(0x10000);

	//设置中断程序入口,以供VIC0ADDRESS提取
	rVIC0VECTADDR16 = (unsigned long)Extint_16;

	//初始化VIC0ADDRESS
	rVIC0ADDRESS = 0;

	//开启中断16号,初始化完毕
	rVIC0INTENABLE  |= 0x10000;
}


void interrupt_led(void)
{
	ext_int_init();
	
	vic0_int_init();
}


