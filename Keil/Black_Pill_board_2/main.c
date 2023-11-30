#include "main.h"

int main (void)
	
{
// uint8_t String[300]="123";
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock

GPIO_DO_setup(GPIOB,12,High);	
GPIO_DO_setup(GPIOB,13,High);	
GPIO_DO_setup(GPIOB,14,High);	
GPIO_DO_setup(GPIOB,15,High);	
GPIO_DO_setup(GPIOA,0,High);
GPIO_DO_setup(GPIOA,1,High);	
GPIO_DO_setup(GPIOA,2,High);	
GPIO_DO_setup(GPIOA,3,High);	
GPIO_DO_setup(GPIOA,4,High);		
	
GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);
	
	
	
Core_F411_init();
SysTick_Init();
I2C_F411_init();
LCD1602_init_via_I2C();
	
//Draw_String(0,(uint8_t*)"123");	
	
	
while (1)
{

if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
delay_us(950);
//	LCD1602_init_via_I2C();
//Draw_String(0,(uint8_t*)"123");	
//Draw_String(0x40, (uint8_t*)"Temperature=");

HUB_08_Send();


}
}



