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
//��������� ����������� ���	
	if (ADC_Init.ADC_Resolution==6) temp=3; 
	if (ADC_Init.ADC_Resolution==8) temp=2;
	if (ADC_Init.ADC_Resolution==10) temp=1;	
	if (ADC_Init.ADC_Resolution==12) temp=0;
	if (temp!=3 && temp!=2 && temp!=1) temp=0;
	ADC1->CR1 &=~(ADC_CR1_RES_Msk);
	ADC1->CR1|=temp<<ADC_CR1_RES_Pos;
//��������� ������ ����������� �������	
	ADC1->CR1 |= ADC_CR1_SCAN;	
//����� ����������� PCLK2 ��� ������ ���
	if (ADC_Init.ADC_Prescaler==2) temp=0;
	if (ADC_Init.ADC_Prescaler==4) temp=1;
	if (ADC_Init.ADC_Prescaler==6) temp=2;
	if (ADC_Init.ADC_Prescaler==8) temp=3;
	if(temp!=0 && temp!=1 && temp!=2) temp=3;
	ADC->CCR &=~(ADC_CCR_ADCPRE_Msk);
	ADC->CCR |=temp<<ADC_CCR_ADCPRE_Pos;
//��������� ���������� ������� � ������� ���
	temp=ADC_Init.ADC_Quantity_of_chanel;
	if (temp>16) temp=1;
	ADC1->SQR1 &=~(ADC_SQR1_L_Msk);
	ADC1->SQR1 |= (temp-1)<<ADC_SQR1_L_Pos;
//��������� ������� ������ � ������� ���
	temp=ADC_Init.ADC_ch1;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ1_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ1_Pos;
//��������� ������� ������ � ������� ���
	temp=ADC_Init.ADC_ch2;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ2_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ2_Pos;
//��������� �������� ������ � ������� ���
	temp=ADC_Init.ADC_ch3;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ3_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ3_Pos;
//��������� ���������� ������ � ������� ���
	temp=ADC_Init.ADC_ch4;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ4_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ4_Pos;
//��������� ������ ������ � ������� ���
	temp=ADC_Init.ADC_ch5;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ5_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ5_Pos;
//��������� ������� ������ � ������� ���
	temp=ADC_Init.ADC_ch6;
	if (temp>15) temp=0;
	ADC1->SQR3 &=~(ADC_SQR3_SQ6_Msk);
	ADC1->SQR3 |= temp<<ADC_SQR3_SQ6_Pos;
//��������� �������� ������ � ������� ���
	temp=ADC_Init.ADC_ch7;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ7_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ7_Pos;
//��������� �������� ������ � ������� ���
	temp=ADC_Init.ADC_ch8;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ8_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ8_Pos;
//��������� �������� ������ � ������� ���
	temp=ADC_Init.ADC_ch9;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ9_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ9_Pos;
//��������� �������� ������ � ������� ���
	temp=ADC_Init.ADC_ch10;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ10_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ10_Pos;
//��������� ������������ ������ � ������� ���
	temp=ADC_Init.ADC_ch11;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ11_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ11_Pos;
//��������� ������������ ������ � ������� ���
	temp=ADC_Init.ADC_ch12;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR2_SQ12_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR2_SQ12_Pos;
//��������� ������������ ������ � ������� ���
	temp=ADC_Init.ADC_ch13;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ13_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ13_Pos;
//��������� �������������� ������ � ������� ���
	temp=ADC_Init.ADC_ch14;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ14_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ14_Pos;
//��������� ������������ ������ � ������� ���
	temp=ADC_Init.ADC_ch15;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ15_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ15_Pos;
//��������� �������������� ������ � ������� ���
	temp=ADC_Init.ADC_ch16;
	if (temp>15) temp=0;
	ADC1->SQR2 &=~(ADC_SQR1_SQ16_Msk);
	ADC1->SQR2 |= temp<<ADC_SQR1_SQ16_Pos;
//����� ������� �������������
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
	ADC1->CR2 |= ADC_CR2_DMA;	//��������� ������� ���
	ADC1->CR2 |= ADC_CR2_DDS;	//����������� ������ �������� ���
	ADC1->CR2 |= ADC_CR2_ADON;	//��������� ������ ���
	ADC1->CR2 |= ADC_CR2_SWSTART; //������ �������������� ���
}

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
