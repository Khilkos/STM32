#ifndef __Core_F411_init_H
#define __Core_F411_init_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "cmsis_armclang.h" 
#include "core_cm4.h"


#define PLL_M 25
#define PLL_N 192
#define PLL_P 0
#define PLL_Q 4

void Core_F411_init(void);




#endif

