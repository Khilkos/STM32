#include "SPI.h"
#define SPI1_CS_ON GPIOA->BSRR = 1<<6
#define SPI1_CS_OFF GPIOA->BSRR = 1<<(6+16)
_Bool SPI1_DMA_buzy=0;

 void SPI_F411_init(void)
 {
	 RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ;
	 
SPI1->CR1 |=( SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_SSM | SPI_CR1_SSI | 5U<<3 | SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA );
__NOP();
SPI1->CR1 |= SPI_CR1_SPE;

 }

 void SPI_F4_init(uint8_t SPI_speed)
 {
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ;
	 
SPI1->CR1 |=( SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_SSM | SPI_CR1_SSI | (uint32_t)SPI_speed<<3 | SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA );
__NOP();
SPI1->CR1 |= SPI_CR1_SPE;

 }
//=========================================================
 void SPI1_F4_send_8bit (uint32_t size,uint8_t* buf)
 {
 SPI1_CS_ON;
SPI1->CR2 |= SPI_CR2_TXDMAEN;
//SPI1->CR1 |= SPI_CR1_SPE;//////	 
//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA2;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA2_Stream2;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = &(SPI1->DR);//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*) buf ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  size ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 2 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size =  DMA_8_bit;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode =  Circular_mode_disabled;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA2_Stream2_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
SPI1_DMA_buzy=1;
//
//---------------------------------------------------
}
 
 void DMA2_Stream2_IRQHandler_User(void)
 {

while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
while ((SPI1->SR&SPI_SR_BSY)) {__NOP();}
SPI1->CR2 &= ~SPI_CR2_TXDMAEN;
//SPI1->CR1 &= ~SPI_CR1_SPE;////////
//DMA2_Stream2->CR &= ~(DMA_SxCR_EN);//
SPI1_CS_OFF;
SPI1_DMA_buzy=0;
GPIOB->BSRR=1<<13;
  }
 //============================================
	