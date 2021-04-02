#include "s5pv210.h"
#include "stdio.h"
#include "delay.h"
#include "api.h"


void ext17_int_init(void)
{
	//设置GPH2DAT[0]为中断功能
	rGPH2CON |= 0xf0;
	
	//EXT_C设置为下降沿触发,使能外部中断16,并将其申请信号清0
	rEXT_INT_2_CON &= ~(0x70);
	rEXT_INT_2_CON |= 0x20;
	
	rEXT_INT_2_MASK &= ~(0x2);

	rEXT_INT_2_PEND |= 0x2;
}


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


void ext14_int_init(void)
{
	rGPH1CON |= (0xf<<24);
	
	//EXT_C设置为下降沿触发,使能外部中断16,并将其申请信号清0
	rEXT_INT_1_CON = (0x2<<24);
	
	rEXT_INT_1_MASK &= ~(0x1<<6);

	rEXT_INT_1_PEND |= (0x1<<6);
}


void Timer0_PWM_change(void)
{
	//IO口设置为中断PWM TOUT_0
	rGPD0CON = (2<<0);

	//预分频
	rTCFG0 = (49<<0);
	//二级分频
	rTCFG1 = (4<<0);

	rTCNTB0 = 12500;
	rTCMPB0 = rTCNTB0/2;

	//manual reload
	rTCON |= (0x1<<1);
	//stop reload
	rTCON &= ~(1<<1);

	//Auto reload
	rTCON |= (1<<3);

	//Start
	rTCON |= (1<<0);
}


void Timer0_PWM_stop(void)
{
	//IO口设置为中断PWM TOUT_0
	rGPD0CON = (2<<0);

	//预分频
	rTCFG0 = (49<<0);
	//二级分频
	rTCFG1 = (4<<0);

	rTCNTB0 = 12500;
	rTCMPB0 = 1;

	//manual reload
	rTCON |= (0x1<<1);
	//stop reload
	rTCON &= ~(1<<1);

	//Auto reload
	rTCON |= (1<<3);

	//Start
	rTCON |= (1<<0);
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

		rTINT_CSTAT &= ~(0x1<<4);

		printf("Stop feed dog...\n");
	}

	//由EXT_C来判断是否为外部中断17(二级中断源)
	if(rEXT_INT_2_PEND & (0x2))
	{
		//PEND清为0,反操作!
		rEXT_INT_2_PEND |= 0x2;

		//清除VIC0中断程序地址
		rVIC0ADDRESS = 0;

		Timer0_PWM_stop();

		printf("interrupting17...\n");
	}
}


void Extint_14(void)
{
		//PEND清为0,反操作!
		rEXT_INT_1_PEND |= 0x1<<6;

		//清除VIC0中断程序地址
		rVIC0ADDRESS = 0;

		printf("Touch point\n");
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


void vic0_int14_init(void)
{
	//屏蔽中断14号,才可以对中断进行初始化
	rVIC0INTENCLEAR |= 0x4000;

	//将14号中断设置为IRQ模式
	rVIC0INTSELECT  &= ~(0x4000);

	//设置中断程序入口,以供VIC0ADDRESS提取
	rVIC0VECTADDR14 = (unsigned long)Extint_14;

	//初始化VIC0ADDRESS
	rVIC0ADDRESS = 0;

	//开启中断14号,初始化完毕
	rVIC0INTENABLE  |= 0x4000;
}


void Timer_4(void)
{
	//clear STATUS
	rTINT_CSTAT |= (1<<9);
	//clear VIC0address
	rVIC0ADDRESS = 0;
	
	rWTCNT = 100000;

	printf("feed dog!\n");
}


void Timer4_Vic0_init(void)
{
	rVIC0INTENCLEAR |= (1<<25);
	
	//IRQ中断
	rVIC0INTSELECT &= ~(1<<25);

	rVIC0VECTADDR25 = (unsigned long)Timer_4;

	rVIC0ADDRESS = 0;

	rVIC0INTENABLE |= (1<<25);
}


void Timer4_init(void)
{
	//预分频
	rTCFG0 = (49<<8);
	//二级分频
	rTCFG1 = (4<<16);

	//初始值
	rTCNTB4 = 10000;

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
}


void Timer0_PWM_init(void)
{
	//IO口设置为中断PWM TOUT_0
	rGPD0CON = (2<<0);

	//预分频
	rTCFG0 = (49<<0);
	//二级分频
	rTCFG1 = (4<<0);

	rTCNTB0 = 12500;
	rTCMPB0 = rTCNTB0/20;

	//manual reload
	rTCON |= (0x1<<1);
	//stop reload
	rTCON &= ~(1<<1);

	//Auto reload
	rTCON |= (1<<3);

	//Start
	rTCON |= (1<<0);
}


void watchdog_init(void)
{
	//预分频
	rWTCON = (49<<8);
	//二级分频
	rWTCON &= ~(0x3<<3);

	rWTCNT = 100000;

	//关闭中断信号
	rWTCON &= ~(1<<2);
	//Enable reset
	rWTCON |= (1<<0);

	//Start watchdog
	rWTCON |= (0x1<<5);
}


void ADC_int(void)
{
	//clear ADC 标记
	rCLRINTADC0 |= 0x1;

	rVIC2ADDRESS = 0;

	int data;

	data = (int)(rTSDATX0 & (0xfff));

	printf("interrupt:data = %d\n",data);

	delay_1sec();

	//开启ADC
	rTSADCCON0 |= (1<<0);
}


void vic2_int23_init(void)
{
	//屏蔽中断23号,才可以对中断进行初始化
	rVIC2INTENCLEAR |= (0x1<<23);

	//将23号中断设置为IRQ模式
	rVIC2INTSELECT  &= ~(0x1<<23);

	//设置中断程序入口,以供VIC2ADDRESS提取
	rVIC2VECTADDR23 = (unsigned long)ADC_int;

	//初始化VIC2ADDRESS
	rVIC2ADDRESS = 0;

	//开启中断23号,初始化完毕
	rVIC2INTENABLE  |= (0x1<<23);
}


void interrupt_init(void)
{
	//ext16_int_init();
	//ext17_int_init();
	ext14_int_init();

	//vic0_int16_init();
	vic0_int14_init();
	//vic2_int23_init();

	
	//Timer4_Vic0_init();

	//Timer4_init();

	//Timer0_PWM_init();

	
	//watchdog_init();


	while(1);
}

