#include "Delay.h"

uint32_t key_delay=0;
uint32_t select_delay=0;


void SysTick_Handler(void)
{

if (count>0)	count--; else count=0;	
if (key_delay>0) key_delay--; else key_delay=0;
if (select_delay>0) select_delay--; else select_delay=0;	
//if (GPIOB->IDR & 1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
}
//---------------------------------------------------------
void delay_us(uint32_t time_delay_us)
{
	
	count=time_delay_us;
	while (count) __NOP();
	
}


void delay_ms(uint32_t delay_time_ms)
{
	
	count=delay_time_ms*1000;
	while (count) __NOP();
}

void SysTick_Init(void)
{	
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
#define HCLK 96			//enable Systick on 1 us takt
SysTick->LOAD =(HCLK-1);
SysTick->CTRL |= 1<<2 | 1<<1 | 1<<0 ;
}


