
#include "Board.h"

uint8_t clock_poz =0;
uint8_t clock_poz_1 =0;
#define key_delay_val 520
#define select_delay_val 10000
uint16_t encoder_data=100;	


void key_scan (void)
{
	
static uint8_t encoder_state;
uint8_t pin_state=0;
	if (GPIOA->IDR & 1<<11) pin_state |=1<<0;
	if (GPIOA->IDR & 1<<10) pin_state |=1<<1;	
	
	if (encoder_state==3)
					{
						if (pin_state==2) encoder_data++;
						if (pin_state==1) encoder_data--;
						
					}
					
	encoder_state=pin_state;
		
		
		
	/*
if (!select_delay) {clock_poz=0; clock_poz_1=0;}	
	
if (!key_delay) 
	{
			if ( GPIOB->IDR & 1<<2 ) 
				{	 if (clock_poz>5) clock_poz=0; else clock_poz++;	
					 key_delay=key_delay_val;
					select_delay=select_delay_val;
				}
			
				if (clock_poz==1)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (hour<23) hour++; else hour=0;
								DS3231_F411_set_hour(hour);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (hour>0) hour--; else hour=23;
								DS3231_F411_set_hour(hour);
							}
					}	

				if (clock_poz==2)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (minutes<59) minutes++; else minutes=0;
								DS3231_F411_set_minutes(minutes);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (minutes>0) minutes--; else minutes=59;
								DS3231_F411_set_minutes(minutes);
							}
					}

					if (clock_poz==3)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (seconds<59) seconds++; else seconds=0;
								DS3231_F411_set_seconds(seconds);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (seconds>0) seconds--; else seconds=59;
								DS3231_F411_set_seconds(seconds);
							}
					}

					if (clock_poz==4)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (((day<31)&&((month==1)||(month==3)||(month==5)||(month==8)||(month==10)||(month==12))) || ((day<30)&&((month==4)||(month==6)||(month==7)||(month==9)||(month==11))) || ((day<28)&&(month==2))) day++; else day=1;
								DS3231_F411_set_day(day);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
									if (day>1) day--; else 
														{	if (month==1||month==3||month==5||month==8||month==10||month==12) day=31;
															if (month==4||month==6||month==7||month==9||month==11) day=30;
															if (month==2) day=28;
														}
								DS3231_F411_set_day(day);
							}
					}
				
					if (clock_poz==5)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (month<12) month++; else month=1;
								DS3231_F411_set_month(month);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (month>1) month--; else month=12;
								DS3231_F411_set_month(month);
							}
					}
					
						if (clock_poz==6)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (year<99) year++; else year=24;
								DS3231_F411_set_year(year);
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (year>24) year--; else year=99;
								DS3231_F411_set_year(year);
							}
					}
								
	}*/
}

