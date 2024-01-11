
#include "Board.h"

uint8_t clock_poz =0;
uint8_t clock_poz_1 =0;
#define key_delay_val 520
#define select_delay_val 10000


void key_scan (void)
{
if (!select_delay) {clock_poz=0; clock_poz_1=0;}	
	
if (!key_delay) 
	{
			if ( GPIOB->IDR & 1<<2 ) 
				{	 if (clock_poz>2) clock_poz=0; else clock_poz++;	
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

					
				
					
				//=========================================
				
					if ( GPIOB->IDR & 1<<10 ) 
				{	 if (clock_poz_1>=7) clock_poz_1=0; else clock_poz_1++;	
					key_delay=key_delay_val;
					select_delay=select_delay_val;
				}
				
				
				
				if (clock_poz_1==1)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_hours<23) RTC_hours++; else RTC_hours=0;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_hours>0) RTC_hours--; else RTC_hours=23;
								RTC_F411_write_time_date();
							}
					}	

				if (clock_poz_1==2)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_minutes<59) RTC_minutes++; else RTC_minutes=0;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_minutes>0) RTC_minutes--; else RTC_minutes=59;
								RTC_F411_write_time_date();
							}
					}

					if (clock_poz_1==3)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_seconds<59) RTC_seconds++; else RTC_seconds=0;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_seconds>0) RTC_seconds--; else RTC_seconds=59;
								RTC_F411_write_time_date();
							}
					}

					if (clock_poz_1==4)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_day_of_week<7) RTC_day_of_week++; else RTC_day_of_week=1;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_day_of_week>1) RTC_day_of_week--; else RTC_day_of_week=7;
								RTC_F411_write_time_date();
							}
					}
					
					if (clock_poz_1==5)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (((RTC_day<31)&&((RTC_month==1)||(RTC_month==3)||(RTC_month==5)||(RTC_month==8)||(RTC_month==10)||(RTC_month==12))) || ((RTC_day<30)&&((RTC_month==4)||(RTC_month==6)||(RTC_month==7)||(RTC_month==9)||(RTC_month==11))) || ((RTC_day<28)&&(RTC_month==2))) RTC_day++; else RTC_day=1;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_day>1) RTC_day--; else 
														{	if (RTC_month==1||RTC_month==3||RTC_month==5||RTC_month==8||RTC_month==10||RTC_month==12) RTC_day=31;
															if (RTC_month==4||RTC_month==6||RTC_month==7||RTC_month==9||RTC_month==11) RTC_day=30;
															if (RTC_month==2) RTC_day=28;
														}
								RTC_F411_write_time_date();
							}
					}
					
					if (clock_poz_1==6)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_month<12) RTC_month++; else RTC_month=1;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_month>1) RTC_month--; else RTC_month=12;
								RTC_F411_write_time_date();
							}
					}
					
					
					if (clock_poz_1==7)
					{
						if ( GPIOB->IDR & 1<<1) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_year<99) RTC_year++; else RTC_year=23;
								RTC_F411_write_time_date();
							}
						if ( GPIOB->IDR & 1<<0) 
							{	key_delay=key_delay_val;
								select_delay=select_delay_val;
								if (RTC_year>23) RTC_year--; else RTC_year=99;
								RTC_F411_write_time_date();
							}
					}
					

	}
}

