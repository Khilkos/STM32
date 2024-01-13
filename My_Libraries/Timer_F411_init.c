#include "Timer_F411_init.h"

uint32_t key_delay=0;
uint32_t select_delay=0;
uint32_t DS18B20_delay=0;
uint32_t HUB75_line_run_delay=0;
uint32_t HUB75_screen_delay=0;


void Timer_F411_init(void)
{
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN; //enable clock for Timer 1
	TIM1->CR1 =0;
	TIM1->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM1->PSC =374;
	TIM1->ARR = 0xFF;
	NVIC->ISER[0] |=1<<25; //enable timer1 update interrupt for NVIC
	//TIM1->CR1 |=TIM_CR1_URS;
	TIM1->CR1 |=TIM_CR1_CEN;// | TIM_CR1_URS;
}

//вызов раз в 1мс, частота 1 к√ц
void TIM1_UP_TIM10_IRQHandler(void)
{
	if (TIM1->SR&TIM_SR_UIF) 
	{		
TIM1->SR &= ~TIM_SR_UIF;	
		if (key_delay>0) key_delay--; else key_delay=0;
if (select_delay>0) select_delay--; else select_delay=0;	
if (DS18B20_delay>0) DS18B20_delay--; else DS18B20_delay=0;	
if (HUB75_line_run_delay>0) HUB75_line_run_delay--; else HUB75_line_run_delay=0;	
if (HUB75_screen_delay>0) HUB75_screen_delay--; else HUB75_screen_delay=0;	
//if (GPIOB->IDR & (1<<12)) GPIOB->BSRR=1U<<(12+res); else GPIOB->BSRR=1U<<12;
	}

}

