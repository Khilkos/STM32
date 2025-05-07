#ifndef _SSD1963_H
#define _SSD1963_H
#include "Config.h"

//требует FSMC

/*
//==========================
//for GT911 define in Config.h
#define TOUCH_IRQ_GPIO GPIOE
#define TOUCH_IRQ_PIN 4	
#define TOUCH_RST_GPIO GPIOE
#define TOUCH_RST_PIN 5	
//==========================
*/

#define LCD_CMD LCD->LCD_RAM
#define LCD_DATA LCD->LCD_REG

#define  HDP 799
#define  HT  928 
#define  HPS 46
#define  LPS 15
#define  HPW 48

#define  VDP 479
#define  VT  525
#define  VPS 16
#define  FPS 8
#define  VPW 16

typedef struct
{ // Структура адресуется по порядку. Базовый адрес в начале.
volatile uint16_t LCD_RAM; // 0x6001FFFE >> 1 = 0x0000FFFF bit 16 = 0 т.е. DATA
volatile uint16_t LCD_REG; // 0x6001FFFE + 2 (т.к. uint16) = 0x60020000 >> 1 = 0x00010000 bit 16 = 1 т.е. CMD
} LCD_TypeDef;
/* LCD is connected to the FSMC_Bank1 and NE1 is used as ship select signal, A16 use as RS */
#define LCD_BASE ((uint32_t)(0x60000000 | 0x0001fffE))
#define LCD ((LCD_TypeDef *) LCD_BASE)



void SSD1963_init (void);



void LCD_WriteReg(const uint8_t LCD_Reg, const uint16_t LCD_RegValue);
void SSD1963_SetArea(uint16_t x1, uint16_t width, uint16_t y1, uint16_t height);
void SSD1963_ClearScreen(uint16_t color);
void SSD1963_dot(uint16_t x, uint16_t y, uint16_t color);
void SSD1963_Vertical_line(uint16_t x, uint16_t y, uint16_t height, uint16_t thickness, uint16_t color);
void SSD1963_Horisontal_line(uint16_t x, uint16_t y, uint16_t width, uint16_t thickness, uint16_t color);
void SSD1963_string_font_10x16 (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color );
void SSD1963_string_font_10x16_back_fone (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color, uint16_t color_back_fone);

void TFT_Set_Work_Area(uint16_t x,uint16_t y,uint16_t length,uint16_t size);
void TFT_Draw_Line (uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2, uint8_t size,uint16_t color);
void TFT_Draw_HLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color);
void TFT_Draw_VLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color);
void TFT_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint8_t size, uint16_t color);
void TFT_Draw_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color);
void TFT_Draw_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint16_t color);
void TFT_Draw_Circle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, uint16_t color);
void TFT_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint16_t color);
void TFT_Draw_Fill_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) ;
void TFT_Draw_Fill_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint16_t color);
void TFT_Draw_Triangle( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint16_t color);
void TFT_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t phone,const uint8_t *table, uint8_t ascii, uint8_t size);

void TFT_Draw_image(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t *img);

#endif





