#include "Timer.h"

uint32_t TIM1_Delay_1=0;
uint32_t TIM1_Delay_2=0;
uint32_t TIM1_Delay_3=0;
uint32_t TIM1_Delay_4=0;
uint32_t TIM1_Delay_5=0;
uint32_t TIM1_Delay_6=0;
uint32_t TIM1_Delay_7=0;
uint32_t TIM1_Delay_8=0;
uint32_t TIM1_Delay_9=0;
uint32_t TIM1_Delay_10=0;
uint32_t TIM2_Delay_1=0;


//=============================================
#ifdef STM32F4
void Timer1_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz)
{
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN; //enable clock for Timer 1
	TIM1->CR1 =0;
	TIM1->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM1->PSC =(CPU_AHB_Hz_frequency/(256*Timer_frequency_Hz)-1);
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
if (TIM1_Delay_1>0) TIM1_Delay_1--; else TIM1_Delay_1=0;
if (TIM1_Delay_2>0) TIM1_Delay_2--; else TIM1_Delay_2=0;
if (TIM1_Delay_3>0) TIM1_Delay_3--; else TIM1_Delay_3=0;
if (TIM1_Delay_4>0) TIM1_Delay_4--; else TIM1_Delay_4=0;
if (TIM1_Delay_5>0) TIM1_Delay_5--; else TIM1_Delay_5=0;
if (TIM1_Delay_6>0) TIM1_Delay_6--; else TIM1_Delay_6=0;
if (TIM1_Delay_7>0) TIM1_Delay_7--; else TIM1_Delay_7=0;
if (TIM1_Delay_8>0) TIM1_Delay_8--; else TIM1_Delay_8=0;
if (TIM1_Delay_9>0) TIM1_Delay_9--; else TIM1_Delay_9=0;
if (TIM1_Delay_10>0) TIM1_Delay_10--; else TIM1_Delay_10=0;
	//if (GPIOB->IDR & (1<<12)) GPIOB->BSRR=1U<<(12+res); else GPIOB->BSRR=1U<<12;
	}
}
//========================================================
void Timer2_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz)
{
RCC->APB1ENR |=RCC_APB1ENR_TIM2EN; //enable clock for Timer 2
	TIM2->CR1 =0;
	TIM2->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM2->PSC =(CPU_AHB_Hz_frequency/(256*Timer_frequency_Hz)-1);
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

#endif
//==============================================================
//
//==============================================================
#ifdef STM32H7

void Timer1_H7_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz)
{
RCC->APB2ENR |=RCC_APB2ENR_TIM1EN; //enable clock for Timer 1
	TIM1->CR1 =0;
	TIM1->DIER |=TIM_DIER_UIE; //enable update interrupt for timer1
	TIM1->PSC =(CPU_AHB_Hz_frequency/(256*Timer_frequency_Hz)-1);
	TIM1->ARR = 0xFF;
	NVIC->ISER[0] |=1<<25; //enable timer1 update interrupt for NVIC
	NVIC->IP[25]=8<<4;
	TIM1->CR1 |=TIM_CR1_CEN;// 
}
//----------------------------------------
void TIM1_UP_IRQHandler (void)
{
	if (TIM1->SR&TIM_SR_UIF) 
	{	//NVIC->ICPR[0] |=1<<25;	
		TIM1->SR &= ~TIM_SR_UIF;	
		if (TIM1_Delay_1>0) TIM1_Delay_1--; else TIM1_Delay_1=0;
		if (TIM1_Delay_2>0) TIM1_Delay_2--; else TIM1_Delay_2=0;
		if (TIM1_Delay_3>0) TIM1_Delay_3--; else TIM1_Delay_3=0;
		if (TIM1_Delay_4>0) TIM1_Delay_4--; else TIM1_Delay_4=0;
		if (TIM1_Delay_5>0) TIM1_Delay_5--; else TIM1_Delay_5=0;
		if (TIM1_Delay_6>0) TIM1_Delay_6--; else TIM1_Delay_6=0;
		if (TIM1_Delay_7>0) TIM1_Delay_7--; else TIM1_Delay_7=0;
		if (TIM1_Delay_8>0) TIM1_Delay_8--; else TIM1_Delay_8=0;
		if (TIM1_Delay_9>0) TIM1_Delay_9--; else TIM1_Delay_9=0;
		if (TIM1_Delay_10>0) TIM1_Delay_10--; else TIM1_Delay_10=0;
	}
//	NVIC->IABR[0]|=1<<25;
}
//-----------------------------------------


#endif
//=============================================================




