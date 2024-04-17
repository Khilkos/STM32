#include "Core_init.h"


void Core_F411_init(void)
{
RCC->CR =RCC_CR_HSEON;	//enable external HSE clock
while (!(RCC->CR & RCC_CR_HSERDY));	//wait for HSE clock is enaled

FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_3WS );		
	

	
RCC->PLLCFGR =( RCC_PLLCFGR_PLLSRC_HSE | PLL_N<<6 | PLL_M<<0 |PLL_P<<16 | PLL_Q<<24 ); //setup PLL module	
RCC->CR |= RCC_CR_PLLON;	//enable PLL
while (!(RCC->CR & RCC_CR_PLLRDY)) __NOP();
	
RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 ); //setup bus preskaler

	
RCC->CFGR &= ~RCC_CFGR_SW;	
RCC->CFGR |=RCC_CFGR_SW_PLL ;	//switched System clock switch from PPL module
 while (!(RCC->CFGR &  RCC_CFGR_SWS_1)) ;	
}
//=========================================================

void Core_F401_init_HSI(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q) //M-16, N-336, P-4, Q-7
	{
	uint32_t temp_PLL_P=0;
if (_PLL_P==2) temp_PLL_P=0;
if (_PLL_P==4) temp_PLL_P=1;
if (_PLL_P==6) temp_PLL_P=2;
if (_PLL_P==8) temp_PLL_P=3;		
		
RCC->CR |=RCC_CR_HSION; //enable internal HSI clock 
while (!(RCC->CR & RCC_CR_HSIRDY)); //wait for HSI clock in  enabled

FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_3WS );				
	
RCC->PLLCFGR =( RCC_PLLCFGR_PLLSRC_HSI | _PLL_M<<0 | _PLL_N<<6 | temp_PLL_P<<16 | _PLL_Q<<24  ); //setup PLL module		

RCC->CR |= RCC_CR_PLLON;	//enable PLL
while (!(RCC->CR & RCC_CR_PLLRDY)) __NOP();

RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 ); //setup bus preskaler

RCC->CFGR &= ~RCC_CFGR_SW;	
RCC->CFGR |=RCC_CFGR_SW_PLL ;	//switched System clock switch from PPL module
 while (!(RCC->CFGR &  RCC_CFGR_SWS_1)) ;			
}
//==========================================================
void Core_F4_init_HSE(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q)
{
	uint32_t temp_PLL_P=0;
if (_PLL_P==2) temp_PLL_P=0;
if (_PLL_P==4) temp_PLL_P=1;
if (_PLL_P==6) temp_PLL_P=2;
if (_PLL_P==8) temp_PLL_P=3;		
RCC->CR =RCC_CR_HSEON;	//enable external HSE clock
while (!(RCC->CR & RCC_CR_HSERDY));	//wait for HSE clock is enaled

FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_3WS );		
	
RCC->PLLCFGR =( RCC_PLLCFGR_PLLSRC_HSE | _PLL_M<<0 | _PLL_N<<6 | temp_PLL_P<<16 | _PLL_Q<<24  ); //setup PLL module		
RCC->CR |= RCC_CR_PLLON;	//enable PLL
while (!(RCC->CR & RCC_CR_PLLRDY)) __NOP();
	
RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 ); //setup bus preskaler
	
RCC->CFGR &= ~RCC_CFGR_SW;	
RCC->CFGR |=RCC_CFGR_SW_PLL ;	//switched System clock switch from PPL module
 while (!(RCC->CFGR &  RCC_CFGR_SWS_1)) ;	
}
//=========================================================
	
	

