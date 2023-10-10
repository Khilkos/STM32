#include "EXTI_F411_init.h"


void EXTI_F411_init(void)
{
EXTI->RTSR |=( 1<<0 | 1<<1 | 1<<2 ); //enable rising triger for exti0 and exti1 and exti2 line interrupt
SYSCFG->EXTICR[0] |=( SYSCFG_EXTICR1_EXTI0_PB | SYSCFG_EXTICR1_EXTI1_PB | SYSCFG_EXTICR1_EXTI2_PB );//0x1UL<<0*4; 	Sourse for EXTI0 and EXTI1 and EXTI2 line is PORTB
NVIC->ISER[0]=( 1<<6 | 1<<7 | 1<<8 );
EXTI->IMR |= (1<<0 | 1<<1 | 1<<2 ) ;	//enable EXTI0 lene interrupt mask		
}





//----------------------------
void EXTI0_IRQHandler(void)
{
	EXTI->PR |=1<<0;
//	GPIOB->BSRR = 1UL<<(15+res);
//	GPIOB->BSRR=1<<12; 
}

//----------------------------
void EXTI1_IRQHandler(void)
{
	EXTI->PR |=1<<1;
//	GPIOB->BSRR=1<<(12+res); 
//	GPIOB->BSRR = 1UL<<(15+res);
}

//----------------------------
void EXTI2_IRQHandler(void)
{
	EXTI->PR |=1<<2;
//GPIOB->BSRR = 1<<13;
}
