#include "reg51.h"
#include "lcd.h"
#include "delay.h"
#include "keypad.h"
#include "i2c.h"


sbit LED_GREEN=P1^0 ;// DOOR UNLOCKED STATUS
sbit LED_RED=P1^1 ;//DOOR LOCKED STATUS


void main()
{
	
	char ch,psd[4], str[4];
	int i;
	//Storing DEFAULT password into EEPROM
	i2cDevWrite(0xA0,0,'1');
	i2cDevWrite(0xA0,1,'2');
	i2cDevWrite(0xA0,2,'3');
	i2cDevWrite(0xA0,3,'#');
	//Execution Starts From Here
	while(1)
	{
		LED_GREEN=0;//Initially Locking Door
		LED_RED=1;

	for(i=0;i<4;i++)//Getting passowrd from EEPROM ...used if Power Fails
	{
		psd[i]=i2cDevRead(0xA0,i);
	}

	LCD_Init();	
	LCD_cmd(0x80);
	LCD_str("Enter:");
	LCD_cmd(0xC0);
	LCD_str("1:Paswd 2:Change");
	ch=keyscan();
	if(ch=='1')//If want to open door
	{
	LCD_cmd(0x01);
	LCD_str("ENTER PASSWORD");
	LCD_cmd(0xC0);
	for(i=0;i<4;i++)//Displaying entered password by user
	{
		ch=keyscan();
		str[i]=ch;
		LCD_char(ch);
	}
	for(i=0;i<4;i++)//Checking for entered password
	{
		if(psd[i]!=str[i])break ;
	}
	delay_ms(500);
	LCD_cmd(0x01);
	if(i!=4)//INCORRECT PASSWORD
	{	
		LCD_str("Incorrect");
		LCD_cmd(0xC0);
		LCD_str("Password");
		delay_ms(2000);
	}
	if(i==4)//CORRECT PASSWORD
	{
		LCD_str("DOOR OPENING");
		LED_RED=0;
		LED_GREEN =1;
	
		delay_ms(3000);
		LCD_cmd(0x01);
		LCD_str("DOOR CLOSING");
		delay_ms(2500);
	}
}
	else //For changing password
	{
		LCD_cmd(0x01);
		LCD_str("Enter Current");
		LCD_cmd(0xC0);
		LCD_str("Password");
		delay_ms(1000);
		LCD_cmd(0x01);
		/*Getting Current Pasword*/
		for(i=0;i<4;i++)
		{
			ch=keyscan();
			str[i]=ch;
			LCD_char(ch);
		}
		/*Checking Entered Password is Correct or not*/
		for(i=0;i<4;i++)
		{
			if(psd[i]!=str[i])break ;
		}
		delay_ms(500);
		LCD_cmd(0x01);
		if(i!=4) //If INCORRECT
		{	
			LCD_str("Incorrect");
			LCD_cmd(0xC0);
			LCD_str("Password");
			delay_ms(2000);
		}
		if(i==4)//If CORRECT -->Proceed for Password Change
	{
		LCD_cmd(0x01);
		LCD_str("ENTER NEW");
		LCD_cmd(0xC0);
		LCD_str("Password");
		delay_ms(1000);
		LCD_cmd(0x01);
		for(i=0;i<4;i++)
		{
			ch=keyscan();
			LCD_char(ch);
			i2cDevWrite(0xA0,i,ch);
		}
		LCD_cmd(0x01);
		LCD_str("Password Changed");
		LCD_cmd(0xC0);
		LCD_str("**Successfully**");
		delay_ms(1500);
		
	}
		
	}//else end

}
}