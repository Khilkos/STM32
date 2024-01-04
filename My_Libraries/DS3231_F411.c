#include "DS3231_F411.h"

uint16_t seconds=0;
uint16_t minutes=0;
uint16_t hour=0;
uint16_t day_of_wk=0;
uint16_t day=0;
uint16_t month=0;
uint16_t year=0;


void DS3231_F411_get_time(void)
{
I2C_F411_Start();	
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(0);
I2C_F411_Start();
I2C_F411_address_read(DS3231_address);
I2C_F411_ACK_enable();	
seconds=(uint16_t)I2C_F411_data_read();
minutes=(uint16_t)I2C_F411_data_read();
hour=(uint16_t)I2C_F411_data_read();
day_of_wk=(uint16_t)I2C_F411_data_read();	
day=(uint16_t)I2C_F411_data_read();	
month=(uint16_t)I2C_F411_data_read();	
I2C_F411_NASK_enable();
year=(uint16_t)I2C_F411_data_read();
I2C_F411_Stop();
seconds=( (((seconds&0xF0)>>4)*10)  + (seconds&0x0F));	
minutes=( (((minutes&0xF0)>>4)*10)  + (minutes&0x0F));		
hour=( (((hour&0xF0)>>4)*10)  + (hour&0x0F));		
day= ( (((day&0xF0)>>4)*10)  + (day&0x0F));
month=( (((month&0xF0)>>4)*10)  + (month&0x0F));
year=( (((year&0xF0)>>4)*10)  + (year&0x0F));		
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
//-----------------------------------------
void DS3231_F411_set_day_of_wk (uint32_t set_day_of_wk)
{
uint32_t data= (((set_day_of_wk/10)<<4) | (set_day_of_wk%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(3);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}
//-----------------------------------------
void DS3231_F411_set_day (uint32_t set_day)
{
uint32_t data= (((set_day/10)<<4) | (set_day%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(4);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}
//-----------------------------------------
void DS3231_F411_set_month (uint32_t set_month)
{
uint32_t data= (((set_month/10)<<4) | (set_month%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(5);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}
//-----------------------------------------
void DS3231_F411_set_year (uint32_t set_year)
{
uint32_t data= (((set_year/10)<<4) | (set_year%10) );
I2C_F411_Start();
I2C_F411_address_write(DS3231_address);
I2C_F411_data_write(6);
I2C_F411_data_write((uint8_t)data);	
I2C_F411_Stop();
}


