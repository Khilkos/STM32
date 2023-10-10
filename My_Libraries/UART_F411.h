#ifndef __UART_F411_H
#define __UART_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Delay.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"



#define res 16


extern uint32_t USART_DR_RX;

void UART_F411_init (void);
void UART_F411_set_9600_baud (void);
void UART_F411_set_115200_baud (void);
void UART_F411_DMA_ON (void);
void UART_F411_DMA_OFF (void);
void UART_F411_DMAR_OFF (void);
void UART_F411_DMAT_OFF (void);
void USART_F411_restart(void);


#endif
