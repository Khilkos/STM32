#include "Delay.h"

// __disable_irq (); // запретить прерывания
//__enable_irq ();  // разрешить прерывания


void SysTick_Handler(void)
{
if (count>0)	count--; else count=0; 

}
//---------------------------------------------------------
void delay_us(uint32_t time_delay_us)
{
	SysTick->CTRL |=(1U<<SysTick_CTRL_ENABLE_Pos);
	count=time_delay_us;
	while (count) __NOP();
	SysTick->CTRL &=~(1U<<SysTick_CTRL_ENABLE_Pos);
}


void delay_ms(uint32_t delay_time_ms)
{
	SysTick->CTRL |=(1U<<SysTick_CTRL_ENABLE_Pos);
	count=delay_time_ms*1000;
	while (count) __NOP();
	SysTick->CTRL &=~(1U<<SysTick_CTRL_ENABLE_Pos);
}

#ifdef STM32F4
void SysTick_Init(void)
{	
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
#define HCLK 96			//enable Systick on 1 us takt
SysTick->LOAD =(HCLK-1);
SysTick->CTRL |= 1<<2 | 1<<1 ;//| 1<<0 ;
}

void SysTick_F4_Init(uint8_t CPU_AHB_MHz_frequency) //frequency AHB bus in MHz
{	
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
			
SysTick->LOAD =(CPU_AHB_MHz_frequency-1); //enable Systick on 1 us takt
SysTick->CTRL |= 1<<SysTick_CTRL_CLKSOURCE_Pos | 1<<SysTick_CTRL_TICKINT_Pos;
}
#endif

#ifdef STM32H7

void SysTick_H7_Init(uint16_t Systick_MHz_frequency) //frequency AHB bus in MHz
{	
RCC->AHB4ENR |= RCC_APB4ENR_SYSCFGEN;
			
SysTick->LOAD =(Systick_MHz_frequency-1); //enable Systick on 1 us takt
SysTick->CTRL |= 1<<SysTick_CTRL_CLKSOURCE_Pos | 1<<SysTick_CTRL_TICKINT_Pos;
}


#endif

