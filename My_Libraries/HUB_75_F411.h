#ifndef __HUB_75_F411_H
#define __HUB_75_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
#include <stdio.h>
#include "Delay.h"
#include "Font_table.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"



#define res 16

extern uint32_t HUB75_screen_buf[16][2];
//static char String[100];

void HUB75_clear_screen_buf(void);
void HUB75_screen_buf_update(void);
void HUB75_Send (void);
void HUB75_screen_buf_dot (uint16_t y, uint16_t x);
void HUB75_screen_buf_no_dot (uint16_t y, uint16_t x);
void HUB75_LCD_string (uint16_t y, uint16_t x, uint8_t *str);


#endif



