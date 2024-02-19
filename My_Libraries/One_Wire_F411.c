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
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)temp_send_buf;		//����� ������
DMA1_Stream6->NDTR = size_buf*8;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;

	USART_F411_DMAT_ON();

DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���

}


//===================================================

//===================================================
void DMA_F411_One_Wire_Recive (uint8_t size_buf, uint8_t* recive_buf)
{		static uint8_t temp_recive_buf[64];
		USART_F411_set_115200_baud();
	for (uint8_t i=0; i<size_buf*8; i++)
		{ temp_recive_buf[i]=0xff;}
		
if (DMA1_Stream5->CR & DMA_SxCR_EN)
	{
		DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream5->CR & DMA_SxCR_EN) __NOP();
	}	
//	if (GPIOB->IDR & (1<<14)) GPIOB->BSRR=1U<<(14+res); else GPIOB->BSRR=1U<<14;
	USART2->DR;
	USART2->DR;
DMA1_Stream5->CR=0;
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//����� ����� ���������� - ���������� ��������
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream5->M0AR = (uint32_t)recive_buf;		//����� ������
DMA1_Stream5->NDTR = size_buf*8;	//���������� ������ ������������ � ���
DMA1_Stream5->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream5->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA1_Stream5->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA1_Stream5->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream5->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream5->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream5->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<16);	//��������� ���������� ���1 ����� 6

	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)temp_recive_buf;		//����� ������
DMA1_Stream6->NDTR = size_buf*8;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;

USART_F411_DMA_ON();	

	DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	
	DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���
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
		
if (DMA1_Stream5->CR & DMA_SxCR_EN)
	{
		DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream5->CR & DMA_SxCR_EN) __NOP();
	}	
//	if (GPIOB->IDR & (1<<14)) GPIOB->BSRR=1U<<(14+res); else GPIOB->BSRR=1U<<14;
	USART2->DR;
	USART2->DR;
DMA1_Stream5->CR=0;
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//����� ����� ���������� - ���������� ��������
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream5->M0AR = (uint32_t)recive_buf;		//����� ������
DMA1_Stream5->NDTR = 8;	//���������� ������ ������������ � ���
DMA1_Stream5->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream5->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA1_Stream5->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA1_Stream5->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream5->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream5->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream5->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<16);	//��������� ���������� ���1 ����� 6
	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)temp_send_buf;		//����� ������
DMA1_Stream6->NDTR = 8;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;

USART_F411_DMA_ON();	

	DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	
	DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���
}

//===================================================
void DMA1_Stream6_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF6)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
			while (!(USART2->SR & USART_SR_TC)) __NOP();
			DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
			if (!(DMA1_Stream5->CR & DMA_SxCR_EN)) DMA_busy=0;
			USART_F411_DMAT_OFF();
		}
}	
//===================================================
void DMA1_Stream5_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF5)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
			DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
			DMA_busy=0;
			USART_F411_DMAR_OFF();
		}
}	

