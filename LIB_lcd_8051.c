#include <REGX52.H>
#include "LIB_lcd_8051.h"
#include "Port_lcd_4bit.h"

void delay_us(unsigned int t)  // Ham tre micro giay
{
	unsigned int i;
	for(i=0;i<t;i++);
}
void delay_ms(unsigned int t)	// Ham tre mini giay
{
	unsigned int i,j;
	for(i=0;i<t;i++)
		for(j=0;j<123;j++);
}
// Ham cho phep hien thi len LCD
void LCD_Enable(void)
{
	LCD_EN = 1;
	delay_us(3);
	LCD_EN = 0;
	delay_us(50); 
}
// Ham gui 4 bit
void LCD_Send4Bit(unsigned char Data)
{
	LCD_D4 = Data & 0x01;
	LCD_D5 = (Data>>1)&1;
	LCD_D6 = (Data>>2)&1;
	LCD_D7 = (Data>>3)&1;
}
// Ham gui 1 Byte du lieu
void LCD_Send1Byte(unsigned char byte)
{
	LCD_Send4Bit(byte >>4);/* Gui 4 bit cao */
	LCD_Enable();
	LCD_Send4Bit(byte); /* Gui 4 bit thap*/
	LCD_Enable();
}
// Ham xoa man hinh
void LCD_Clear()
{
	LCD_Send1Byte(0x01);
	delay_us(10);
}
// Ham khoi tao LCD
void LCD_Init()
{
	LCD_Send4Bit(0x00);
	delay_ms(20);
	LCD_RS = 0;
  LCD_Send4Bit(0x03);	 // function setting
	LCD_Enable();
	delay_ms(5);
	LCD_Enable();
	delay_ms(100);
	LCD_Enable();
	LCD_Send4Bit(0x02);	// dua con tro ve dau man hinh
	LCD_Enable();
	LCD_Send1Byte(0x28);	// Function Setting(001D NF**) D=0(4bit), N=1(2hang), F=0(5x8), **=00	
	LCD_Send1Byte(0x0C); // Bat hien thi, tat con tro
	LCD_Send1Byte(0x06);
	LCD_Clear();
	delay_ms(20);
}
// Ham di chuyen con tro: row=0-1; col=0-15 (2 hang + 16 cot)
void LCD_SetCursor(unsigned char row, unsigned char col)
{
	unsigned char address;   
	if (row == 0) address = (0x80 + col);	 // row=0 - hang 1
    else address = (0xC0 + col);			 // row=1 - hang 2
    delay_us(1000);
    LCD_Send1Byte(address);
    delay_us(50);
}
// Ham hien thi ra man hinh chuoi ki tu
void LCD_Print(char *s)
{
	while (*s)
	{
		LCD_RS=1;
		LCD_Send1Byte(*s);
		//delay_ms(800);
		LCD_RS=0;
		s++;
	}
}
void LCD_PutChar(char c)
{
	LCD_RS=1;
	LCD_Send1Byte(c);//c la ma trong bang lenh ki tu cua LCD HD44780
	LCD_RS=0;
}