void delay_1usec()
{
	volatile int count;
	count = 0x90000;
	while(count--);
}

void delay_1sec()
{
	int i;
	for(i=0; i<10; i++)
	{
		delay_1usec();
	}
}
