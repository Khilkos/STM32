#ifndef __1602_I2C_H
#define __1602_I2C_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "I2C_F411.h"
#include "Delay.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16

void LCD1602_send_command_via_I2C(uint8_t command);
void LCD1602_send_data_via_I2C(uint8_t data);
void LCD1602_init_via_I2C(void);
void Draw_String(uint8_t adr, uint8_t *str);


#endif
