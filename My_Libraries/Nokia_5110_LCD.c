#include "Nokia_5110_LCD.h"

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


