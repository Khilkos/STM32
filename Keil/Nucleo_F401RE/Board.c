#include "Board.h"
uint8_t Menu_poz=0; 	
uint8_t Cursor_poz=0;

void key_scan(void)
{

	if (!TIM1_Delay_3 && !(GPIOB->IDR & 1<<5)) 
			{
				TIM1_Delay_3=250; 
				if (Cursor_poz==5 && Menu_poz<7) Menu_poz++;
				if (Cursor_poz<5) Cursor_poz++;
			}
	if (!TIM1_Delay_3 && !(GPIOA->IDR & 1<<10))
			{
				TIM1_Delay_3=250;
				if (Cursor_poz==0 && Menu_poz!=0) Menu_poz--;
				if (Cursor_poz>0) Cursor_poz--;
			}



}

