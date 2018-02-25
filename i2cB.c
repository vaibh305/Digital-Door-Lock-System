                     /* i2cB.c */
#include<reg51.h>
#include "types.h"
#include "defines.h"
#include "delay.h"

void i2cStart(void)
{
  sda=1; 
  scl=1;
  sda=0;
}
void i2cWrite(u8 dat)
{
  u8 i;
  for(i=0;i<8;i++)
  {
	scl=0;
	sda=dat&(0x80>>i)?1:0;
	scl=1;
  }
}

void i2cAck(void)
{
  scl=0; 
  sda=1; 
  scl=1;
  //while(sda);
}
void i2cStop(void)
{
  scl=0; 
  sda=0; 
  scl=1;
  sda=1;
}

void i2cReStart(void)
{
  scl=0;
  sda=1; 
  scl=1;
  sda=0;
}
void i2cNoAck(void)
{
  scl=0; 
  sda=1; 
  scl=1;
}	

u8 i2cRead(void)
{
  u8 i;
  u8 buff=0;
  for(i=0;i<8;i++)
  {
	scl=0;
    scl=1;
    delay_us(1);
    if(sda)
      buff|=0x80>>i;
  }
  return buff;
}
void i2cDevWrite(u8 slaveAddr,u8 buffAddr,u8 dat)
{
	i2cStart();
	i2cWrite(slaveAddr &0xFE);
	i2cAck();
	i2cWrite(buffAddr);
	i2cAck();
	i2cWrite(dat);
	i2cAck();
    i2cStop();
	delay_ms(10);
}	
u8 i2cDevRead(u8 slaveAddr,u8 buffAddr)
{
	u8 buff;
    i2cStart();
	i2cWrite(slaveAddr & 0xFE);
	i2cAck();
	i2cWrite(buffAddr);
	i2cAck();
	i2cReStart();
	i2cWrite(slaveAddr|1);
	i2cAck();
	buff=i2cRead();
	i2cNoAck();
	i2cStop();
	return buff;
}