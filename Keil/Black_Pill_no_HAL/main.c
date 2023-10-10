#include "main.h"

#define res 16
#define Y_time_poz 10
#define X_time_poz 0
uint8_t day_of_week[7][3]={"Пн","Вт","Ср","Чт","Пт","Сб","Вс"};
char String[100];
uint32_t i=12;	

int main(void)
{
Core_F411_init();
SysTick_Init();	
Timer_F411_init();

RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock


GPIO_DO_setup(GPIOB,15,High);
GPIO_DO_setup(GPIOB,12,High);
GPIO_DO_setup(GPIOA,6,High);
GPIO_DO_setup(GPIOC,13,High);
GPIO_DO_setup(GPIOB,13,High);
GPIO_DO_setup(GPIOB,14,High);

GPIO_DI_setup(GPIOB,0,Pull_down);
GPIO_DI_setup(GPIOB,1,Pull_down);
GPIO_DI_setup(GPIOB,2,Pull_down);
GPIO_DI_setup(GPIOB,10,Pull_down);
//GPIO_DI_setup(GPIOA,3,No_pull);	//USART2 RX2
	
GPIO_Alternate(GPIOA,7,Push_pull,High,No_pull,AF5);
GPIO_Alternate(GPIOA,5,Push_pull,High,No_pull,AF5);
GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);
GPIO_Alternate(GPIOA,2,Open_drain,High,Pull_up,AF7);// USART2 TX2
GPIO_Alternate(GPIOA,3,Open_drain,High,Pull_up,AF7);// USART2 RX2
	
GPIO_Analog_setup (GPIOA,0);
GPIO_Analog_setup (GPIOA,1);
//GPIO_Analog_setup (GPIOA,2);

I2C_F411_init();
SPI_F411_init();
RTC_F411_Init();
EXTI_F411_init();
DMA_F411_init();
DMA_F411_ADC_init();
ADC1_F411_Init();
UART_F411_init();



delay_ms(100);
LCD_init();

	
while(1)
{
	
key_scan();
	RTC_F411_read_time_date();
	DS3231_F411_get_time();
	
		
	sprintf(String,"Время %02d:%02d:%02d DS3231",hour, minutes,seconds );
	LCD_string(0,0,(uint8_t*)String);	
	if (clock_poz) 	line(8,17+18*clock_poz,8,28+18*clock_poz);	
	
	sprintf(String,"Prediv_A/S %d/%d",(RTC->PRER & 0x7f0000)>>16, RTC->PRER & 0x7fff);
	LCD_string(32,0,(uint8_t*)String);
	
	sprintf(String,"DC_calibr %d", (0x1f&RTC->CALIBR));
	LCD_string(40,0,(uint8_t*)String);
	
	sprintf(String,"ADC_ch0/1= %.2f/%.2fB", (double)ADC_ch0/1262, (double)ADC_ch1/1262 );
	LCD_string (48,0, (uint8_t*)String);

	sprintf(String,"Темпер. %.1f", (test_DMA()*0.1));
	LCD_string (56,0, (uint8_t*)String);
//	sprintf(String,"clock_poz %d", clock_poz);
//	LCD_string(48,0,(uint8_t*)String);
	
	
//	sprintf(String,"clock_poz_1 %d", clock_poz_1);
//	LCD_string(56,0,(uint8_t*)String);
	
	
	sprintf(String,"Время %02d:%02d:%02d RTC", RTC_hours, RTC_minutes, RTC_seconds);
	LCD_string (Y_time_poz,X_time_poz, (uint8_t*)String);	

	sprintf(String,"Дата %s/%02d/%02d/%02d", day_of_week[RTC_day_of_week-1], RTC_day, RTC_month,  RTC_year+2000 );
	LCD_string (Y_time_poz+10,X_time_poz, (uint8_t*)String);	

	if (clock_poz_1 && clock_poz_1<4 ) 	line(Y_time_poz+8,X_time_poz+18+18*clock_poz_1,Y_time_poz+8,X_time_poz+28+18*clock_poz_1);	
	if (clock_poz_1 && clock_poz_1>3 && clock_poz_1<7 ) 	line(Y_time_poz+18,X_time_poz+12+18*(clock_poz_1-3),Y_time_poz+18,X_time_poz+22+18*(clock_poz_1-3));	
	if (clock_poz_1 && clock_poz_1==7) line(Y_time_poz+18,X_time_poz +12+18*(clock_poz_1-3),Y_time_poz+18,X_time_poz+34+18*(clock_poz_1-3));
	
	
LCD_out();


//	sprintf(String,"ADC_ch0 %.2fB", (double)ADC_ch0/1235 );
//LCD_string (32,X_time_poz, (uint8_t*)String);
	
	

	
if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;	
	//GPIOB->BSRR=1<<14;	
}	
}





