#ifndef __DS18B20_F411_H
#define __DS18B20_F411_H

//#include "stm32f411xe.h"
#include "stdint.h"
//#include "I2C_F411.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#include "UART_F411.h"
#include "DMA_F411.h"

#define skip_rom 0xCC
#define convert_t 0x44
#define read_scratchpad 0xBE


extern const uint8_t convert_T[];
extern const uint8_t read_scratch[];
extern volatile uint16_t DS18B20_temperature;
extern _Bool DMA_busy;
extern uint8_t DMA_read_temp[32];

_Bool DS18B20_Reset_single (void);
void DS18B20_write_bit(_Bool);
void DS18B20_write_byte (uint8_t write_byte);
_Bool DS18B20_read_bit (void);
uint8_t DS18B20_read_byte (void);
uint16_t DS18B20_read_temperatur (void);
uint16_t DS18B20_read_temperatur_via_DMA (void);
uint16_t test_DMA (void);

#endif
