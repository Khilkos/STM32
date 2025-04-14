#include "GPIO_setup.h"
#include "stm32f407xx.h"

void GPIO_DO_setup (GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t Output_speed)
{
PORT->MODER &= ~(0x3UL<<PIN_number*2);
PORT->MODER |= (1U<<PIN_number*2);
PORT->OSPEEDR |=(Output_speed<<PIN_number*2);	
}

void GPIO_DI_setup (GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t Pull_mode)
{
PORT->MODER &= ~(0x3UL<<PIN_number*2);
PORT->PUPDR |=(Pull_mode<<PIN_number*2);	
	
}

void GPIO_Alternate(GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t OTYPER, uint32_t Output_speed, uint32_t Pull_mode, uint32_t Alternate_function)
{
PORT->MODER &= ~(0x3UL<<PIN_number*2);
PORT->MODER |= (2UL<<PIN_number*2);
PORT->OTYPER |= OTYPER<<PIN_number;
PORT->OSPEEDR |=(Output_speed<<PIN_number*2);	
PORT->PUPDR |=(Pull_mode<<PIN_number*2);	
if (PIN_number<=7) PORT->AFR[0] |= Alternate_function<<PIN_number*4; else PORT->AFR[1] |= Alternate_function<<(PIN_number-8)*4;
}

void GPIO_Analog_setup (GPIO_TypeDef *PORT, uint32_t PIN_number)
{
PORT->MODER |= 3UL<<(PIN_number*2);
	
}



/*
GPIOB->MODER |= ( (1<<(12*2)) | (1<<(15*2)) );	//pin 12 and 15 portB are output type 
GPIOB->OSPEEDR |= (	0x3U<<(15*2) | 0x3UL<<(12*2)  );	//setup high speed of pin 12 and 15 portB  

GPIOB->MODER &= ~( 0x3UL<<(0*2) | 0X3UL<<(1*2) ); // portB pin 0 and pin 1  are input
GPIOB->PUPDR |= ( 0x2UL<<(0*2) | 0x2UL<<(1*2) ); // portB inpet pin 0 and pin 1  are Pull-down type
*/


