#ifndef __PROMLED_H
#define __PROMLED_H

#include "stm32f411xe.h"
#include "main.h"


#define res 16
#define Promled_kvantum_delay 50
#define pre_led 255


void Promled_kvantum_out (uint8_t size_led, uint8_t (*Led_RGB)[3]);


#endif
