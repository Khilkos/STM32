#include "PROMLED.h"

void Promled_kvantum_out (uint8_t size_led, uint8_t (*Led_RGB)[3])
{
uint8_t	temp=0;	
	
for (uint8_t i=0; i<64; i++) {if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;	delay_us(Promled_kvantum_delay);}
delay_us(Promled_kvantum_delay*4);


for (uint8_t led_num=0; led_num<size_led; led_num++)
	{
		temp=pre_led;
		for (uint8_t i=0;i<8;i++)
			{	
				if (temp&0x80) GPIOB->BSRR=1<<13; else GPIOB->BSRR=1<<(13+res);
				temp<<=1;
				GPIOB->BSRR=1<<12;
				delay_us(Promled_kvantum_delay);
				GPIOB->BSRR=1<<(12+res);
				if (i==0 || i==2 || i==4 || i==6)	delay_us(Promled_kvantum_delay); else delay_us(Promled_kvantum_delay*4);
			}
		GPIOB->BSRR=1<<(13+res);

			for (uint8_t color_led=0; color_led<3;color_led++)
				{
					temp=*(*(Led_RGB+led_num)+color_led);
						for (uint8_t i=0; i<8; i++)
							{
								if (temp&0x80) GPIOB->BSRR=1<<13; else GPIOB->BSRR=1<<(13+res);
								GPIOB->BSRR=1<<12;
								delay_us(Promled_kvantum_delay);
								GPIOB->BSRR=1<<(12+res);
								delay_us(Promled_kvantum_delay);
								temp<<=1;
							}
						GPIOB->BSRR=1<<(13+res);
				delay_us(Promled_kvantum_delay*3);
				}
				
		}

for (uint8_t i=0; i<64; i++) {if (GPIOB->IDR&1<<12) GPIOB->BSRR=1<<(12+res); else GPIOB->BSRR=1<<12;	delay_us(Promled_kvantum_delay);}
delay_ms(25);	
}	


