#include "main.h"
//#include "GPIO_setup.h"


int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(6,168,2,4,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	
	GPIO_DO_setup(GPIOE,6,High);
GPIO_DO_setup(GPIOA,1,High);	

	GPIOE->BSRR = 1<<6;
//		GPIOA->BSRR = 1<<1;
	
	
	while (1)
	{
		
	if (!TIM1_Delay_1) {if (GPIOA->IDR & 1<<1) GPIOA->BSRR = 1<<(1+16); else GPIOA->BSRR = 1<<1;  	TIM1_Delay_1 = 250;}
			
		
	}
	
}
