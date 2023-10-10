#ifndef __EXTI_F411_init_H
#define __EXTI_F411_init_H

#include "stm32f411xe.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16

void EXTI_F411_init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);

#endif
