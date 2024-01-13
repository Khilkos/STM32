#ifndef __Board_H
#define __Board_H

#include "stm32f411xe.h"
#include "stdint.h"
#include "Timer_F411_init.h"
//#include "RTC_F411.h"
#include "DS3231_F411.h"
//#include "I2C_F411.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"


extern uint8_t clock_poz;
extern uint8_t clock_poz_1;
void key_scan (void);
extern uint16_t encoder_data;	

#endif

