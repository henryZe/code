#include "s5pv210.h"


void Led_RunDelay(volatile int count);	
int led_run(void)
{
        int i=0;
        rGPJ2CON = 0x1111;
        rGPJ2DAT = 0xf;
        while (1)
        {
                rGPJ2DAT = ~(0x1<<i);
                Led_RunDelay(0x9000000);
                i++;
                if(i==4)
                {
                        i=0;
                        rGPJ2DAT = 0xf;
                }
        }
        return 0;
}

void Led_RunDelay(volatile int count)
{
        while (count--);
}

