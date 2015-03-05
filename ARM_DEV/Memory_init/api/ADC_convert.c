#include "s5pv210.h"
#include "api.h"
#include "stdio.h"


void ADC_block_init(void)
{
	int  data;

	//片选
	rADCMUX = ~(0xf<<0);
	//Enable分频,频率,12bits,普通模式
	rTSADCCON0 = (1<<14)|(65<<6)|(1<<16);
	rTSADCCON0 &= ~(1<<2);

	while(1)
	{
		//开启ADC
		rTSADCCON0 |= (1<<0);
		//等待开启
		while(rTSADCCON0 & (0x1));

		//等待转化完成,1表示处理完成
		while(!(rTSADCCON0 & (0x1<<15)));

		//精度为12bits
		data = (int)(rTSDATX0 & (0xfff));

		printf("register:data = %d\n",data);

		delay_1sec();
	}
}


void ADC_interrupt_init(void)
{	
	//片选
	rADCMUX = ~(0xf<<0);
	//Enable分频,频率,12bits,普通模式
	rTSADCCON0 = (1<<14)|(65<<6)|(1<<16);
	rTSADCCON0 &= ~(1<<2);

	//开启ADC
	rTSADCCON0 |= (1<<0);
}
