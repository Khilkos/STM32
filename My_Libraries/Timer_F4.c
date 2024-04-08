#include "Timer_F4.h"

uint32_t Delay_1=0;
uint32_t Delay_2=0;
uint32_t Delay_3=0;
uint32_t Delay_4=0;
uint32_t Delay_5=0;
uint32_t Delay_6=0;
uint32_t Delay_7=0;
uint32_t Delay_8=0;
uint32_t Delay_9=0;
uint32_t Delay_10=0;
uint32_t TIM2_Delay_1=0;


void Timer1_F4_init(uint8_t CPU_AHB_MHz_frequency)
{
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN; //enable clock for Timer 1
	TIM1->CR1 =0;
	TIM1->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM1->PSC =(CPU_AHB_MHz_frequency*1000/256-1);
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
if (Delay_1>0) Delay_1--; else Delay_1=0;
if (Delay_2>0) Delay_2--; else Delay_2=0;
if (Delay_3>0) Delay_3--; else Delay_3=0;
if (Delay_4>0) Delay_4--; else Delay_4=0;
if (Delay_5>0) Delay_5--; else Delay_5=0;
if (Delay_6>0) Delay_6--; else Delay_6=0;
if (Delay_7>0) Delay_7--; else Delay_7=0;
if (Delay_8>0) Delay_8--; else Delay_8=0;
if (Delay_9>0) Delay_9--; else Delay_9=0;
if (Delay_10>0) Delay_10--; else Delay_10=0;
	//if (GPIOB->IDR & (1<<12)) GPIOB->BSRR=1U<<(12+res); else GPIOB->BSRR=1U<<12;
	}
}
//========================================================
void Timer2_F4_init(uint8_t CPU_AHB_MHz_frequency)
{
RCC->APB1ENR |=RCC_APB1ENR_TIM2EN; //enable clock for Timer 2
	TIM2->CR1 =0;
	TIM2->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM2->PSC =(CPU_AHB_MHz_frequency*1000/256-1);
	TIM2->ARR = 0xFF;
	NVIC->ISER[0] |=1<<28; //enable timer1 update interrupt for NVIC
	//TIM1->CR1 |=TIM_CR1_URS;
	TIM2->CR1 |=TIM_CR1_CEN;// | TIM_CR1_URS;
}

void TIM2_IRQHandler(void)
{
if (TIM2->SR&TIM_SR_UIF) 
	{		
TIM2->SR &= ~TIM_SR_UIF;	
if (TIM2_Delay_1>0) TIM2_Delay_1--; else TIM2_Delay_1=0;

	//if (GPIOB->IDR & (1<<12)) GPIOB->BSRR=1U<<(12+res); else GPIOB->BSRR=1U<<12;
	}




}
