#include "Core_F411_init.h"


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

