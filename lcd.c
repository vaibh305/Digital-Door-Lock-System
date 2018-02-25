#include<reg51.h>
#include"delay.h"
#include"lcd.h"
#define lcd_data P0
sbit rs=P2^0;
sbit rw=P2^1;
sbit en=P2^2;



void LCD_Init(void)
{
	delay_ms(20);
	LCD_cmd(0x30);
	delay_ms(8);
	LCD_cmd(0x30);
	delay_ms(2);
	LCD_cmd(0x30);
	delay_ms(2);
	LCD_cmd(0x38);
	LCD_cmd(0x10);
	LCD_cmd(0x01);
	LCD_cmd(0x06);
	LCD_cmd(0x0e);
}
void LCD_cmd(char cmd)
{
	lcd_data=cmd;
	rs=0;
	rw=0;
	en=1;
	delay_ms(2);
	en=0;
}
void LCD_char(char ch)
{
	lcd_data=ch;
	rw=0;
	rs=1;
	en=1;
	delay_ms(2);
	en=0;

}
void LCD_str(char *ptr)
{
	while(*ptr!='\0')
	{
		LCD_char(*ptr);
		ptr++;
	}	
}

