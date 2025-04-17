#include "main.h"
//#include "GPIO_setup.h"


int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(8,336,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	
	GPIO_DO_setup(GPIOD,12,High);//Green_Led
	GPIO_DO_setup(GPIOD,13,High);//Orange_Led
	GPIO_DO_setup(GPIOD,14,High);//Red_Led
	GPIO_DO_setup(GPIOD,15,High);//Blue_Led

GPIO_DI_setup(GPIOA,0,Pull_down);	

//	GPIOE->BSRR = 1<<6;
//		GPIOA->BSRR = 1<<1;
	
	
	while (1)
	{
		
	if (!TIM1_Delay_1) {if (GPIOD->IDR & 1<<12) GPIOD->BSRR = 1<<(12+16); else GPIOD->BSRR = 1<<12;  	TIM1_Delay_1 = 250;}
	if (GPIOA->IDR &  1<<0) GPIOD->BSRR = 1<<13; else GPIOD->BSRR = 1<<(13+16);		
		
	}
	
}
