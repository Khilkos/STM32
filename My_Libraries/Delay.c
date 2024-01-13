#include "Delay.h"




void SysTick_Handler(void)
{

if (count>0)	count--; else count=0;  	

if (GPIOB->IDR & 1<<15) GPIOB->BSRR=1<<(15+res); else GPIOB->BSRR=1<<15;
}
//---------------------------------------------------------
void delay_us(uint32_t time_delay_us)
{
	SysTick->CTRL |=(1U<<0);
	count=time_delay_us;
	while (count) __NOP();
	SysTick->CTRL &=~(1U<<0);
}


void delay_ms(uint32_t delay_time_ms)
{
	SysTick->CTRL |=(1U<<0);
	count=delay_time_ms*1000;
	while (count) __NOP();
	SysTick->CTRL &=~(1U<<0);
}

void SysTick_Init(void)
{	
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
#define HCLK 96			//enable Systick on 1 us takt
SysTick->LOAD =(HCLK-1);
SysTick->CTRL |= 1<<2 | 1<<1 ;//| 1<<0 ;
}


