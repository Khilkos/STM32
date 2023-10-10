#include "DMA_F411.h"

#define ADC_Average_val 20000
uint16_t ADC_DMA_val[2]={0,0};


void DMA_F411_init (void)
{
RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN | RCC_AHB1ENR_DMA1EN;
}

//=============================================
void DMA_F411_ADC_init (void)
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
void DMA_F411_DS18B20_convert_T (void)
{
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)convert_T;		//����� ������
DMA1_Stream6->NDTR = 16;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;
UART_F411_DMA_ON();	
DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���

}


//===================================================
void DMA1_Stream6_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF6)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
			while (!(USART2->SR & USART_SR_TC)) __NOP();
		//	while (!(USART2->SR & USART_SR_RXNE)) __NOP();
//			DMA1_Stream6->CR=0;	
			DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
			if (!(DMA1_Stream5->CR & DMA_SxCR_EN)) DMA_busy=0;
				
			UART_F411_DMAT_OFF();
			
			
		}
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
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//����� ����� ���������� - ���������� ��������
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream5->M0AR = (uint32_t)DMA_read_temp;		//����� ������
DMA1_Stream5->NDTR = 32;	//���������� ������ ������������ � ���
DMA1_Stream5->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream5->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA1_Stream5->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA1_Stream5->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream5->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream5->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream5->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<16);	//��������� ���������� ���1 ����� 6
//DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	

	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)read_scratch;		//����� ������
DMA1_Stream6->NDTR = 32;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;
	
//USART2->SR=0;	
//(void)USART2->DR;
//(void)USART2->DR;


UART_F411_DMA_ON();	
//USART_F411_restart();		

	DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	
	//delay_ms(10);
	DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���
}



//===================================================
void DMA1_Stream5_IRQHandler(void)
{
	if (DMA1->HISR & DMA_HISR_TCIF5)
		{
			DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
//			DMA1_Stream5->CR=0;
			DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
	//		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
	
			DMA_busy=0;
			UART_F411_DMAR_OFF();
		}
	GPIOB->BSRR=1<<14;	
}	


//===================================================

void DMA_read_test (void)
{
if (DMA1_Stream5->CR & DMA_SxCR_EN)
	{
		DMA1_Stream5->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream5->CR & DMA_SxCR_EN) __NOP();
	}	
	
DMA1_Stream5->CR=0;
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF5;//����� ����� ���������� - ���������� ��������
DMA1_Stream5->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream5->M0AR = (uint32_t)DMA_read_temp;		//����� ������
DMA1_Stream5->NDTR = 8;	//���������� ������ ������������ � ���
DMA1_Stream5->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream5->CR |= 0x3UL<<DMA_SxCR_PL_Pos; //������� ��������� ������
DMA1_Stream5->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ��������� � ������
DMA1_Stream5->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream5->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream5->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream5->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream5->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<16);	//��������� ���������� ���1 ����� 6
//DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	

	
if (DMA1_Stream6->CR & DMA_SxCR_EN)
	{
		DMA1_Stream6->CR &= ~(DMA_SxCR_EN);
		while (DMA1_Stream6->CR & DMA_SxCR_EN) __NOP();
	}

DMA1_Stream6->CR=0;	
	
DMA1->HIFCR |=DMA_HIFCR_CTCIF6;//����� ����� ���������� - ���������� ��������
DMA1_Stream6->PAR = (uint32_t)&USART2->DR;	//����� ���������
DMA1_Stream6->M0AR = (uint32_t)read_scratch;		//����� ������
DMA1_Stream6->NDTR = 8;	//���������� ������ ������������ � ���
DMA1_Stream6->CR |= (0x4UL<<DMA_SxCR_CHSEL_Pos); //����� 4 ������ ���
DMA1_Stream6->CR |= 0x1UL<<DMA_SxCR_PL_Pos; //������ ��������� ������
DMA1_Stream6->FCR  &= ~(DMA_SxFCR_DMDIS); //������ ������ ��� ������������� FIFO
DMA1_Stream6->CR |= (0x1UL<<DMA_SxCR_DIR_Pos); //����������� ������ ������ �� ������ � ���������
DMA1_Stream6->CR |= DMA_SxCR_MINC; //��������� ������ ��������
DMA1_Stream6->CR &= ~DMA_SxCR_PINC; //��������� ��������� ���������
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_PSIZE_Pos); //������ ������ ��������� 8 ���
DMA1_Stream6->CR &= ~(0x3UL<<DMA_SxCR_MSIZE_Pos); //������ ������ ������ 8 ���
DMA1_Stream6->CR &= ~DMA_SxCR_CIRC;	//��������� ����� ��������	
DMA1_Stream6->CR |= DMA_SxCR_TCIE; //��������� ���������� ��� ���������� ��������
NVIC->ISER[0]=( 1<<17);	//��������� ���������� ���1 ����� 6
USART2->SR &=~USART_SR_TC;
USART2->SR &=~USART_SR_RXNE;
	
//USART2->SR=0;	
//(void)USART2->DR;
//(void)USART2->DR;


UART_F411_DMA_ON();	
//USART_F411_restart();		

	DMA1_Stream5->CR |=DMA_SxCR_EN; //��������� ���	
	//delay_ms(10);
	DMA1_Stream6->CR |=DMA_SxCR_EN; //��������� ���
}







