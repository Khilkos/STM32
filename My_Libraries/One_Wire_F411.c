#include "One_Wire_F411.h"

uint8_t One_wire_recive_buf[64];


//=================================================
void DMA_F411_One_Wire_Send (uint8_t size_buf, uint8_t* send_buf)
{	uint8_t temp=0;
	static uint8_t temp_send_buf[64];
		USART_F411_set_115200_baud();
	for (uint8_t i=0; i<size_buf;i++)
		{	temp=*(send_buf+i);
			for (uint8_t k=0; k<8; k++)
			{ if (temp&0x01) temp_send_buf[i*8+k]=0xff; else temp_send_buf[i*8+k]=0x00;
				temp>>=1;
			}
		}
//-----------------------
//
DMA_STM_F4.DMA_Number = DMA1;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream6;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR);//адрес перефирии
DMA_STM_F4.DMA_Memory_address =  (void*)temp_send_buf ;//адрес памяти
DMA_STM_F4.DMA_Quantity =  size_buf*8 ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel =  4;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_very_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction =  DMA_Memory_to_Peripheral;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =   DMA_Inc_ON;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt =  DMA1_Stream6_IRQn;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//------------------------

USART2->SR &=~USART_SR_TC;

	USART_F411_DMAT_ON();
}


//===================================================

//===================================================
void DMA_F411_One_Wire_Recive (uint8_t size_buf, uint8_t* recive_buf)
{		static uint8_t temp_recive_buf[64];
		USART_F411_set_115200_baud();
	for (uint8_t i=0; i<size_buf*8; i++)
		{ temp_recive_buf[i]=0xff;}
	
	USART2->DR;
	USART2->DR;

//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA1;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream5;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR);//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address =  (void*)recive_buf ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity = size_buf*8  ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Peripheral_to_memory ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc = DMA_Inc_ON ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream5_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------	
	
//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA1;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream6;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR) ;//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*)temp_recive_buf ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  size_buf*8 ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc = DMA_Inc_ON  ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc =  DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream6_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------
	
	USART_F411_DMA_ON();	
}



//===================================================

//===================================================
void DMA_F411_One_Wire_Reset (uint8_t* recive_buf)
{ 
		uint8_t temp=0xf0;
		static uint8_t temp_send_buf[64];
	USART_F411_set_9600_baud();
	
	for (uint8_t i=0; i<8; i++)
			{ if (temp&0x01) temp_send_buf[i*8]=0xff; else temp_send_buf[i*8]=0x00;
				temp>>=1;
			}
USART2->DR;
USART2->DR;		

//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA1 ;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream5 ;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR) ;//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address =  (void*)recive_buf ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  8 ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Peripheral_to_memory ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream5_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------

//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA1 ;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream6 ;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR) ;//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*)temp_send_buf  ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  8 ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc = DMA_Inc_ON  ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit ;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled ;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream6_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;
	
USART_F411_DMA_ON();	
}

//====================================================
void DMA1_Stream5_IRQHandler_User(void)
{
		DMA_busy=0;
		USART_F411_DMAR_OFF();
}
//====================================================
void DMA1_Stream6_IRQHandler_User(void)
{
			while (!(USART2->SR & USART_SR_TC)) __NOP();
			if (!(DMA1_Stream5->CR & DMA_SxCR_EN)) DMA_busy=0;
			USART_F411_DMAT_OFF();
}
//====================================================

