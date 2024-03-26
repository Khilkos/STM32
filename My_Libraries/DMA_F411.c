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
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//сброс флага прерывания - завершение передачи
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//адрес перефирии
DMA1_Stream6->M0AR = (uint32_t)convert_T;		//адрес памяти
DMA1_Stream6->NDTR = 16;	//количество данный передаваемых в ДМА
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //выбор 4 канала ДМА
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //низкий приоритет потока
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //направление потока данных из памяти в перефирию
DMA1_Stream6->CR |= DMA_SxCR_MINC; //инкремент памяти включить
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //инкремент перефирии отключить
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //размер потока перефирии 8 бит
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //размер потока памяти 8 бит
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//кольцевой режим выключен	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //включение прерываний при завершении передачи
NVIC->ISER[0]=( 1<<17);	//включение прерывания ДМА1 поток 6
USART2->SR &=~USART_SR_TC;
USART_F411_DMAT_ON();

DMA1_Stream6->CR |=DMA_SxCR_EN; //включение ДМА



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
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//сброс флага прерывания - завершение передачи
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//адрес перефирии
DMA1_Stream5->M0AR = (uint32_t)DMA_read_temp;		//адрес памяти
DMA1_Stream5->NDTR = 32;	//количество данный передаваемых в ДМА
DMA1_Stream5->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //выбор 4 канала ДМА
DMA1_Stream5->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //высокий приоритет потока
DMA1_Stream5->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //направление потока данных из перефирии в память
DMA1_Stream5->CR |= DMA_SxCR_MINC; //инкремент памяти включить
DMA1_Stream5->CR &= ~DMA_SxCR_PINC; //инкремент перефирии отключить
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //размер потока перефирии 8 бит
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //размер потока памяти 8 бит
DMA1_Stream5->CR &= ~DMA_SxCR_CIRC;	//кольцевой режим выключен	
DMA1_Stream5->CR |= DMA_SxCR_TCIE; //включение прерываний при завершении передачи
NVIC->ISER[0]=( 1<<16);	//включение прерывания ДМА1 поток 6
//DMA1_Stream5->CR |=DMA_SxCR_EN; //включение ДМА	

	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//сброс флага прерывания - завершение передачи
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//адрес перефирии
DMA1_Stream6->M0AR = (uint32_t)read_scratch;		//адрес памяти
DMA1_Stream6->NDTR = 32;	//количество данный передаваемых в ДМА
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //выбор 4 канала ДМА
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //низкий приоритет потока
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //направление потока данных из памяти в перефирию
DMA1_Stream6->CR |= DMA_SxCR_MINC; //инкремент памяти включить
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //инкремент перефирии отключить
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //размер потока перефирии 8 бит
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //размер потока памяти 8 бит
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//кольцевой режим выключен	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //включение прерываний при завершении передачи
NVIC->ISER[0]=( 1<<17);	//включение прерывания ДМА1 поток 6
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;

USART_F411_DMA_ON();	
//USART_F411_restart();		

	DMA1_Stream5->CR |=DMA_SxCR_EN; //включение ДМА	
	//delay_ms(10);
	DMA1_Stream6->CR |=DMA_SxCR_EN; //включение ДМА
}
//==========================================================================











