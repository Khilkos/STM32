#ifndef __HUB_08_F411_H
#define __HUB_08_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
#include <stdio.h>
#include "Delay.h"
#include "Font_table.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"



#define res 16

extern uint32_t screen_buf[16][2];
//static char String[100];

void clear_screen_buf(void);
void screen_buf_update(void);
void HUB_08_Send (void);
void HUB08_screen_buf_dot (uint16_t y, uint16_t x);
void HUB08_screen_buf_no_dot (uint16_t y, uint16_t x);
void LCD_string (uint16_t y, uint16_t x, uint8_t *str);


#endif



