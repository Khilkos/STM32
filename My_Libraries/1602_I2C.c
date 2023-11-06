#include "1602_I2C.h"

#define LCD_1602_adress 0b01111110

void LCD1602_send_command_via_I2C(uint8_t command)
{
uint8_t command_Hi=0, command_Lo=0;
command_Hi=command & 0xF0;
command_Lo=(command & 0x0F)*16; //<<4;	
I2C_F411_data_write(command_Hi|0x04);
I2C_F411_data_write(command_Hi);	
//I2C_F411_data_write(command_Lo|0x04);	
//I2C_F411_data_write(command_Lo);
}

//=======================================
void LCD1602_send_data_via_I2C(uint8_t data)
{
uint8_t data_Hi=0, data_Lo=0;
data_Hi=data & 0xF0;
data_Lo=(data & 0x0F)*16; //<<4;	
I2C_F411_data_write(data_Hi|0x04);
I2C_F411_data_write(data_Hi);	
I2C_F411_data_write(data_Lo|0x04);	
I2C_F411_data_write(data_Lo);
}

//=========================================

void LCD1602_init_via_I2C(void)
{
delay_ms(150);
	
I2C_F411_Start();
I2C_F411_address_write(LCD_1602_adress);
	
	LCD1602_send_command_via_I2C(0x20);
	LCD1602_send_command_via_I2C(0x20);
	//включаем дисплей, в режиме 2-х линий
	LCD1602_send_command_via_I2C(0xC0);
	
	delay_us(150);
	
	LCD1602_send_command_via_I2C(0x00);
	//включаем отображение мерцающего курсора
	LCD1602_send_command_via_I2C(0xF0);
	
	delay_us(150);

	LCD1602_send_command_via_I2C(0x00);
	//очищаем дисплей
	LCD1602_send_command_via_I2C(0x10);
	
	delay_ms(150);
	
	LCD1602_send_command_via_I2C(0x00);
	//значение DDRAM увеличивается, без сдвига экрана
	LCD1602_send_command_via_I2C(0x60);
		delay_ms(150);

I2C_F411_Stop();

}


