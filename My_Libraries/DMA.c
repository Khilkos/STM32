#include "DMA.h"

void DMA_F4_init (void)
{
RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN | RCC_AHB1ENR_DMA1EN;
}

struct 
{
DMA_TypeDef * DMA_Number; //выбор ДМА напр. - DMA2
DMA_Stream_TypeDef * DMA_Stream;//выбор потока ДМА напр. -  DMA2_Stream0
uint32_t *DMA_Peripheral_address;	//адрес перефирии
uint32_t *DMA_Memory_address;//адрес памяти
uint32_t DMA_Quantity;//количество данный передаваемых в ДМА
uint32_t DMA_Chanel;//выбор канала ДМА

} DMA_STM_F4 ;
//==========================================
void DMA_F4_param_init (void)
{
if (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN)
	{
		DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_EN);
		while (DMA_STM_F4.DMA_Stream->CR & DMA_SxCR_EN) __NOP();
	}
DMA_STM_F4.DMA_Number->LIFCR |=DMA_LIFCR_CTCIF0;//сброс флага прерывания - завершение передачи
DMA_STM_F4.DMA_Stream->PAR = (uint32_t)DMA_STM_F4.DMA_Peripheral_address;	//адрес перефирии
DMA_STM_F4.DMA_Stream->M0AR = (uint32_t)DMA_STM_F4.DMA_Memory_address;		//адрес памяти
DMA_STM_F4.DMA_Stream->NDTR = DMA_STM_F4.DMA_Quantity;	//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CHSEL_Msk);//выбор  канала ДМА
DMA_STM_F4.DMA_Stream->CR |= (DMA_STM_F4.DMA_Chanel<<DMA_SxCR_CHSEL_Pos); 
DMA_STM_F4.DMA_Stream->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //высокий приоритет потока
DMA_STM_F4.DMA_Stream->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
DMA_STM_F4.DMA_Stream->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //направление потока данных из перефирии в память
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_MINC; //инкремент памяти включить
DMA_STM_F4.DMA_Stream->CR &= ~DMA_SxCR_PINC; //инкремент перефирии отключить
DMA_STM_F4.DMA_Stream->CR |= 0x1UL<<DMA_SxCR_PSIZE_Pos; //размер потока перефирии 16 бит
DMA_STM_F4.DMA_Stream->CR |= 0x1UL<<DMA_SxCR_MSIZE_Pos; //размер потока памяти 16 бит
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_CIRC;	//кольцевой режим	
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_TCIE; //включение прерываний при завершении передачи
NVIC->ISER[1]=( 1<<24);	//включение прерывания ДМА2 поток 0
DMA_STM_F4.DMA_Stream->CR |=DMA_SxCR_EN; //включение ДМА
}

//================================================


