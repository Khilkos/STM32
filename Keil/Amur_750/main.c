#include "main.h"
#define SRAM2_start_adress ((uint32_t*)0x30020000)
static uint32_t led_temp=0;
static uint16_t SPI2_temp=0;

uint32_t send_buf_SPI1[3] __attribute__((section(".ARM.__at_0x30020000")));
volatile uint32_t send_buf_SPI2[2] __attribute__((section(".ARM.__at_0x30020000")));


int main(void)
	{
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;		
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
		
		RCC->AHB2ENR |= RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN | RCC_AHB2ENR_D2SRAM3EN;

send_buf_SPI1[0]=0x0f0f0f0f;
send_buf_SPI1[1]=0x0a0a0a0a;

send_buf_SPI2[0]=0x0b0b0b0b;
send_buf_SPI2[1]=0x0c0c0c0c;		
		
GPIO_DO_setup(GPIOE,0,High);
		
GPIO_Alternate(GPIOA,7,Push_pull,High,Pull_down,AF5);// SPI1 MOSI
GPIO_Alternate(GPIOA,5,Push_pull,High,Pull_down,AF5);// SPI1 CLK
GPIO_Alternate(GPIOA,4,Push_pull,High,Pull_up,AF5);// SPI1 NSS
 
GPIO_Alternate(GPIOC,2,Push_pull,High,Pull_down,AF5);// SPI2 MISO
GPIO_Alternate(GPIOB,10,Push_pull,High,Pull_down,AF5);// SPI2 CLK
GPIO_Alternate(GPIOB,12,Push_pull,High,Pull_up,AF5);// SPI2 NSS
		
SysTick_H7_Init(456);	
Core_STM32_H7_init(1,114,2,19,2);
		
//-----------------------------------------------
//----------инициализация SPI--------------------
//-----------------------------------------------
	//настройка режима работы SPI
SPI_H7.SPI_Number = SPI1;	//Выбор SPI, например SPI1
SPI_H7.MBR = 4; // делитель тактовой частоты для SPI, от 0=/2, 1=/4 ....7=/256 	
SPI_H7.DSIZE = 31; // количество бит в кадре от 3=4бита, 4=5бит, .... 31=32бита.	
SPI_H7.MASTER_bit = 1; //режим SPI: 0-Slave, 1-Master	
SPI_H7.COMM = 1;	//режим работы SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
SPI_H7.FTHLV = 15; // уровень поорга FIFO, количество кадров данных, от 0=1кадр, 1=2кадр ... 15=16кадр	
SPI_H7.TSIZE =2;	//количество кадров в одной посылке (во время активного SS)	
	//настройка CLK
SPI_H7.CPOL_bit =0; //полярность CLK:	0-SCK сигнал когда 0 на idle, 1-SCK сигнал когда 1 на idle
SPI_H7.CPHA_bit =0; //фаза CLK: 0-захват сигнала по первому фронту CLK, 1-захват сигнала по фторому фронту CLK	
	//настройка вывода SS
SPI_H7.SSM_bit =0; // программный SS если SSM=1, управляется битом SSI, если SSM=0 - SS управляется аппаратно
SPI_H7.SSOE_bit =1; //включение аппаратного выхода SS: 0 - выключен, 1-включен
SPI_H7.SSIOP_bit = 1; //выбор активного уровня SS: 0-низкий уровень это активный SS, 1- высокий уровень это активный SS	
SPI_H7.SSOM_bit = 0; //режим работы выхода SS в MASTER mode
SPI_H7.MSSI = 0; //отступ от SS начала передачи, значение от 0 до 15 тактов	
	//настройка DMA
SPI_H7.Tx_DMA = 1;// включение потока ДМА на передачу (Tx DMA stream enable): 1- включен, 0- выключен	
SPI_H7.Rx_DMA = 0;// включение потока ДМА на прием (Rx DMA stream enable): 1- включен, 0- выключен
//
SPI_H7_init();//запуск SPI с заданными параметрами
//------------------------------------------------

//-------------------------------------------------
//-------------инициализация DMA-------------------
//-------------------------------------------------
DMA_H7.DMA_Number = DMA1; //выбор ДМА, напр. - DMA2
DMA_H7.DMA_Stream = DMA1_Stream0; //выбор потока ДМА напр. -  DMA2_Stream0
DMA_H7.DMA_Peripheral_address = &SPI1->TXDR;//адрес перефирии, например &USART2->DR;
DMA_H7.DMA_Memory_address = send_buf_SPI1; //адрес памяти, например (void*)temp_send_buf ;
DMA_H7.DMA_Quantity = 1;//NDTR - Number of data items to transfer (0 up to 65535), количество данный передаваемых в ДМА
DMA_H7.DMA_Request_source = 38; //выбор источника тактирования DMAMUX для канала ДМА
DMA_H7.DMA_flow_control =1;//если=0 - контроллером потока является DMA, если=1 - перифирическое устройство
DMA_H7.DMA_Prioroty = 0;//приоритет потока: 0-Low, 1-Medium, 2-High, 3-Very high
DMA_H7.DMA_Memory_data_size = 2; //Размер памяти: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Peripheral_data_size = 2;	//Размер перефирического устройства: 0-Byte (8-bit), 1-Half-word (16-bit), 2-Word (32-bit), 3-Reserved
DMA_H7.DMA_Data_transfer_direction = 1; //направление передачи DMA: 0-Peripheral-to-memory, 1-Memory-to-peripheral, 2-Memory-to-memory, 3-Reserved
DMA_H7.DMA_Memory_inc = 1;//инкремент памяти: 0-выкл, 1-включен
DMA_H7.DMA_Peripheral_inc = 0; //инкремент перефирии: 0-выкл, 1-включен
DMA_H7.DMA_Circular_mode =0; //циклический режим: 0-выключен, 1-включен

//DMA_STM_F4.DMA_Interrupt =  ;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_H7_init();//Запуск ДМА с заданными параметрами
//
//---------------------------------------------------	


SPI1->CR1 |= (SPI_CR1_CSTART);	

//------------------------------------------------

//-----------------------------------------------
//----------инициализация SPI--------------------
//-----------------------------------------------
	//настройка режима работы SPI
SPI_H7.SPI_Number = SPI2;	//Выбор SPI, например SPI1
SPI_H7.MBR = 4; // делитель тактовой частоты для SPI, от 0=/2, 1=/4 ....7=/256 	
SPI_H7.DSIZE = 31; // количество бит в кадре от 3=4бита, 4=5бит, .... 31=32бита.	
SPI_H7.MASTER_bit = 0; //режим SPI: 0-Slave, 1-Master	
SPI_H7.COMM = 1;	//режим работы SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
SPI_H7.FTHLV = 7; // уровень поорга FIFO, количество кадров данных, от 0=1кадр, 1=2кадр ... 15=16кадр	
SPI_H7.TSIZE = 4;	//количество кадров в одной посылке (во время активного SS)	
	//настройка CLK
SPI_H7.CPOL_bit =0; //полярность CLK:	0-SCK сигнал когда 0 на idle, 1-SCK сигнал когда 1 на idle
SPI_H7.CPHA_bit =0; //фаза CLK: 0-захват сигнала по первому фронту CLK, 1-захват сигнала по фторому фронту CLK	
	//настройка вывода SS
SPI_H7.SSM_bit =1; // программный SS если SSM=1, управляется битом SSI, если SSM=0 - SS управляется аппаратно
//SPI_H7.SSOE_bit =; //включение аппаратного выхода SS: 0 - выключен, 1-включен
SPI_H7.SSIOP_bit = 1; //выбор активного уровня SS: 0-низкий уровень это активный SS, 1- высокий уровень это активный SS	
//SPI_H7.SSOM_bit = ; //режим работы выхода SS в MASTER mode
SPI_H7.MSSI = 0; //отступ от SS начала передачи, значение от 0 до 15 тактов	

//SPI_H7_init();//запуск SPI с заданными параметрами
//------------------------------------------------		

		
		
		while (1)
	{
		
	if (SPI1->SR&SPI_SR_EOT) 
			{	SPI1->CR1 &= ~SPI_CR1_SPE; //desable SPI1	
				SPI1->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );
				
				DMA1_Stream0->CR &=~DMA_SxCR_EN; //включение DMA
						while (DMA1_Stream0->CR & DMA_SxCR_EN) __NOP();
			
				DMA1->LIFCR=DMA_LIFCR_CTCIF0;
				DMA1_Stream0->CR |=DMA_SxCR_EN; //включение DMA
			
				SPI1->CR1 |= SPI_CR1_SPE;
				SPI1->CR1 |= (SPI_CR1_CSTART);
			}	

led_temp++;
if (led_temp==0xfffff)
	{	
		led_temp=0;
		if (GPIOE->IDR & 1<<0)	GPIOE->BSRR=1<<(0+16); else GPIOE->BSRR=1<<(0);
	}	
/*
	SPI2->CR1 |= SPI_CR1_SPE; //enable SPI2		
SPI1->CR1 |= SPI_CR1_SPE; //enable SPI1			
*/
	
/*SPI1->TXDR =0xffffffff;		
SPI1->TXDR =0x00000000;
SPI1->TXDR =0xffffffff;		
SPI1->TXDR =0x00000ff0;	

SPI2->TXDR =0xffffffff;		
SPI2->TXDR =0x00000000;
SPI2->TXDR =0xffffffff;		
SPI2->TXDR =0x00000ff0;		
*/
//SPI1->TXDR=send_data;	
	
/*	
SPI2_temp++;
if (SPI2_temp==1)
	{	
		SPI2_temp=0;
		SPI2->CR1 |= (SPI_CR1_SSI);
		//SPI2->CR1 &= ~(SPI_CR1_SSI);
	}	
*/	
/*	
SPI1->CR1 |= (SPI_CR1_CSTART);		

while (!(SPI1->SR&SPI_SR_EOT)) {__NOP();}
SPI1->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );
*/
/*
SPI2->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );

SPI2->CR1 &= ~(SPI_CR1_SSI);
//SPI2->CR1 |= (SPI_CR1_SSI);
*/
//SPI1->CR1 &= ~SPI_CR1_SPE; //desable SPI1	
//----------------

			



	
//while (!(SPI2->SR&SPI_SR_EOT)) {__NOP();}
//SPI2->IFCR |= ( SPI_IFCR_EOTC | SPI_IFCR_TXTFC );

//SPI2->CR1 &= ~SPI_CR1_SPE; //desable SPI2



	}
	
}
