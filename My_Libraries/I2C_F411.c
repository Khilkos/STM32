#include "I2C_F411.h"

uint32_t temp_count;



void I2C_F411_init(void)
{
RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
// current value of frequency PCLK1 APB1 buss
I2C1->CR2 &= ~I2C_CR2_FREQ;
I2C1->CR2 |= 48;

	
//set prescaler for I2C in FM mode 400 kHz
I2C1->CCR |=I2C_CCR_FS; //selection FM mode
I2C1->CCR &= ~I2C_CCR_CCR;
I2C1->CCR |=40; // =48MHz/3/400kHz
	

I2C1->TRISE = 15; // =300ns/(1/48MHz) +1

I2C1->CR1 |=I2C_CR1_PE; //enable I2C	
}
//---------------------------------------
void I2C_F411_Start (void)
{
I2C1->CR1 |= I2C_CR1_START;
while (!(I2C1->SR1&I2C_SR1_SB)) __NOP();
}
//---------------------------------------
void I2C_F411_Stop (void)
{
I2C1->CR1 |= I2C_CR1_STOP;
}
//---------------------------------------

_Bool I2C_F411_address_read (uint8_t address)
{
	uint32_t count=0;
	_Bool address_error=0;
(void) I2C1->SR1;
	I2C1->DR = address+1;
while (!(I2C1->SR1 & I2C_SR1_ADDR))
	{ 	count++;
			if (count>delay_answer) {address_error=1; break;}
	}

(void) I2C1->SR1;
(void) I2C1->SR2;

	return address_error;
}
//----------------------------------------


_Bool I2C_F411_address_write (uint8_t address)
{ 
	uint32_t count=0;
	_Bool address_error=0;
(void) I2C1->SR1;
	I2C1->DR = address;
while (!(I2C1->SR1 & I2C_SR1_ADDR))
	{ 	count++;
			if (count>delay_answer) {address_error=1; break;}
	}

(void) I2C1->SR1;
(void) I2C1->SR2;

	return address_error;
}	
//----------------------------------------

_Bool I2C_F411_data_write (uint8_t data)
{
_Bool ACK_error=0;
I2C1->DR = data;
while (!(I2C1->SR1 & I2C_SR1_BTF)) __NOP();
if (I2C1->SR1 & I2C_SR1_AF) ACK_error=1;	
	
return ACK_error;
}

//----------------------------------------

uint32_t I2C_F411_data_read (void)
{
	uint32_t count=0;
while (!(I2C1->SR1 & I2C_SR1_RXNE)) 
{ 	count++;
			if (count>delay_answer) {return 0;}
	}	
	return I2C1->DR;
}

//----------------------------------------

void I2C_F411_ACK_enable(void)
{
I2C1->CR1 |=I2C_CR1_ACK;	
}

//----------------------------------------

void I2C_F411_NASK_enable(void)
{
I2C1->CR1 &= ~I2C_CR1_ACK;
}
	
//----------------------------------------

