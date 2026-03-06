#include "main.h"

static uint8_t String[300];
static uint16_t temp16;
static uint8_t temp8;

int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(8,336,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	FSMC_init();
	USART_F4_init(USART2);
	USART_F4_set_9600_baud(USART2);
	
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

//	GPIO_DI_setup(GPIOA,0,Pull_down);	

//	GPIOE->BSRR = 1<<6;
//		GPIOA->BSRR = 1<<1;
	
	
	
	FSMC_Low_init();
	delay_ms(300);
	Open407_LCD_Init();
	Open407_ClearScreen(0xff);
//	Open407_dot(10, 100, 0xffff);
	while (1)
	{
		
	if (!TIM1_Delay_1) {if (GPIOD->IDR & 1<<12) Green_led_OFF; else Green_led_ON;  	TIM1_Delay_1 = 250;}
//	if (GPIOA->IDR &  1<<0) Orange_led_ON; else Orange_led_OFF;		
	
	if (!TIM1_Delay_2) {if (temp16<999) temp16++; else temp16=0; TIM1_Delay_2=10;}
	
	sprintf(String,"—четчик = %03d",temp16);	
TFT_Draw_string_font_10x16_back_fone(2,2,String,0xff00, 0xff);
TFT_Draw_string_font_5x8_back_fone(2,20,String,0xff00, 0xff);	

if (USART2->SR & USART_SR_RXNE)	
temp8= USART2->DR;
sprintf(String,"USART Rx = %x",temp8);		
TFT_Draw_string_font_10x16_back_fone(2,40,String,0xff00, 0xff);	
//	GPIOA->BSRR = 1<<0;
//	if ( (USART2->SR & USART_SR_TXE))
//	{USART2->DR = 0xAA;}
	
	
	}
	
}
