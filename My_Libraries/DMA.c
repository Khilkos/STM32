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
uint8_t DMA_Prioroty;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
	uint8_t DMA_Data_transfer_direction;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
_Bool DMA_Memory_inc;	//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
_Bool DMA_Peripheral_inc;////инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
uint8_t DMA_Memory_data_size;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
uint8_t DMA_Peripheral_data_size;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
	_Bool DMA_Circular_mode;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
} DMA_STM_F4 ;
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
DMA_STM_F4.DMA_Number->LIFCR |=DMA_LIFCR_CTCIF0;//сброс флага прерывания - завершение передачи
DMA_STM_F4.DMA_Stream->PAR = (uint32_t)DMA_STM_F4.DMA_Peripheral_address;	//адрес перефирии
DMA_STM_F4.DMA_Stream->M0AR = (uint32_t)DMA_STM_F4.DMA_Memory_address;		//адрес памяти
DMA_STM_F4.DMA_Stream->NDTR = DMA_STM_F4.DMA_Quantity;	//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CHSEL_Msk);//выбор  канала ДМА
DMA_STM_F4.DMA_Stream->CR |= (DMA_STM_F4.DMA_Chanel<<DMA_SxCR_CHSEL_Pos); 
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PL_Msk);
//приоритет потока
	temp=DMA_STM_F4.DMA_Prioroty;
	if (DMA_STM_F4.DMA_Prioroty>4) temp=3;
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_PL_Pos; 
DMA_STM_F4.DMA_Stream->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
//направление потока данных перефирия <-> память	
temp=DMA_STM_F4.DMA_Data_transfer_direction;
if (DMA_STM_F4.DMA_Data_transfer_direction>3) temp=0;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_DIR_Msk);
DMA_STM_F4.DMA_Stream->CR |= (temp<<DMA_SxCR_DIR_Pos);
//инкремент памяти
bit_temp=DMA_STM_F4.DMA_Memory_inc;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_MINC_Msk); 	
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_MINC_Pos; 
//инкремент перефирии 	
bit_temp=DMA_STM_F4.DMA_Peripheral_inc;	
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PINC_Msk); 	
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_PINC_Pos;
//размер потока перефирии 
temp=DMA_STM_F4.DMA_Peripheral_data_size;
if (DMA_STM_F4.DMA_Peripheral_data_size>3) temp=2;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_PSIZE_Msk);
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_PSIZE_Pos; 
//размер потока памяти 
temp=DMA_STM_F4.DMA_Memory_data_size;
if (DMA_STM_F4.DMA_Memory_data_size>3) temp=2;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_MSIZE_Msk);
DMA_STM_F4.DMA_Stream->CR |= temp<<DMA_SxCR_MSIZE_Pos; 
//кольцевой режим	
bit_temp=DMA_STM_F4.DMA_Circular_mode;
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CIRC_Msk);
DMA_STM_F4.DMA_Stream->CR |= (uint32_t)bit_temp<<DMA_SxCR_CIRC_Pos;
//включение прерываний при завершении передачи
DMA_STM_F4.DMA_Stream->CR |= DMA_SxCR_TCIE; 

NVIC->ISER[1]=( 1<<24);	//включение прерывания ДМА2 поток 0
DMA_STM_F4.DMA_Stream->CR |=DMA_SxCR_EN; //включение ДМА
}

//================================================


