#ifndef __LIB_LCD_8051_H__
#define __LIB_LCD_8051_H__

void delay_us(unsigned int t);
void delay_ms(unsigned int t);
void LCD_Enable(void);
void LCD_Send4Bit(unsigned char Data);
void LCD_Send1Byte(unsigned char byte);
void LCD_Clear();
void LCD_Init();
void LCD_SetCursor(unsigned char row, unsigned char col);
void LCD_Print(char *s);
void LCD_PutChar(char c);

#endif