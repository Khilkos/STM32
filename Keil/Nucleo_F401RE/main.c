#include "main.h"





int main(void)
{
Core_F401_init_HSI(16,336,4,7);
SysTick_F4_Init (84);	
	
RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN ;

GPIO_DO_setup(GPIOA,5,High);
	
	while (1)
	{
	
		GPIOA->BSRR = 1<<(5);
		delay_ms(500);
		GPIOA->BSRR = 1<<(5+16);
		delay_ms(500);
	
	
		
	
	
	
	
	}
	
}
