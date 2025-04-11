#ifndef __DMA_H
#define __DMA_H

#include "Config.h"
#include "stdint.h"
#include "main.h"


#ifdef STM32F4
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
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);


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


//================================================================================
//==============================STM32H7===========================================
//================================================================================
#ifdef STM32H7

void DMA_H7_init(void);
void DMA1_Stream0_IRQHandler(void);

struct DMA_H7_init
	

//-------------------------------------------------
//-------------инициализация DMA-------------------
//-------------------------------------------------
//DMA_H7.DMA_Number = ; //выбор ДМА, напр. - DMA2
//DMA_H7.DMA_Stream = ; //выбор потока ДМА напр. -  DMA2_Stream0
//DMA_H7.DMA_Peripheral_address = ;//адрес перефирии, например &USART2->DR;
//DMA_H7.DMA_Memory_address = ; //адрес памяти, например (void*)temp_send_buf ;
//DMA_H7.DMA_Quantity = ;//NDTR - Number of data items to transfer (0 up to 65535), количество данный передаваемых в ДМА
//DMA_H7.DMA_Request_source = ; //выбор источника тактирования DMAMUX для канала ДМА
//DMA_H7.DMA_flow_control =;//если=0 - контроллером потока является DMA, если=1 - перифирическое устройство
//DMA_H7.DMA_Prioroty = ;//приоритет потока: 0-Low, 1-Medium, 2-High, 3-Very high
//DMA_H7.DMA_Memory_data_size = ; //Размер памяти: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
//DMA_H7.DMA_Peripheral_data_size = ;	//Размер перефирического устройства: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
//DMA_H7.DMA_Data_transfer_direction = ; //направление передачи DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved
//DMA_H7.DMA_Memory_inc = ;//инкремент памяти: 0-выкл, 1-включен
//DMA_H7.DMA_Peripheral_inc = ; //инкремент перефирии: 0-выкл, 1-включен
//DMA_H7.DMA_Circular_mode = ; //циклический режим: 0-выключен, 1-включен
//DMA_H7.DMA_Transfer_complete_interrupt= ; //Прерывание после завершения передачи: 0-выключен, 1-включен	
//DMA_H7.DMA_Interrupt =  ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
//DMA_H7.DMA_Interrupt_Priority = ; //приоритет прерывания

//DMA_H7_init();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------	

{
DMA_TypeDef * DMA_Number; //выбор ДМА напр. - DMA2
DMA_Stream_TypeDef * DMA_Stream;//выбор потока ДМА напр. -  DMA2_Stream0
volatile uint32_t *DMA_Peripheral_address;	//адрес перефирии, например &USART2->DR;
uint32_t *DMA_Memory_address;//адрес памяти
uint32_t DMA_Quantity;//количество данный передаваемых в ДМА
uint8_t DMA_Request_source;//выбор источника тактирования DMAMUX для канала ДМА
_Bool DMA_flow_control;////если=0 - контроллером потока является DMA, если=1 - перифирическое устройство
uint8_t DMA_Prioroty;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
	uint8_t DMA_Data_transfer_direction;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
_Bool DMA_Memory_inc;	//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
_Bool DMA_Peripheral_inc;////инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
uint8_t DMA_Memory_data_size;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
uint8_t DMA_Peripheral_data_size;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
	_Bool DMA_Circular_mode;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
_Bool DMA_Transfer_complete_interrupt; //Прерывание после завершения передачи	
uint8_t DMA_Interrupt;	 //из stm32f411xe.h, например - DMA2_Stream0_IRQn
uint8_t DMA_Interrupt_Priority; //приоритет прерывания DMA, от 0 до 15 (0 самый высокий приоритет)
};

extern struct DMA_H7_init DMA_H7;













#endif






#endif
