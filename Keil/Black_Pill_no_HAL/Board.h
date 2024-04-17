#ifndef __Board_H
#define __Board_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Delay.h"
#include "RTC_F411.h"
#include "DS3231_F411.h"
#include "Timer_F4.h"

extern uint8_t clock_poz;
extern uint8_t clock_poz_1;
void key_scan (void);


#endif

