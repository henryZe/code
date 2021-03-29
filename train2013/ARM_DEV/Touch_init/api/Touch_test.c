#include "stdio.h"
#include "s5pv210.h"
#include "api.h"


void IIC_port2_init(void)
{
	//I2C2_SDA,I2C2_SCL
	rGPD1CON = (0x22<<16);
	//上拉电阻,1010
	rGPD1PUD = (0xa<<2);
}


void IIC_2_init(void)
{
	//acknowledge enable;16分频;enable interrupt;16分频
	rI2CCON2 = (0x1<<7)|(0x0<<6)|(0x1<<5)|(0x0<<4)|(0xf<<0);
}


void Touch_test(void)
{
	IIC_port2_init();
	IIC_2_init();
}



