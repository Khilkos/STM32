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
//сброс флага прерывания - завершение передачи
//if (DMA_STM_F4.DMA_Stream)	
//DMA_STM_F4.DMA_Number->LIFCR |=DMA_LIFCR_CTCIF0;
//адрес перефирии	
DMA_STM_F4.DMA_Stream->PAR = (uint32_t)DMA_STM_F4.DMA_Peripheral_address;	
//адрес памяти	
DMA_STM_F4.DMA_Stream->M0AR = (uint32_t)DMA_STM_F4.DMA_Memory_address;	
//количество данный передаваемых в ДМА	
DMA_STM_F4.DMA_Stream->NDTR = DMA_STM_F4.DMA_Quantity;	
//выбор  канала ДМА	
DMA_STM_F4.DMA_Stream->CR &= ~(DMA_SxCR_CHSEL_Msk);
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
//включение прерывания ДМА
if (DMA_STM_F4.DMA_Interrupt<32) NVIC->ISER[0]=( 1UL<<DMA_STM_F4.DMA_Interrupt);
if (DMA_STM_F4.DMA_Interrupt>=32 && DMA_STM_F4.DMA_Interrupt<64) NVIC->ISER[1]=( 1UL<<(DMA_STM_F4.DMA_Interrupt-32));
if (DMA_STM_F4.DMA_Interrupt>=64 && DMA_STM_F4.DMA_Interrupt<96) NVIC->ISER[2]=( 1UL<<(DMA_STM_F4.DMA_Interrupt-64));
//включение ДМА
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
		//	__disable_irq (); // запретить прерывания
			DMA2->LIFCR |= DMA_LIFCR_CTCIF2;
			if (!(DMA2_Stream2->CR & DMA_SxCR_CIRC)) 
			DMA2_Stream2->CR &= ~(DMA_SxCR_EN);
			DMA2_Stream2_IRQHandler_User();
			//__enable_irq ();  // разрешить прерывания
		}
}	
#endif
//===================================================

#endif


#ifdef STM32H7

void DMA_H7_init (void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	
if (DMA1_Stream0->CR & DMA_SxCR_EN) 
	{
		DMA1_Stream0->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream0->CR & DMA_SxCR_EN) __NOP();
	}
DMA1_Stream0->PAR = (uint32_t)&SPI1->TXDR;
DMA1_Stream0->M0AR = (uint32_t)ptr;
DMA1_Stream0->NDTR =0;

DMAMUX1_Channel0->CCR &=~ (DMAMUX_CxCR_DMAREQ_ID_Msk);
DMAMUX1_Channel0->CCR |= 38<<DMAMUX_CxCR_DMAREQ_ID_Pos;//выбор источника для DMA потока
	
DMA1_Stream0->CR &= ~DMA_SxCR_PFCTRL_Msk; 
DMA1_Stream0->CR |= 1<<DMA_SxCR_PFCTRL_Pos; //если=0 - контроллером потока является DMA, если=1 - перифирическое устройство

DMA1_Stream0->CR &=~DMA_SxCR_PL_Msk;
DMA1_Stream0->CR |= 0<<DMA_SxCR_PL_Pos; //0-Low, 1-Medium, 2-High, 3-Very high	
	
DMA1_Stream0->CR &=~DMA_SxCR_MSIZE_Msk;
DMA1_Stream0->CR |=2<<DMA_SxCR_MSIZE_Pos; //Размер памяти: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved	
	
DMA1_Stream0->CR &=~DMA_SxCR_PSIZE_Msk;
DMA1_Stream0->CR |=2<<DMA_SxCR_PSIZE_Pos; //Размер перефирического устройства: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
	
DMA1_Stream0->CR &=~DMA_SxCR_MINC_Msk;
DMA1_Stream0->CR |=0<<DMA_SxCR_MINC_Pos; //инкремент памяти: 0-выкл, 1-включен
	
DMA1_Stream0->CR &=~DMA_SxCR_PINC_Msk;	
DMA1_Stream0->CR |=0<<DMA_SxCR_PINC_Pos; //инкремент перефирии: 0-выкл, 1-включен

DMA1_Stream0->CR &=~DMA_SxCR_CIRC_Msk;
DMA1_Stream0->CR |=0<<DMA_SxCR_CIRC_Pos; //циклический режим: 0-выключен, 1-включен

DMA1_Stream0->CR &=~DMA_SxCR_DIR_Msk;
DMA1_Stream0->CR |=1<<DMA_SxCR_DIR_Pos; //направление передачи DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved


//DMA1_Stream0->CR |=DMA_SxCR_EN; //включение DMA
	
}







#endif
