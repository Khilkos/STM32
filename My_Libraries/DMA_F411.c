#include "DMA_F411.h"


void DMA_F411_init (void)
{
RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN | RCC_AHB1ENR_DMA1EN;
}

//=============================================


//=================================================
void DMA_F411_DS18B20_convert_T (void)
{
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)convert_T;		//����� ������
DMA1_Stream6->NDTR = 16;	//���������� ������ ������������ � ���
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
void DMA_F411_DS18B20_read_scratch (void)
{
	
if (DMA1_Stream5->CR & DMA_SxCR_EN)
	{
		DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream5->CR & DMA_SxCR_EN) __NOP();
	}	
	
DMA1_Stream5->CR=0;
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//����� ����� ���������� - ���������� ��������
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream5->M0AR = (uint32_t)DMA_read_temp;		//����� ������
DMA1_Stream5->NDTR = 32;	//���������� ������ ������������ � ���
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
//DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	

	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)read_scratch;		//����� ������
DMA1_Stream6->NDTR = 32;	//���������� ������ ������������ � ���
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
//USART_F411_restart();		

	DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	
	//delay_ms(10);
	DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���
}
//==========================================================================











