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
DMA_STM_F4.DMA_Number = DMA2;//����� ���, ����. - DMA2
DMA_STM_F4.DMA_Stream = DMA2_Stream2;//����� ������ ��� ����. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = &(SPI1->DR);//����� ���������, �������� (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*) buf ;//����� ������, �������� (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity =  size ;//���������� ������ ������������ � ���
DMA_STM_F4.DMA_Chanel = 2 ;//����� ������ ���
DMA_STM_F4.DMA_Prioroty = DMA_Priority_low ;//��������� ������ - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral ;//����������� ������ ������ ��������� <-> ������: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON ;//��������� ������ DMA_Inc_ON-��������, DMA_Inc_OFF-���������
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//��������� ��������� DMA_Inc_ON-��������, DMA_Inc_OFF-���������
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit ;//������ ������ ������: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size =  DMA_8_bit;//������ ������ ���������: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode =  Circular_mode_disabled;//��������� �����:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA2_Stream2_IRQn ;// ���������� �� stm32f411xe.h, �������� - DMA2_Stream0_IRQn
DMA_F4_param_init ();//������ ��� � ��������� �����������
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

void SPI1_H7_init(void)
{
RCC->D2CCIP1R &= ~RCC_D2CCIP1R_SPI123SEL_Msk;
RCC->D2CCIP1R |= 0U<<RCC_D2CCIP1R_SPI123SEL_Pos;	//����� ��������� ������������ SPI 

RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;


SPI1->CR1 |= (SPI_CR1_SSI);
SPI1->CFG2 |= (SPI_CFG2_SSM ); // ����������� SS, ����������� ����� SSI
	
SPI1->CFG1 &=~SPI_CFG1_DSIZE_Msk;
SPI1->CFG1 |= (4<<SPI_CFG1_MBR_Pos | 31<<SPI_CFG1_DSIZE_Pos | 8<<SPI_CFG1_FTHLV_Pos);
//SPI1->CFG2 |= (SPI_CFG2_SSM | SPI_CFG2_MASTER | 1<<SPI_CFG2_COMM_Pos | SPI_CFG2_CPOL | SPI_CFG2_CPHA);	
SPI1->CFG2 |= ( SPI_CFG2_MASTER ); 
SPI1->CFG2 |= ( 1<<SPI_CFG2_COMM_Pos );	
//SPI1->CFG2 |= ( SPI_CFG2_CPOL ); //���������� CLK	
//SPI1->CFG2 |= ( SPI_CFG2_CPHA);	 //���� CLK
	
//SPI1->CFG2 |= ( SPI_CFG2_SSOE ); //��������� ������ SS	
//SPI1->CFG2 |= ( SPI_CFG2_SSIOP ); //����� ��������� ������ SS

	
SPI1->CFG2 |= ( SPI_CFG2_SSOM );
SPI1->CFG2 |= ( 0<<SPI_CFG2_MSSI_Pos );	//������ �� SS ������ ��������, �������� �� 0 �� 15 ������
	
SPI1->CR2 |= (4<<SPI_CR2_TSIZE_Pos);
SPI1->CR2 |= (0<<SPI_CR2_TSER_Pos);
SPI1->CR1 |= SPI_CR1_SPE; //enable SPI	
//SPI1->CR1 |= (SPI_CR1_SSI);
}

//===============================================

void SPI2_H7_init(void)
{
RCC->D2CCIP1R &= ~RCC_D2CCIP1R_SPI123SEL_Msk;
RCC->D2CCIP1R |= 0U<<RCC_D2CCIP1R_SPI123SEL_Pos;	//����� ��������� ������������ SPI 

RCC->APB1LENR |= RCC_APB1LENR_SPI2EN;


//SPI2->CR1 |= (SPI_CR1_SSI);	
SPI2->CFG2 |= (SPI_CFG2_SSM ); // ����������� SS, ����������� ����� SSI	
	
SPI2->CFG1 &=~SPI_CFG1_DSIZE_Msk;
SPI2->CFG1 &=~SPI_CFG1_UDRDET_Msk;
SPI2->CFG1 |= (1<<SPI_CFG1_UDRDET_Pos);	
SPI2->CFG1 |= (4<<SPI_CFG1_MBR_Pos | 31<<SPI_CFG1_DSIZE_Pos | 8<<SPI_CFG1_FTHLV_Pos);
//SPI2->CFG2 |= (SPI_CFG2_SSM | SPI_CFG2_MASTER | 1<<SPI_CFG2_COMM_Pos | SPI_CFG2_CPOL | SPI_CFG2_CPHA);	
//SPI2->CFG2 |= ( SPI_CFG2_MASTER );
SPI2->CFG2 |= ( 1<<SPI_CFG2_COMM_Pos );	
//SPI2->CFG2 |= ( SPI_CFG2_CPOL ); //���������� CLK	
//SPI2->CFG2 |= ( SPI_CFG2_CPHA);	 //���� CLK

//SPI2->CFG2 |= ( SPI_CFG2_SSOE ); //��������� ������ SS	
SPI2->CFG2 |= ( SPI_CFG2_SSIOP ); //����� ��������� ������ SS	
 	
SPI2->CFG2 |= ( SPI_CFG2_SSOM );
SPI2->CFG2 |= ( 0<<SPI_CFG2_MSSI_Pos );	//������ �� SS ������ ��������, �������� �� 0 �� 15 ������
	
SPI2->CR2 |= (4<<SPI_CR2_TSIZE_Pos);
SPI2->CR2 |= (0<<SPI_CR2_TSER_Pos);
	
SPI2->CR1 |= SPI_CR1_SPE; //enable SPI	
}


#endif
