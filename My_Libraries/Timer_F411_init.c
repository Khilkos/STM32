#include "Timer_F411_init.h"

void Timer_F411_init(void)
{
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN; //enable clock for Timer 1
	TIM1->CR1 =0;
	TIM1->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM1->PSC =800;
	TIM1->ARR = 0xFFFF;
	NVIC->ISER[0] |=1<<25; //enable timer1 update interrupt for NVIC
	//TIM1->CR1 |=TIM_CR1_URS;
	TIM1->CR1 |=TIM_CR1_CEN;// | TIM_CR1_URS;
}


void TIM1_UP_TIM10_IRQHandler(void)
{
	if (TIM1->SR&TIM_SR_UIF)
	{		
TIM1->SR &= ~TIM_SR_UIF;	
if (GPIOB->IDR & (1<<15)) GPIOB->BSRR=1U<<(15+res); else GPIOB->BSRR=1U<<15;
	}

}

