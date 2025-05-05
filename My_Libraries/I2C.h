#ifndef _I2C_H
#define _I2C_H

#include "Config.h"

/*
//==========================
//fof I2C  define in Config.h
#define CPU_freq 96000000 
#define I2C_speed 400000
//==========================
*/

#define delay_answer  CPU_freq*9/I2C_speed //  (1/I2C_speed)*9/(1/CPU_freq)

extern uint32_t temp_count;


void I2C_STM32F4_init(void);
void I2C_STM32F4_Start (void);
void I2C_STM32F4_Stop (void);
_Bool I2C_STM32F4_address_read (uint8_t address);
_Bool I2C_STM32F4_address_write (uint8_t address);
_Bool I2C_STM32F4_data_write (uint8_t data);
uint32_t I2C_STM32F4_data_read (void);
void I2C_STM32F4_ACK_enable(void);
void I2C_STM32F4_NASK_enable(void);


#endif

