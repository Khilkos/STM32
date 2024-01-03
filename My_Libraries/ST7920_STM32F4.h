#ifndef __ST7920_STM32F4_H
#define __ST7920_STM32F4_H

#include "stm32f411xe.h"
#include <math.h>
#include "Font_table.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
#define size_y 64
#define size_x 128/8
#define CS 6

extern uint8_t img_scr[size_y][size_x];


void LCD_comand (unsigned char data);
void LCD_data (unsigned char data);
void LCD_init(void);
void LCD_out (void);
void dot (int y, int x);
void no_dot (int y, int x);
void digit_single (uint8_t y, uint8_t x, uint8_t dig);

void LCD_string (int y, int x, uint8_t *str); //вывод строки с координатами y,x,(uint8_t*)"—трока", либо буква uint8_t ch[2]="0"; *ch='?'; LCD_string(10,68,(uint8_t*)&ch);
void line (int y1, int x1, int y2, int x2); //отрисовка линий функци€ line агументы y1,x1,y2,x2 -  начальные и конечные кооординаты тр€мой,требует библиотеки math.h
//
extern void delay_us(uint32_t time_delay_us);
void ST7920_running_line(uint8_t *str, uint8_t Y_pos);
void LCD_string_font_10x16 (int y, int x, uint8_t *str);


#endif
