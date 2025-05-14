#include "DMA.h"

#ifdef STM32F4
void DMA_F4_init (void)
{
RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN | RCC_AHB1ENR_DMA1EN;
}

struct DMA_STM_F4_init_param DMA_STM_F4;

//==========================================
void DMA_F4_param_init (void)
{
uint32_t temp=0;
_Bool bit_temp=0;
if (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN)
	{
		DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_EN);
		while (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN) __NOP();
	}
//����� ����� ���������� - ���������� ��������
//if (DMA_STM_F4.DMA_Stream)	
//DMA_STM_F4.DMA_Number->LIFCR |=DMA_LIFCR_CTCIF0;
//����� ���������	
DMA_STM_F4.DMA_Stream->PAR = (uint32_t)DMA_STM_F4.DMA_Peripheral_address;	
//����� ������	
DMA_STM_F4.DMA_Stream->M0AR = (uint32_t)DMA_STM_F4.DMA_Memory_address;	
//���������� ������ ������������ � ���	
DMA_STM_F4.DMA_Stream->NDTR = DMA_STM_F4.DMA_Quantity;	
//�����  ������ ���	
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CHSEL_Msk);
DMA_STM_F4.DMA_Stream->CR |= (DMA_STM_F4.DMA_Chanel<<DMA_SxCR_CHSEL_Pos); 
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PL_Msk);
//��������� ������
	temp=DMA_STM_F4.DMA_Prioroty;
	if (DMA_STM_F4.DMA_Prioroty>4) temp=3;
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_PL_Pos; 
DMA_STM_F4.DMA_Stream->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
//����������� ������ ������ ��������� <-> ������	
temp=DMA_STM_F4.DMA_Data_transfer_direction;
if (DMA_STM_F4.DMA_Data_transfer_direction>3) temp=0;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_DIR_Msk);
DMA_STM_F4.DMA_Stream->CR |= (temp<<DMA_SxCR_DIR_Pos);
//��������� ������
bit_temp=DMA_STM_F4.DMA_Memory_inc;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_MINC_Msk); 	
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_MINC_Pos; 
//��������� ��������� 	
bit_temp=DMA_STM_F4.DMA_Peripheral_inc;	
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PINC_Msk); 	
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_PINC_Pos;
//������ ������ ��������� 
temp=DMA_STM_F4.DMA_Peripheral_data_size;
if (DMA_STM_F4.DMA_Peripheral_data_size>3) temp=2;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PSIZE_Msk);
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_PSIZE_Pos; 
//������ ������ ������ 
temp=DMA_STM_F4.DMA_Memory_data_size;
if (DMA_STM_F4.DMA_Memory_data_size>3) temp=2;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_MSIZE_Msk);
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_MSIZE_Pos; 
//��������� �����	
bit_temp=DMA_STM_F4.DMA_Circular_mode;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CIRC_Msk);
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_CIRC_Pos;
//��������� ���������� ��� ���������� ��������
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_TCIE; 
//��������� ���������� ���
if (DMA_STM_F4.DMA_Interrupt<32) NVIC->ISER[0]=( 1UL<<DMA_STM_F4.DMA_Interrupt);
if (DMA_STM_F4.DMA_Interrupt>=32 && DMA_STM_F4.DMA_Interrupt<64) NVIC->ISER[1]=( 1UL<<(DMA_STM_F4.DMA_Interrupt-32));
if (DMA_STM_F4.DMA_Interrupt>=64 && DMA_STM_F4.DMA_Interrupt<96) NVIC->ISER[2]=( 1UL<<(DMA_STM_F4.DMA_Interrupt-64));
//��������� ���
DMA_STM_F4.DMA_Stream->CR |=DMA_SxCR_EN;

}

//================================================
#ifdef DMA1_Stream5_IRQHandler_define
void DMA1_Stream5_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF5)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
			if (!(DMA1_Stream5->CR & DMA_SxCR_CIRC)) 
			DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
			DMA1_Stream5_IRQHandler_User();
		}
}	
#endif
//===============================================
#ifdef DMA1_Stream6_IRQHandler_define
void DMA1_Stream6_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF6)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
			if (!(DMA1_Stream6->CR & DMA_SxCR_CIRC)) 
			DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
			DMA1_Stream6_IRQHandler_User();
		}
}	
#endif
//===================================================
#ifdef DMA2_Stream0_IRQHandler_define
void DMA2_Stream0_IRQHandler(void)
{
if (DMA2->LISR & DMA_LISR_TCIF0)
	{
			DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
			if (!(DMA2_Stream0->CR & DMA_SxCR_CIRC)) 
			DMA2_Stream0->CR &=~DMA_SxCR_EN;
			DMA2_Stream0_IRQHandler_User();
			
	}
}	
#endif
//================================================
//===============================================
#ifdef DMA2_Stream2_IRQHandler_define
void DMA2_Stream2_IRQHandler(void)
{
	if (DMA2->LISR & DMA_LISR_TCIF2)
		{
		//	__disable_irq (); // ��������� ����������
			DMA2->LIFCR |= DMA_LIFCR_CTCIF2;
			if (!(DMA2_Stream2->CR & DMA_SxCR_CIRC)) 
			DMA2_Stream2->CR &= ~(DMA_SxCR_EN);
			DMA2_Stream2_IRQHandler_User();
			//__enable_irq ();  // ��������� ����������
		}
}	
#endif
//===================================================
//================================================
#ifdef DMA2_Stream5_IRQHandler_define
void DMA2_Stream5_IRQHandler(void)
{
	if (DMA2->HISR & DMA_HISR_TCIF5)
		{
			DMA2->HIFCR |= DMA_HIFCR_CTCIF5;
			if (!(DMA2_Stream5->CR & DMA_SxCR_CIRC)) 
			DMA2_Stream5->CR &= ~(DMA_SxCR_EN);
			DMA2_Stream5_IRQHandler_User();
		}
}	
#endif
//===============================================
#ifdef DMA2_Stream6_IRQHandler_define
void DMA2_Stream7_IRQHandler(void)
{
	if (DMA2->HISR & DMA_HISR_TCIF7)
		{
			DMA2->HIFCR |= DMA_HIFCR_CTCIF6;
			if (!(DMA2_Stream7->CR & DMA_SxCR_CIRC)) 
			DMA2_Stream7->CR &= ~(DMA_SxCR_EN);
			DMA2_Stream7_IRQHandler_User();
		}
}	
#endif
//===============================================















#endif

//***********************************************************************
//
//***********************************************************************
#ifdef STM32H7

struct DMA_H7_init DMA_H7;

void DMA_H7_init (void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

if (DMA_H7.DMA_Stream->CR & DMA_SxCR_EN) 
	{
		DMA_H7.DMA_Stream->CR &= ~(DMA_SxCR_EN);
		while (DMA_H7.DMA_Stream->CR & DMA_SxCR_EN) __NOP();
	}
DMA_H7.DMA_Stream->PAR = (uint32_t)DMA_H7.DMA_Peripheral_address;

DMA_H7.DMA_Stream->M0AR = (uint32_t)DMA_H7.DMA_Memory_address;

DMA_H7.DMA_Stream->NDTR = DMA_H7.DMA_Quantity;

if (DMA_H7.DMA_Stream == DMA1_Stream0)
{DMAMUX1_Channel0->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel0->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream0
}	
if (DMA_H7.DMA_Stream == DMA1_Stream1)
{DMAMUX1_Channel1->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel1->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream1
}	
if (DMA_H7.DMA_Stream == DMA1_Stream2)
{DMAMUX1_Channel2->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel2->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream2
}	
if (DMA_H7.DMA_Stream == DMA1_Stream3)
{DMAMUX1_Channel3->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel3->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream3
}	
if (DMA_H7.DMA_Stream == DMA1_Stream4)
{DMAMUX1_Channel4->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel4->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream4
}	
if (DMA_H7.DMA_Stream == DMA1_Stream5)
{
DMAMUX1_Channel5->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel5->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream5
}	
if (DMA_H7.DMA_Stream == DMA1_Stream6)
{DMAMUX1_Channel6->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel6->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream6
}	
if (DMA_H7.DMA_Stream == DMA1_Stream7)
{DMAMUX1_Channel7->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel7->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA1_Stream7
}	
if (DMA_H7.DMA_Stream == DMA2_Stream0)
{DMAMUX1_Channel8->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel8->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream0
}	
if (DMA_H7.DMA_Stream == DMA2_Stream1)
{
DMAMUX1_Channel9->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel9->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream1
}	
if (DMA_H7.DMA_Stream == DMA2_Stream2)
{DMAMUX1_Channel10->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel10->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream2
}	
if (DMA_H7.DMA_Stream == DMA2_Stream3)
{DMAMUX1_Channel11->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel11->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream3
}	
if (DMA_H7.DMA_Stream == DMA2_Stream4)
{DMAMUX1_Channel12->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel12->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream4
}	
if (DMA_H7.DMA_Stream == DMA2_Stream5)
{DMAMUX1_Channel13->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel13->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream5
}	
if (DMA_H7.DMA_Stream == DMA2_Stream6)
{DMAMUX1_Channel14->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel14->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream6
}	
if (DMA_H7.DMA_Stream == DMA2_Stream7)
{DMAMUX1_Channel15->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel15->CCR |= (uint32_t)DMA_H7.DMA_Request_source<<DMAMUX_CxCR_DMAREQ_ID_Pos;//����� ��������� ��� DMA ������ DMA2_Stream7
}	

DMA_H7.DMA_Stream->CR &= ~DMA_SxCR_PFCTRL_Msk; 
DMA_H7.DMA_Stream->CR |= (uint32_t)DMA_H7.DMA_flow_control<<DMA_SxCR_PFCTRL_Pos; //����=0 - ������������ ������ �������� DMA, ����=1 - �������������� ����������

if (DMA_H7.DMA_Prioroty>=3) DMA_H7.DMA_Prioroty=3;
DMA_H7.DMA_Stream->CR &=~DMA_SxCR_PL_Msk;
DMA_H7.DMA_Stream->CR |= (uint32_t)DMA_H7.DMA_Prioroty<<DMA_SxCR_PL_Pos; //��������� ������: 0-Low, 1-Medium, 2-High, 3-Very high

if(DMA_H7.DMA_Memory_data_size>=2) DMA_H7.DMA_Memory_data_size=2;
DMA_H7.DMA_Stream->CR &=~DMA_SxCR_MSIZE_Msk;
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Memory_data_size<<DMA_SxCR_MSIZE_Pos; //������ ������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved	

if(DMA_H7.DMA_Peripheral_data_size>=2) DMA_H7.DMA_Peripheral_data_size=2;
DMA_H7.DMA_Stream->CR &=~DMA_SxCR_PSIZE_Msk;
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Peripheral_data_size<<DMA_SxCR_PSIZE_Pos; //������ ��������������� ����������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved

if(DMA_H7.DMA_Data_transfer_direction>=2) DMA_H7.DMA_Data_transfer_direction=2;
DMA_H7.DMA_Stream->CR &=~DMA_SxCR_DIR_Msk;
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Data_transfer_direction<<DMA_SxCR_DIR_Pos; //����������� �������� DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved


DMA_H7.DMA_Stream->CR &=~DMA_SxCR_MINC_Msk;
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Memory_inc<<DMA_SxCR_MINC_Pos; //��������� ������: 0-����, 1-�������
	
DMA_H7.DMA_Stream->CR &=~DMA_SxCR_PINC_Msk;	
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Peripheral_inc<<DMA_SxCR_PINC_Pos; //��������� ���������: 0-����, 1-�������

DMA_H7.DMA_Stream->CR &=~DMA_SxCR_CIRC_Msk;
DMA_H7.DMA_Stream->CR |=(uint32_t)DMA_H7.DMA_Circular_mode<<DMA_SxCR_CIRC_Pos; //����������� �����: 0-��������, 1-�������

if (DMA_H7.DMA_Transfer_complete_interrupt) 
{	DMA_H7.DMA_Stream->CR |=DMA_SxCR_TCIE;
	if (DMA_H7.DMA_Interrupt<32) NVIC->ISER[0]=( 1UL<<DMA_H7.DMA_Interrupt);
	if (DMA_H7.DMA_Interrupt>=32 && DMA_H7.DMA_Interrupt<64) NVIC->ISER[1]=( 1UL<<(DMA_H7.DMA_Interrupt-32));
	if (DMA_H7.DMA_Interrupt>=64 && DMA_H7.DMA_Interrupt<96) NVIC->ISER[2]=( 1UL<<(DMA_H7.DMA_Interrupt-64));
}

if (DMA_H7.DMA_Transfer_complete_interrupt)
{	if(DMA_H7.DMA_Interrupt_Priority>15) DMA_H7.DMA_Interrupt_Priority=15;
	NVIC->IP[DMA_H7.DMA_Interrupt]=DMA_H7.DMA_Interrupt_Priority*16; // ��������� ���������� (���� �� 4 �����)
}


DMA_H7.DMA_Stream->CR |=DMA_SxCR_EN; //��������� DMA
	
}


//===============================================
#ifdef DMA1_Stream0_IRQHandler_define
void DMA1_Stream0_IRQHandler(void)
{
	if (DMA1->LISR & DMA_LISR_TCIF0)
		{
	//		NVIC->ICPR[0] |=1<<DMA1_Stream0_IRQn;
			DMA1->LIFCR |= DMA_LIFCR_CTCIF0;
		while (DMA1->LISR & DMA_LISR_TCIF0) __NOP();
			if (!(DMA1_Stream0->CR & DMA_SxCR_CIRC)) 
			DMA1_Stream0->CR &= ~(DMA_SxCR_EN);
			DMA1_Stream0_IRQHandler_User();
		//	NVIC->IABR[0]|=1<<DMA1_Stream0_IRQn;
		}
}	
#endif
//===================================================





#endif
