#include<LPC21XX.h>
//#include "delay_header.C"
#define LCD_D 0xf<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

void delay_millisecond(int msecond)
{
	T0PR = 15000-1;
	T0TCR = 0X01;
  while(T0TC<msecond);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void LCD_CMD(unsigned char cmd)
{
	IOPIN1=(cmd&0xf0)<<16;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_millisecond(2);
	IOCLR1=E;
	
	IOPIN1=(cmd&0x0f)<<20;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_millisecond(2);
	IOCLR1=E;
}
void LCD_INIT(void)
{
	IODIR1|=LCD_D|RS|E|RW;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X28);
	LCD_CMD(0X80);
}
void LCD_DATA(unsigned char D)
{
	IOPIN1=(D&0xf0)<<16;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_millisecond(2);
	IOCLR1=E;
	
	IOPIN1=(D&0x0f)<<20;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_millisecond(2);
	IOCLR1=E;
}
void LCD_STR(unsigned char *s)
{
	while(*s)
	{
	LCD_DATA(*s++);
	
	}
}
void LCD_INTEGER(int n)
{
	unsigned char a[5];
	signed char i=0;
	if(n==0)
	{
		LCD_DATA('0');
	}
	else
		if(n<0)
		{
			LCD_DATA('-');
			n=-n;
		}
		while(n>0)
		{
			a[i++]=n%10;
			n=n/10;
		}
		for(--i;i>=0;i--)
		{
			LCD_DATA(a[i]+48);
		}
		
}

