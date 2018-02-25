#include "reg51.h"
#include "lcd.h"
#include "delay.h"
#include "i2c.h"

void main()
{
	int i;
	char psd[4];
	LCD_Init();
	/*
	Commented code is used only while during SIMULATION on PROTEUS
	don't use while building project

	i2cDevWrite(0xA0,0,'1');
	i2cDevWrite(0xA0,1,'2');
	i2cDevWrite(0xA0,2,'3');
	i2cDevWrite(0xA0,3,'#');
		*/
	
	LCD_str("PASSWRD RECOVERY");
	LCD_cmd(0xC0);
	LCD_str("MODE");
	delay_ms(1000);
	LCD_cmd(0x01);
	LCD_str("PASSWORD IS:-->");
	LCD_cmd(0xC0);
	for(i=0;i<4;i++)//Fetching Password from EEPROM
		{
			psd[i]=i2cDevRead(0xA0,i);
		}

		for(i=0;i<4;i++)// Showing it on LCD
			LCD_char(psd[i]);
		delay_ms(1500);
		LCD_cmd(0x01);
		LCD_str("PLEASE CHANGE");
		LCD_cmd(0xC0);
		LCD_str("PASSWORD");
		while(1);

}