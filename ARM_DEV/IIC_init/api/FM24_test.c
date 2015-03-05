#include "stdio.h"
#include "s5pv210.h"
#include "api.h"


void IIC_port_init(void)
{
	//I2C0_SDA,I2C0_SCL
	rGPD1CON = 0x22;
	//上拉电阻,1010
	rGPD1PUD = 0xa;
}


void IIC_init(void)
{
	//acknowledge enable;16分频;enable interrupt;clear interrupt pending;1分频(注意频率,读写顺利)
	rI2CCON0 = (0x1<<7)|(0x0<<6)|(0x1<<5)|(0x0<<4)|(0xf<<0);
}


void IIC_write_Byte(int slvaddr, int wordaddr, char data)
{
	rI2CDS0 = slvaddr;
	//START:master transmit mode:11; START; serial output enable RT
	rI2CSTAT0 = (0x3<<6)|(0x1<<5)|(0x1<<4);

	rI2CCON0 &= ~(0x1<<4);
	//1 means ACK
	while(!(rI2CCON0&(0x1<<4)));

	rI2CDS0 = wordaddr;
	//clean ACK pending,0
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));

	rI2CDS0 = data;
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));

	//PAUSE:master transmit,not busy,serial output enable
	rI2CSTAT0 = (0x3<<6)|(0x0<<5)|(0x1<<4);
}


unsigned char IIC_read_Byte(int slvaddr, int wordaddr)
{
	unsigned char ret = 0;
	
	
	//0xa0 先写命令
	rI2CDS0 = slvaddr&(0xfe);
	//START: Master transmit, busy, enable serial
	rI2CSTAT0 = (0x3<<6)|(0x1<<5)|(0x1<<4);
	//
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));
	

	rI2CDS0 = wordaddr;
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));


	rI2CDS0 = slvaddr;
	//rI2CADD0 = slvaddr;
	//START: Master receive, busy, enable serial
	rI2CSTAT0 = (0x2<<6)|(0x1<<5)|(0x1<<4);
	//ACK pend
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));


	//No acknowledge:disable
	rI2CCON0 &= ~(0x1<<7);
	
	//!!
	rI2CCON0 &= ~(0x1<<4);
	while(!(rI2CCON0&(0x1<<4)));
	
	ret = rI2CDS0;


	//PAUSE
	rI2CSTAT0 = (0x3<<6)|(0x0<<5)|(0x1<<4);
	//恢复ACK使能
	rI2CCON0 |= (0x1<<7);

	return ret;
}


void FM24_test(void)
{
	char write_buf[256] = {0};
	sprintf(write_buf,"Good morning,Henry!\n");
	
	char read_buf[256] = {0};
	char *point;
	int  i;


	IIC_port_init();
	IIC_init();

	point = write_buf;
	for(i=0; i<256; i++)
	{
		//a0:1 0 1 0 A2 A1 A0 !W
		IIC_write_Byte(0xa0, i, *point);
		point++;
	}


	for(i=0; i<256; i++)
	{
		//a1:1 0 1 0 A2 A1 A0 R
		read_buf[i] = IIC_read_Byte(0xa1, i);
	}

	printf("%s",read_buf);
}
