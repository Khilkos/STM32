#include "HUB_08_F411.h"

uint32_t screen_buf[16][2];
static char String[100];

void clear_screen_buf(void)
{
for (uint8_t y=0; y<16; y++)
	{
			for (uint8_t x=0; x<2; x++)
				{	screen_buf[y][x]=0;
				}
	}
}
//==================================

void screen_buf_update(void)
{
	clear_screen_buf();

sprintf(String,"����������.");
	LCD_string (0,0, (uint8_t*)String);										

sprintf(String,"��������.");
	LCD_string (8,0, (uint8_t*)String);														
}
//==================================
void HUB08_screen_buf_dot (uint16_t y, uint16_t x)
{
screen_buf[y][x/32] |=(1<<x%32);
}
//==================================
void HUB08_screen_buf_no_dot (uint16_t y, uint16_t x)
{
screen_buf[y][x/32] &=~(1<<x%32);
}
//=========================================================
//����� ������ ASCII �� ����� 
//=========================================================
void LCD_string (uint16_t y, uint16_t x, uint8_t *str)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (uint8_t k=0; k<5; k++)
		{	int temp=FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( uint8_t i=0; i<8; i++)
				{if (temp&(1<<7)) HUB08_screen_buf_dot(y+7-i,x+k); else HUB08_screen_buf_no_dot(y+7-i,x+k);
				temp=(temp<<1);}
		}
	x+=6;
	str++;
	}
}
//==================================
//==================================
void HUB_08_Send (void)
{

	static uint8_t line_num;
					
										
GPIOA->BSRR=1<<4;
	if (line_num>15) line_num=0;
	if (line_num==0) screen_buf_update();
	if (line_num==0) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==1) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==2) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==3) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==4) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==5) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==6) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==7) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==8) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==9) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==10) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==11) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==12) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==13) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==14) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==15) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
																
	
	
			for (uint8_t x=0; x<2; x++)
			{
					for (uint8_t i=0; i<32; i++)
						{
								if (screen_buf[line_num][x]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
								//delay_ms(1);
								GPIOB->BSRR=1<<14;
								delay_us(1);
								GPIOB->BSRR=1<<(14+res);
								screen_buf[line_num][x] >>=1;
						}
						
						}
		

GPIOB->BSRR=1<<15;
delay_us(1);
GPIOB->BSRR=1UL<<(15+res);
GPIOA->BSRR=1UL<<(4+res);
line_num++;
}


