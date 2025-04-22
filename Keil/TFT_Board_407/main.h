#include "stdio.h"
#include "stdint.h"

#include "Config.h"

typedef struct
{ // ��������� ���������� �� �������. ������� ����� � ������.
volatile uint16_t LCD_RAM; // 0x6001FFFE >> 1 = 0x0000FFFF bit 16 = 0 �.�. DATA
volatile uint16_t LCD_REG; // 0x6001FFFE + 2 (�.�. uint16) = 0x60020000 >> 1 = 0x00010000 bit 16 = 1 �.�. CMD
} LCD_TypeDef;
/* LCD is connected to the FSMC_Bank1 and NE1 is used as ship select signal, A16 use as RS */
#define LCD_BASE ((uint32_t)(0x60000000 | 0x0001fffE))
#define LCD ((LCD_TypeDef *) LCD_BASE)

void LCD_WriteReg(const uint8_t LCD_Reg, const uint16_t LCD_RegValue);