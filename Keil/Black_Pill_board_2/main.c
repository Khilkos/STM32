#include "main.h"
#define CLK_ON GPIOB->BSRR = 1<<12
#define CLK_OFF GPIOB->BSRR = 1<<(12+ res)
#define R1_ON GPIOB->BSRR = 1<<13
#define R1_OFF GPIOB->BSRR = 1<<(13+ res)
#define LAT_ON GPIOB->BSRR = 1<<14
#define LAT_OFF GPIOB->BSRR = 1<<(14+ res)
#define OE_ON GPIOB->BSRR = 1UL<<15
#define OE_OFF GPIOB->BSRR = 1UL<<(15+ res)


int main (void)
	
{
 char String[300];
uint16_t tmp=0;

static uint32_t led_buf = 0x0F0F0f0f;
static uint32_t temp32=0;

 static uint8_t Led_RGB2_1 [2][3]=	{	{255,0,0},{0,0,0}	};
 static uint8_t Led_RGB2_2 [2][3]=	{	{0,0,0},{0,0,255}	};
 static uint8_t Led_RGB2_3 [2][3]=	{	{0,0,0},{0,0,0}	};
 
 static uint8_t Led_RGB10_1 [10][3]=	{	{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}	};	
 static uint8_t Led_RGB10_2 [10][3]=	{	{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,255},{0,0,255},{0,0,255},{0,0,255},{0,0,255}	};	
 static uint8_t Led_RGB10_3 [10][3]=	{	{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}	};	
 
	
	
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN ); // enable portA and portB clock

	
GPIO_DO_setup(GPIOB,12,High);	
GPIO_DO_setup(GPIOB,13,High);	
	 GPIOB->OTYPER |=1<<13;
	 GPIOB->PUPDR |=2<<(13*2);
GPIO_DO_setup(GPIOB,14,High);	
GPIO_DO_setup(GPIOB,15,High);	
GPIO_DO_setup(GPIOB,8,High); //Nokia 5110_RST	
GPIO_DO_setup(GPIOB,9,High); //nokia 5110_CE
GPIO_DO_setup(GPIOA,6,High); //Nokia 5110_D/C
GPIO_DO_setup(GPIOC,13,High);

//GPIOB->BSRR|=1<<8;	
//GPIO_DO_setup(GPIOA,4,High);	
	
GPIO_Alternate(GPIOA,7,Push_pull,High,No_pull,AF5);// SPI MOSI_1
GPIO_Alternate(GPIOA,5,Push_pull,High,No_pull,AF5);// SPI CLK_1
//GPIO_Alternate(GPIOA,4,Push_pull,High,Pull_up,AF5);// SPI NSS_1


/*
GPIO_DI_setup(GPIOA,15,No_pull);//���������� jtag
GPIO_DO_setup(GPIOA,15,High);
	
GPIO_DI_setup(GPIOB,3,No_pull);//���������� jtag
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
	
	
Core_F4_init_HSE(25,192,2,4);
SysTick_Init();
Timer1_F4_init(96000000,1000);
I2C_F411_init();
DMA_F4_init();
USART_F411_init();
LCD1602_init_via_I2C();
SPI_F4_init(4);
//Nokia_5110_init(65);


while (1)
{
key_scan();
/*
#define delay3 20	
	Promled_kvantum_out(2,Led_RGB2_1);	
delay_ms(delay3);	
Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
Promled_kvantum_out(2,Led_RGB2_1);	
delay_ms(delay3);	
Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
Promled_kvantum_out(2,Led_RGB2_1);	
delay_ms(delay3);
	Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
	
	delay_ms(delay3*2);

	Promled_kvantum_out(2,Led_RGB2_2);	
delay_ms(delay3);
Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
	Promled_kvantum_out(2,Led_RGB2_2);	
delay_ms(delay3);
	Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
		Promled_kvantum_out(2,Led_RGB2_2);	
delay_ms(delay3);
	Promled_kvantum_out(2,Led_RGB2_3);	
delay_ms(delay3);
	

	
	
	
	
	
*/


sprintf(String,"Encoder = %02d / %d",encoder_data,SPI1_send_num);
Draw_String(0,(uint8_t*)String);	
	
DS18B20_read_temperatur_of_2_sensor(ROM1,ROM2,DS18B20_temperature_of_2_sensor);	
sprintf(String,"Temp. %04.1f/%04.1f",DS18B20_temperature_of_2_sensor[0]*0.1, DS18B20_temperature_of_2_sensor[1]*0.1);
//sprintf(String,"%02x%02x%02x%02x%02x%02x%02x%02x",ROM[7],ROM[6],ROM[5],ROM[4],ROM[3],ROM[2],ROM[1],ROM[0] );

Draw_String(0x40, (uint8_t*)String);

	sprintf(String,"����� 1234");
//	Nokia_5110_String(0,0,(uint8_t*)String);
//	Nokia_5110_LCD_Out();
//Nokia_test();


if (!TIM1_Delay_2) { if (GPIOC->IDR & 1<<13) GPIOC->BSRR = 1<<(13+res); else	GPIOC->BSRR = 1<<(13);	TIM1_Delay_2=250;}
if (!TIM1_Delay_3) { if (GPIOB->IDR & 1<<12) GPIOB->BSRR = 1<<(12+res); else	GPIOB->BSRR = 1<<(12);	TIM1_Delay_3=500;}

	
	
	
}

}

