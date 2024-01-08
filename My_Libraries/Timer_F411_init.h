#ifndef __Timer_F411_init_H
#define __Timer_F411_init_H

#include "stm32f411xe.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
extern uint32_t key_delay;
extern uint32_t select_delay;
extern uint32_t DS18B20_delay;
extern uint32_t HUB75_line_run_delay;
extern uint32_t HUB75_screen_delay;


void TIM1_UP_TIM10_IRQHandler(void);
void Timer_F411_init(void);

#endif

