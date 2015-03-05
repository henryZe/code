#ifndef __COMMON_H_
#define __COMMON_H_

#define WON_MAGIC 'K'

#define SWITCH _IO(WON_MAGIC,1)
#define CONFIG _IO(WON_MAGIC,2)
#define AUTO   _IO(WON_MAGIC,3)

struct data_t{
	int  flag;
	int  argum;
	char direct;
};

#endif
