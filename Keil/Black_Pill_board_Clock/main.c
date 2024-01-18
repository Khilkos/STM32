#include "main.h"

int main (void)
	
{
// uint8_t String[300]="123";
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock

	
GPIO_DO_setup(GPIOB,12,High);	
GPIO_DO_setup(GPIOB,13,High);	
GPIO_DO_setup(GPIOB,14,High);	
GPIO_DO_setup(GPIOB,15,High);	
GPIO_DO_setup(GPIOB,9,High);
GPIO_DO_setup(GPIOB,8,High);	
GPIO_DO_setup(GPIOA,12,High);	
GPIO_DO_setup(GPIOA,11,High);	
GPIO_DO_setup(GPIOA,10,High);
GPIO_DO_setup(GPIOA,8,High);
GPIO_DO_setup(GPIOA,9,High);

GPIO_DI_setup(GPIOA,15,No_pull);//отключение jtag
GPIO_DO_setup(GPIOA,15,High);
	
GPIO_DI_setup(GPIOB,3,No_pull);//отключение jtag
GPIO_DO_setup(GPIOB,3,High);	
	
GPIO_DI_setup(GPIOB,0,Pull_down);
GPIO_DI_setup(GPIOB,1,Pull_down);
GPIO_DI_setup(GPIOB,2,Pull_down);	
	
GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOA,2,Open_drain,High,Pull_up,AF7);// USART2 TX2
GPIO_Alternate(GPIOA,3,Open_drain,High,Pull_up,AF7);// USART2 RX2	
	
	
Core_F411_init();
SysTick_Init();
Timer_F411_init();
I2C_F411_init();
//LCD1602_init_via_I2C();
DMA_F411_init();
USART_F411_init();
//Draw_String(0,(uint8_t*)"123");	
	
	
while (1)
{
key_scan();
	DS3231_F411_get_time();
//if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
//delay_us(200);
//Draw_Strng(0,(uint8_t*)"123");	
//Draw_String(0x40, (uint8_t*)"Temperature=");

HUB75_Send();


}
}



