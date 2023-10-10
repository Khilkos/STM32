#include "RTC_F411.h"

uint8_t RTC_seconds=0;
uint8_t RTC_minutes=0;
uint8_t RTC_hours=0;
uint8_t RTC_day_of_week=0;
uint8_t RTC_day=0;
uint8_t RTC_month=0;
uint8_t RTC_year=0;


void RTC_F411_Unlock_reg (void)
{
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
}

//---------------------------------------
void RTC_F411_Init (void)
{
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_DBP;
	if (!(RCC->BDCR & RCC_BDCR_RTCEN))
		{
			RCC->BDCR |= 0x01<<RCC_BDCR_RTCSEL_Pos; //LSE tackting for RTC enamle
			RCC->BDCR |= RCC_BDCR_LSEON;
			while (!RCC_BDCR_LSERDY) {__NOP();}
			RCC->BDCR |= RCC_BDCR_RTCEN;
	//		GPIOB->BSRR =1<<14;
		}
	RTC_F411_Unlock_reg();
	RTC->ISR &= ~(RTC_ISR_RSF);
	
	if (!(RCC->BDCR & RCC_BDCR_RTCEN))
		{
			RTC->ISR |= RTC_ISR_INIT;
				while (!(RTC->ISR & RTC_ISR_INITF)) __NOP();
				RTC->PRER &= ~(0x7fUL<<RTC_PRER_PREDIV_A_Pos);
				RTC->PRER &=~ (0x7fffUL<<RTC_PRER_PREDIV_S_Pos);
			
				RTC->PRER |= 112UL<<RTC_PRER_PREDIV_A_Pos;
				RTC->PRER |= 289UL<<RTC_PRER_PREDIV_S_Pos;			
			
				RTC->CR |= RTC_CR_DCE; //разрешение грубой цифровой калибровки
				RTC->CALIBR |= (RTC_CALIBR_DCS); //грубая корректировка хода часов, 0 - положительная, 1- отрицательная
				RTC->CALIBR &= ~(0x1fUL<<RTC_CALIBR_DC_Pos);
				RTC->CALIBR |= 22UL<<RTC_CALIBR_DC_Pos; 	//калибровочный коэффициент, максимум 31
			RTC->ISR &=~(RTC_ISR_INIT);
//	GPIOB->BSRR =1<<13;
		}
}

//---------------------------------------
void RTC_F411_read_time_date (void)
{
	uint32_t temp;
	if (RTC_ISR_RSF)
	{
		RTC->ISR &=~RTC_ISR_RSF;
		temp = RTC->TR;
		RTC_seconds = (uint8_t)( (((temp&0x00000070)>>4)*10) + (temp&0x0000000f) );
		RTC_minutes = (uint8_t)( (((temp&0x00007000)>>12)*10) + ((temp&0x00000f00)>>8));
		RTC_hours = (uint8_t)( (((temp&0x00300000)>>20)*10) + ((temp&0x000f0000)>>16) );
		temp = RTC->DR;
		RTC_year = (uint8_t)((((temp&0x00f00000)>>20)*10) + ((temp&0x000f0000)>>16) );
		RTC_day_of_week = (uint8_t)( (temp&0xe000)>>13 );
		RTC_month = (uint8_t)( (((temp&0x1000)*10)>>12) + ((temp&0xf00)>>8) );
		RTC_day = (uint8_t)( (((temp&0x30)>>4)*10) + (temp&0xf));
	
	}
}
//---------------------------------------
void RTC_F411_write_time_date (void)
{
	uint32_t temp=0;
	RTC->ISR |= RTC_ISR_INIT;
	while (!(RTC->ISR & RTC_ISR_INITF)) __NOP();
		temp |= (uint32_t)(((RTC_seconds/10)<<4) | (RTC_seconds%10));
		temp |= (uint32_t)(((RTC_minutes/10)<<12) | ((RTC_minutes%10)<<8) );
		temp |= (uint32_t)(((RTC_hours/10)<<20) | ((RTC_hours%10)<<16) );
	RTC->TR = temp;
		temp=0;
		temp |= (uint32_t)( ((RTC_year/10)<<20) | ((RTC_year%10)<<16) );
		temp |= (uint32_t)( ((RTC_day_of_week)<<13) );
		temp |= (uint32_t)( ((RTC_month/10)<<12) | ((RTC_month%10)<<8) );
		temp |= (uint32_t)( ((RTC_day/10)<<4) | (RTC_day%10) );
	RTC->DR = temp;	
	
	RTC->ISR &=~(RTC_ISR_INIT);
}	
	
	





