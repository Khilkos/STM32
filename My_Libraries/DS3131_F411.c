#include "DS3231_F411.h"

uint32_t seconds=0;
uint32_t minutes=0;
uint32_t hour=0;
uint32_t day=0;



void DS3231_F411_get_time(void)
{
I2C_F411_Start();	
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(0);
I2C_F411_Start();
I2C_F411_address_read(DS3231_address);
I2C_F411_ACK_enable();	
seconds=I2C_F411_data_read();
minutes=I2C_F411_data_read();
I2C_F411_NASK_enable();
hour=I2C_F411_data_read();
I2C_F411_Stop();
seconds=( (((seconds&0xF0)>>4)*10)  + (seconds&0x0F));	
minutes=( (((minutes&0xF0)>>4)*10)  + (minutes&0x0F));		
hour=( (((hour&0xF0)>>4)*10)  + (hour&0x0F));		
}

//----------------------------------------
void DS3231_F411_set_hour (uint32_t set_hour)
{
uint32_t data= (((set_hour/10)<<4) | (set_hour%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(2);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}

//-----------------------------------------
void DS3231_F411_set_minutes (uint32_t set_minutes)
{
uint32_t data= (((set_minutes/10)<<4) | (set_minutes%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(1);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}

//-----------------------------------------
void DS3231_F411_set_seconds (uint32_t set_seconds)
{
uint32_t data= (((set_seconds/10)<<4) | (set_seconds%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(0);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}





