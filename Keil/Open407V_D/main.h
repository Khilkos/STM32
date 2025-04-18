#include "stdio.h"
#include "stdint.h"

#include "Config.h"

#define Green_led_ON GPIOD->BSRR = 1<<12
#define Green_led_OFF GPIOD->BSRR = 1<<(12+16)

#define Orange_led_ON GPIOD->BSRR = 1<<13
#define Orange_led_OFF GPIOD->BSRR = 1<<(13+16)

#define Red_led_ON GPIOD->BSRR = 1<<14
#define Red_led_OFF GPIOD->BSRR = 1<<(14+16)

#define Blue_led_ON GPIOD->BSRR = 1<<15
#define Blue_led_OFF GPIOD->BSRR = 1<<(15+16)

typedef struct
{ // Структура адресуется по порядку. Базовый адрес в начале.
volatile uint16_t LCD_RAM; // 0x6001FFFE >> 1 = 0x0000FFFF bit 16 = 0 т.е. DATA
volatile uint16_t LCD_REG; // 0x6001FFFE + 2 (т.к. uint16) = 0x60020000 >> 1 = 0x00010000 bit 16 = 1 т.е. CMD
} LCD_TypeDef;
/* LCD is connected to the FSMC_Bank1 and NE1 is used as ship select signal, A16 use as RS */
#define LCD_BASE ((uint32_t)(0x60000000 | 0x0001fffE))
#define LCD ((LCD_TypeDef *) LCD_BASE)



