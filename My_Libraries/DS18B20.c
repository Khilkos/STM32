#include "DS18B20.h"

static volatile uint8_t read_temperature_stage=0;
volatile uint16_t DS18B20_temperature=0;
#define USART_answer 100000
_Bool DMA_busy=0;

uint16_t DS18B20_temperature_of_2_sensor[2]={0,0};
uint8_t ROM[8];

uint8_t ROM1[8]={0x28,0xe4,0xbc,0x75,0xd0,0x01,0x3c,0x6c};
uint8_t ROM2[8]={0x28,0x69,0x0c,0x75,0xd0,0x01,0x3c,0x83};
uint8_t ROM3[8]={0x28,0x4d,0xb0,0x75,0xd0,0x01,0x3c,0x87};
uint8_t ROM_work[8]={0x28,0x7a,0x19,0xc7,0x0e,0x00,0x00,0x8d};
uint8_t ROM_work_1[8]={0x28,0xd9,0xf1,0x75,0xd0,0x01,0x3c,0xce};


#define OW_0    0x00
#define OW_1    0xff
#define OW_R    0xff



uint8_t convert_T[16] = {
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
_Bool DS18B20_Reset_single (USART_TypeDef * USARTx)
{
uint32_t temp=0;	
uint32_t count=0;
USART_F4_set_9600_baud(USARTx);
	USARTx->DR=0xf0;
	while (!(USARTx->SR & USART_SR_TC)) 
		{ 	count++;
				if (count>USART_answer)  {usart_fault=1;	break;}
		}	
	
	
	while (!(USARTx->SR & USART_SR_RXNE)) 
		{ 	count++;
				if (count>USART_answer)  {usart_fault=1;	break;}
		}	
	USART_F4_set_115200_baud(USARTx);
	temp=USARTx->DR;
	if (temp==0xf0) return 0;
	return 1;
}

//==================================================
void DS18B20_write_bit(_Bool write_bit, USART_TypeDef * USARTx)
{
	uint32_t count=0;
USART_F4_set_115200_baud(USARTx);
if (write_bit) USARTx->DR=0xff;	else USARTx->DR=0x00;
while (!(USARTx->SR & USART_SR_TC))
		{ 	count++;
				if (count>USART_answer)  {usart_fault=1;	break;}
		}
}

//==================================================
void DS18B20_write_byte (uint8_t write_byte, USART_TypeDef * USARTx)
{
for (uint8_t i=0; i<8; i++)
	{
		if (write_byte & 0x01) DS18B20_write_bit(1, USARTx); else DS18B20_write_bit(0, USARTx);
		write_byte>>=1;	
	}
}

//==================================================
_Bool DS18B20_read_bit (USART_TypeDef * USARTx)
{
	uint32_t count=0;
uint32_t temp=0;
	DS18B20_write_bit(1, USARTx);
	while (!(USARTx->SR & USART_SR_RXNE)) 
		{ 	count++;
				if (count>USART_answer)  {usart_fault=1;	break;}
		}
		temp=USARTx->DR;
	if (temp==0xff) return 1;
	return 0;
}	

//==================================================
uint8_t DS18B20_read_byte (USART_TypeDef * USARTx)
{
	uint8_t temp=0;
	USART2->DR; //������ ���� ������ ����� ������� ���������� ���������� 
for (uint8_t i=0; i<8; i++)
	{ 
		temp|=(uint8_t)(DS18B20_read_bit(USARTx)<<i);
	}
	return temp;
}

//==================================================
void DS18B20_read_ROM (USART_TypeDef * USARTx)
{
	DS18B20_Reset_single(USARTx);
	DS18B20_write_byte(read_ROM, USARTx);
	for (uint8_t i=0; i<8;i++)
	{
	ROM[i] = DS18B20_read_byte(USARTx);	
	}

	
	}
//==================================================
uint16_t DS18B20_read_temperatur (USART_TypeDef * USARTx)
{
	_Bool Sensor_OK=0;
	if (read_temperature_stage==0) 
		{
			Sensor_OK=DS18B20_Reset_single(USARTx);
			if (!Sensor_OK) return 0;
			DS18B20_write_byte(skip_rom, USARTx);
			DS18B20_write_byte(convert_t, USARTx);
			read_temperature_stage=1;
			TIM1_Delay_1=1000;
		}
	if (read_temperature_stage==1)
		{
			if (DS18B20_read_bit(USARTx)) read_temperature_stage=2;		
		}
	if (read_temperature_stage==2)
		{
			Sensor_OK=DS18B20_Reset_single(USARTx);
			if (!Sensor_OK)	return 0;
			DS18B20_write_byte(skip_rom, USARTx);
			DS18B20_write_byte(read_scratchpad, USARTx);
			DS18B20_temperature=(uint16_t)(DS18B20_read_byte(USARTx)) + (uint16_t)(DS18B20_read_byte(USARTx)<<8);
			DS18B20_temperature=(DS18B20_temperature/16*10)+(uint16_t)((DS18B20_temperature&0b00001111)*0.625);
			read_temperature_stage=0;
		}
return DS18B20_temperature;
}

//==================================================
_Bool DS18B20_read_temperatur_of_2_sensor (uint8_t* _ROM_1, uint8_t* _ROM_2,uint16_t* _temperature_of_2_sensor)
{
	uint8_t temp=0;
	_Bool temp_bit=0;
	uint16_t temp16=0;
	
	if (read_temperature_stage==0) 
		{
			DMA_busy=1;
			DMA_F4_One_Wire_Reset(One_wire_recive_buf, USART_def);
			read_temperature_stage=1;
		}	
	if (read_temperature_stage==1 && !DMA_busy) 		
		{	
			temp=skip_rom;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=2;
			DMA_busy=1;
		}
	if (read_temperature_stage==2 && !DMA_busy)
		{
			temp=convert_t;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=3;
			DMA_busy=1;
		}		
	if (read_temperature_stage==3 && !DMA_busy)
		{
			TIM1_Delay_1=1000;
			read_temperature_stage=4;
		}
	if (read_temperature_stage==4)
		{
			if (!TIM1_Delay_1) read_temperature_stage=5;		
		}
	if (read_temperature_stage==5)
		{
			//1 sensor
			DMA_busy=1;
			DMA_F4_One_Wire_Reset(One_wire_recive_buf, USART_def);
			read_temperature_stage=6;
		}
	if (read_temperature_stage==6 && !DMA_busy)
		{
			temp=match_ROM;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=7;
			DMA_busy=1;
		}
	if (read_temperature_stage==7 && !DMA_busy)		
		{	DMA_F4_One_Wire_Send (8, _ROM_1, USART_def);
			read_temperature_stage=8;
			DMA_busy=1;
		}
	if (read_temperature_stage==8 && !DMA_busy)			
		{	
			temp=read_scratchpad;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=9;
			DMA_busy=1;
		}
	if (read_temperature_stage==9 && !DMA_busy)				
		{	DMA_busy=1;
			DMA_F4_One_Wire_Recive(2,One_wire_recive_buf, USART_def);
			read_temperature_stage=10;
		}
	if (read_temperature_stage==10 && !DMA_busy)				
		{
				for (uint8_t i=0; i<16; i++)
				{	
					if (One_wire_recive_buf[i]==0xff) temp_bit=1; else temp_bit=0;
					temp16|= temp_bit<<i;
				}
			*_temperature_of_2_sensor=temp16;
			*_temperature_of_2_sensor=(*_temperature_of_2_sensor/16*10)+(uint16_t)((*_temperature_of_2_sensor&0b00001111)*0.625);
			if 	(*_temperature_of_2_sensor>2000) *_temperature_of_2_sensor=0;
			read_temperature_stage=11;
		}
	if (read_temperature_stage==11)		
		{			//	2 sensor
			DMA_busy=1;
			DMA_F4_One_Wire_Reset(One_wire_recive_buf, USART_def);
			read_temperature_stage=12;	
		}
	if (read_temperature_stage==12 && !DMA_busy)	
		{	temp=match_ROM;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=13;
			DMA_busy=1;
		}
	if (read_temperature_stage==13 && !DMA_busy)				
		{	DMA_F4_One_Wire_Send (8, _ROM_2, USART_def);
			read_temperature_stage=14;
			DMA_busy=1;
		}
	if (read_temperature_stage==14 && !DMA_busy)			
		{	temp=read_scratchpad;
			DMA_F4_One_Wire_Send (1, &temp, USART_def);
			read_temperature_stage=15;
			DMA_busy=1;
		}
	if (read_temperature_stage==15 && !DMA_busy)		
		{	DMA_busy=1;
			DMA_F4_One_Wire_Recive(2,One_wire_recive_buf, USART_def);
			read_temperature_stage=16;
		}
	if (read_temperature_stage==16 && !DMA_busy)				
		{
				for (uint8_t i=0; i<16; i++)
				{	
					if (One_wire_recive_buf[i]==0xff) temp_bit=1; else temp_bit=0;
					temp16|= temp_bit<<i;
				}
			*(_temperature_of_2_sensor+1)=temp16;
			*(_temperature_of_2_sensor+1)=(*(_temperature_of_2_sensor+1)/16*10)+(uint16_t)((*(_temperature_of_2_sensor+1)&0b00001111)*0.625);
			if 	(*(_temperature_of_2_sensor+1)>2000) *(_temperature_of_2_sensor+1)=0;
			read_temperature_stage=17;
		}
	if (read_temperature_stage==17)			
		{			
			read_temperature_stage=0;
		}
return 1;
}
//===================================================
/*uint16_t DS18B20_read_temperatur_via_DMA (void)
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
*/
//======================================================================
//===================================================
/*
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
			TIM1_Delay_1=5000;
		}

	if (read_temperature_stage==1 && !DMA_busy)
		{
			if (!TIM1_Delay_1) read_temperature_stage=2;		
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
*/
//======================================================================

