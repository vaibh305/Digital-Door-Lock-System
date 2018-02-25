#include "keypad.h"
#include "reg51.h"
#include "lcd.h"
#include "delay.h"
sbit c0=P3^0 ;
sbit c1=P3^1 ;
sbit c2=P3^2 ;
sbit r0=P3^3 ;
sbit r1=P3^4 ;
sbit r2=P3^5 ;
sbit r3=P3^6 ;

char ch,row,col;
void init_keypad()
{
	c0=c1=c2=1;
	r0=r1=r2=r3=0;
}
char a[4][3]={'1','2','3','4','5','6','7','8','9','*','0','#'};
char colstatus(void)
{
	return (c0&&c1&&c2);
}
char keyscan(void)
{
	init_keypad();
	while(colstatus()); //Waiting for Key_Press
	//Here key is Pressed ...At this moment we have to check the status
	
	r0=0; r1=r2=r3=1;
	if(!colstatus())
	{
		row=0;
		goto colcheck;
	}
	
	r1=0; r0=r2=r3=1;
	if(!colstatus())
	{
		row=1;
		goto colcheck;
	}
	
	r2=0; r1=r0=r3=1;
	if(!colstatus())
	{
		row=2;
		goto colcheck;
	}
	
	r3=0; r1=r2=r0=1;
	if(!colstatus())
	{
		row=3;
	//	goto colcheck;
	}
	colcheck: 
	if(c0==0) col=0;
	else if(c1==0) col=1;
	else col=2;
	while(!(colstatus()));//Waiting for key release

	return (a[row][col]);	
}