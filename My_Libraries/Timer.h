#ifndef __Timer_H
#define __Timer_H

#include "Config.h"

extern volatile uint32_t TIM1_Delay_1;
extern volatile uint32_t TIM1_Delay_2;
extern volatile uint32_t TIM1_Delay_3;
extern volatile uint32_t TIM1_Delay_4;
extern volatile uint32_t TIM1_Delay_5;
extern volatile uint32_t TIM1_Delay_6;
extern volatile uint32_t TIM1_Delay_7;
extern volatile uint32_t TIM1_Delay_8;
extern volatile uint32_t TIM1_Delay_9;
extern volatile uint32_t TIM1_Delay_10;
extern volatile uint32_t TIM2_Delay_1;

//============================================
#ifdef STM32F4
void TIM1_UP_TIM10_IRQHandler(void);
void TIM2_IRQHandler(void);
void Timer1_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz);//частота шины тактирования, необходимая частота таймера
void Timer2_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz);//частота шины тактирования, необходимая частота таймера
#endif
//============================================
//
//============================================
#ifdef STM32H7
void Timer1_H7_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz);//частота шины тактирования, необходимая частота таймера
void TIM1_UP_IRQHandler (void);

#endif
//============================================



#endif

