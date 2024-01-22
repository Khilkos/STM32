#include "DS18B20_F411.h"

static volatile uint8_t read_temperature_stage=0;
volatile uint16_t DS18B20_temperature=0;
_Bool DMA_busy=0;

uint16_t DS18B20_temperature_of_sensor[2]={0,0};
uint8_t ROM[8];
//static uint8_t ROM_[8]={0x,0x,0x,0x,0x,0x,0x,0x};
static uint8_t ROM1[8]={0x28,0xe4,0xbc,0x75,0xd0,0x01,0x3c,0x6c};
static uint8_t ROM2[8]={0x28,0x69,0x0c,0x75,0xd0,0x01,0x3c,0x83};
static uint8_t ROM3[8]={0x28,0x4d,0xb0,0x75,0xd0,0x01,0x3c,0x87};
static uint8_t ROM_work[8]={0x28,0x7a,0x19,0xc7,0x0e,0x00,0x00,0x8d};
static uint8_t ROM_work_1[8]={0x28,0xd9,0xf1,0x75,0xd0,0x01,0x3c,0xce};

#define OW_0    0x00
#define OW_1    0xff
#define OW_R    0xff



const uint8_t convert_T[16] = {
                OW_0, OW_0, OW_1, OW_1, OW_0, OW_0, OW_1, OW_1, // 0xcc SKIP ROM
                OW_0, OW_0, OW_1, OW_0, OW_0, OW_0, OW_1, OW_0  // 0x44 CONVERT
};

const uint8_t read_scratch[32] = {
                OW_0, OW_0, OW_1, OW_1, OW_0, OW_0, OW_1, OW_1, // 0xcc SKIP ROM
								OW_0, OW_1, OW_1, OW_1, OW_1, OW_1, OW_0, OW_1, // 0xbe READ SCRATCH
                OW_R, OW_R, OW_R, OW_R, OW_R, OW_R, OW_R, OW_R,
                OW_R, OW_R, OW_R, OW_R, OW_R, OW_R, OW_R, OW_R
};

uint8_t DMA_read_temp[32];
//==================================================
_Bool DS18B20_Reset_single (void)
{
uint32_t temp=0;	
USART_F411_set_9600_baud();
	USART2->DR=0xf0;
	while (!(USART2->SR & USART_SR_TC)) __NOP();
	
	
	while (!(USART2->SR & USART_SR_RXNE)) __NOP();
	USART_F411_set_115200_baud();
	temp=USART2->DR;
	if (temp==0xf0) return 0;
	return 1;
}

//==================================================
void DS18B20_write_bit(_Bool write_bit)
{
USART_F411_set_115200_baud();
if (write_bit) USART2->DR=0xff;	else USART2->DR=0x00;
while (!(USART2->SR & USART_SR_TC)) __NOP();
}

//==================================================
void DS18B20_write_byte (uint8_t write_byte)
{
for (uint8_t i=0; i<8; i++)
	{
		if (write_byte & 0x01) DS18B20_write_bit(1); else DS18B20_write_bit(0);
		write_byte>>=1;	
	}
}

//==================================================
_Bool DS18B20_read_bit (void)
{
uint32_t temp=0;
	DS18B20_write_bit(1);
	while (!(USART2->SR & USART_SR_RXNE)) __NOP();
		temp=USART2->DR;
	if (temp==0xff) return 1;
	return 0;
}	

//==================================================
uint8_t DS18B20_read_byte (void)
{
	uint8_t temp=0;
	USART2->DR; //чтение чтоб убрать перед чтением предыдущее содержимое 
for (uint8_t i=0; i<8; i++)
	{ 
		temp|=(uint8_t)(DS18B20_read_bit()<<i);
	}
	return temp;
}

//==================================================
void DS18B20_read_ROM (void)
{
	DS18B20_Reset_single();
	DS18B20_write_byte(read_ROM);
	for (uint8_t i=0; i<8;i++)
	{
	ROM[i] = DS18B20_read_byte();	
	}

	
	}
//==================================================
uint16_t DS18B20_read_temperatur (void)
{
	_Bool Sensor_OK=0;
	
	if (read_temperature_stage==0) 
		{
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK) return 0;
			DS18B20_write_byte(skip_rom);
			DS18B20_write_byte(convert_t);
			read_temperature_stage=1;
			DS18B20_delay=1000;
		}
	if (read_temperature_stage==1)
		{
			if (DS18B20_read_bit()) read_temperature_stage=2;		
			//if (DS18B20_read_bit()) read_temperature_stage=2;		
		}
	if (read_temperature_stage==2)
		{
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK)	return 0;
			DS18B20_write_byte(skip_rom);
			DS18B20_write_byte(read_scratchpad);
			DS18B20_temperature=(uint16_t)(DS18B20_read_byte()) + (uint16_t)(DS18B20_read_byte()<<8);
			DS18B20_temperature=(DS18B20_temperature/16*10)+(uint16_t)((DS18B20_temperature&0b00001111)*0.625);
			read_temperature_stage=0;
		}
return DS18B20_temperature;
}

//==================================================
_Bool DS18B20_read_temperatur_of_sensor (void)
{
	_Bool Sensor_OK=0;
	
	if (read_temperature_stage==0) 
		{
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK) return 0;
			DS18B20_write_byte(skip_rom);
			DS18B20_write_byte(convert_t);
			read_temperature_stage=1;
			DS18B20_delay=1000;
		}
	if (read_temperature_stage==1)
		{
			if (DS18B20_read_bit()) read_temperature_stage=2;		
			//if (DS18B20_read_bit()) read_temperature_stage=2;		
		}
	if (read_temperature_stage==2)
		{
			//1 sensor
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK)	return 0;
			DS18B20_write_byte(match_ROM);
			
			for (uint8_t i=0; i<8; i++)
				{
				DS18B20_write_byte(ROM_work[i]);
				}
			DS18B20_write_byte(read_scratchpad);
			DS18B20_temperature_of_sensor[0]=(uint16_t)(DS18B20_read_byte()) + (uint16_t)(DS18B20_read_byte()<<8);
			DS18B20_temperature_of_sensor[0]=(DS18B20_temperature_of_sensor[0]/16*10)+(uint16_t)((DS18B20_temperature_of_sensor[0]&0b00001111)*0.625);
			
			//	2 sensor
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK)	return 0;
			DS18B20_write_byte(match_ROM);
			
			for (uint8_t i=0; i<8; i++)
				{
				DS18B20_write_byte(ROM_work_1[i]);
				}
			DS18B20_write_byte(read_scratchpad);
			DS18B20_temperature_of_sensor[1]=(uint16_t)(DS18B20_read_byte()) + (uint16_t)(DS18B20_read_byte()<<8);
			DS18B20_temperature_of_sensor[1]=(DS18B20_temperature_of_sensor[1]/16*10)+(uint16_t)((DS18B20_temperature_of_sensor[1]&0b00001111)*0.625);
				
				
				
				
				read_temperature_stage=0;
		}
return 1;
}
//===================================================
uint16_t DS18B20_read_temperatur_via_DMA (void)
{
	_Bool temp_bit=0;
	_Bool Sensor_OK=0;

	if (read_temperature_stage==0&& !DMA_busy) 
		{	
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK) return 0;
			DMA_F411_DS18B20_convert_T();
			DMA_busy=1;
			read_temperature_stage=1;
			//	GPIOB->BSRR =1<<14;
		}

	if (read_temperature_stage==1 && !DMA_busy)
		{
			if (DS18B20_read_bit()) read_temperature_stage=2;		
		}

	if (read_temperature_stage==2 && !DMA_busy)
		{
			Sensor_OK=DS18B20_Reset_single();
		if (!Sensor_OK)	return 0;
			DMA_busy=1;
			DMA_F411_DS18B20_read_scratch();
			
			read_temperature_stage=3;
		}
	if (read_temperature_stage==3 && !DMA_busy)
		{		
			DS18B20_temperature=0;
			for (uint8_t i=0; i<16; i++)
				{	
					if (DMA_read_temp[i+16]==0xff) temp_bit=1; else temp_bit=0;
					DS18B20_temperature|= temp_bit<<i;
				}
				read_temperature_stage=0;
			DS18B20_temperature=(DS18B20_temperature/16*10)+(uint16_t)((DS18B20_temperature&0b00001111)*0.625);
			}
		
return DS18B20_temperature;
}

//======================================================================
//===================================================
uint16_t DS18B20_read_temperatur_via_DMA_timer (void)
{
	_Bool temp_bit=0;
	_Bool Sensor_OK=0;

	if (read_temperature_stage==0&& !DMA_busy) 
		{	
			Sensor_OK=DS18B20_Reset_single();
			if (!Sensor_OK) return 0;
			DMA_F411_DS18B20_convert_T();
			DMA_busy=1;
			read_temperature_stage=1;
			DS18B20_delay=5000;
			//	GPIOB->BSRR =1<<14;
		}

	if (read_temperature_stage==1 && !DMA_busy)
		{
			if (!DS18B20_delay) read_temperature_stage=2;		
		}

	if (read_temperature_stage==2 && !DMA_busy)
		{
			Sensor_OK=DS18B20_Reset_single();
		if (!Sensor_OK)	return 0;
			DMA_busy=1;
			DMA_F411_DS18B20_read_scratch();
			
			read_temperature_stage=3;
		}
	if (read_temperature_stage==3 && !DMA_busy)
		{		
			DS18B20_temperature=0;
			for (uint8_t i=0; i<16; i++)
				{	
					if (DMA_read_temp[i+16]==0xff) temp_bit=1; else temp_bit=0;
					DS18B20_temperature|= temp_bit<<i;
				}
				read_temperature_stage=0;
			DS18B20_temperature=(DS18B20_temperature/16*10)+(uint16_t)((DS18B20_temperature&0b00001111)*0.625);
			}
		
return DS18B20_temperature;
}

//======================================================================



