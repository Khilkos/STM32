#ifndef __SPI_H
#define __SPI_H
#include "Config.h"

//#include "stm32f411xe.h"  //!!!!!!!!!!!!!!!!!!!
#include "main.h"


#define res 16

#define SPI1_CS_ON GPIOA->BSRR = 1<<6
#define SPI1_CS_OFF GPIOA->BSRR = 1<<(6+16)

extern _Bool SPI1_DMA_buzy;
extern uint32_t SPI1_send_num;

void SPI_F411_init(void);
void SPI_F4_init(uint8_t SPI_speed);
void SPI1_F4_send_8bit (uint32_t size,uint8_t* buf);
//#define DMA2_Stream2_IRQHandler_define
//void DMA2_Stream2_IRQHandler_User(void);

void SPI1_H7_init(void);
void SPI2_H7_init(void);



#endif





