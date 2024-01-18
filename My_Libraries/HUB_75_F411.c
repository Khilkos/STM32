#include "HUB_75_F411.h"

uint32_t HUB75_RED_screen_buf[32][2];
uint32_t HUB75_GREEN_screen_buf[32][2];
uint32_t HUB75_BLUE_screen_buf[32][2];

static char String[300];





void HUB75_clear_screen_buf(void)
{
for (uint8_t y=0; y<32; y++)
	{
			for (uint8_t x=0; x<2; x++)
				{
					HUB75_RED_screen_buf[y][x]=0xffffffff;
					HUB75_GREEN_screen_buf[y][x]=0xffffffff;
					HUB75_BLUE_screen_buf[y][x]=0xffffffff;
				}
	}
}
//==================================

void HUB75_screen_buf_update(void)
{
	static _Bool screen_num;

	HUB75_clear_screen_buf();

	sprintf(String,"%02d",hour);
		HUB75_LCD_string_font_10x16 (1,2, (uint8_t*)String, 1,1,1);
	
	sprintf(String,":");
	HUB75_LCD_string (5,23, (uint8_t*)String,0,1,1);	
	
sprintf(String,"%02d",minutes);
	HUB75_LCD_string_font_10x16 (1,27, (uint8_t*)String,1,0,1);

	sprintf(String,":");
	HUB75_LCD_string (8,48, (uint8_t*)String,0,1,1);	
	
	sprintf(String,"%02d",seconds);
	HUB75_LCD_string (8,52, (uint8_t*)String,0,1,0);	
	
	if (!HUB75_screen_delay)
	{
		screen_num=!screen_num;
		HUB75_screen_delay=2500;
	}
	
	if (screen_num || clock_poz) 	sprintf(String,"%02d/%02d/%02d",day,month,year+2000);
		else sprintf(String,"Темп.%.1fC", (DS18B20_read_temperatur_via_DMA_timer()*0.1));
		
	HUB75_LCD_string (16,3, (uint8_t*)String,1,1,0);			
if (!HUB75_line_run_delay) 
	{ 
		HUB75_line_run_delay=13;
sprintf((char*)String,"Акционерное общество \"Пивобезалкогольный комбинат \"Крым\" / Энерго-Механическая служба        ");
HUB75_running_line((uint8_t*)&String,24);
	}

if (clock_poz==1) HUB75_h_line (15,4,17,0,0,1);
if (clock_poz==2) HUB75_h_line (15,29,17,0,0,1);
if (clock_poz==3) HUB75_h_line (15,52,11,0,0,1);
if (clock_poz==4) HUB75_h_line (23,3,11,0,0,1);
if (clock_poz==5)	HUB75_h_line (23,21,11,0,0,1);
if (clock_poz==6) HUB75_h_line (23,39,23,0,0,1);



//sprintf((char*)String,"Скорость ветра очень высока     ");
//HUB75_running_line((uint8_t*)&"Скорость ветра очень высока     ",16);


	
	}
//==================================
void HUB75_screen_buf_dot (uint16_t y, uint16_t x, _Bool R, _Bool G, _Bool B)
{
if (R) HUB75_RED_screen_buf[y][x/32] &=~(1<<x%32);
if (G) HUB75_GREEN_screen_buf[y][x/32] &=~(1<<x%32);
if (B) HUB75_BLUE_screen_buf[y][x/32] &=~(1<<x%32);
}
//==================================
void HUB75_screen_buf_no_dot (uint16_t y, uint16_t x, _Bool R, _Bool G, _Bool B)
{
if (R) HUB75_RED_screen_buf[y][x/32] |=(1<<x%32);
if (G) HUB75_GREEN_screen_buf[y][x/32] |=(1<<x%32);
if (B) HUB75_BLUE_screen_buf[y][x/32] |=(1<<x%32);
	

}
//=========================================================
//Вывод строки ASCII на экран 
//=========================================================
void HUB75_LCD_string (uint16_t y, uint16_t x, uint8_t *str, _Bool R, _Bool G, _Bool B)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (uint8_t k=0; k<5; k++)
		{	int temp=FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( uint8_t i=0; i<8; i++)
				{if (temp&(1<<7)) HUB75_screen_buf_dot(y+7-i,x+k, R, G, B); else HUB75_screen_buf_no_dot(y+7-i,x+k, R, G, B);
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
					
HUB75_RED_screen_buf[0][0]=0x1;
HUB75_GREEN_screen_buf[0][0]=HUB75_RED_screen_buf[0][0];
HUB75_BLUE_screen_buf[0][0]=HUB75_RED_screen_buf[0][0];
	
GPIOA->BSRR=1<<10;
	if (line_num>15) line_num=0;
	if (line_num==0) HUB75_screen_buf_update();
	if (line_num==0) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11+res);}
			else if (line_num==1) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11+res);}
			else if(line_num==2) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11+res);}
			else if(line_num==3) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11+res);}
			else if(line_num==4) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11+res);}
			else if (line_num==5) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11+res);}
			else if (line_num==6) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11+res);}
			else if (line_num==7) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11+res);}
			else if (line_num==8) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11);}
			else if (line_num==9) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11);}
			else if (line_num==10) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11);}
			else if (line_num==11) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12+res);GPIOA->BSRR=1<<(11);}
			else if (line_num==12) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11);}
			else if (line_num==13) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15+res);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11);}
			else if (line_num==14) {GPIOB->BSRR=1<<(3+res); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11);}
			else if (line_num==15) {GPIOB->BSRR=1<<(3); GPIOA->BSRR=1U<<(15);GPIOA->BSRR=1<<(12);GPIOA->BSRR=1<<(11);}
																
	
			
			for (uint8_t x=0; x<2; x++) //вывод второй половины экрана
			{
					for (uint8_t i=0; i<32; i++)
						{
								if (HUB75_RED_screen_buf[line_num+16][x]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
								if (HUB75_GREEN_screen_buf[line_num+16][x]&0x01) GPIOB->BSRR=1<<(14+res); else GPIOB->BSRR=1<<(14);
								if (HUB75_BLUE_screen_buf[line_num+16][x]&0x01) GPIOB->BSRR=1UL<<(15+res); else GPIOB->BSRR=1<<(15);
							
								//delay_ms(1);
								GPIOA->BSRR=1<<9;
								delay_us(1);
								GPIOA->BSRR=1<<(9+res);
								HUB75_RED_screen_buf[line_num+16][x] >>=1;
								HUB75_GREEN_screen_buf[line_num+16][x] >>=1;
								HUB75_BLUE_screen_buf[line_num+16][x] >>=1;
						}
			}
	
			for (uint8_t x=0; x<2; x++) //вывод первой половины экрана
			{
					for (uint8_t i=0; i<32; i++)
						{
								if (HUB75_RED_screen_buf[line_num][x]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
								if (HUB75_GREEN_screen_buf[line_num][x]&0x01) GPIOB->BSRR=1<<(14+res); else GPIOB->BSRR=1<<(14);
								if (HUB75_BLUE_screen_buf[line_num][x]&0x01) GPIOB->BSRR=1UL<<(15+res); else GPIOB->BSRR=1<<(15);
								//delay_us(1);
								GPIOA->BSRR=1<<9;
								delay_us(1);
								GPIOA->BSRR=1<<(9+res);
								HUB75_RED_screen_buf[line_num][x] >>=1;
								HUB75_GREEN_screen_buf[line_num][x] >>=1;
								HUB75_BLUE_screen_buf[line_num][x] >>=1;
						}
			}
		

GPIOA->BSRR=1<<8;
delay_us(1);
GPIOA->BSRR=1UL<<(8+res);
GPIOA->BSRR=1UL<<(10+res);
line_num++;
}
//==============================================================
void HUB75_running_line(uint8_t *str, uint8_t Y_pos)
{static uint32_t HUB75_temp_screen_buf[8][2];
	static uint8_t HUB75_temp_buffet_update;
	static uint8_t HUB75_temp_buffer[8];
	static uint8_t* HUB75_running_let;
	for (uint8_t y=0; y<8; y++)
	{	for (uint8_t x=0; x<(64); x++) //32=64
		{	if(HUB75_temp_screen_buf[y][(x+1)/32]&(0x1UL<<(x+1)%32)) HUB75_temp_screen_buf[y][x/32] |=(1<<x%32); else HUB75_temp_screen_buf[y][x/32] &=~(1<<x%32);	
			if (x==(64-1)) 
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
HUB75_RED_screen_buf[i+Y_pos][0]=~HUB75_temp_screen_buf[i][0];
HUB75_RED_screen_buf[i+Y_pos][1]=~HUB75_temp_screen_buf[i][1];
}	
}
//=========================================================
//Вывод строки ASCII на экран 
//=========================================================
void HUB75_LCD_string_font_10x16 (uint16_t y, uint16_t x, uint8_t *str,  _Bool R, _Bool G, _Bool B)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (uint8_t k=0; k<10; k++)
		{	int temp= font_10x16[let*10+k];//FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( uint8_t i=0; i<16; i++)
				{if (temp&(1<<15)) HUB75_screen_buf_dot(y+15-i,x+k, R, G, B); else HUB75_screen_buf_no_dot(y+15-i,x+k, R, G, B);
				temp=(temp<<1);}
		}
	x+=11;
	str++;
	}
}
//==================================
void HUB75_h_line (uint16_t y, uint16_t x, uint16_t lenght, _Bool R, _Bool G, _Bool B)
{
for (uint16_t i=0; i<lenght; i++)
	{
		HUB75_screen_buf_dot (y,x+i,R,G,B);
	}

}
