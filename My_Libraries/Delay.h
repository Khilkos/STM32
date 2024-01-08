#ifndef __Delay_H
#define __Delay_H

/*
Libraries for delay in ms and us
need degined in mail programm SysTick();
*/


#include "stm32f411xe.h"
#include "stdint.h"
#include "cmsis_armclang.h" 
#include "core_cm4.h"
#include "DS3231_F411.h"

static uint32_t count=0;


void delay_us(uint32_t);
void delay_ms(uint32_t);
void SysTick_Handler(void);
void SysTick_Init(void);

#endif

