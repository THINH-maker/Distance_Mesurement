#include<REGX52.H>
#include "LIB_lcd_8051.h"
#include <stdio.h>
#include "Port_lcd_4bit.h"
#include <math.h>
#define Trigger P3_1
#define Echo P3_2
unsigned char check = 0; 
unsigned int temp;		 
float t, D;  
char str[16]; 
void StartRange()
{
	Trigger=1;
    delay_us(20);       
    Trigger=0;
	delay_us(1);
    Echo=1;       
    while(!(Echo));        
    TR0=IT0=EX0=EA=1;	  
}

void SRF05_Init(void)
{
	Trigger = 0;
	TMOD &= 0xF0;
	TMOD |= 0x01;   
	TR0 = 1;
	IT0 = 1;       
	EX0 = 1;      
	EA = 1;        
}

void Interrupt0(void)interrupt 0
{
	temp = TH0;				 
	temp <<= 8;				  
	temp |= TL0;
	t = (float)temp*12/11.0592/pow(10,6); 	
	D = t*34320 /2;  
	TR0 = IT0 = EX0 = 0;    
	TL0 = TH0 = 0;               
	check = 1;	
}
int main(){
	SRF05_Init(); 
	LCD_Init();	  
	while(1)  
	{		
		StartRange();  
		if(check)
		{			
	//LCD_Init();
	LCD_SetCursor(0,0);
	LCD_Print("thinh.vc174239");
	sprintf(str,"K.cach= %.2fcm",D);
	LCD_SetCursor(1,0);
	LCD_Print(str);
	/*if(D>70)
	{
		P3_4=0;
	}
	else
		{
			P3_4=1;
		}
		*/
	P3_4=1;
	delay_ms(800);
	LCD_Clear();
}
}	
}