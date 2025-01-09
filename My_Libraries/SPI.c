#include "SPI.h"

_Bool SPI1_DMA_buzy=0;
uint32_t SPI1_send_num=0;

#ifdef STM32F4
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

if (SPI_speed>7) SPI_speed=7;	 
SPI1->CR1 |=( SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_SSM | SPI_CR1_SSI | (uint32_t)SPI_speed<<3 | SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_CPHA );
__NOP();
SPI1->CR1 |= SPI_CR1_SPE;

 }
//=========================================================
 void SPI1_F4_send_8bit (uint32_t size,uint8_t* buf)
 {
 SPI1_CS_ON;
SPI1->CR2 |= SPI_CR2_TXDMAEN;
SPI1_DMA_buzy=1;	 
//-------------------------------------------------
//
DMA_STM_F4.DMA_Number = DMA2;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA2_Stream2;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = &(SPI1->DR);//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*) buf ;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  size ;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 2 ;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_low ;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral ;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON ;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size =  DMA_8_bit;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode =  Circular_mode_disabled;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA2_Stream2_IRQn ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//SPI1_DMA_buzy=1;
//
//---------------------------------------------------
}
 /*
 void DMA2_Stream2_IRQHandler_User(void)
 {

while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
while ((SPI1->SR&SPI_SR_BSY)) {__NOP();}
SPI1->CR2 &= ~SPI_CR2_TXDMAEN;
SPI1_CS_OFF;
//SPI1_DMA_buzy=0;
if (GPIOB->IDR&1<<15) GPIOB->BSRR=1UL<<(15+res); else GPIOB->BSRR=1<<15;
if (SPI1_send_num<5)
	{	SPI1_send_num++;
		SPI1->CR2 |= SPI_CR2_TXDMAEN; 
		DMA2_Stream2->M0AR=(uint32_t)(temp_send_buf+SPI1_send_num); 
		DMA2_Stream2->CR |= (DMA_SxCR_EN); } 
	else {SPI1_send_num=0;SPI1_DMA_buzy=0;}




 }
 //============================================
	*/
#endif

#ifdef STM32H7

void SPI1_init(void)
{
RCC->D2CCIP1R &= ~RCC_D2CCIP1R_SPI123SEL_Msk;
RCC->D2CCIP1R |= 0U<<RCC_D2CCIP1R_SPI123SEL_Pos;	//выбор источника тактирования SPI 

RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

SPI1->CR1 |= (SPI_CR1_SSI | SPI_CR1_CSTART);	
SPI1->CFG1 |= (5<<SPI_CFG1_MBR_Pos | 7<<SPI_CFG1_DSIZE_Pos );
SPI1->CFG2 |= (SPI_CFG2_SSM | SPI_CFG2_MASTER);	

SPI1->CR1 |= SPI_CR1_SPE; //enable SPI	
}



#endif
