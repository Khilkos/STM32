#ifndef __One_Wire_F411_H
#define __One_Wire_F411_H

#include "Config.h"
#include "stm32f411xe.h"
#include "stdint.h"
#include "USART_F411.h"
#include "DMA_F411.h"
#include "Delay.h"
#include "Timer_F411_init.h"




void DMA_F411_One_Wire_Send (uint8_t size_buf, uint8_t* send_buf);
void DMA_F411_One_Wire_Recive (uint8_t size_buf, uint8_t* recive_buf);
void DMA_F411_One_Wire_Reset (uint8_t* recive_buf);
extern uint8_t One_wire_recive_buf[64];

void DMA1_Stream5_IRQHandler_User(void);
void DMA1_Stream6_IRQHandler_User(void);

#endif
