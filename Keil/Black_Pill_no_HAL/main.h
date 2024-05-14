#include "stm32f411xe.h"
#include <stdio.h>
#include "stdint.h"
#include "core_cm4.h"
#include "DS18B20_F411.h"
#include "Delay.h"
#include "GPIO_setup.h"
#include "Core_init.h"
#include "Timer_F4.h"
#include "EXTI_F411_init.h"
#include "SPI.h"
#include "ST7920_STM32F4.h"
#include "Font_table.h"
#include "I2C_F411.h"
#include "DS3231_F411.h"
#include "Board.h"
#include "RTC_F411.h"
#include "ADC.h"
#include "USART_F411.h"
#include "DS18B20_F411.h"
#include "DMA.h"
#include "One_Wire_F411.h"




//TIM1_Delay1 - ds18b20
//TIM1_delay2 - Board
//TIM1_delay3 - Board




extern uint8_t day_of_week[7][3];
extern char String[100];


