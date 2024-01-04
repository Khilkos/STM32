#ifndef __DS3231_F411_init_H
#define __DS3231_F411_init_H

//#include "stm32f411xe.h"
#include "stdint.h"
#include "I2C_F411.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#define DS3231_address 0b11010000


extern uint16_t seconds;
extern uint16_t minutes;
extern uint16_t hour;
extern uint16_t day_of_wk;
extern uint16_t day;
extern uint16_t month;
extern uint16_t year;


void DS3231_F411_get_time(void);
void DS3231_F411_set_hour (uint32_t set_hour);
void DS3231_F411_set_minutes (uint32_t set_minutes);
void DS3231_F411_set_seconds (uint32_t set_seconds);
void DS3231_F411_set_day_of_wk (uint32_t set_day_of_wk);
void DS3231_F411_set_day (uint32_t set_day);
void DS3231_F411_set_month (uint32_t set_month);
void DS3231_F411_set_year (uint32_t set_year);

#endif
