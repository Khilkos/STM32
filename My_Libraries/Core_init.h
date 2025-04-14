#ifndef __Core_init_H
#define __Core_init_H

#include "Config.h"
#include "stdint.h"


#define PLL_M 25
#define PLL_N 192
#define PLL_P 0
#define PLL_Q 4

void Core_F411_init(void);
void Core_F401_init_HSI(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q);
void Core_F4_init_HSE(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q);
void Core_F4_init_HSE_full(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q, uint32_t AHB_DIV, uint32_t APB1_DIV, uint32_t APB2_DIV);

void Core_STM32_H7_init (uint8_t DivM1, uint8_t DivN1, uint8_t DivP1, uint8_t DivQ1, uint8_t DivR1);



#endif

