#include "DMA.h"

void DMA_F4_init (void)
{
RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN | RCC_AHB1ENR_DMA1EN;
}

struct 
{
DMA_TypeDef * DMA_Number; //����� ��� ����. - DMA2
DMA_Stream_TypeDef * DMA_Stream;//����� ������ ��� ����. -  DMA2_Stream0
uint32_t *DMA_Peripheral_address;	//����� ���������
uint32_t *DMA_Memory_address;//����� ������
uint32_t DMA_Quantity;//���������� ������ ������������ � ���
uint32_t DMA_Chanel;//����� ������ ���

} DMA_STM_F4 ;
//==========================================
void DMA_F4_param_init (void)
{
if (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN)
	{
		DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_EN);
		while (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN) __NOP();
	}
DMA_STM_F4.DMA_Number->LIFCR |=DMA_LIFCR_CTCIF0;//����� ����� ���������� - ���������� ��������
DMA_STM_F4.DMA_Stream->PAR = (uint32_t)DMA_STM_F4.DMA_Peripheral_address;	//����� ���������
DMA_STM_F4.DMA_Stream->M0AR = (uint32_t)DMA_STM_F4.DMA_Memory_address;		//����� ������
DMA_STM_F4.DMA_Stream->NDTR = DMA_STM_F4.DMA_Quantity;	//���������� ������ ������������ � ���
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CHSEL_Msk);//�����  ������ ���
DMA_STM_F4.DMA_Stream->CR |= (DMA_STM_F4.DMA_Chanel<<DMA_SxCR_CHSEL_Pos); 
DMA_STM_F4.DMA_Stream->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA_STM_F4.DMA_Stream->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA_STM_F4.DMA_Stream->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA_STM_F4.DMA_Stream->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA_STM_F4.DMA_Stream->CR |= 0x1UL<<DMA_SxCR_PSIZE_Pos; //������ ������ ��������� 16 ���
DMA_STM_F4.DMA_Stream->CR |= 0x1UL<<DMA_SxCR_MSIZE_Pos; //������ ������ ������ 16 ���
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_CIRC;	//��������� �����	
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[1]=( 1<<24);	//��������� ���������� ���2 ����� 0
DMA_STM_F4.DMA_Stream->CR |=DMA_SxCR_EN; //��������� ���
}

//================================================


