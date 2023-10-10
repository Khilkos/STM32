#ifndef __I2C_F411_H
#define __I2C_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
#define CPU_freq 96000000 
#define I2C_speed 400000

#define delay_answer  CPU_freq*9/I2C_speed //  (1/I2C_speed)*9/(1/CPU_freq)

extern uint32_t temp_count;


void I2C_F411_init(void);
void I2C_F411_Start (void);
void I2C_F411_Stop (void);
_Bool I2C_F411_address_read (uint8_t address);
_Bool I2C_F411_address_write (uint8_t address);
_Bool I2C_F411_data_write (uint8_t data);
uint32_t I2C_F411_data_read (void);
void I2C_F411_ACK_enable(void);
void I2C_F411_NASK_enable(void);


#endif

