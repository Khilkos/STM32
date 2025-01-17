#include "main.h"
static uint16_t led_temp=0;
static uint16_t SPI2_temp=0;

int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;		
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
		
GPIO_DO_setup(GPIOE,0,High);
		
GPIO_Alternate(GPIOA,7,Push_pull,High,Pull_down,AF5);// SPI1 MOSI
GPIO_Alternate(GPIOA,5,Push_pull,High,Pull_down,AF5);// SPI1 CLK
GPIO_Alternate(GPIOA,4,Push_pull,High,Pull_up,AF5);// SPI1 NSS
 
GPIO_Alternate(GPIOC,2,Push_pull,High,Pull_down,AF5);// SPI2 MISO
GPIO_Alternate(GPIOB,10,Push_pull,High,Pull_down,AF5);// SPI2 CLK
GPIO_Alternate(GPIOB,12,Push_pull,High,Pull_up,AF5);// SPI2 NSS
		
SysTick_H7_Init(456);	
Core_STM32_H7_init(1,114,2,19,2);			
SPI1_H7_init();	
SPI2_H7_init();			
		
		
		while (1)
	{
	
led_temp++;
if (led_temp==0xfff)
	{	
		led_temp=0;
		if (GPIOE->IDR & 1<<0)	GPIOE->BSRR=1<<(0+16); else GPIOE->BSRR=1<<(0);
	}	
		
SPI1->CR1 |= SPI_CR1_SPE; //enable SPI			
SPI2->CR1 |= SPI_CR1_SPE; //enable SPI
	
SPI1->TXDR =0xffffffff;		
SPI1->TXDR =0x00000000;
SPI1->TXDR =0xffffffff;		
SPI1->TXDR =0x00000ff0;	

SPI2->TXDR =0xffffffff;		
SPI2->TXDR =0x00000000;
SPI2->TXDR =0xffffffff;		
SPI2->TXDR =0x00000ff0;		
	
	

//SPI2->CR1 |= (SPI_CR1_SSI);
	
SPI2_temp++;
if (SPI2_temp==3)
	{	
		SPI2_temp=0;
		SPI2->CR1 |= (SPI_CR1_SSI);
	}	
	
SPI1->CR1 |= (SPI_CR1_CSTART);		
while (!(SPI1->SR&SPI_SR_EOT)) {__NOP();}
SPI1->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );

SPI2->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );
SPI2->CR1 &= ~(SPI_CR1_SSI);

SPI1->CR1 &= ~SPI_CR1_SPE; //desable SPI	
//----------------

			



	
//while (!(SPI2->SR&SPI_SR_EOT)) {__NOP();}
//SPI2->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );

SPI2->CR1 &= ~SPI_CR1_SPE; //desable SPI



	}
	
}
