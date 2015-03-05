#include "s5pv210.h"
#include "api.h"
#include "stdio.h"


void delay_T(void)
{
	volatile int i;
	for(i=0; i<5; i++);
}


void NAND_port_init(void)
{
	//NFCSn[0]片选NAND0
	rMP0_1CON |= (3<<8);
	//引脚复用选择
	rMP0_3CON = 0x22222222;
}


void NAND_reset(void)
{
	//唤醒NAND
	rNFCONT &= ~(1<<1);
	//清除RnB标志(low to high)
	rNFSTAT |= (1<<4);
	
	//command
	rNFCMMD = 0xff;
	//1 means detected
	while(!(rNFSTAT&(1<<4)));

	//关闭NAND
	rNFCONT |= (1<<1);
}


void NAND_init(void)
{
	//SLC NAND,2K per page,5 addr cycle,TACLS(准备期),TWRPH0(执行期),TWRPH1(恢复期)
	rNFCONF = (0<<3)|(0<<2)|(1<<1)|(0x8<<12)|(0x4<<8)|(0x4<<4);
	//enable controller,关闭片选NAND0
	rNFCONT = (0x1<<0)|(0x1<<1);

	NAND_reset();
}


void NAND_readID(void)
{
	int ID_1st,ID_2nd,ID_3rd,ID_4th,ID_5th;
	
	rNFCONT &= ~(1<<1);
	
	rNFCMMD = 0x90;
	delay_T();
	rNFADDR = 0x0;

	delay_T();
	ID_1st = rNFDATA & (0xff);
	delay_T();
	ID_2nd = rNFDATA & (0xff);
	delay_T();
	ID_3rd = rNFDATA & (0xff);
	delay_T();
	ID_4th = rNFDATA & (0xff);
	delay_T();
	ID_5th = rNFDATA & (0xff);

	//turn off
	rNFCONT |= (1<<1);

	printf("NAND ID = %x%x%x%x%x\n",ID_1st,ID_2nd,ID_3rd,ID_4th,ID_5th);
}


int  NAND_erase(unsigned int blocknum)
{
	unsigned int page_num = blocknum*64;

	rNFCONT &= ~(0x1<<1);
	rNFSTAT |= (0x1<<4);

	//command
	rNFCMMD = 0x60;

	//page addr 17bits,2048block*64page
	rNFADDR = page_num&(0xff);
	rNFADDR = (page_num>>8)&(0xff);
	rNFADDR = (page_num>>16)&(0xff);

	rNFCMMD = 0xd0;

	//RnB:low to high,1 ready
	while(!(rNFSTAT&(0x1<<4)));

	//判断成功与否
	rNFCMMD = 0x70;
	if(rNFDATA&(0x1))
	{
		rNFCONT |= (0x1<<1);
		printf("erase fail\n");
		return -1;
	}

	//成功
	rNFCONT |= (0x1<<1);
	printf("erase success\n");
	return 0;
}


int  NAND_write(unsigned char *buf,unsigned long nand_addr)
{
	unsigned long page_num = nand_addr / 2048;
	unsigned long offset = nand_addr % 2048;
	int  i;

	rNFCONT &= ~(0x1<<1);
	rNFSTAT |= (0x1<<4);

	rNFCMMD = 0x80;

	delay_T();
	//col低位
	rNFADDR = offset&(0xff);
	//col高位
	rNFADDR = (offset>>8)&(0xff);

	//row
	rNFADDR = page_num&(0xff);
	rNFADDR = (page_num>>8)&(0xff);
	rNFADDR = (page_num>>16)&(0xff);

	delay_T();

	for(i=offset; i<2048; i++)
	{
		rNFDATA = *buf;
		buf++;
	}

	rNFCMMD = 0x10;

	while(!(rNFSTAT&(0x1<<4)));

	rNFCMMD = 0x70;

	delay_T();

	if(rNFDATA&(0x1))
	{
		rNFCONT |= (0x1<<1);
		printf("write fail\n");
		return -1;
	}

	rNFCONT |= (0x1<<1);
	printf("write success\n");
	return 0;
}


void NAND_read(unsigned char *buf,unsigned long nand_addr)
{
	unsigned long page_num = nand_addr / 2048;
	unsigned long offset = nand_addr % 2048;
	int  i;

	rNFCONT &= ~(0x1<<1);
	rNFSTAT |= (1<<4);

	rNFCMMD = 0x0;

	//col低位
	rNFADDR = offset&(0xff);
	//col高位
	rNFADDR = (offset>>8)&(0xff);

	//row
	rNFADDR = page_num&(0xff);
	rNFADDR = (page_num>>8)&(0xff);
	rNFADDR = (page_num>>16)&(0xff);

	rNFCMMD = 0x30;

	while(!(rNFSTAT&(1<<4)));

	for(i=offset; i<2048; i++)
	{
		*buf = rNFDATA;
		buf++;
	}

	printf("read over\n");
}


void NAND_test(void)
{
	unsigned char write_buf[2048] = "good night!\n";
	unsigned char read_buf[2049];
	read_buf[2048] = '\0';

	NAND_port_init();
	NAND_init();

	NAND_readID();

	//blocknum*0x20000 <= addr < (blocknum+1)*0x20000
	if(NAND_erase(2047) == 0)
	{
		if(NAND_write(write_buf,0xffe0000) == 0)
		{
			NAND_read(read_buf,0xffe0000);
			printf("%s",read_buf);
		}
	}

	if(NAND_erase(2047) == 0)
	{
		NAND_read(read_buf,0xffe0000);
		printf("%s\n",read_buf);
	}
}


