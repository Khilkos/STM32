#include "ADC.h"

//#define ADC_Average_val 5
static uint16_t ADC_DMA_val[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t ADC_main_count=0;
uint32_t ADC_ch[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t ADC_ch_summ[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



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
	//-------------------------------------------------
//
DMA2->LIFCR |=DMA_LIFCR_CTCIF0;//����� ����� ���������� - ���������� ��������
DMA_STM_F4.DMA_Number = DMA2;//����� ���, ����. - DMA2
DMA_STM_F4.DMA_Stream = DMA2_Stream0;//����� ������ ��� ����. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = &ADC1->DR ;//����� ���������, �������� (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address =  (void*)(ADC_DMA_val+1) ;//����� ������, �������� (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity = ADC_Init.ADC_Quantity_of_chanel  ;//���������� ������ ������������ � ���
DMA_STM_F4.DMA_Chanel = 0 ;//����� ������ ���
DMA_STM_F4.DMA_Prioroty =  DMA_Priority_low;//��������� ������ - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Peripheral_to_memory ;//����������� ������ ������ ��������� <-> ������: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON ;//��������� ������ DMA_Inc_ON-��������, DMA_Inc_OFF-���������
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF ;//��������� ��������� DMA_Inc_ON-��������, DMA_Inc_OFF-���������
DMA_STM_F4.DMA_Memory_data_size = DMA_16_bit ;//������ ������ ������: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_16_bit ;//������ ������ ���������: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_enabled ;//��������� �����:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA2_Stream0_IRQn ;// ���������� �� stm32f411xe.h, �������� - DMA2_Stream0_IRQn
DMA_F4_param_init ();//������ ��� � ��������� �����������
//
}

//=================================================
void DMA2_Stream0_IRQHandler_User(void)
{	
	ADC_main_count++;
			for (uint8_t i=1; i<17;i++)
				{ADC_ch_summ[i]+=ADC_DMA_val[i];}
			
	if (ADC_main_count>=ADC_Init.ADC_Average_val) 
		{
			ADC_main_count=0;
			for (uint8_t i=1; i<17;i++)
				{	ADC_ch[i]=(ADC_ch_summ[i]/ADC_Init.ADC_Average_val);
					ADC_ch_summ[i]=0;	}
		}
			ADC1->CR2 |=ADC_CR2_SWSTART; 	
}
//=================================================

