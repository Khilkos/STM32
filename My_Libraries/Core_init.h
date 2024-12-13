#ifndef __Core_init_H
#define __Core_init_H

#include "Config.h"
//#include "stm32f411xe.h" //!!!!!!!!!!!!!
#include "stdint.h"
//#include "cmsis_armclang.h" //!!!!!!!!!!!!!!!!
//#include "core_cm4.h" //!!!!!!!!!!!!!!!!!!!!!!


#define PLL_M 25
#define PLL_N 192
#define PLL_P 0
#define PLL_Q 4

void Core_F411_init(void);
void Core_F401_init_HSI(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q);
void Core_F4_init_HSE(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q);

void Core_STM32_H7_init (void);



#endif

