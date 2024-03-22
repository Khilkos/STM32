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
	ADC->CCR |= 3UL<<ADC_CCR_ADCPRE_Pos; //set prescaler 8 (3 ������������� �������� = �������� �� 8)
	ADC1->SQR1 |= (1UL<<ADC_SQR1_L_Pos); //��������� ���������� ������� � ������� ���
	ADC1->SQR3 &= ~(0x1fUL<<ADC_SQR3_SQ1_Pos); //��������� ������ ������� � ������� ��� ������ 0
	ADC1->SQR3 |= 1UL<<ADC_SQR3_SQ2_Pos; //��������� ������ ������� � ������� ��� ������ 1
//	ADC1->SQR3 |= 2UL<<ADC_SQR3_SQ2_Pos;	//��������� ������ ������� � ������� ��� ������ 2
	ADC1->SMPR2 |= 7UL<<ADC_SMPR2_SMP0_Pos; //����� ������� �������������, ����������� 7
//	ADC1->CR1 |= 1UL<<ADC_CR1_RES_Pos; //����� ����������� ���
//	ADC1->CR1 |= ADC_CR1_EOCIE; //���������� ���������� �� ���
//	NVIC->ISER[0]=( 1<<18); //���������� ���������� � ����������� ����������
	ADC1->CR1 |= ADC_CR1_SCAN;	//��������� ������ ����������� �������
//	ADC1->CR2 |= ADC_CR2_CONT; //����������� ����� ������������
	ADC1->CR2 |= ADC_CR2_DMA;	//��������� ������� ���
	ADC1->CR2 |= ADC_CR2_DDS;	//����������� ������ �������� ���
	ADC1->CR2 |= ADC_CR2_ADON;	//��������� ������ ���
	ADC1->CR2 |= ADC_CR2_SWSTART; //������ �������������� ���
}

void ADC_IRQHandler(void)
{
		//	ADC_ch0_count++;
	//		ADC_ch0_summ+=ADC1->DR; //���������� �������� ���� ����������, ����� ������� �������� ���
		//	if (ADC_ch0_count>=ADC_Average_val) {ADC_ch0=(ADC_ch0_summ/ADC_Average_val); ADC_ch0_count=0; ADC_ch0_summ=0; }
		//	ADC1->CR2 |=ADC_CR2_SWSTART; 
}
//===========================================
void ADC1_F4_via_DMA_2ch_Init (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC->CCR |= 3UL<<ADC_CCR_ADCPRE_Pos; //set prescaler 8 (3 ������������� �������� = �������� �� 8)
	ADC1->SQR1 |= ((2-1)<<ADC_SQR1_L_Pos); //��������� ���������� ������� � ������� ���
	ADC1->SQR3 &= ~(0x1fUL<<ADC_SQR3_SQ1_Pos); //��������� ������ ������� � ������� ��� ������ 0
	ADC1->SQR3 |= 1UL<<ADC_SQR3_SQ2_Pos; //��������� ������ ������� � ������� ��� ������ 1
	ADC1->SMPR2 |= 7UL<<ADC_SMPR2_SMP0_Pos; //����� ������� �������������, ����������� 7
	ADC1->CR1 |= ADC_CR1_SCAN;	//��������� ������ ����������� �������
	ADC1->CR2 |= ADC_CR2_DMA;	//��������� ������� ���
	ADC1->CR2 |= ADC_CR2_DDS;	//����������� ������ �������� ���
	ADC1->CR2 |= ADC_CR2_ADON;	//��������� ������ ���
	ADC1->CR2 |= ADC_CR2_SWSTART; //������ �������������� ���
}
//============================================
void DMA_F4_ADC_init (void)
{
if (DMA2_Stream0->CR & DMA_SxCR_EN)
	{
		DMA2_Stream0->CR &= ~(DMA_SxCR_EN);
		while (DMA2_Stream0->CR & DMA_SxCR_EN) __NOP();
	}
DMA2->LIFCR |=DMA_LIFCR_CTCIF0;//����� ����� ���������� - ���������� ��������
DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;	//����� ���������
DMA2_Stream0->M0AR = (uint32_t)ADC_DMA_val;		//����� ������
DMA2_Stream0->NDTR = 2;	//���������� ������ ������������ � ���
DMA2_Stream0->CR &= ~(0x7UL<<DMA_SxCR_CHSEL_Pos); //����� � ������ ���
DMA2_Stream0->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA2_Stream0->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA2_Stream0->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA2_Stream0->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA2_Stream0->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA2_Stream0->CR |= 0x1UL<<DMA_SxCR_PSIZE_Pos; //������ ������ ��������� 16 ���
DMA2_Stream0->CR |= 0x1UL<<DMA_SxCR_MSIZE_Pos; //������ ������ ������ 16 ���
DMA2_Stream0->CR |= DMA_SxCR_CIRC;	//��������� �����	
DMA2_Stream0->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[1]=( 1<<24);	//��������� ���������� ���2 ����� 0
DMA2_Stream0->CR |=DMA_SxCR_EN; //��������� ���
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
