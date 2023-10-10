#ifndef __DS3231_F411_init_H
#define __DS3231_F411_init_H

//#include "stm32f411xe.h"
#include "stdint.h"
#include "I2C_F411.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#define DS3231_address 0b11010000


extern uint32_t seconds;
extern uint32_t minutes;
extern uint32_t hour;
extern uint32_t day;

void DS3231_F411_get_time(void);
void DS3231_F411_set_hour (uint32_t set_hour);
void DS3231_F411_set_minutes (uint32_t set_minutes);
void DS3231_F411_set_seconds (uint32_t set_seconds);

#endif
