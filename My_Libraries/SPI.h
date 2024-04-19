#ifndef __SPI_H
#define __SPI_H

#include "stm32f411xe.h"
#include "Config.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
extern _Bool SPI1_DMA_buzy;

void SPI_F411_init(void);
void SPI_F4_init(uint8_t SPI_speed);
void SPI1_F4_send_8bit (uint32_t size,uint8_t* buf);
#define DMA2_Stream2_IRQHandler_define
void DMA2_Stream2_IRQHandler_User(void);
#endif





