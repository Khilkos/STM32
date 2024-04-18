#ifndef __Board_H
#define __Board_H

#include "stm32f411xe.h"
#include "stdint.h"


extern uint8_t clock_poz;
extern uint8_t clock_poz_1;
void key_scan (void);
extern uint16_t encoder_data;	

#endif

