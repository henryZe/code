#ifndef __COMMON_H_
#define __COMMON_H_

#define WON_MAGIC 'K'

#define clockwise _IO(WON_MAGIC,1)
#define anti_clockwise _IO(WON_MAGIC,2)
#define speedup _IO(WON_MAGIC,3)
#define speeddown _IO(WON_MAGIC,4)
#define exit_app _IO(WON_MAGIC,5)

#endif
