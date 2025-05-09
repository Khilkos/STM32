#include "main.h"
#define SRAM2_start_adress ((uint32_t*)0x30020000)
volatile static uint32_t led_temp=0;
static uint32_t temp1=0;

uint32_t send_buf_SPI1[3] __attribute__((section(".ARM.__at_0x30020000")));
uint32_t send_buf_SPI2[2] __attribute__((section(".ARM.__at_0x30020000")));


int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;		
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
		
		RCC->AHB2ENR |= RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN | RCC_AHB2ENR_D2SRAM3EN;

send_buf_SPI1[0]=0x0f0f0f0f;
send_buf_SPI1[1]=0x0a0a0a0a;

send_buf_SPI2[0]=0xff0b0bff;
send_buf_SPI2[1]=0x0cffff0c;		
		
GPIO_DO_setup(GPIOE,0,High);
GPIO_DO_setup(GPIOE,1,High);
GPIO_DO_setup(GPIOE,2,High);
GPIO_DO_setup(GPIOE,3,High);		
GPIO_DO_setup(GPIOB,2,High);		
		
GPIO_Alternate(GPIOA,7,Push_pull,High,Pull_down,AF5);// SPI1 MOSI
GPIO_Alternate(GPIOA,5,Push_pull,High,Pull_down,AF5);// SPI1 CLK
GPIO_Alternate(GPIOA,4,Push_pull,High,Pull_up,AF5);// SPI1 NSS
 
GPIO_Alternate(GPIOC,2,Push_pull,High,Pull_down,AF5);// SPI2 MISO
GPIO_Alternate(GPIOB,10,Push_pull,High,Pull_down,AF5);// SPI2 CLK
//GPIO_Alternate(GPIOB,12,Push_pull,High,Pull_up,AF5);// SPI2 NSS
GPIO_DO_setup(GPIOB,12,High);
		
SysTick_H7_Init(408);	
Core_STM32_H7_init(1,102,2,17,2);//1,114,2,19,2
Timer1_H7_init(204000000,1000);
		
//-----------------------------------------------
//----------������������� SPI--------------------
//-----------------------------------------------
	//��������� ������ ������ SPI
SPI_H7.SPI_Number = SPI1;	//����� SPI, �������� SPI1
SPI_H7.MBR = 4; // �������� �������� ������� ��� SPI, �� 0=/2, 1=/4 ....7=/256 	
SPI_H7.DSIZE = 31; // ���������� ��� � ����� �� 3=4����, 4=5���, .... 31=32����.	
SPI_H7.MASTER_bit = 1; //����� SPI: 0-Slave, 1-Master	
SPI_H7.COMM = 1;	//����� ������ SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
SPI_H7.FTHLV = 15; // ������� ������ FIFO, ���������� ������ ������, �� 0=1����, 1=2���� ... 15=16����	
SPI_H7.TSIZE =2;	//���������� ������ � ����� ������� (�� ����� ��������� SS)	
	//��������� CLK
SPI_H7.CPOL_bit =0; //���������� CLK:	0-SCK ������ ����� 0 �� idle, 1-SCK ������ ����� 1 �� idle
SPI_H7.CPHA_bit =0; //���� CLK: 0-������ ������� �� ������� ������ CLK, 1-������ ������� �� ������� ������ CLK	
	//��������� ������ SS
SPI_H7.SSM_bit =1; // ����������� SS ���� SSM=1, ����������� ����� SSI, ���� SSM=0 - SS ����������� ���������
SPI_H7.SSOE_bit =1; //��������� ����������� ������ SS: 0 - ��������, 1-�������
SPI_H7.SSIOP_bit = 1; //����� ��������� ������ SS: 0-������ ������� ��� �������� SS, 1- ������� ������� ��� �������� SS	
SPI_H7.SSOM_bit = 0; //����� ������ ������ SS � MASTER mode
SPI_H7.MSSI = 0; //������ �� SS ������ ��������, �������� �� 0 �� 15 ������	
	//��������� DMA
SPI_H7.Tx_DMA = 1;// ��������� ������ ��� �� �������� (Tx DMA stream enable): 1- �������, 0- ��������	
SPI_H7.Rx_DMA = 0;// ��������� ������ ��� �� ����� (Rx DMA stream enable): 1- �������, 0- ��������
//
SPI_H7_init();//������ SPI � ��������� �����������
//------------------------------------------------

//-------------------------------------------------
//-------------������������� DMA-------------------
//-------------------------------------------------
DMA_H7.DMA_Number = DMA1; //����� ���, ����. - DMA2
DMA_H7.DMA_Stream = DMA1_Stream0; //����� ������ ��� ����. -  DMA2_Stream0
DMA_H7.DMA_Peripheral_address = &SPI1->TXDR;//����� ���������, �������� &USART2->DR;
DMA_H7.DMA_Memory_address = send_buf_SPI1; //����� ������, �������� (void*)temp_send_buf ;
DMA_H7.DMA_Quantity = 1;//NDTR - Number of data items to transfer (0 up to 65535), ���������� ������ ������������ � ���
DMA_H7.DMA_Request_source = 38; //����� ��������� ������������ DMAMUX ��� ������ ���
DMA_H7.DMA_flow_control =1;//����=0 - ������������ ������ �������� DMA, ����=1 - �������������� ����������
DMA_H7.DMA_Prioroty = 0;//��������� ������: 0-Low, 1-Medium, 2-High, 3-Very high
DMA_H7.DMA_Memory_data_size = 2; //������ ������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Peripheral_data_size = 2;	//������ ��������������� ����������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Data_transfer_direction = 1; //����������� �������� DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved
DMA_H7.DMA_Memory_inc = 1;//��������� ������: 0-����, 1-�������
DMA_H7.DMA_Peripheral_inc = 0; //��������� ���������: 0-����, 1-�������
DMA_H7.DMA_Circular_mode =0; //����������� �����: 0-��������, 1-�������
DMA_H7.DMA_Transfer_complete_interrupt=1; //���������� ����� ���������� ��������: 0-��������, 1-�������	
DMA_H7.DMA_Interrupt = DMA1_Stream0_IRQn; // ���������� �� stm32f411xe.h, �������� - DMA2_Stream0_IRQn
DMA_H7.DMA_Interrupt_Priority = 4; //��������� ����������

DMA_H7_init();//������ ��� � ��������� �����������
//
//---------------------------------------------------	




//------------------------------------------------

//-----------------------------------------------
//----------������������� SPI--------------------
//-----------------------------------------------
	//��������� ������ ������ SPI
SPI_H7.SPI_Number = SPI2;	//����� SPI, �������� SPI1
SPI_H7.MBR = 4; // �������� �������� ������� ��� SPI, �� 0=/2, 1=/4 ....7=/256 	
SPI_H7.DSIZE = 31; // ���������� ��� � ����� �� 3=4����, 4=5���, .... 31=32����.	
SPI_H7.MASTER_bit = 0; //����� SPI: 0-Slave, 1-Master	
SPI_H7.COMM = 1;	//����� ������ SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
SPI_H7.FTHLV = 15; // ������� ������ FIFO, ���������� ������ ������, �� 0=1����, 1=2���� ... 15=16����	
SPI_H7.TSIZE = 2;	//���������� ������ � ����� ������� (�� ����� ��������� SS)	
	//��������� CLK
SPI_H7.CPOL_bit =0; //���������� CLK:	0-SCK ������ ����� 0 �� idle, 1-SCK ������ ����� 1 �� idle
SPI_H7.CPHA_bit =0; //���� CLK: 0-������ ������� �� ������� ������ CLK, 1-������ ������� �� ������� ������ CLK	
	//��������� ������ SS
SPI_H7.SSM_bit =1; // ����������� SS ���� SSM=1, ����������� ����� SSI, ���� SSM=0 - SS ����������� ���������
//SPI_H7.SSOE_bit =; //��������� ����������� ������ SS: 0 - ��������, 1-�������
SPI_H7.SSIOP_bit = 1; //����� ��������� ������ SS: 0-������ ������� ��� �������� SS, 1- ������� ������� ��� �������� SS	
//SPI_H7.SSOM_bit = ; //����� ������ ������ SS � MASTER mode
SPI_H7.MSSI = 0; //������ �� SS ������ ��������, �������� �� 0 �� 15 ������	
//��������� DMA
SPI_H7.Tx_DMA = 1;// ��������� ������ ��� �� �������� (Tx DMA stream enable): 1- �������, 0- ��������	
SPI_H7.Rx_DMA = 0;// ��������� ������ ��� �� ����� (Rx DMA stream enable): 1- �������, 0- ��������
//
SPI_H7_init();//������ SPI � ��������� �����������
//------------------------------------------------		
//-------------------------------------------------
//-------------������������� DMA-------------------
//-------------------------------------------------
DMA_H7.DMA_Number = DMA1; //����� ���, ����. - DMA2
DMA_H7.DMA_Stream = DMA1_Stream1; //����� ������ ��� ����. -  DMA2_Stream0
DMA_H7.DMA_Peripheral_address = &SPI2->TXDR;//����� ���������, �������� &USART2->DR;
DMA_H7.DMA_Memory_address = send_buf_SPI2; //����� ������, �������� (void*)temp_send_buf ;
DMA_H7.DMA_Quantity = 1;//NDTR - Number of data items to transfer (0 up to 65535), ���������� ������ ������������ � ���
DMA_H7.DMA_Request_source = 40; //����� ��������� ������������ DMAMUX ��� ������ ���
DMA_H7.DMA_flow_control =1;//����=0 - ������������ ������ �������� DMA, ����=1 - �������������� ����������
DMA_H7.DMA_Prioroty = 0;//��������� ������: 0-Low, 1-Medium, 2-High, 3-Very high
DMA_H7.DMA_Memory_data_size = 2; //������ ������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Peripheral_data_size = 2;	//������ ��������������� ����������: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Data_transfer_direction = 1; //����������� �������� DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved
DMA_H7.DMA_Memory_inc = 1;//��������� ������: 0-����, 1-�������
DMA_H7.DMA_Peripheral_inc = 0; //��������� ���������: 0-����, 1-�������
DMA_H7.DMA_Circular_mode =0; //����������� �����: 0-��������, 1-�������

//DMA_STM_F4.DMA_Interrupt =  ;// ���������� �� stm32f411xe.h, �������� - DMA2_Stream0_IRQn
DMA_H7_init();//������ ��� � ��������� �����������
//
//---------------------------------------------------	
SPI2->CR1 |= (SPI_CR1_SSI);
SPI2->CR1 |= (SPI_CR1_CSTART);
SPI1->CR1 |= (SPI_CR1_CSTART);			


		while (1)
	{
		
	if (SPI1->SR&SPI_SR_EOT) 
			{	SPI1->CR1 &= ~SPI_CR1_SPE; //desable SPI1	
				SPI1->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );
				DMA1_Stream0->CR &=~DMA_SxCR_EN; //��������� DMA
				while (DMA1_Stream0->CR & DMA_SxCR_EN) __NOP();
				
					SPI2->CR1 &= ~SPI_CR1_SPE; //desable SPI2	
					SPI2->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );
					DMA1_Stream1->CR &=~DMA_SxCR_EN; //��������� DMA
					while (DMA1_Stream1->CR & DMA_SxCR_EN) __NOP();
			
					DMA1->LIFCR=DMA_LIFCR_CTCIF1 ;//| DMA_LIFCR_CFEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTCIF3;
					DMA1_Stream1->CR |=DMA_SxCR_EN; //��������� DMA
					SPI2->CR1 |= SPI_CR1_SPE;
					//SPI2->CR1 |= (SPI_CR1_CSTART);
					SPI2->CR1 |= (SPI_CR1_SSI);
				
				DMA1->LIFCR=DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTEIF0  | DMA_LIFCR_CDMEIF0 |   DMA_LIFCR_CFEIF0 ;
				DMA1_Stream0->CR |=DMA_SxCR_EN; //��������� DMA
				SPI1->CR1 |= SPI_CR1_SPE;
				SPI1->CR1 |= (SPI_CR1_CSTART);
			}	
//delay_us(100);

if (!led_temp)
	{	
		led_temp=0xfffff;
		if (GPIOE->IDR & 1<<0)	GPIOE->BSRR=1<<(0+16); else GPIOE->BSRR=1<<(0);
	}	
led_temp--;
	
if (!TIM1_Delay_1) 
	{
			if (GPIOB->IDR & 1<<2)	GPIOB->BSRR=1<<(2+16); else GPIOB->BSRR=1<<(2);
			TIM1_Delay_1=500;
	}
//if (GPIOE->IDR & 1<<2)	GPIOE->BSRR=1<<(2+16); else GPIOE->BSRR=1<<(2);	
	
	
}
}

//-------------------------------------
void DMA1_Stream0_IRQHandler_User(void)
{
	GPIOE->BSRR=1<<(2);
	GPIOE->BSRR=1<<(3+res);
	if (GPIOB->IDR & 1<<12)	GPIOB->BSRR=1<<(12+16); else GPIOB->BSRR=1<<(12);
	temp1++;
if (temp1==0xfff)
	{	
		temp1=0;
		if (GPIOE->IDR & 1<<1)	GPIOE->BSRR=1<<(1+16); else GPIOE->BSRR=1<<(1);
	}
//	delay_us(10);
	GPIOE->BSRR=1<<(3);
	GPIOE->BSRR=1<<(2+res);
}	
