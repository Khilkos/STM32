#ifndef __Timer_F4_H
#define __Timer_F4_H

#include "stm32f411xe.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
extern uint32_t Delay_1;
extern uint32_t Delay_2;
extern uint32_t Delay_3;
extern uint32_t Delay_4;
extern uint32_t Delay_5;
extern uint32_t Delay_6;
extern uint32_t Delay_7;
extern uint32_t Delay_8;
extern uint32_t Delay_9;
extern uint32_t Delay_10;
extern uint32_t TIM2_Delay_1;


void TIM1_UP_TIM10_IRQHandler(void);
void TIM2_IRQHandler(void);
void Timer1_F4_init(uint8_t CPU_AHB_MHz_frequency);
void Timer2_F4_init(uint8_t CPU_AHB_MHz_frequency);

#endif

