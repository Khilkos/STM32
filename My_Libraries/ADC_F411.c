#include "ADC_F411.h"

#define ADC_Average_val 20000

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


