#include "main.h"

#define res 16
#define Y_time_poz 10
#define X_time_poz 0
uint8_t day_of_week[7][3]={"��","��","��","��","��","��","��"};
char String[100];
uint16_t fault=0;

int main(void)
{

	
Core_F4_init_HSE(25,192,2,4);
SysTick_Init();	
Timer1_F4_init(96000000,1000);
DMA_F4_init();
	
RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN  ); // enable portA and portB clock
	
I2C_F411_init();
SPI_F4_init(7);
RTC_F411_Init();
USART_F411_init();


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


//-----------------------
ADC_Init.ADC_Resolution=  12;//6,8,10,12 ��� ����������� ����������� ���
ADC_Init.ADC_Prescaler=  8;//2,4,6,8 ����� ����������� PCLK2 ��� ������ ���
ADC_Init.ADC_Quantity_of_chanel= 2 ; //���������� ������� ��� ��������������, 1- ���� ��������������, 16(�����������)- 16 ��������������
ADC_Init.ADC_ch1= 0 ; //����� ������ ��� (�����������) ��� 1-�� ��������������, ��������� � ADC_ch[1]
ADC_Init.ADC_ch2=  1; //����� ������ ��� (�����������) ��� 2-�� ��������������, ��������� � ADC_ch[2]
//ADC_Init.ADC_ch3=  ; //����� ������ ��� (�����������) ��� 3-�� ��������������, ��������� � ADC_ch[3]
ADC_Init.ADC_Sample_time= 480 ; // ��������� ������� ������������� � ������ 3,15,28,56,84,112,144,480
ADC_Init.ADC_Average_val=  10000;// ������� ���������� ���������� ���, ����� ��� ���� ������� 
DMA_F4_ADC_init();
ADC_F4_init_via_DMA();
//-----------------------


delay_ms(100);
LCD_init();

//DS18B20_read_ROM();
	
while(1)
{
//fault=0;
GPIOB->BSRR=1<<13;
//key_scan();
//fault=1;	
RTC_F411_read_time_date();
//fault=2;	
//	GPIOB->BSRR=1<<(13+16);
DS3231_F411_get_time();
//fault=3;	

	//GPIOB->BSRR=1<<(13+16);
	
	DS18B20_read_temperatur_of_2_sensor(ROM_work, ROM_work_1,DS18B20_temperature_of_2_sensor);	
//fault=4;	
	sprintf(String,"%02x%02x%02x%02x%02x%02x%02x%02x",ROM[7],ROM[6],ROM[5],ROM[4],ROM[3],ROM[2],ROM[1],ROM[0] );	
//	sprintf(String,"����� %02d:%02d:%02d DS3231",hour, minutes,seconds );
//fault=5;	
	LCD_string(0,0,(uint8_t*)String);	
//fault=6;	
	if (clock_poz) 	line(8,17+18*clock_poz,8,28+18*clock_poz);	
//fault=7;		
	sprintf(String,"%02d:%02d:%02d",hour, minutes,seconds );
//fault=8;
	LCD_string_font_10x16(32,0,(uint8_t*)String);
//	sprintf(String,"Prediv_A/S %d/%d",(RTC->PRER & 0x7f0000)>>16, RTC->PRER & 0x7fff);
//	LCD_string(32,0,(uint8_t*)String);
	
//	sprintf(String,"DC_calibr %d", (0x1f&RTC->CALIBR));
//	LCD_string(40,0,(uint8_t*)String);
	
	sprintf(String,"ADC_ch0/1= %.2f/%.2fB", (double)ADC_ch[1]/1262, (double)ADC_ch[2]/1262 );
//fault=9;	
	LCD_string (48,0, (uint8_t*)String);
//fault=10;  
	sprintf(String,"������. %.1f / %.1f",DS18B20_temperature_of_2_sensor[0]*0.1, DS18B20_temperature_of_2_sensor[1]*0.1 );
//GPIOB->BSRR=1<<(13+16);
//fault=11;
LCD_string (56,0, (uint8_t*)String);
//fault=12;	
	sprintf(String,"����� %02d:%02d:%02d RTC", RTC_hours, RTC_minutes, RTC_seconds);
//fault=13;
LCD_string (Y_time_poz,X_time_poz, (uint8_t*)String);	
//fault=14;
	sprintf(String,"���� %s/%02d/%02d/%02d", day_of_week[RTC_day_of_week-1], RTC_day, RTC_month,  RTC_year+2000 );
//fault=15;
LCD_string (Y_time_poz+10,X_time_poz, (uint8_t*)String);	

	if (clock_poz_1 && clock_poz_1<4 ) 	line(Y_time_poz+8,X_time_poz+18+18*clock_poz_1,Y_time_poz+8,X_time_poz+28+18*clock_poz_1);	
	if (clock_poz_1 && clock_poz_1>3 && clock_poz_1<7 ) 	line(Y_time_poz+18,X_time_poz+12+18*(clock_poz_1-3),Y_time_poz+18,X_time_poz+22+18*(clock_poz_1-3));	
	if (clock_poz_1 && clock_poz_1==7) line(Y_time_poz+18,X_time_poz +12+18*(clock_poz_1-3),Y_time_poz+18,X_time_poz+34+18*(clock_poz_1-3));
//fault=16;
//LCD_out();
LCD_DMA_out();
//	delay_ms(500);
//fault=17;	
if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;
	
}	
}





