#include "main.h"


int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
		
GPIO_DO_setup(GPIOE,0,High);

SysTick_H7_Init(456);	
Core_STM32_H7_init(1,114,2,19,2);		
		
		while (1)
	{
	
//GPIOB->BSRR=1<<(2);		
GPIOE->BSRR=1<<(0+16);	
delay_us (50);		
GPIOE->BSRR=1<<(0);		
delay_us (50);		
		
	}
	
}
