
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include "LCD.h"
volatile int c=0;
volatile char buffer[20];
ISR(INT0_vect)
{
 LCD_CMD(0xC0);
 c=c+1;
 itoa(c,buffer,10);
 displayWord(buffer);
}
ISR(INT1_vect)
{
	LCD_CMD(0x80);
	//_delay_us(1);
	displayWord("Timer Starts");
	//_delay_us(1);
	for(int i=c;i>=0;i--)
	{
		if(i>=10)
		{
		LCD_CMD(0xC0);
		}
		else
		{
			LCD_CMD(0xC0);
			displayWord("0");
		LCD_CMD(0xC1);	
		}
		itoa(i,buffer,10);
		displayWord(buffer);
		_delay_ms(1000);
	}
	c=0;
	PORTB|=_BV(PORTB3);
	_delay_ms(1000);
	PORTB&=~(_BV(PORTB3));
	_delay_ms(1000);
	LCD_CMD(0xC0);
	displayWord("                ");
	//_delay_us(1);
	LCD_CMD(0x80);
	//_delay_us(1);
	displayWord("                ");
	//_delay_us(1);
	LCD_CMD(0x80);
	//_delay_us(1);
	displayWord("Enter Time");
}
int main(void)
{
	/* Replace with your application code */
	DDRB|=_BV(DDB3)|_BV(DDB4);
	LCDinit();
	//_delay_us(3);
	displayWord("enter time");
	//_delay_us(5);
	LCD_CMD(0xC0);
	//_delay_us(1);
	EICRA|=_BV(ISC11)|_BV(ISC01);
	EICRA&=~((0x01<<2)|(0x01<<0));
	EIMSK|=_BV(INT1)|_BV(INT0);
	sei();
	while (1)
	{
		PORTB^=_BV(PORTB4);
		_delay_ms(200);
	}
}

