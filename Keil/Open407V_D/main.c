#include "main.h"



int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(8,336,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	
	GPIO_DO_setup(GPIOD,12,High);//Green_Led
	GPIO_DO_setup(GPIOD,13,High);//Orange_Led
	//GPIO_DO_setup(GPIOD,14,High);//Red_Led
	//GPIO_DO_setup(GPIOD,15,High);//Blue_Led
	
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
	GPIO_Alternate(GPIOD,11,Push_pull,High,No_pull,AF12); //FSMC D16/RS
	GPIO_Alternate(GPIOD,4,Push_pull,High,No_pull,AF12); //FSMC NOE/RD
	GPIO_Alternate(GPIOD,5,Push_pull,High,No_pull,AF12); //FSMC NWE/WR
	GPIO_Alternate(GPIOD,7,Push_pull,High,No_pull,AF12); //FSMC NE1/LCS

	GPIO_DI_setup(GPIOA,0,Pull_down);	

//	GPIOE->BSRR = 1<<6;
//		GPIOA->BSRR = 1<<1;
	
	
	while (1)
	{
		
	if (!TIM1_Delay_1) {if (GPIOD->IDR & 1<<12) Green_led_OFF; else Green_led_ON;  	TIM1_Delay_1 = 250;}
	if (GPIOA->IDR &  1<<0) Orange_led_ON; else Orange_led_OFF;		
	
		
	}
	
}
