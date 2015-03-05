
#ifndef __LCD_DRV__
#define __LCD_DRV__

#define GPF0CON			(0xE0200120)
#define GPF1CON			(0xE0200140)
#define GPF2CON			(0xE0200160)
#define GPF3CON			(0xE0200180)

#define GPD0CON			(0xE02000A0)
#define GPD0DAT			(0xE02000A4)

#define CLK_SRC1		(0xe0100204)
#define SRC_MASK		(0xe0100280)
#define CLK_DIV1		(0xe0100304)
#define CLK_GATE 		(0xe0100464)
#define CLK_GATE_BLOCK		(0xe0100480)


#define DCONTROL		(0xe0107008)
#define WINCHMAP2		(0xee00003c)



#define VIDCON0			(0xF8000000)
#define VIDCON1			(0xF8000004)
#define VIDCON2			(0xF8000008)

#define VIDTCON0 		(0xF8000010)
#define VIDTCON1 		(0xF8000014)
#define VIDTCON2		(0xF8000018)


#define WINCON0 		(0xF8000020)
#define WINCON2 		(0xF8000028)
#define SHADOWCON 		(0xF8000034)
#define VIDOSD0A 		(0xF8000040)
#define VIDOSD0B 		(0xF8000044)
#define VIDOSD0C 		(0xF8000048)

#define VIDW00ADD0B0 		(0xF80000A0)
#define VIDW00ADD1B0 		(0xF80000D0)
#define VIDW00ADD2  		(0xF8000100)


#define GPJ2CON			(0xe0200280)
#define GPJ2DAT			(0xe0200284)
#define GPJ2PUD			(0xe0200288)


#if 0
#define HSPW			(9+1)  
#define HBPD                    (37+1) 
#define HFPD                    (209+1)   
#define VSPW			(6+1)
#define VBPD                    (17+1)
#define VFPD                    (21+1)
#endif


#define HSPW                    (40)
#define HBPD                    (10-1)
#define HFPD                    (210-1)
#define VSPW                    (20)
#define VBPD                    (3-1)
#define VFPD                    (22-1)

#define FB_FREQ			(60)

// FB²ÎÊý
#define ROW			(480)
#define COL			(800)
#define HOZVAL			(COL-1)
#define LINEVAL			(ROW-1)


#define LeftTopX		0
#define LeftTopY		0
#define RightBotX		799
#define RightBotY		479



#endif
