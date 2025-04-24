#include "main.h"
//#include "GPIO_setup.h"

static uint16_t temp16=0;


int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOHEN); // enable portA and portB clock

	Core_F4_init_HSE_full(6,168,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	
	
	GPIO_DO_setup(GPIOE,6,High);//LCD подсветка
	GPIO_DO_setup(GPIOE,0,High);//LCD_Reset
	GPIO_DO_setup(GPIOA,1,High);	
	
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

FSMC_init();

GPIOE->BSRR = 1<<6;//включить подсветку дисплея
delay_ms(150);
GPIOE->BSRR = 1<<(0+16); //сброс дисплея
delay_ms(200);
GPIOE->BSRR = 1<<(0);
delay_ms(150);

SSD1963_init();
SSD1963_ClearScreen(0x0000);	
	
SSD1963_dot(50,50,0xffff);
SSD1963_Vertical_line(100,10,200,0xff);	
SSD1963_Horisontal_line(100,10,200,0xff);
	
	while (1)
	{
			
	if (!TIM1_Delay_1) {if (GPIOA->IDR & 1<<1) GPIOA->BSRR = 1<<(1+16); else GPIOA->BSRR = 1<<1;  	TIM1_Delay_1 = 250;}
/*temp16=3;
	for (uint16_t i=0;i<16;i++)
{
//temp16 |= 0x01;	
SSD1963_ClearScreen(temp16);
temp16  <<=1;	
delay_ms(500);	
}	
*/
	

		
	}
	
}

