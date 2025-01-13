#include "main.h"


int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
		
GPIO_DO_setup(GPIOE,0,High);
		
GPIO_Alternate(GPIOA,7,Push_pull,High,No_pull,AF5);// SPI MOSI_1
GPIO_Alternate(GPIOA,5,Push_pull,High,No_pull,AF5);// SPI CLK_1
GPIO_Alternate(GPIOA,4,Push_pull,High,Pull_up,AF5);// SPI NSS_1
 

SysTick_H7_Init(456);	
Core_STM32_H7_init(1,114,2,19,2);			
SPI1_init();		

//SPI1->CR1 |= (SPI_CR1_CSTART);			
		
		while (1)
	{
	
//GPIOB->BSRR=1<<(2);		
GPIOE->BSRR=1<<(0+16);	
//delay_us (50);		
GPIOE->BSRR=1<<(0);		
//delay_us (50);		
	//SPI1->DR=temp;
//SPI1->TXDR = 0b10101010;	
SPI1->TXDR =0x00000000;		
SPI1->TXDR =0xFfFfffff;
SPI1->TXDR =0x00000000;		
SPI1->TXDR =0xFfFfffff;		
SPI1->CR1 |= (SPI_CR1_CSTART);		
while (!(SPI1->SR&SPI_SR_EOT)) {__NOP();}
//delay_us(10);
		
	}
	
}
