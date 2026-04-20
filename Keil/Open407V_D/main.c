#include "main.h"

static uint8_t String[300];
static uint16_t temp16;
static uint8_t temp8;
static uint8_t Modbus_count=0;
static uint8_t Modbus_buf[10];
uint8_t Modbus_RX_buf[10];
uint8_t Modbus_TX_buf[10];
static uint16_t _FPS=0;
static uint16_t CRC_res=0;
// Таймер1_4 для отслеживания конца модбас пакета

int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(8,336,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	FSMC_init();
	
//-------------------------------------------------
//-------------инициализация DMA-------------------
//-------------------------------------------------
DMA_STM_F4.DMA_Number = DMA1;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream5;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR);//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*)Modbus_buf;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity = 1;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Peripheral_to_memory;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_OFF;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream5_IRQn;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//---------------------------------------------------
DMA_STM_F4.DMA_Number = DMA1;//выбор ДМА, напр. - DMA2
DMA_STM_F4.DMA_Stream = DMA1_Stream6;//выбор потока ДМА напр. -  DMA2_Stream0
DMA_STM_F4.DMA_Peripheral_address = (volatile uint32_t*)&(USART2->DR);//адрес перефирии, например (volatile uint32_t*)&(USART2->DR);
DMA_STM_F4.DMA_Memory_address = (void*)Modbus_TX_buf;//адрес памяти, например (void*)temp_send_buf ;
DMA_STM_F4.DMA_Quantity = 8;//количество данный передаваемых в ДМА
DMA_STM_F4.DMA_Chanel = 4;//выбор канала ДМА
DMA_STM_F4.DMA_Prioroty = DMA_Priority_high;//приоритет потока - DMA_Priority_low, DMA_Priority_medium, DMA_Priority_high, DMA_Priority_very_high
DMA_STM_F4.DMA_Data_transfer_direction = DMA_Memory_to_Peripheral;//направление потока данных перефирия <-> память: DMA_Peripheral_to_memory, DMA_Memory_to_Peripheral, DMA_Memory_to_memory
DMA_STM_F4.DMA_Memory_inc =  DMA_Inc_ON;//инкремент памяти DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Peripheral_inc = DMA_Inc_OFF;//инкремент перефирии DMA_Inc_ON-включить, DMA_Inc_OFF-выключить
DMA_STM_F4.DMA_Memory_data_size = DMA_8_bit;//размер потока памяти: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Peripheral_data_size = DMA_8_bit;//размер потока перифирии: DMA_8_bit, DMA_16_bit, DMA_32_bit
DMA_STM_F4.DMA_Circular_mode = Circular_mode_disabled;//кольцевой режим:  Circular_mode_disabled, Circular_mode_enabled
DMA_STM_F4.DMA_Interrupt = DMA1_Stream6_IRQn;// прерывание из stm32f411xe.h, например - DMA2_Stream0_IRQn
DMA_F4_param_init ();//Запуск ДМА с заданными параметрами
//---------------------------------------------------
	
	USART_F4_init(USART2);
	USART_F4_set_9600_baud(USART2);
	USART_F4_DMAR_ON(USART2);
//	USART_F4_DMAT_ON(USART2);
	
	GPIO_Alternate(GPIOA,2,Open_drain,High,Pull_up,AF7);// USART2 TX2
	GPIO_Alternate(GPIOA,3,Open_drain,High,Pull_up,AF7);// USART2 RX2
	
	GPIO_DO_setup(GPIOD,12,High);//Green_Led
	GPIO_DO_setup(GPIOD,13,High);//Orange_Led
	//GPIO_DO_setup(GPIOD,14,High);//Red_Led
	//GPIO_DO_setup(GPIOD,15,High);//Blue_Led
	GPIO_DO_setup(GPIOA,0,High);
	
	GPIO_Alternate(GPIOD,14,Push_pull,High,No_pull,AF12); //FSMC D0
	GPIO_Alternate(GPIOD,15,Push_pull,High,No_pull,AF12); //FSMC D1
	GPIO_Alternate(GPIOD,0,Push_pull,High,No_pull,AF12); //FSMC D2
	GPIO_Alternate(GPIOD,1,Push_pull,High,No_pull,AF12); //FSMC D3
	GPIO_Alternate(GPIOE,7,Push_pull,High,No_pull,AF12); //FSMC D4
	GPIO_Alternate(GPIOE,8,Push_pull,High,No_pull,AF12); //FSMC D5
	GPIO_Alternate(GPIOE,9,Push_pull,High,No_pull,AF12); //FSMC D6
	GPIO_Alternate(GPIOE,10,Push_pull,High,No_pull,AF12); //FSMC D7
	GPIO_Alternate(GPIOE,11,Push_pull,High,No_pull,AF12); //FSMC D8
	GPIO_Alternate(GPIOE,12,Push_pull,High,No_pull,AF12); //FSMC D9
	GPIO_Alternate(GPIOE,13,Push_pull,High,No_pull,AF12); //FSMC D10
	GPIO_Alternate(GPIOE,14,Push_pull,High,No_pull,AF12); //FSMC D11
	GPIO_Alternate(GPIOE,15,Push_pull,High,No_pull,AF12); //FSMC D12
	GPIO_Alternate(GPIOD,8,Push_pull,High,No_pull,AF12); //FSMC D13
	GPIO_Alternate(GPIOD,9,Push_pull,High,No_pull,AF12); //FSMC D14
	GPIO_Alternate(GPIOD,10,Push_pull,High,No_pull,AF12); //FSMC D15
	GPIO_Alternate(GPIOD,11,Push_pull,High,No_pull,AF12); //FSMC A16/RS
	GPIO_Alternate(GPIOD,4,Push_pull,High,No_pull,AF12); //FSMC NOE/RD
	GPIO_Alternate(GPIOD,5,Push_pull,High,No_pull,AF12); //FSMC NWE/WR
	GPIO_Alternate(GPIOD,7,Push_pull,High,Pull_down,AF12); //FSMC NE1/LCS

	GPIO_DI_setup(GPIOA,4,Pull_up);
	GPIO_DI_setup(GPIOC,6,Pull_up);
	
	
	FSMC_Low_init();
	delay_ms(300);
	Open407_LCD_Init();
	Open407_ClearScreen(0xff);
//	Open407_dot(10, 100, 0xffff);
	while (1)
	{
		
	if (!TIM1_Delay_1) {if (GPIOD->IDR & 1<<12) Green_led_OFF; else Green_led_ON;  	TIM1_Delay_1 = 250;}
	if (!(GPIOA->IDR &  1<<4) && !(GPIOD->IDR & 1<<13)) {Orange_led_ON;  CRC_fn5(0x01,0x00,0xFF00);  }// else Orange_led_OFF;		
	if (!(GPIOC->IDR &  1<<6) && (GPIOD->IDR & 1<<13)) {Orange_led_OFF; CRC_fn5(0x01,0x00,0x0000);  }// else Orange_led_OFF;
	
	if (!TIM1_Delay_2) {if (temp16<999) temp16++; else temp16=0; TIM1_Delay_2=10;}
	if (!TIM1_Delay_3)
			{	sprintf(String,"FPS = %03d",_FPS);	
				TFT_Draw_string_font_10x16_back_fone(2,200,String,0xff00, 0xff);
				TIM1_Delay_3=1000; 
				_FPS=0;}
		else _FPS++;
	
	sprintf(String,"Счетчик = %03d",temp16);	
TFT_Draw_string_font_10x16_back_fone(2,2,String,0xff00, 0xff);
TFT_Draw_string_font_5x8_back_fone(2,20,String,0xff00, 0xff);	

sprintf(String,"Tx = %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",Modbus_TX_buf[0],Modbus_TX_buf[1],Modbus_TX_buf[2],Modbus_TX_buf[3],Modbus_TX_buf[4],Modbus_TX_buf[5],Modbus_TX_buf[6],Modbus_TX_buf[7]);		
TFT_Draw_string_font_10x16_back_fone(2,40,String,0xff00, 0xff);

sprintf(String,"Rx = %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",Modbus_RX_buf[0],Modbus_RX_buf[1],Modbus_RX_buf[2],Modbus_RX_buf[3],Modbus_RX_buf[4],Modbus_RX_buf[5],Modbus_RX_buf[6],Modbus_RX_buf[7]);		
TFT_Draw_string_font_10x16_back_fone(2,80,String,0xff00, 0xff);

sprintf(String,"CRC = %02x:%02x",(CRC_res&0xFF00)>>8,(CRC_res&0xFF));		
TFT_Draw_string_font_10x16_back_fone(2,100,String,0xff00, 0xff);

//======================================================================				
if (!TIM1_Delay_4) 
			{
				if (Modbus_RX_buf[1]==05)
				{
					CRC_res = CRC_modbus(Modbus_RX_buf,6);
				}
			
			
			
				
				
				
			}
//======================================================================				

			
				
				
	}
	
}

void DMA1_Stream5_IRQHandler_User(void)
{
	if (!TIM1_Delay_4) 	
		{	
			for (uint8_t i=0;i<10;i++) 
			Modbus_RX_buf[i]=0; 
			Modbus_count=0;}
	Modbus_RX_buf[Modbus_count] = Modbus_buf[0];
	Modbus_count++;
	TIM1_Delay_4=3;
			
	DMA1_Stream5->CR |= DMA_SxCR_EN;
}
//==========================================================
void DMA1_Stream6_IRQHandler_User(void)
{
USART_F4_DMAT_OFF(USART2);
GPIOA->BSRR =1<< (0+16);
//USART2->DR;
//USART2->DR;

}
//==========================================================
uint16_t CRC_modbus (uint8_t* buf, uint8_t size)
{	
					uint16_t CRC_temp16=0xffff;
					for (uint8_t i=0;i<size;i++)
						{
							CRC_temp16 = CRC_temp16^(*(buf+i));
							for (uint8_t j=0; j<8;j++)
								{
									if ((CRC_temp16&0x01) ==1) {CRC_temp16 = CRC_temp16>>1; CRC_temp16 = CRC_temp16^0xA001;}
									else CRC_temp16 = CRC_temp16>>1;
								}

						}
				CRC_temp16 = (CRC_temp16&0xff00)>>8 | (CRC_temp16&0x00ff)<<8;
		return CRC_temp16;
}
//=========================================================
void CRC_fn5(uint8_t Id, uint16_t adresse, uint16_t data)
{	uint16_t loc_temp16=0;
	Modbus_TX_buf[0]=Id;
	Modbus_TX_buf[1]=0x05;
	Modbus_TX_buf[2]=(adresse&0xff00)>>8;
	Modbus_TX_buf[3]=adresse&0xff;
	Modbus_TX_buf[4]=(data&0xff00)>>8;
	Modbus_TX_buf[5]=data&0xff;
	loc_temp16=CRC_modbus(Modbus_TX_buf,6);
	Modbus_TX_buf[6]=(loc_temp16&0xff00)>>8;
	Modbus_TX_buf[7]=loc_temp16&0xff;
	GPIOA->BSRR = 1<<0;
	USART_F4_DMAT_ON(USART2);
}