#include "USART.h"

uint32_t USART_DR_RX=0;

void USART_F4_init (USART_TypeDef * USARTx)
{
if (USARTx == USART1)	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включение тактирования усар1
if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // включение тактирования усар2

USARTx->CR1 &= ~USART_CR1_M;	//длина передаваемого пакета 8 бит
USARTx->CR2 &= ~(3UL<<USART_CR2_STOP_Pos); //установка 1 стоп бита
USART_F4_set_115200_baud (USART1);
USARTx->CR1 |= USART_CR1_TE; //включение передатчика
USARTx->CR1 |= USART_CR1_RE; //включение приемника
USARTx->CR1 |= USART_CR1_UE; //USART enable
// USART2->DR=123;
}

//=======================================
void USART_F4_set_9600_baud (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->BRR = 0;
USARTx->BRR |= 273UL<<USART_BRR_DIV_Mantissa_Pos; //set usart baud 9600 //312 для 48МГц
USARTx->BRR |= 7UL<<USART_BRR_DIV_Fraction_Pos;	//8 для 48МГц
//USART2->CR1 |= USART_CR1_UE;	
}
//=======================================
void USART_F4_set_115200_baud (USART_TypeDef * USARTx)
{
//USART2->CR1 &= ~USART_CR1_UE;
USARTx->BRR = 0;
USARTx->BRR |= 22UL<<USART_BRR_DIV_Mantissa_Pos; //26 для 48МГц
USARTx->BRR |= 13UL<<USART_BRR_DIV_Fraction_Pos;	//1 для 48Мгц
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

	

