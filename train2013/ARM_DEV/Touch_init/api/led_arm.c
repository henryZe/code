#include "stdio.h"


#define rGPJ2CON *((volatile unsigned long *)0xe0200280)
#define rGPJ2DAT *((volatile unsigned long *)0xe0200284)
#define rGPH2CON *((volatile unsigned long *)0xe0200C40)
#define rGPH2DAT *((volatile unsigned long *)0xe0200C44)


void key_init()
{
	//input
	rGPH2CON &= ~(0xf);
}

void led_init()
{
	//output
	rGPJ2CON &= ~(0xffff);
	rGPJ2CON |= 0x1111;

	rGPJ2DAT |= 0xf;
}


void delay_c(void)
{
	int i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
		}
	}
}


void led_arm(void)
{
	printf(">>>> Welcome to C_Program <<<<\n");

	key_init();
	led_init();

	while(1)
	{
		if(!(rGPH2DAT & 0x1))
		{
			//防抖动功能
			delay_c();
			if(!(rGPH2DAT & 0x1))
			{
				//松开按键才转换LED
				while(!(rGPH2DAT & 0x1));
				rGPJ2DAT = ~rGPJ2DAT;	
			}
		}
	}
}


