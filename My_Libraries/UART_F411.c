#include "UART_F411.h"

uint32_t USART_DR_RX=0;

void UART_F411_init (void)
{
RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // включение тактирования усар2
USART2->CR1 &= ~USART_CR1_M;	//длина передаваемого пакета 8 бит
USART2->CR2 &= ~(3UL<<USART_CR2_STOP_Pos); //установка 1 стоп бита
UART_F411_set_9600_baud ();
USART2->CR1 |= USART_CR1_TE; //включение передатчика
USART2->CR1 |= USART_CR1_RE; //включение приемника
USART2->CR1 |= USART_CR1_UE; //USART enable
// USART2->DR=123;
}

//=======================================
void UART_F411_set_9600_baud (void)
{
//USART2->CR1 &= ~USART_CR1_UE;
USART2->BRR = 0;
USART2->BRR |= 312UL<<USART_BRR_DIV_Mantissa_Pos; //set usart baud 9600
USART2->BRR |= 8UL<<USART_BRR_DIV_Fraction_Pos;	
//USART2->CR1 |= USART_CR1_UE;	
}
//=======================================
void UART_F411_set_115200_baud (void)
{
//USART2->CR1 &= ~USART_CR1_UE;
USART2->BRR = 0;
USART2->BRR |= 26UL<<USART_BRR_DIV_Mantissa_Pos; //set usart baud 9600
USART2->BRR |= 1UL<<USART_BRR_DIV_Fraction_Pos;	
//USART2->CR1 |= USART_CR1_UE;	
}

//=======================================
void UART_F411_DMA_ON (void)
{
//USART2->CR1 &= ~USART_CR1_UE;
USART2->CR3 |= USART_CR3_DMAR;
USART2->CR3 |= USART_CR3_DMAT ;
//USART2->CR1 |= USART_CR1_UE;	
}

//=======================================
void UART_F411_DMA_OFF (void)
{
//USART2->CR1 &= ~USART_CR1_UE;
USART2->CR3 &= ~USART_CR3_DMAT;
USART2->CR3 &= ~USART_CR3_DMAR;
//USART2->CR1 |= USART_CR1_UE;	
}

void UART_F411_DMAR_OFF (void)
{
USART2->CR3 &= ~USART_CR3_DMAR;
}

void UART_F411_DMAT_OFF (void)
{
USART2->CR3 &= ~USART_CR3_DMAT;
}

//=========================================
void USART_F411_restart(void)
{
USART2->CR1 &= ~USART_CR1_UE;
USART2->CR1 |= USART_CR1_UE;	
}

	

