#ifndef __HUB_75_F411_H
#define __HUB_75_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
#include <stdio.h>
#include "Delay.h"
#include "Font_table.h"
#include "Board.h"
#include "DS18B20_F411.h"
#include "Timer_F411_init.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"



#define res 16

extern uint32_t HUB75_RED_screen_buf[32][2];
extern uint32_t HUB75_GREEN_screen_buf[32][2];
extern uint32_t HUB75_BLUE_screen_buf[32][2];
//static char String[100];

void HUB75_clear_screen_buf(void);
void HUB75_screen_buf_update(void);
void HUB75_Send (void);
void HUB75_screen_buf_dot (uint16_t y, uint16_t x, _Bool R, _Bool G, _Bool B);
void HUB75_screen_buf_no_dot (uint16_t y, uint16_t x, _Bool R, _Bool G, _Bool B);
void HUB75_LCD_string (uint16_t y, uint16_t x, uint8_t *str, _Bool R, _Bool G, _Bool B);
void HUB75_running_line(uint8_t *str, uint8_t Y_pos);
void HUB75_LCD_string_font_10x16 (uint16_t y, uint16_t x, uint8_t *str,  _Bool R, _Bool G, _Bool B);
void HUB75_h_line (uint16_t y, uint16_t x, uint16_t lenght, _Bool R, _Bool G, _Bool B);

#endif



