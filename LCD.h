#define LCD PORTD
#define rs PB0
#define rw PB1
#define en PB2
void LCD_CMD(char a)
{
	char upper=(0xf0 & a);// extracting upper nibble
	LCD=upper;
	PORTB&=~(0x01<<rs);
	PORTB&=~(0x01<<rw);
	PORTB|=(0x01<<en);
	_delay_ms(1);
	PORTB&=~(0x01<<en);
	char lower=((0x0f & a)<<4);
	LCD=lower;
	PORTB|=(0x01<<en);
	_delay_ms(1);
	PORTB&=~(0x01<<en);
}
void LCD_DATA(char d)
{
	char upper=(0xf0 & d);
	LCD=upper;
	PORTB|=(0x01<<rs);
	PORTB&=~(0x01<<rw);
	PORTB|=(0x01<<en);
	_delay_ms(1);
	PORTB&=~(0x01<<en);
	char lower=((0x0f & d) << 4);
	LCD=lower;
	PORTB|=(0x01<<en);
	_delay_ms(1);
	PORTB&=~(0x01<<en);
}
void displayWord(char *p)
{
	
	while(*p!='\0')
	{
		LCD_DATA(*p);
		p=p+1;
	}
}
void LCDinit()
{
	DDRB|=(0x01<<0)|(0x01<<1)|(0x01<<2);
	DDRD|=(0x01<<4)|(0x01<<5)|(0x01<<6)|(0x01<<7);
	LCD_CMD(0x02);
	LCD_CMD(0x28);
	LCD_CMD(0x0c);
	LCD_CMD(0x06);
	LCD_CMD(0x80);
	
}