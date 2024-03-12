#include "main.h"

#define led_delay 50



int main(void)
{
Core_F401_init_HSI(16,336,4,7);
SysTick_F4_Init (84);	
	
RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN ;

GPIO_DO_setup(GPIOA,5,High);
GPIO_DO_setup(GPIOC,10,High);
GPIO_DO_setup(GPIOC,11,High);
GPIO_DO_setup(GPIOC,12,High);
GPIO_DO_setup(GPIOC,2,High);
GPIO_DO_setup(GPIOC,3,High);

	GPIO_DI_setup(GPIOA,10,No_pull);// A
	GPIO_DI_setup(GPIOB,3,No_pull);// B
	GPIO_DI_setup(GPIOB,5,No_pull);// C
	GPIO_DI_setup(GPIOB,4,No_pull);// D
	GPIO_DI_setup(GPIOB,10,No_pull);// E
	GPIO_DI_setup(GPIOA,8,No_pull);// F
	GPIO_DI_setup(GPIOA,9,No_pull);// Key




	
	while (1)
	{
	
		GPIOA->BSRR = 1<<(5);
		GPIOC->BSRR = 1<<(10);
			delay_ms(led_delay);
		GPIOA->BSRR = 1<<(5+16);
		GPIOC->BSRR = 1<<(10+16);
				delay_ms(led_delay);
	
	if (!(GPIOA->IDR & 1<<10)) GPIOC->BSRR |=1<<11; else GPIOC->BSRR |=1<<(11+16);
		
	
	
	
	
	}
	
}
