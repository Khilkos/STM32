#include "USART.h"

uint32_t USART_DR_RX=0;

void USART_F4_init (USART_TypeDef * USARTx)
{
if (USARTx == USART1)	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // ��������� ������������ ����1
if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // ��������� ������������ ����2

USARTx->CR1 &= ~USART_CR1_M;	//����� ������������� ������ 8 ���
USARTx->CR2 &= ~(3UL<<USART_CR2_STOP_Pos); //��������� 1 ���� ����
USART_F4_set_115200_baud (USART1);
USARTx->CR1 |= USART_CR1_TE; //��������� �����������
USARTx->CR1 |= USART_CR1_RE; //��������� ���������
USARTx->CR1 |= USART_CR1_UE; //USART enable
// USART2->DR=123;
}

//=======================================
void USART_F4_set_9600_baud (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->BRR = 0;
USARTx->BRR |= 273UL<<USART_BRR_DIV_Mantissa_Pos; //set usart baud 9600 //312 ��� 48���
USARTx->BRR |= 7UL<<USART_BRR_DIV_Fraction_Pos;	//8 ��� 48���
//USART2->CR1 |= USART_CR1_UE;	
}
//=======================================
void USART_F4_set_115200_baud (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->BRR = 0;
USARTx->BRR |= 22UL<<USART_BRR_DIV_Mantissa_Pos; //26 ��� 48���
USARTx->BRR |= 13UL<<USART_BRR_DIV_Fraction_Pos;	//1 ��� 48���
//USART2->CR1 |= USART_CR1_UE;	
}

//=======================================
void USART_F4_DMA_ON (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->CR3 |= USART_CR3_DMAR;
USARTx->CR3 |= USART_CR3_DMAT ;
//USART2->CR1 |= USART_CR1_UE;	
}

//=======================================
void USART_F4_DMAT_ON (USART_TypeDef * USARTx)
{
USARTx->CR3 |= USART_CR3_DMAT ;
}

//=======================================
void USART_F4_DMAR_ON (USART_TypeDef * USARTx)
{
USARTx->CR3 |= USART_CR3_DMAR;
}


//=======================================
void USART_F4_DMA_OFF (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->CR3 &= ~USART_CR3_DMAT;
USARTx->CR3 &= ~USART_CR3_DMAR;
//USART2->CR1 |= USART_CR1_UE;	
}
//======================================
void USART_F4_DMAR_OFF (USART_TypeDef * USARTx)
{
USARTx->CR3 &= ~USART_CR3_DMAR;
}

//=================================
void USART_F4_DMAT_OFF (USART_TypeDef * USARTx)
{
USARTx->CR3 &= ~USART_CR3_DMAT;
}

//=========================================
void USART_F4_restart(USART_TypeDef * USARTx)
{
USARTx->CR1 &= ~USART_CR1_UE;
USARTx->CR1 |= USART_CR1_UE;	
}

	

