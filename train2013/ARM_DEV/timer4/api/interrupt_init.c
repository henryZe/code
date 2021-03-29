#include "s5pv210.h"
#include "stdio.h"
#include "delay.h"
#include "api.h"


void ext16_int_init(void)
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

		set_clock_init_240_120();

		printf("interrupting...\n");
	}
}

void vic0_int16_init(void)
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


void Timer_4(void)
{
	//clear STATUS
	rTINT_CSTAT |= (1<<9);
	//clear VIC0address
	rVIC0ADDRESS = 0;
	
	printf("Timer4 is up!\n");
}


void Timer4_Vic0_init(void)
{
	printf("1\n");
	rVIC0INTENCLEAR |= (1<<25);
	//IRQ中断
	rVIC0INTSELECT &= ~(1<<25);

	rVIC0VECTADDR25 = (unsigned long)Timer_4;

	rVIC0ADDRESS = 0;

	rVIC0INTENABLE |= (1<<25);

	printf("1over\n");
}


void Timer4_init(void)
{
	printf("2\n");
	//预分频
	rTCFG0 = (49<<8);
	//二级分频
	rTCFG1 = (4<<16);

	//初始值
	rTCNTB4 = 82500;

	//STATUS clear
	rTINT_CSTAT |= (0x1<<9);
	//Enable
	rTINT_CSTAT |= (0x1<<4);

	//Manual reload
	rTCON |= (1<<21);
	//stop reload
	rTCON &= ~(1<<21);

	//Auto reload
	rTCON |= (1<<22);

	//Start Timer4
	rTCON |= (1<<20);

	printf("2over\n");
}


void interrupt_init(void)
{
	//ext16_int_init();
	
	//vic0_int16_init();

	Timer4_Vic0_init();

	Timer4_init();

	while(1);
}


