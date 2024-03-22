#ifndef __DMA_H
#define __DMA_H

#include "stm32f411xe.h"
#include "stdint.h"


void DMA_F4_init (void);

#define DMA_Priority_low 0
#define DMA_Priority_medium 1
#define DMA_Priority_high 2
#define DMA_Priority_very_high 3

#define DMA_Inc_ON 1
#define DMA_Inc_OFF 0

#define DMA_Peripheral_to_memory 0
#define DMA_Memory_to_Peripheral 1
#define DMA_Memory_to_memory 2

#define DMA_8_bit 0
#define DMA_16_bit 1
#define DMA_32_bit 2

#define Circular_mode_disabled 0
#define Circular_mode_enabled 1




#endif
