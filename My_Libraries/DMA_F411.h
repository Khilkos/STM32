#ifndef __DMA_F411_H
#define __DMA_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#include "DS18B20_F411.h"


#define res 16


extern uint16_t ADC_DMA_val[2];

void DMA_F411_init (void);
void DMA_F411_ADC_init (void);
void DMA2_Stream0_IRQHandler(void);
void DMA_F411_DS18B20_convert_T (void);
void DMA_F411_DS18B20_read_scratch (void);


#endif
