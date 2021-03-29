#ifndef __COMMON_H_
#define __COMMON_H_

#define WON_MAGIC 'K'

#define LED_0 _IO(WON_MAGIC,0)
#define LED_1 _IO(WON_MAGIC,1)
#define LED_2 _IO(WON_MAGIC,2)
#define LED_3 _IO(WON_MAGIC,3)

struct data_t{
	int  flag;
	char name[40];
};

#endif
