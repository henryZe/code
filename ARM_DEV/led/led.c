
#define rGPJ2CON (*(volatile unsigned long *)0xe0200280)
#define rGPJ2DAT (*(volatile unsigned long *)0xe0200284)

void Led_RunDelay(volatile int count);	
int xmain(void)
{
        int i=0;
        rGPJ2CON = 0x1111;
        rGPJ2DAT = 0xf;
        while (1)
        {
                rGPJ2DAT = ~(0x1<<i);
                Led_RunDelay(0x90000);
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

