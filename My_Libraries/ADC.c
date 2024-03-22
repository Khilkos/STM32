#include "ADC.h"

#define ADC_Average_val 5
static uint16_t ADC_DMA_val[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t ADC_main_count=0;
uint32_t ADC_ch[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t ADC_ch_summ[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



struct STM_F4_ADC ADC_Init;
//==========================================================
void ADC_F4_init_via_DMA (void)
{
uint32_t temp=0;
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//установка разрядности АЦП	
	if (ADC_Init.ADC_Resolution==6) temp=3; 
	if (ADC_Init.ADC_Resolution==8) temp=2;
	if (ADC_Init.ADC_Resolution==10) temp=1;	
	if (ADC_Init.ADC_Resolution==12) temp=0;
	if (temp!=3 && temp!=2 && temp!=1) temp=0;
	ADC1->CR1 &=~(ADC_CR1_RES_Msk);
	ADC1->CR1|=temp<<ADC_CR1_RES_Pos;
//включение режима сканироания каналов	
	ADC1->CR1 |= ADC_CR1_SCAN;	
//выбор пределителя PCLK2 для работы АЦП
	if (ADC_Init.ADC_Prescaler==2) temp=0;
	if (ADC_Init.ADC_Prescaler==4) temp=1;
	if (ADC_Init.ADC_Prescaler==6) temp=2;
	if (ADC_Init.ADC_Prescaler==8) temp=3;
	if(temp!=0 && temp!=1 && temp!=2) temp=3;
	ADC->CCR &=~(ADC_CCR_ADCPRE_Msk);
	ADC->CCR |=temp<<ADC_CCR_ADCPRE_Pos;
//установка количества каналов в очереди АЦП
	temp=ADC_Init.ADC_Quantity_of_chanel;
	if (temp>16) temp=1;
	ADC1->SQR1 &=~(ADC_SQR1_L_Msk);
	ADC1->SQR1 |= (temp-1)<<ADC_SQR1_L_Pos;
//установка первого канала в очереди АЦП
	temp=ADC_Init.ADC_ch1;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ1_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ1_Pos;
//установка второго канала в очереди АЦП
	temp=ADC_Init.ADC_ch2;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ2_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ2_Pos;
//установка третьего канала в очереди АЦП
	temp=ADC_Init.ADC_ch3;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ3_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ3_Pos;
//установка четвертого канала в очереди АЦП
	temp=ADC_Init.ADC_ch4;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ4_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ4_Pos;
//установка пятого канала в очереди АЦП
	temp=ADC_Init.ADC_ch5;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ5_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ5_Pos;
//установка шестого канала в очереди АЦП
	temp=ADC_Init.ADC_ch6;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ6_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ6_Pos;
//установка седьмого канала в очереди АЦП
	temp=ADC_Init.ADC_ch7;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ7_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ7_Pos;
//установка восьмого канала в очереди АЦП
	temp=ADC_Init.ADC_ch8;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ8_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ8_Pos;
//установка девятого канала в очереди АЦП
	temp=ADC_Init.ADC_ch9;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ9_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ9_Pos;
//установка десятого канала в очереди АЦП
	temp=ADC_Init.ADC_ch10;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ10_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ10_Pos;
//установка одиннацатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch11;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ11_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ11_Pos;
//установка двенадцатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch12;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ12_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ12_Pos;
//установка тринадцатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch13;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ13_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ13_Pos;
//установка четарнадцатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch14;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ14_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ14_Pos;
//установка пятнадцатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch15;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ15_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ15_Pos;
//установка шестьнадцатого канала в очереди АЦП
	temp=ADC_Init.ADC_ch16;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ16_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ16_Pos;
//выбор времени семплирования
	ADC1->SMPR1=0;
	ADC1->SMPR2=0;
	if (ADC_Init.ADC_Sample_time==3) temp=0;
	if (ADC_Init.ADC_Sample_time==15) temp=1;
	if (ADC_Init.ADC_Sample_time==28) temp=2;
	if (ADC_Init.ADC_Sample_time==56) temp=3;
	if (ADC_Init.ADC_Sample_time==84) temp=4;
	if (ADC_Init.ADC_Sample_time==112) temp=5;
	if (ADC_Init.ADC_Sample_time==144) temp=6;
	if (ADC_Init.ADC_Sample_time==480) temp=7;
	if (temp!=0 && temp!=1 && temp!=2 && temp!=3 && temp!=4 && temp!=5 && temp!=6 && temp!=7) temp=7;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP0_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP2_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP3_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP4_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP5_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP6_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP7_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP8_Pos;
	ADC1->SMPR2|=temp<<ADC_SMPR2_SMP9_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP10_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP11_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP12_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP13_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP14_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP15_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP16_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP17_Pos;
	ADC1->SMPR1|=temp<<ADC_SMPR1_SMP18_Pos;
//
	ADC1->CR2 |= ADC_CR2_DMA;	//включение запроса ДМА
	ADC1->CR2 |= ADC_CR2_DDS;	//непрерывная выдача запросов ДМА
	ADC1->CR2 |= ADC_CR2_ADON;	//включение модуля АЦП
	ADC1->CR2 |= ADC_CR2_SWSTART; //запуск преобразования АЦП
}

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
			for (uint8_t i=0; i<16;i++)
				{ADC_ch_summ[i]+=ADC_DMA_val[i];}
			
	if (ADC_main_count>=ADC_Average_val) 
		{
					ADC_main_count=0;
			for (uint8_t i=0; i<16;i++)
				{	ADC_ch[i]=(ADC_ch_summ[i]/ADC_Average_val);
					ADC_ch_summ[i]=0;	}

		}
			ADC1->CR2 |=ADC_CR2_SWSTART; 	
	}
}	

//=================================================
