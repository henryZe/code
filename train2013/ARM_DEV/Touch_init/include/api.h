#ifndef _API_H_
#define _API_H_


void set_clock_init_240_120(void);
void set_clock_init_1000_667(void);


void ADC_block_init(void);
void ADC_interrupt_init(void);


void delay_1sec(void);
void delay_1usec(void);
void led_arm(void);
void buzzer(void);
void led_run(void);
void interrupt_init(void);


void LCD_test(void);
void NAND_test(void);
void FM24_test(void);
void Touch_test(void);


#endif
