#ifndef __UART_F411_H
#define __UART_F411_H

#include "Config.h"


#define res 16


extern uint32_t USART_DR_RX;
extern _Bool usart_fault;

void USART_F4_init (USART_TypeDef * USARTx);
void USART_F4_set_9600_baud (USART_TypeDef * USARTx);
void USART_F4_set_115200_baud (USART_TypeDef * USARTx);
void USART_F4_DMA_ON (USART_TypeDef * USARTx);
void USART_F4_DMA_OFF (USART_TypeDef * USARTx);
void USART_F4_DMAR_OFF (USART_TypeDef * USARTx);
void USART_F4_DMAT_OFF (USART_TypeDef * USARTx);
void USART_F4_restart(USART_TypeDef * USARTx);
void USART_F4_DMAT_ON (USART_TypeDef * USARTx);
void USART_F4_DMAR_ON (USART_TypeDef * USARTx);


#endif
