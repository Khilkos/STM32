#include "Core_init.h"

#ifdef STM32F4
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
void Core_F4_init_HSE_full(uint32_t _PLL_M, uint32_t _PLL_N, uint32_t _PLL_P, uint32_t _PLL_Q, uint32_t AHB_DIV, uint32_t APB1_DIV, uint32_t APB2_DIV)
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
	
 //setup bus preskaler
if (AHB_DIV == 1 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
if (AHB_DIV == 2 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV2;
if (AHB_DIV == 4 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV4;
if (AHB_DIV == 8 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV8;
if (AHB_DIV == 16 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV16;
if (AHB_DIV == 64 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV64;	
if (AHB_DIV == 128 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV128;
if (AHB_DIV == 256 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV256;
if (AHB_DIV == 512 ) RCC->CFGR |= RCC_CFGR_HPRE_DIV512;

if (APB1_DIV == 1) RCC_CFGR_PPRE1_DIV1;
if (APB1_DIV == 2) RCC_CFGR_PPRE1_DIV2;
if (APB1_DIV == 4) RCC_CFGR_PPRE1_DIV4;
if (APB1_DIV == 8) RCC_CFGR_PPRE1_DIV8;
if (APB1_DIV == 16) RCC_CFGR_PPRE1_DIV16;

if (APB2_DIV == 1) RCC_CFGR_PPRE2_DIV1;
if (APB2_DIV == 2) RCC_CFGR_PPRE2_DIV2;
if (APB2_DIV == 4) RCC_CFGR_PPRE2_DIV4;
if (APB2_DIV == 8) RCC_CFGR_PPRE2_DIV8;
if (APB2_DIV == 16) RCC_CFGR_PPRE2_DIV16;

RCC->CFGR &= ~RCC_CFGR_SW;	
RCC->CFGR |=RCC_CFGR_SW_PLL ;	//switched System clock switch from PPL module
 while (!(RCC->CFGR &  RCC_CFGR_SWS_1)) ;	
}
//=========================================================


















#endif	
	
#ifdef STM32H7

void Core_STM32_H7_init (uint8_t DivM1, uint8_t DivN1, uint8_t DivP1, uint8_t DivQ1, uint8_t DivR1)
{

FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk | FLASH_ACR_WRHIGHFREQ_Msk);
FLASH->ACR = (FLASH_ACR_LATENCY_4WS | 2<<FLASH_ACR_WRHIGHFREQ_Pos);

RCC->CR |= (RCC_CR_HSEON); //enable external HSE clock
while (!(RCC->CR & RCC_CR_HSERDY)) __NOP();	//wait for HSE clock is enaled	

RCC->D1CFGR |= RCC_D1CFGR_D1CPRE_DIV1 | RCC_D1CFGR_D1PPRE_DIV2 | RCC_D1CFGR_HPRE_DIV2;	
RCC->D2CFGR |= RCC_D2CFGR_D2PPRE2_DIV2 | RCC_D2CFGR_D2PPRE1_DIV2;
RCC->D3CFGR |= RCC_D3CFGR_D3PPRE_DIV2;

RCC->PLLCKSELR &= ~(RCC_PLLCKSELR_DIVM1_Msk | RCC_PLLCKSELR_PLLSRC_Msk);	
RCC->PLLCKSELR |=	(uint32_t)DivM1<<RCC_PLLCKSELR_DIVM1_Pos | RCC_PLLCKSELR_PLLSRC_HSE;
//RCC->PLLCKSELR |=	1U<<RCC_PLLCKSELR_DIVM1_Pos | RCC_PLLCKSELR_PLLSRC_HSE;	
RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN | RCC_PLLCFGR_DIVQ1EN | RCC_PLLCFGR_DIVR1EN | 3U<<RCC_PLLCFGR_PLL1RGE_Pos;

RCC->PLL1DIVR &= ~(RCC_PLL1DIVR_N1_Msk | RCC_PLL1DIVR_P1_Msk | RCC_PLL1DIVR_Q1_Msk);	
RCC->PLL1DIVR |= ((uint32_t)(DivN1-1)<<RCC_PLL1DIVR_N1_Pos | (uint32_t)(DivP1-1)<<RCC_PLL1DIVR_P1_Pos | (uint32_t)(DivQ1-1)<<RCC_PLL1DIVR_Q1_Pos | (uint32_t)(DivR1-1)<<RCC_PLL1DIVR_R1_Pos);
//RCC->PLL1DIVR |= ((60-1)<<RCC_PLL1DIVR_N1_Pos | (2-1)<<RCC_PLL1DIVR_P1_Pos | (20-1)<<RCC_PLL1DIVR_Q1_Pos );
	
RCC->CR |= RCC_CR_PLL1ON;	//enable PLL
while (!(RCC->CR & RCC_CR_PLL1RDY)) __NOP();	

RCC->CFGR &=~(RCC_CFGR_SW_Msk);
RCC->CFGR |= RCC_CFGR_SW_PLL1; //switched System clock switch from PPL module
while (!(RCC->CFGR &  RCC_CFGR_SW_PLL1)) __NOP();		


	
}

#endif
	
	
	

