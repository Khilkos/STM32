#include "main.h"

#define led_delay 50
#define GREEN_ON 	GPIOC->BSRR = 1<<(5)
#define GREEN_OFF GPIOC->BSRR = 1<<(5+16)
#define RED_ON 	GPIOC->BSRR = 1<<(6)
#define RED_OFF GPIOC->BSRR = 1<<(6+16)
#define WHITE_ON 	GPIOC->BSRR = 1<<(8)
#define WHITE_OFF GPIOC->BSRR = 1<<(8+16)
#define YELLOW_ON 	GPIOC->BSRR = 1<<(9)
#define YELLOW_OFF GPIOC->BSRR = 1<<(9+16)

//static char String[100];

	

int main(void)
{
Core_F401_init_HSI(16,336,4,7);
SysTick_F4_Init (84);	
	
RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN ;

GPIO_Alternate(GPIOA,7,Push_pull,High,No_pull,AF5);// SPI MOSI_1
GPIO_Alternate(GPIOA,5,Push_pull,High,No_pull,AF5);// SPI CLK_1	
	
//GPIO_DO_setup(GPIOA,5,High);
GPIO_DO_setup(GPIOC,5,High);
GPIO_DO_setup(GPIOC,6,High);
GPIO_DO_setup(GPIOC,8,High);
GPIO_DO_setup(GPIOC,9,High);
	GPIO_DO_setup(GPIOB,8,High); //Nokia 5110_RST	
GPIO_DO_setup(GPIOB,9,High); //nokia 5110_CE
GPIO_DO_setup(GPIOA,6,High); //Nokia 5110_D/C

	GPIO_DI_setup(GPIOA,10,No_pull);// A
	GPIO_DI_setup(GPIOB,3,No_pull);// B
	GPIO_DI_setup(GPIOB,5,No_pull);// C
	GPIO_DI_setup(GPIOB,4,No_pull);// D
	GPIO_DI_setup(GPIOB,10,No_pull);// E
	GPIO_DI_setup(GPIOA,8,No_pull);// F
	GPIO_DI_setup(GPIOA,9,No_pull);// Key

GPIO_Analog_setup (GPIOA,0);//ADC_X
GPIO_Analog_setup (GPIOA,1);//ADC_Y
GPIO_Analog_setup (GPIOB,1);//ADC9

Timer1_F4_init(84000000,1000);
Timer2_F4_init(84000000,9856);
SPI_F4_init(2);
Nokia_5110_init(72);
DMA_F4_init();

//-----------------------
ADC_Init.ADC_Resolution=12;//6,8,10,12 бит разрешающая способность АЦП
ADC_Init.ADC_Prescaler=8;//2,4,6,8 выбор пределителя PCLK2 для работы АЦП
ADC_Init.ADC_Quantity_of_chanel=3;//количество каналов для преобразования, 1- одно преобразование, 16(максимально)- 16 преобразований
ADC_Init.ADC_ch1=0;//выбор канала АЦП (физического) для 1-го преобразования
ADC_Init.ADC_ch2=1;//выбор канала АЦП (физического) для 2-го преобразования
ADC_Init.ADC_ch3=9;//выбор канала АЦП (физического) для 3-го преобразования
ADC_Init.ADC_Sample_time=480;// установка времени семплирования в тактах 3,15,28,56,84,112,144,480
ADC_Init.ADC_Average_val= 1;// глубина усреднения результата АЦП, общая для всех каналов 
DMA_F4_ADC_init();
ADC_F4_init_via_DMA();
//-----------------------

RCC->APB1ENR |= RCC_APB1ENR_PWREN;
PWR->CR |= PWR_CR_DBP;

//RCC->BDCR|=RCC_BDCR_RTCSEL_1;
RCC->BDCR |= 0x01<<RCC_BDCR_RTCSEL_Pos; //LSE tackting for RTC enamle
RCC->BDCR |= RCC_BDCR_LSEON;
			while (!RCC_BDCR_LSERDY) {__NOP();}

//RCC->CSR |=RCC_CSR_LSION;			
//while (!RCC_CSR_LSIRDY) {__NOP();}
RCC->BDCR |= RCC_BDCR_RTCEN;
	
	while (1)
	{
Nokia_5110_clr_screen_buf();		
//if (!TIM2_Delay_1) {if (GPIOC->IDR &1 <<5) GREEN_OFF; else GREEN_ON; TIM2_Delay_1=1000; }

		
//			delay_ms(led_delay);
//		GPIOA->BSRR = 1<<(5+16);
	//	GREEN_OFF;
	//			delay_ms(led_delay);
	
	if (!(GPIOA->IDR & 1<<10)) {RED_ON; Nokia_5110_clr_screen_buf();} else RED_OFF;
//sprintf(String,"%d",15%8 );
//sprintf(String,"Коорд.Х-%04d",ADC_ch[0]);
//Nokia_5110_String(0,0,(uint8_t*)String);
//sprintf(String,"Коорд.Y-%04d",ADC_ch[1]);
//Nokia_5110_String(0,8,(uint8_t*)String);	
	
Game_Car();		
Nokia_5110_LCD_Out();		

	
	
	}
	
}
