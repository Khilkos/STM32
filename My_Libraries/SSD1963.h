#ifndef _SSD1963_H
#define _SSD1963_H
#include "Config.h"

//требует FSMC

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
void SSD1963_Vertical_line(uint16_t x, uint16_t y, uint16_t height, uint16_t color);
void SSD1963_Horisontal_line(uint16_t x, uint16_t y, uint16_t width, uint16_t color);

#endif





