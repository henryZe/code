#include "s5pv210.h"
#include "api.h"
#include "stdio.h"


void draw_point(int x,int y,long color)
{
	unsigned long *frame_buf = (unsigned long *)0x42000000;

	*(frame_buf + y*800 + x) = color;
}


void clear_creen(unsigned long color)
{
	int  x,y;
	for(y=0; y<480; y++)
	{
		for(x=0; x<800; x++)
		{
			draw_point(x,y,color);
		}
	}
}


void draw_circle(int x,int y,int R,unsigned long color)
{
	int  xx,rr,xt,yt,rs;
	int  col,row;

	yt = R;
	rr = R*R;
	rs = R*71/100;

	for(xt = 0; xt <= rs; xt++)
	{
		xx = xt*xt;
		while((yt*yt) > (rr-xx))
		{
			yt--;
		}

		//第一象限
		col = x+xt;
		row = y-yt;
		draw_point(col, row, color);
		//第二象限
		col = x-xt;
		row = y-yt;
		draw_point(col, row, color);
		//第三象限
		col = x-xt;
		row = y+yt;
		draw_point(col, row, color);
		//第四象限
		col = x+xt;
		row = y+yt;
		draw_point(col, row, color);
		
		//45度镜像变换
		//第一象限
		col = x+yt;
		row = y-xt;
		draw_point(col, row, color);
		//第二象限
		col = x-yt;
		row = y-xt;
		draw_point(col, row, color);
		//第三象限
		col = x-yt;
		row = y+xt;
		draw_point(col, row, color);
		//第四象限
		col = x+yt;
		row = y+xt;
		draw_point(col, row, color);
	}
}


void LCD_init(void)
{
/*	
	//当前显存立即启动
	rVIDCON0 |= (1<<0);
	//立即启动
	rVIDCON0 |= (1<<1);
	//HCLK选用,166MHz
	rVIDCON0 &= ~(1<<2);
	//分频功能
	rVIDCON0 |= (1<<4);
	//分频4+1
	rVIDCON0 |= (4<<6);
	//并行RGB
	rVIDCON0 &= ~(1<<18);
	//RGB interface
	rVIDCON0 &= ~(7<<26);
*/
	rVIDCON0 = (1<<0)|(1<<1)|(0<<2)|(1<<4)|(4<<6)|(0<<18)|(0<<26);

	//HSYNC invert
	rVIDCON1 |= (1<<5);
	//VSYNC invert
	rVIDCON1 |= (1<<6);


	//控制时序
	//帧 VSPW VFPD VBPD
	rVIDTCON0 = (19<<0)|(21<<8)|(2<<16);
	//行 HSPW HFPD HBPD
	rVIDTCON1 = (39<<0)|(209<<8)|(5<<16);
	//像素 Lineval Hozval
	rVIDTCON2 = (479<<11)|(799<<0);


	//window 0 基址8bits+偏移量24bits
	rVIDW00ADD0B0 = 0x42000000;
	//结束地址
	rVIDW00ADD1B0 = 0x42000000+800*480*4;
	//虚拟屏幕
	rVIDW00ADD2 = ((800*4)<<0);


	//position
	//左上角 X Y
	rVIDOSD0A = (0<<11)|(0<<0);
	//右下角 X Y
	rVIDOSD0B = (799<<11)|(479<<0);
	//window0 position control
	rVIDOSD0C = 800*480;


	//enable WINDOW0,R8-G8-B8,word对齐
	rWINCON0 = (1<<0)|(0xB<<2)|(1<<15);
	//enable channel 0
	rSHADOWCON |= (1<<0);


	//select path RGB=FIMD
	rDISPLAY_CONTROL = (1<<1);
}


void LCD_port_init(void)
{
	//将复用引脚设置为LCD_VD模式
	rGPF0CON = 0x22222222;
	rGPF1CON = 0x22222222;
	rGPF2CON = 0x22222222;
	rGPF3CON = 0x2222;
}


void LCD_test(void)
{	
	LCD_port_init();
	LCD_init();

	clear_creen(0xffffff);
/*
	draw_point(10,10,0xff0000);
	draw_point(11,10,0xff0000);
	draw_point(9,10,0xff0000);
	draw_point(10,11,0xff0000);
	draw_point(10,9,0xff0000);


	draw_circle(400,240,20,0xff0000);
	draw_circle(400,240,40,0x00ff00);
	draw_circle(400,240,80,0x0000ff);
*/
}
