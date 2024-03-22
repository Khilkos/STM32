#include "ADC.h"

#define ADC_Average_val 50
static uint16_t ADC_DMA_val[2]={0,0};
uint32_t ADC_main_count=0;

uint32_t ADC_ch0=0;
uint32_t ADC_ch0_summ = 0;
uint32_t ADC_ch0_count =0;

uint32_t ADC_ch1=0;
uint32_t ADC_ch1_summ = 0;
uint32_t ADC_ch1_count =0;

uint32_t ADC_ch2=0;
uint32_t ADC_ch2_summ = 0;
uint32_t ADC_ch2_count =0;

void ADC1_F411_Init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC->CCR |= 3UL<<ADC_CCR_ADCPRE_Pos; //set prescaler 8 (3 макксимальное значение = делителю на 8)
	ADC1->SQR1 |= (1UL<<ADC_SQR1_L_Pos); //установка количества каналов в очереди АЦП
	ADC1->SQR3 &= ~(0x1fUL<<ADC_SQR3_SQ1_Pos); //установка первым каналом в очереди АЦП канала 0
	ADC1->SQR3 |= 1UL<<ADC_SQR3_SQ2_Pos; //установка вторым каналом в очереди АЦП канала 1
//	ADC1->SQR3 |= 2UL<<ADC_SQR3_SQ2_Pos;	//установка вторым каналом в очереди АЦП канала 2
	ADC1->SMPR2 |= 7UL<<ADC_SMPR2_SMP0_Pos; //выбор времени семплирования, максимально 7
//	ADC1->CR1 |= 1UL<<ADC_CR1_RES_Pos; //выбор разрядности АЦП
//	ADC1->CR1 |= ADC_CR1_EOCIE; //разрешение прерываний от АЦП
//	NVIC->ISER[0]=( 1<<18); //разрешение прерываний в контроллере прерываний
	ADC1->CR1 |= ADC_CR1_SCAN;	//включение режима сканироания каналов
//	ADC1->CR2 |= ADC_CR2_CONT; //непрерывный режим сканирования
	ADC1->CR2 |= ADC_CR2_DMA;	//включение запроса ДМА
	ADC1->CR2 |= ADC_CR2_DDS;	//непрерывная выдача запросов ДМА
	ADC1->CR2 |= ADC_CR2_ADON;	//включение модуля АЦП
	ADC1->CR2 |= ADC_CR2_SWSTART; //запуск преобразования АЦП
}

void ADC_IRQHandler(void)
{
		//	ADC_ch0_count++;
	//		ADC_ch0_summ+=ADC1->DR; //необходимо сбросить флаг прерывания, можно чтением регистра АЦП
		//	if (ADC_ch0_count>=ADC_Average_val) {ADC_ch0=(ADC_ch0_summ/ADC_Average_val); ADC_ch0_count=0; ADC_ch0_summ=0; }
		//	ADC1->CR2 |=ADC_CR2_SWSTART; 
}
//===========================================
void ADC1_F4_via_DMA_2ch_Init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC->CCR |= 3UL<<ADC_CCR_ADCPRE_Pos; //set prescaler 8 (3 макксимальное значение = делителю на 8)
	ADC1->SQR1 |= ((2-1)<<ADC_SQR1_L_Pos); //установка количества каналов в очереди АЦП
	ADC1->SQR3 &= ~(0x1fUL<<ADC_SQR3_SQ1_Pos); //установка первым каналом в очереди АЦП канала 0
	ADC1->SQR3 |= 1UL<<ADC_SQR3_SQ2_Pos; //установка вторым каналом в очереди АЦП канала 1
	ADC1->SMPR2 |= 7UL<<ADC_SMPR2_SMP0_Pos; //выбор времени семплирования, максимально 7
	ADC1->CR1 |= ADC_CR1_SCAN;	//включение режима сканироания каналов
	ADC1->CR2 |= ADC_CR2_DMA;	//включение запроса ДМА
	ADC1->CR2 |= ADC_CR2_DDS;	//непрерывная выдача запросов ДМА
	ADC1->CR2 |= ADC_CR2_ADON;	//включение модуля АЦП
	ADC1->CR2 |= ADC_CR2_SWSTART; //запуск преобразования АЦП
}
//============================================
void DMA_F4_ADC_init (void)
{
if (DMA2_Stream0->CR & DMA_SxCR_EN)
	{
		DMA2_Stream0->CR &= ~(DMA_SxCR_EN);
		while (DMA2_Stream0->CR & DMA_SxCR_EN) __NOP();
	}
DMA2->LIFCR |=DMA_LIFCR_CTCIF0;//сброс флага прерывания - завершение передачи
DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;	//адрес перефирии
DMA2_Stream0->M0AR = (uint32_t)ADC_DMA_val;		//адрес памяти
DMA2_Stream0->NDTR = 2;	//количество данный передаваемых в ДМА
DMA2_Stream0->CR &= ~(0x7UL<<DMA_SxCR_CHSEL_Pos); //выбор о канала ДМА
DMA2_Stream0->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //высокий приоритет потока
DMA2_Stream0->FCR  &= ~(DMA_SxFCR_DMDIS); //прямой домтуп без измользования FIFO
DMA2_Stream0->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //направление потока данных из перефирии в память
DMA2_Stream0->CR |= DMA_SxCR_MINC; //инкремент памяти включить
DMA2_Stream0->CR &= ~DMA_SxCR_PINC; //инкремент перефирии отключить
DMA2_Stream0->CR |= 0x1UL<<DMA_SxCR_PSIZE_Pos; //размер потока перефирии 16 бит
DMA2_Stream0->CR |= 0x1UL<<DMA_SxCR_MSIZE_Pos; //размер потока памяти 16 бит
DMA2_Stream0->CR |= DMA_SxCR_CIRC;	//кольцевой режим	
DMA2_Stream0->CR |= DMA_SxCR_TCIE; //включение прерываний при завершении передачи
NVIC->ISER[1]=( 1<<24);	//включение прерывания ДМА2 поток 0
DMA2_Stream0->CR |=DMA_SxCR_EN; //включение ДМА
}

//================================================
void DMA2_Stream0_IRQHandler(void)
{
	if (DMA2->LISR & DMA_LISR_TCIF0)
		{
			DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
			
			ADC_main_count++;
					
			ADC_ch0_summ+=ADC_DMA_val[0];
			ADC_ch1_summ+=ADC_DMA_val[1];
			if (ADC_main_count>=ADC_Average_val) 
				{
					ADC_main_count=0;
					ADC_ch0=(ADC_ch0_summ/ADC_Average_val);
					ADC_ch1=(ADC_ch1_summ/ADC_Average_val);
					ADC_ch0_summ=0;
					ADC_ch1_summ=0;
				}
			ADC1->CR2 |=ADC_CR2_SWSTART; 	
		}
//			GPIOB->BSRR =1<<14;
}	

//=================================================
