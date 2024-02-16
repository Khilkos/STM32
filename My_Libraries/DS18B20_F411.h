#ifndef __DS18B20_F411_H
#define __DS18B20_F411_H

//#include "stm32f411xe.h"
#include "stdint.h"
//#include "I2C_F411.h"
//#include "cmsis_armclang.h" 
//#include "core_cm4.h"
#include "USART_F411.h"
#include "DMA_F411.h"
#include "Delay.h"
#include "Timer_F411_init.h"
#define skip_rom 0xCC
#define convert_t 0x44
#define read_scratchpad 0xBE
#define read_ROM 0x33
#define match_ROM 0x55



extern uint8_t convert_T[];
extern const uint8_t read_scratch[];
extern volatile uint16_t DS18B20_temperature;
extern _Bool DMA_busy;
extern uint8_t DMA_read_temp[32];
extern uint8_t ROM[8];
extern uint16_t DS18B20_temperature_of_sensor[2];

_Bool DS18B20_Reset_single (void);
void DS18B20_write_bit(_Bool);
void DS18B20_write_byte (uint8_t write_byte);
_Bool DS18B20_read_bit (void);
uint8_t DS18B20_read_byte (void);
uint16_t DS18B20_read_temperatur (void);
uint16_t DS18B20_read_temperatur_via_DMA (void);
uint16_t DS18B20_read_temperatur_via_DMA_timer (void);
void DS18B20_read_ROM (void);
_Bool DS18B20_read_temperatur_of_sensor (void);
void DMA_F411_One_Wire_Send (uint8_t size_buf, uint8_t* send_buf);
void DMA_F411_One_Wire_Recive (uint8_t size_buf, uint8_t* recive_buf);


#endif
