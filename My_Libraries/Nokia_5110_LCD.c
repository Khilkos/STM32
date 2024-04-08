#include "Nokia_5110_LCD.h"

uint8_t Nokia_5110_screen_buf[6][84];

#define Nokia_5110_Reset_1 GPIOB->BSRR |= 1<<(8)
#define Nokia_5110_Reset_0 GPIOB->BSRR |= 1<<(8+16)
#define Nokia_5110_CE_1 GPIOB->BSRR |= 1<<(9)
#define Nokia_5110_CE_0 GPIOB->BSRR |= 1<<(9+16)
#define Nokia_5110_Data GPIOA->BSRR |= 1<<(6)
#define Nokia_5110_Command GPIOA->BSRR |= 1<<(6+16)

//===========================================
void Nokia_5110_init (uint8_t V0_max_127)
{
Nokia_5110_CE_1;
delay_ms(50);
Nokia_5110_Reset_0;
delay_ms(150);
Nokia_5110_Reset_1;
Nokia_5110_send_command(0b00100001); //use extetdet instruction set
Nokia_5110_send_command(128+V0_max_127); //set v0
Nokia_5110_send_command(0b00000100); //set temperature 
Nokia_5110_send_command(0b00010011);//bias voltage
Nokia_5110_send_command(0x20);
Nokia_5110_send_command(0b00001100);	
Nokia_5110_clear_LCD();	
}
//===========================================

void Nokia_5110_send_command (uint8_t command)
{
	Nokia_5110_CE_0;
//	delay_us(100);
	Nokia_5110_Command;
	SPI1->DR=command;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
while ((SPI1->SR&SPI_SR_BSY)) {__NOP();}
//delay_us(1);
	Nokia_5110_CE_1;
//delay_us(1);
}
//============================================	

void Nokia_5110_send_data (uint8_t data)
{
	Nokia_5110_CE_0;
	Nokia_5110_Data;
	SPI1->DR=data;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
while ((SPI1->SR&SPI_SR_BSY)) {__NOP();}
//delay_us(1);
	Nokia_5110_CE_1;
//delay_us(1);

}
//============================================
void Nokia_5110_clear_LCD(void)
{
Nokia_5110_send_command(0b10000000);	
Nokia_5110_send_command(0b01000000);
for (uint16_t i=0; i<504;i++)	
Nokia_5110_send_data(0x00);	
}
//============================================
void Nokia_5110_LCD_Out (void)
{
for (uint8_t y=0; y<6;y++)
		{Nokia_5110_send_command(Nokia_Y+y);
			for (uint8_t x=0;x<84;x++)
				{Nokia_5110_send_command(Nokia_X+x);
				 Nokia_5110_send_data(Nokia_5110_screen_buf[y][x]);	
				}
		}
}
//============================================
void Nokia_5110_dot (uint8_t x, uint8_t y)
{
Nokia_5110_screen_buf[y/8][x] |=1<<(y%8);
}
//============================================
void Nokia_5110_no_dot (uint8_t x, uint8_t y)
{
Nokia_5110_screen_buf[y/8][x] &=~(1<<(y%8));
}
//============================================
void Nokia_5110_String (uint8_t x, uint8_t y, uint8_t *str)
{
uint8_t let=0;
uint8_t temp=0;
while (*str!='\0')
	{let=*str;
		for (uint8_t k=0; k<5; k++)
			{	temp=FontTable[let][k];
				for (uint8_t i=0; i<8;i++)
				{	if (temp&1<<0) Nokia_5110_dot(x+k,y+i); else Nokia_5110_no_dot (x+k,y+i);
					temp>>=1;
				}
			}
	x+=6;
	str++;
	}
}
//==========================================
void Nokia_5110_clr_screen_buf(void)
{
void *ptr=Nokia_5110_screen_buf;

	for (uint8_t i=0; i<126; i++)
			{*((uint32_t*)ptr+i)=0;}
}
//==========================================
void Nokia_5110_Vertical_line (uint8_t X_poz, uint8_t Y_poz, uint8_t Lenght)
{
for (uint8_t i=0; i<Lenght; i++)
	{	if ((Y_poz+i)<48 && X_poz<84 )	Nokia_5110_dot (X_poz, Y_poz+i); }
}
//==========================================
void Nokia_5110_Horizontal_line (uint8_t X_poz, uint8_t Y_poz, uint8_t Lenght)
{
for (uint8_t i=0; i<Lenght; i++)
	{	if ((X_poz+i)<84)	Nokia_5110_dot (X_poz+i, Y_poz); }
}
//==========================================


