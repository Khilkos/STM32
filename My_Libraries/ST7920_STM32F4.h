#ifndef __ST7920_STM32F4_H
#define __ST7920_STM32F4_H

#include "stm32f411xe.h"
#include <math.h>
#include "Font_table.h"
#include "Config.h"
//#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"

#define res 16
#define size_y 64
#define size_x 128/8
#define CS 6


extern uint8_t SPI_send_buf [3];
extern uint8_t img_scr[size_y][size_x];
extern uint32_t Send_poz;
extern uint8_t ST7920_SPI_Send_buf [3456][3];
extern uint32_t Buf_poz;

void LCD_comand (unsigned char data);
void LCD_data (unsigned char data);
void LCD_init(void);
void LCD_out (void);
void dot (int y, int x);
void no_dot (int y, int x);
void digit_single (uint8_t y, uint8_t x, uint8_t dig);

void LCD_string (int y, int x, uint8_t *str); //вывод строки с координатами y,x,(uint8_t*)"Строка", либо буква uint8_t ch[2]="0"; *ch='?'; LCD_string(10,68,(uint8_t*)&ch);
void line (int y1, int x1, int y2, int x2); //отрисовка линий функция line агументы y1,x1,y2,x2 -  начальные и конечные кооординаты трямой,требует библиотеки math.h
//
extern void delay_us(uint32_t time_delay_us);
void ST7920_running_line(uint8_t *str, uint8_t Y_pos);
void LCD_string_font_10x16 (int y, int x, uint8_t *str);
//
void copy_to_img_scr (uint8_t y_pos, uint8_t x_pos, uint8_t y_size, uint8_t x_size, const unsigned char ar[][x_size/8]);
//копирование изображение из флеша в кадровый буфер, сначала координаты y, x-кратная 8, затем размер массива с изображением y,x-кратное 8 */
//

void digit (uint8_t y_pos, uint8_t x_pos,uint16_t data, uint8_t size, uint8_t dot_pos, uint8_t mask);
//вывод блока максимально из 5 чисел, с координатами y,x, само число, количество цифр не больше 5, количество цифр после запятой не больше 5, 
//позиция цифры которая будет мерцать с тактовой частотой переменной Bool pulse_1000ms
//
void ST7920_makeDMA_buf_command(uint32_t poz, uint8_t data);
void ST7920_makeDMA_buf_data(uint32_t poz, uint8_t data);
void LCD_DMA_out (void);


#endif
