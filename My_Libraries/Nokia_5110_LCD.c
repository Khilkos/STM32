#include "Nokia_5110_LCD.h"

#define Nokia_5110_Reset_1 GPIOB->BSRR |= 1<<(8)
#define Nokia_5110_Reset_0 GPIOB->BSRR |= 1<<(8+16)
#define Nokia_5110_CE_1 GPIOB->BSRR |= 1<<(9)
#define Nokia_5110_CE_0 GPIOB->BSRR |= 1<<(9+16)
#define Nokia_5110_Data GPIOA->BSRR |= 1<<(6)
#define Nokia_5110_Command GPIOA->BSRR |= 1<<(6+16)

//===========================================
void Nokia_5110_init (void)
{
Nokia_5110_CE_1;
delay_ms(30);
Nokia_5110_Reset_0;
delay_ms(120);
Nokia_5110_Reset_1;
Nokia_5110_send_command(0x21);
Nokia_5110_send_command(0xBA);
Nokia_5110_send_command(0x04);
Nokia_5110_send_command(0x14);
Nokia_5110_send_command(0x20);
Nokia_5110_send_command(0x0C);	
	
}
//===========================================

void Nokia_5110_send_command (uint8_t command)
{
	Nokia_5110_CE_0;
	Nokia_5110_Command;
	SPI1->DR=command;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
	Nokia_5110_CE_1;
}
//============================================	

void Nokia_5110_send_data (uint8_t data)
{
	Nokia_5110_CE_0;
	Nokia_5110_Data;
	SPI1->DR=data;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
	Nokia_5110_CE_1;
}
