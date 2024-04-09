#ifndef __Timer_F4_H
#define __Timer_F4_H

#include "stm32f411xe.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
extern uint32_t TIM1_Delay_1;
extern uint32_t TIM1_Delay_2;
extern uint32_t TIM1_Delay_3;
extern uint32_t TIM1_Delay_4;
extern uint32_t TIM1_Delay_5;
extern uint32_t TIM1_Delay_6;
extern uint32_t TIM1_Delay_7;
extern uint32_t TIM1_Delay_8;
extern uint32_t TIM1_Delay_9;
extern uint32_t TIM1_Delay_10;
extern uint32_t TIM2_Delay_1;


void TIM1_UP_TIM10_IRQHandler(void);
void TIM2_IRQHandler(void);
void Timer1_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz);//частота шины тактирования, необходимая частота таймера
void Timer2_F4_init(uint32_t CPU_AHB_Hz_frequency, uint32_t Timer_frequency_Hz);//частота шины тактирования, необходимая частота таймера

#endif

