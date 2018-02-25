void delay_ms(unsigned int n)
{
	unsigned int i;
	for(n;n>0;n--)
		for(i=122;i>0;i--);
}


void delay_us(unsigned int us)
{
	unsigned int i;
	for (i=0;i<us;i++);
}
