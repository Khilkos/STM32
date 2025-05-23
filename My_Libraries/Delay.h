#ifndef __Delay_H
#define __Delay_H

/*
Libraries for delay in ms and us
need degined in mail programm SysTick();
*/

#include "Config.h"
//#include "stm32f411xe.h"
#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

static uint32_t count=0;


void delay_us(uint32_t);
void delay_ms(uint32_t);
void SysTick_Handler(void);
void SysTick_Init(void);
void SysTick_F4_Init(uint8_t CPU_AHB_MHz_frequency);
void SysTick_H7_Init(uint16_t Systick_MHz_frequency);

#endif

