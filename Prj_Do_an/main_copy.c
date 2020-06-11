#include<REGX52.H>
#include "LIB_lcd_8051.h"
#include <stdio.h>
#include "Port_lcd_4bit.h"
#include <math.h>
#define Trigger P3_1
#define Echo P3_2
unsigned char check = 0; // khai bao bien kiem tra
unsigned int temp;		 // bien trung gian
float t, D;  // khai bao bien thoi gian, khoang cach
char str[16];  // khai bao chuoi ki tu
void StartRange()
{
	Trigger=1;
    delay_us(20);        //  Tao 1 xung tren chan Trig toi thieu 10us
    Trigger=0;
	delay_us(1);
    Echo=1;       
    while(!(Echo));        // Doi cho den khi chan ECHO duoc keo len cao
    TR0=IT0=EX0=EA=1;	  // Cho phep ngat ngoai
}
// Ham khoi tao SRF05 - Thiet lap timer va ngat ngoai
void SRF05_Init(void)
{
	Trigger = 0;
	TMOD &= 0xF0;
	TMOD |= 0x01;   //timer 0 che do 1 (16bit)
	TR0 = 1;
	IT0 = 1;       //ngat ngoai 0 theo suon
	EX0 = 1;       //cho phep ngat ngoai 0
	EA = 1;        //cho phep ngat toan cuc
}
//Chuong trinh phuc vu ngat
void Interrupt0(void)interrupt 0
{
	temp = TH0;				  // Luu gia tri vao bien CTR_temp = TH0 TL0 (16 bit)
	temp <<= 8;				  // Gia tri dem duoc la so dao dong
	temp |= TL0;
	t = (float)temp*12/11.0592/pow(10,6); 	
	D = t*34320 /2;  // van toc song sieu am: v = 343.2m/s = 34320cm/s
	TR0 = IT0 = EX0 = 0;    // Ngung timer
	TL0 = TH0 = 0;          // Xoa du lieu trong thanh ghi Timer 0       
	check = 1;		// Kiem tra da nhan duoc gia tri
}
int main(){
	SRF05_Init(); // Goi ham khoi tao SRF05
	LCD_Init();	  // Goi ham khoi tao LCD1602	
	while(1)  // vong lap vo han
	{		
		StartRange();  // Goi ham bat dau phat tin hieu
		if(check)
		{			
	LCD_Init();
	LCD_SetCursor(0,0);
	LCD_Print("thinh.vc174239");
	sprintf(str,"K.cach= %.2fcm",D);
	LCD_SetCursor(1,0);
	LCD_Print(str);
	delay_ms(800);
	LCD_Clear();
}
}	}