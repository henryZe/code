#include "stdio.h"


#define rGPJ2CON *((volatile unsigned long *)0xe0200280)
#define rGPJ2DAT *((volatile unsigned long *)0xe0200284)
#define rGPH2CON *((volatile unsigned long *)0xe0200C40)
#define rGPH2DAT *((volatile unsigned long *)0xe0200C44)


void key2_init()
{
	//input
	rGPH2CON &= ~(0xf0);
}

void led2_init()
{
	//output
	rGPJ2CON &= ~(0xffff);
	rGPJ2CON |= 0x1111;

	rGPJ2DAT |= 0xf;
}


void delay2_c(void)
{
	int i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<1000;j++)
		{
		}
	}
}


void buzzer(void)
{
	printf(">>>> Welcome to C_Program <<<<\n");

	key2_init();
	led2_init();

	while(1)
	{
		if(!(rGPH2DAT & 0x2))
		{
			//防抖动功能
			delay2_c();
			if(!(rGPH2DAT & 0x2))
			{
				//松开按键才转换LED
				while(!(rGPH2DAT & 0x2));
				//异或操作
				rGPJ2DAT ^= 0x5;	
			}
		}
	}
}


