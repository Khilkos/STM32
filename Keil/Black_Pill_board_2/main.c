#include "main.h"

int main (void)
	
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock

GPIO_DO_setup(GPIOB,12,High);	

GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);
	
	
	
Core_F411_init();
SysTick_Init();
I2C_F411_init();
LCD1602_init_via_I2C();
	

	
	
while (1)
{

if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
//delay_ms(200);
	LCD1602_init_via_I2C();
	
	




}
}



