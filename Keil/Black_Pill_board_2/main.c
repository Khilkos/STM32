#include "main.h"

int main (void)
	
{
Core_F411_init();
SysTick_Init();
	
RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock

GPIO_DO_setup(GPIOB,12,High);	
	
	
	
while (1)
{

if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
//delay_ms(200);
	
	
	




}
}



