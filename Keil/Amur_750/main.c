#include "main.h"



int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
/*GPIOB->MODER &= ~(3U<<2*2);
GPIOB->MODER |= 1U<<2*2;		
GPIOA->MODER |= 1U<<2*1;		
GPIOE->MODER &= ~(3U<<2*0);
GPIOE->MODER |= 1U<<2*0;
	*/	
		
GPIO_DO_setup(GPIOE,0,High);
	
		
		while (1)
	{
	
//GPIOB->BSRR=1<<(2);		
GPIOE->BSRR=1<<(0+16);				
GPIOE->BSRR=1<<(0);		
		
		
	}
	
}
