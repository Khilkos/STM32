#ifndef _DS18B20_H
#define _DS18B20_H

//******************************
// ������� ��������� 
//  "USART.h"
//	"Timer.h"
//	"One_Wire.h"
//******************************


#include "Config.h"



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
extern uint16_t DS18B20_temperature_of_2_sensor[2];


extern uint8_t ROM1[8];
extern uint8_t ROM2[8];
extern uint8_t ROM3[8];
extern uint8_t ROM_work[8];
extern uint8_t ROM_work_1[8];

_Bool DS18B20_Reset_single (USART_TypeDef * USARTx);
void DS18B20_write_bit(_Bool, USART_TypeDef * USARTx);
void DS18B20_write_byte (uint8_t write_byte, USART_TypeDef * USARTx);
_Bool DS18B20_read_bit (USART_TypeDef * USARTx);
uint8_t DS18B20_read_byte (USART_TypeDef * USARTx);
uint16_t DS18B20_read_temperatur (USART_TypeDef * USARTx);
uint16_t DS18B20_read_temperatur_via_DMA (void);
uint16_t DS18B20_read_temperatur_via_DMA_timer (void);
void DS18B20_read_ROM (USART_TypeDef * USARTx);
_Bool DS18B20_read_temperatur_of_2_sensor (uint8_t* _ROM_1, uint8_t* _ROM_2,uint16_t* _temperature_of_2_sensor);



#endif
