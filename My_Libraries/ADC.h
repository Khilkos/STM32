#ifndef __ADC_H
#define __ADC_H

#include "stm32f411xe.h"
#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16

extern uint32_t ADC_main_count;

extern uint32_t ADC_ch0;
extern uint32_t ADC_ch0_summ;
extern uint32_t ADC_ch0_count;

extern uint32_t ADC_ch1;
extern uint32_t ADC_ch1_summ;
extern uint32_t ADC_ch1_count;

extern uint32_t ADC_ch2;
extern uint32_t ADC_ch2_summ;
extern uint32_t ADC_ch2_count;

void ADC1_F411_Init (void);
void ADC_IRQHandler(void);
void ADC1_F4_via_DMA_2ch_Init (void);
void DMA_F4_ADC_init (void);
void DMA2_Stream0_IRQHandler(void);

#endif
