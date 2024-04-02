#ifndef __DMA_H
#define __DMA_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Config.h"


//-------------------------------------------------
//
//DMA_STM_F4.DMA_Number = ;//выбор ДМА, напр. - DMA2
//DMA_STM_F4.DMA_Stream = ;//выбор потока ДМА напр. -  DMA2_Stream0
//DMA_STM_F4.DMA_Peripheral_address = ;//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
//DMA_STM_F4.DMA_Memory_address =   ;//адрес памяти, например (void*)temp_send_buf ;
//DMA_STM_F4.DMA_Quantity =   ;//количество данный передаваемых в ДМА
//DMA_STM_F4.DMA_Chanel =  ;//выбор канала ДМА
//DMA_STM_F4.DMA_Prioroty =  ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
//DMA_STM_F4.DMA_Data_transfer_direction =  ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
//DMA_STM_F4.DMA_Memory_inc =   ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
//DMA_STM_F4.DMA_Peripheral_inc =  ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
//DMA_STM_F4.DMA_Memory_data_size =  ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
//DMA_STM_F4.DMA_Peripheral_data_size =  ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
//DMA_STM_F4.DMA_Circular_mode =  ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
//DMA_STM_F4.DMA_Interrupt =  ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
//DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------





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

void DMA_F4_param_init (void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);



struct DMA_STM_F4_init_param
{
DMA_TypeDef * DMA_Number; //выбор ДМА напр. - DMA2
DMA_Stream_TypeDef * DMA_Stream;//выбор потока ДМА напр. -  DMA2_Stream0
volatile uint32_t *DMA_Peripheral_address;	//адрес перефирии
uint32_t *DMA_Memory_address;//адрес памяти
uint32_t DMA_Quantity;//количество данный передаваемых в ДМА
uint32_t DMA_Chanel;//выбор канала ДМА
uint8_t DMA_Prioroty;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
	uint8_t DMA_Data_transfer_direction;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
_Bool DMA_Memory_inc;	//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
_Bool DMA_Peripheral_inc;////инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
uint8_t DMA_Memory_data_size;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
uint8_t DMA_Peripheral_data_size;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
	_Bool DMA_Circular_mode;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
uint8_t DMA_Interrupt;	 //из stm32f411xe.h, например - DMA2_Stream0_IRQn
};

extern struct DMA_STM_F4_init_param DMA_STM_F4;





#endif
