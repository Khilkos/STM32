#ifndef __One_Wire_H
#define __One_Wire_H

//***********************
// #include "USART.h"
//	#include "DMA.h"
//***********************

#include "Config.h"




void DMA_F4_One_Wire_Send (uint8_t size_buf, uint8_t* send_buf, USART_TypeDef * USARTx);
void DMA_F4_One_Wire_Recive (uint8_t size_buf, uint8_t* recive_buf, USART_TypeDef * USARTx);
void DMA_F4_One_Wire_Reset (uint8_t* recive_buf, USART_TypeDef * USARTx);
extern uint8_t One_wire_recive_buf[64];

#define DMA1_Stream5_IRQHandler_define
#define DMA1_Stream6_IRQHandler_define
void DMA1_Stream5_IRQHandler_User(void);
void DMA1_Stream6_IRQHandler_User(void);

#endif
