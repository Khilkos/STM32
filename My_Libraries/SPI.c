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
struct SPI_H7_init SPI_H7;

void SPI_H7_init(void)
{
	RCC->D2CCIP1R &= ~RCC_D2CCIP1R_SPI123SEL_Msk;
	RCC->D2CCIP1R |= 0U<<RCC_D2CCIP1R_SPI123SEL_Pos;	//выбор источника тактирования SPI 

	if (SPI_H7.SPI_Number == SPI1) RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // включение тактирования SPI
	if (SPI_H7.SPI_Number == SPI2) RCC->APB1LENR |= RCC_APB1LENR_SPI2EN; // включение тактирования SPI
	
	SPI_H7.SPI_Number ->CR1 |= (SPI_CR1_SSI);
	if (SPI_H7.SSM_bit == 1) SPI_H7.SPI_Number->CFG2 |= (SPI_CFG2_SSM ); // программный SS, управляется битом SSI
	
	if (SPI_H7.MBR >=7) SPI_H7.MBR =7;
	SPI_H7.SPI_Number->CFG1 |= ((uint32_t)SPI_H7.MBR<<SPI_CFG1_MBR_Pos); // делитель тактовой частоты для SPI, от 0=/2, 1=/4 ....7=/256 
	
	if (SPI_H7.DSIZE <=3) SPI_H7.DSIZE =3;
	if (SPI_H7.DSIZE>=31) SPI_H7.DSIZE = 31;
	SPI_H7.SPI_Number->CFG1 &=~SPI_CFG1_DSIZE_Msk;
	SPI_H7.SPI_Number->CFG1 |=((uint32_t)SPI_H7.DSIZE<<SPI_CFG1_DSIZE_Pos); // количество бит в кадре от 3=4бита, 4=5бит, .... 31=32бита.
	
	if (SPI_H7.FTHLV >=15) SPI_H7.FTHLV=15;
	SPI_H7.SPI_Number->CFG1 |= ((uint32_t)SPI_H7.FTHLV<<SPI_CFG1_FTHLV_Pos); // уровень поорга FIFO, количество кадров данных, от 0=1кадр, 1=2кадр ... 15=16кадр
	
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_MASTER;
	if (SPI_H7.MASTER_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_MASTER ); //режим SPI: 0-Slave, 1-Master
	
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_CPOL;
	if (SPI_H7.CPOL_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_CPOL );//полярность CLK:	0-SCK сигнал когда 0 на idle, 1-SCK сигнал когда 1 на idle

	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_CPHA;
	if (SPI_H7.CPHA_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_CPHA ); //фаза CLK: 0-захват сигнала по первому фронту CLK, 1-захват сигнала по фторому фронту CLK
	
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_SSOE;
	if (SPI_H7.SSOE_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_SSOE ); //включение аппаратного выхода SS: 0 - выключен, 1-включен	
	
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_SSIOP;
	if (SPI_H7.SSIOP_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_SSIOP ); //выбор активного уровня SS: 0-низкий уровень это активный SS, 1- высокий уровень это активный SS	
	
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_SSOM;
	if (SPI_H7.SSOM_bit) SPI_H7.SPI_Number ->CFG2 |= ( SPI_CFG2_SSOM ); //режим работы выхода SS в MASTER mode

	if (SPI_H7.MSSI >=15) SPI_H7.MSSI =15;
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_MSSI_Msk;
	SPI_H7.SPI_Number->CFG2 |= ((uint32_t)SPI_H7.MSSI<<SPI_CFG2_MSSI_Pos); //отступ от SS начала передачи, значение от 0 до 15 тактов
	
	if (SPI_H7.COMM >=3) SPI_H7.COMM =3;
	SPI_H7.SPI_Number->CFG2 &=~SPI_CFG2_COMM_Msk;
	SPI_H7.SPI_Number->CFG2 |= ((uint32_t)SPI_H7.COMM<<SPI_CFG2_COMM_Pos); //режим работы SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex

	if (SPI_H7.TSIZE >=10000) SPI_H7.TSIZE =10000;
	SPI_H7.SPI_Number->CR2 &=~SPI_CR2_TSIZE_Msk;
	SPI_H7.SPI_Number->CR2 |= ((uint32_t)SPI_H7.TSIZE<<SPI_CR2_TSIZE_Pos); //количество кадров в одной посылке (во время активного SS)
	
	SPI_H7.SPI_Number->CFG1 &=~SPI_CFG1_TXDMAEN_Msk;
	if (SPI_H7.Tx_DMA) SPI_H7.SPI_Number->CFG1|=SPI_CFG1_TXDMAEN;
	
	SPI_H7.SPI_Number->CFG1 &=~SPI_CFG1_RXDMAEN_Msk;
	if (SPI_H7.Rx_DMA) SPI_H7.SPI_Number->CFG1|=SPI_CFG1_RXDMAEN;
		
	SPI_H7.SPI_Number->CR1 |= SPI_CR1_SPE; //enable SPI	
	
}




#endif
