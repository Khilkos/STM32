#include "HUB_75_F411.h"

uint32_t HUB75_screen_buf[32][2];
static char String[300];





void HUB75_clear_screen_buf(void)
{
for (uint8_t y=0; y<32; y++)
	{
			for (uint8_t x=0; x<2; x++)
				{	HUB75_screen_buf[y][x]=0xffffffff;
				}
	}
}
//==================================

void HUB75_screen_buf_update(void)
{
	HUB75_clear_screen_buf();

	
sprintf(String,"Время");
	HUB75_LCD_string (0,0, (uint8_t*)String);										
sprintf(String,"Время");
	HUB75_LCD_string (8,0, (uint8_t*)String);		
	
sprintf(String,"27/12/2023");
	HUB75_LCD_string (16,0, (uint8_t*)String);		

sprintf((char*)String,"Здесь могла быть Ваша реклама        ");
HUB75_running_line((uint8_t*)&String,24);

//sprintf((char*)String,"Скорость ветра очень высока     ");
//HUB75_running_line((uint8_t*)&"Скорость ветра очень высока     ",16);


	
	}
//==================================
void HUB75_screen_buf_dot (uint16_t y, uint16_t x)
{
HUB75_screen_buf[y][x/32] |=(1<<x%32);
}
//==================================
void HUB75_screen_buf_no_dot (uint16_t y, uint16_t x)
{
HUB75_screen_buf[y][x/32] &=~(1<<x%32);
}
//=========================================================
//Вывод строки ASCII на экран 
//=========================================================
void HUB75_LCD_string (uint16_t y, uint16_t x, uint8_t *str)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (uint8_t k=0; k<5; k++)
		{	int temp=FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( uint8_t i=0; i<8; i++)
				{if (temp&(1<<7)) HUB75_screen_buf_no_dot(y+7-i,x+k); else HUB75_screen_buf_dot(y+7-i,x+k);
				temp=(temp<<1);}
		}
	x+=6;
	str++;
	}
}
//==================================
//==================================
void HUB75_Send (void)
{

	static uint8_t line_num;
					
										
GPIOA->BSRR=1<<4;
	if (line_num>15) line_num=0;
	if (line_num==0) HUB75_screen_buf_update();
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
																
	
			
			for (uint8_t x=0; x<2; x++) //вывод второй половины экрана
			{
					for (uint8_t i=0; i<32; i++)
						{
								if (HUB75_screen_buf[line_num+16][x]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
								//delay_ms(1);
								GPIOB->BSRR=1<<14;
								delay_us(1);
								GPIOB->BSRR=1<<(14+res);
								HUB75_screen_buf[line_num+16][x] >>=1;
						}
			}
	
			for (uint8_t x=0; x<2; x++) //вывод первой половины экрана
			{
					for (uint8_t i=0; i<32; i++)
						{
								if (HUB75_screen_buf[line_num][x]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
								//delay_ms(1);
								GPIOB->BSRR=1<<14;
								delay_us(1);
								GPIOB->BSRR=1<<(14+res);
								HUB75_screen_buf[line_num][x] >>=1;
						}
			}
		

GPIOB->BSRR=1<<15;
delay_us(1);
GPIOB->BSRR=1UL<<(15+res);
GPIOA->BSRR=1UL<<(4+res);
line_num++;
}
//==============================================================
void HUB75_running_line(uint8_t *str, uint8_t Y_pos)
{static uint32_t HUB75_temp_screen_buf[8][2];
	static uint8_t HUB75_temp_buffet_update;
	static uint8_t HUB75_temp_buffer[8];
	static uint8_t* HUB75_running_let;
	for (uint8_t y=0; y<8; y++)
	{	for (uint8_t x=0; x<(64-1); x++) //32=64
		{	if(HUB75_temp_screen_buf[y][(x+1)/32]&(0x1UL<<(x+1)%32)) HUB75_temp_screen_buf[y][x/32] |=(1<<x%32); else HUB75_temp_screen_buf[y][x/32] &=~(1<<x%32);	
			if (x==(64-2)) 
				{	if (y==0) 
								{	if (HUB75_temp_buffet_update==0)
										{	    if (HUB75_running_let==0) HUB75_running_let=str;
											for (uint8_t x1=0; x1<5; x1++)
											{	for (uint8_t y1=0; y1<8;y1++)
												{if ( ((FontTable[*HUB75_running_let][x1]))&(1<<y1) ) HUB75_temp_buffer[y1]|=(1<<(6-x1));}
											}
											if (*HUB75_running_let!='\0')	 HUB75_running_let++; else HUB75_running_let=0;
										}
									if (HUB75_temp_buffet_update<5) HUB75_temp_buffet_update++; else HUB75_temp_buffet_update=0;	
								}
					
					if (HUB75_temp_buffer[y]&(1<<7)) HUB75_temp_screen_buf[y][x/32] |=(1<<x%32); else HUB75_temp_screen_buf[y][x/32] &=~(1<<x%32); 
					HUB75_temp_buffer[y]*=2; //сдвиг влево
				}
		}		
	}
for (uint8_t i=0; i<8; i++)
{
HUB75_screen_buf[i+Y_pos][0]=~HUB75_temp_screen_buf[i][0];
HUB75_screen_buf[i+Y_pos][1]=~HUB75_temp_screen_buf[i][1];
}	
	
	
}

