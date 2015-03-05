#ifndef __COMMON_H_
#define __COMMON_H_

#define WON_MAGIC 'K'

#define TURN_OFF  _IO(WON_MAGIC,0)
#define TURN_ON   _IO(WON_MAGIC,1)


struct data_t{
	char  direct;
};

#endif
