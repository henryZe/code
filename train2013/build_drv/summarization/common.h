#ifndef __COMMON_H_
#define __COMMON_H_

#define WON_MAGIC 'K'

#define LED		_IO(WON_MAGIC,0)
#define BUZZER	_IO(WON_MAGIC,1)

struct data_t{
	int  flag;
};

#endif
