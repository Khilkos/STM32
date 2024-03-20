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


SPI_F4_init(2);
Nokia_5110_init(72);


	
	while (1)
	{
	
//		GPIOA->BSRR = 1<<(5);
		GREEN_ON;
			delay_ms(led_delay);
//		GPIOA->BSRR = 1<<(5+16);
		GREEN_OFF;
				delay_ms(led_delay);
	
	if (!(GPIOA->IDR & 1<<10)) RED_ON; else RED_OFF;
	
		
Nokia_5110_send_command(128+5);	
Nokia_5110_send_command(64+1);
Nokia_5110_send_data(0xff);	
		Nokia_5110_send_data(0xff);	
		Nokia_5110_send_data(0xff);	
	
	
	}
	
}
