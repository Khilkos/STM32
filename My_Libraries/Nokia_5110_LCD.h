#ifndef __Nokia_5110_LCD_H
#define __Nokia_5110_LCD_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Delay.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

void Nokia_5110_init (void);
void Nokia_5110_send_command (uint8_t command);
void Nokia_5110_send_data (uint8_t data);






#endif

