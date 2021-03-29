#include "s5pv210.h"
#include "stdio.h"


void set_clock_init_1000_667(void)
{	
	printf("clk_init_1000APLL_667MPLL\n");


	//APLL倍频时间设置
	rAPLL_LOCK = 0xffff;
	//rAPLL_CON0[31]=1;[25:16]=125;[13:8]=3;[2:0]=1;
	rAPLL_CON0 = ((1<<31)|(125<<16)|(3<<8)|(1<<0));
	
	//MPLL倍频时间设置
	rMPLL_LOCK = 0xffff;	
	//rMPLL_CON[31]=1;[25:16]=667;[13:8]=12;[2:0]=1;
	rMPLL_CON = ((1<<31)|(667<<16)|(12<<8)|(1<<0));

	//rCLK_SRC0[4]=1;[24]=0;
	//rCLK_SRC0[0]=1;[16]=0;
	rCLK_SRC0 = ((1<<0)|(1<<4));
	
	//rCLK_DIV0[2:0]=0;[10:8]=4;[14:12]=1;DRAM5倍分频(4+1)
	//rCLK_DIV0[27:24]=3;[30:28]=1;	
	rCLK_DIV0 = ((4<<4)|(4<<8)|(1<<12)|(3<<24)|(1<<28));


	printf("1000 done\n");
}

void set_clock_init_240_120(void)
{
	printf("clk_init_240APLL_120MPLL\n");

	
	//APLL倍频时间设置
	rAPLL_LOCK = 0xffff;
	//rAPLL_CON0[31]=1;[25:16]=30;[13:8]=3;[2:0]=1;
	rAPLL_CON0 = ((1<<31)|(30<<16)|(3<<8)|(1<<0));
	
	//MPLL倍频时间设置
	rMPLL_LOCK = 0xffff;	
	//rMPLL_CON[31]=1;[25:16]=120;[13:8]=12;[2:0]=1;
	rMPLL_CON = ((1<<31)|(120<<16)|(12<<8)|(1<<0));

	//rCLK_SRC0[4]=1;[24]=0;
	//rCLK_SRC0[0]=1;[16]=0;
	rCLK_SRC0 = ((1<<0)|(1<<4));
	
	//rCLK_DIV0[2:0]=0;[10:8]=4;[14:12]=1;DRAM5倍分频(4+1)
	//rCLK_DIV0[27:24]=3;[30:28]=1;	
	rCLK_DIV0 = ((4<<4)|(4<<8)|(1<<12)|(3<<24)|(1<<28));


	printf("240 done\n");
}
