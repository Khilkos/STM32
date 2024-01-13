#include "main.h"

int main (void)
	
{
 char String[300];
	
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock

	
GPIO_DO_setup(GPIOB,12,High);	
GPIO_DO_setup(GPIOB,13,High);	
GPIO_DO_setup(GPIOB,14,High);	
GPIO_DO_setup(GPIOB,15,High);	

/*
GPIO_DI_setup(GPIOA,15,No_pull);//отключение jtag
GPIO_DO_setup(GPIOA,15,High);
	
GPIO_DI_setup(GPIOB,3,No_pull);//отключение jtag
GPIO_DO_setup(GPIOB,3,High);	
*/

GPIO_DI_setup (GPIOA,10,No_pull);
GPIO_DI_setup (GPIOA,11,No_pull);
	
GPIO_DI_setup(GPIOB,0,Pull_down);
GPIO_DI_setup(GPIOB,1,Pull_down);
GPIO_DI_setup(GPIOB,2,Pull_down);	
	
GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);// I2C SCL1
GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);// I2C SDA1
GPIO_Alternate(GPIOA,2,Open_drain,High,Pull_up,AF7);// USART2 TX2
GPIO_Alternate(GPIOA,3,Open_drain,High,Pull_up,AF7);// USART2 RX2	
	
	
Core_F411_init();
SysTick_Init();
Timer_F411_init();
I2C_F411_init();
LCD1602_init_via_I2C();
DMA_F411_init();
USART_F411_init();


DS18B20_read_ROM();


while (1)
{
key_scan();
//	DS3231_F411_get_time();
if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
delay_us(100);
sprintf(String,"Encoder = %3d",encoder_data);
Draw_String(0,(uint8_t*)String);	
	
//sprintf(String,"Temper. %.1fC", (DS18B20_read_temperatur_via_DMA()*0.1));
sprintf(String,"%02x%02x%02x%02x%02x%02x%02x%02x",ROM[7],ROM[6],ROM[5],ROM[4],ROM[3],ROM[2],ROM[1],ROM[0] );

Draw_String(0x40, (uint8_t*)String);



}
}



