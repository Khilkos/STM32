#ifndef __Nokia_5110_LCD_H
#define __Nokia_5110_LCD_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Delay.h"
#include "Font_table.h"

//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define Nokia_X 128
#define Nokia_Y 64
extern uint8_t Nokia_5110_screen_buf[6][84];

void Nokia_5110_init (uint8_t V0_max_127);
void Nokia_5110_send_command (uint8_t command);
void Nokia_5110_send_data (uint8_t data);
void Nokia_5110_clear_LCD(void);
void Nokia_5110_LCD_Out (void);
void Nokia_5110_dot (uint8_t x, uint8_t y);
void Nokia_5110_no_dot (uint8_t x, uint8_t y);
void Nokia_5110_String (uint8_t x, uint8_t y, uint8_t *str);
void Nokia_5110_clr_screen_buf(void);
void Nokia_5110_Vertical_line (uint8_t X_poz, uint8_t Y_poz, uint8_t Lenght);
void Nokia_5110_Horizontal_line (uint8_t X_poz, uint8_t Y_poz, uint8_t Lenght);
#endif

