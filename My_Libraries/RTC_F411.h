#ifndef __RTC_F411_H
#define __RTC_F411_H

#include "stm32f411xe.h"
#include "stdint.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#include "DS3231_F411.h"

#define res 16
extern uint8_t RTC_seconds;
extern uint8_t RTC_minutes;
extern uint8_t RTC_hours;
extern uint8_t RTC_day_of_week;
extern uint8_t RTC_day;
extern uint8_t RTC_month;
extern uint8_t RTC_year;

void RTC_F411_Unlock_reg (void);
void RTC_F411_Init (void);
void RTC_F411_read_time_date (void);
void RTC_F411_write_time_date (void);



#endif
