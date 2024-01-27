#include "1602_I2C.h"

#define LCD_1602_adress 0x4e //0b01111110

void LCD1602_send_command_via_I2C(uint8_t command)
{
uint8_t command_Hi=0, command_Lo=0;
command_Hi=command & 0xF0;
command_Lo=(command & 0x0F)*16; //<<4;	
I2C_F411_data_write(command_Hi|0x04|0x08);
I2C_F411_data_write(command_Hi|0x08);	
I2C_F411_data_write(command_Lo|0x04|0x08);	
I2C_F411_data_write(command_Lo|0x08);
}

//=======================================
void LCD1602_send_data_via_I2C(uint8_t data)
{
uint8_t data_Hi=0, data_Lo=0;
data_Hi=data & 0xF0;
data_Lo=(data & 0x0F)*16; //<<4;	
I2C_F411_data_write(data_Hi|0x04|0x08|0x01);
I2C_F411_data_write(data_Hi|0x08|0x01);	
I2C_F411_data_write(data_Lo|0x04|0x08|0x01);	
I2C_F411_data_write(data_Lo|0x08|0x01);
}

//=========================================

void LCD1602_init_via_I2C(void)
{
delay_ms(800);
	
I2C_F411_Start();
I2C_F411_address_write(LCD_1602_adress);
	
	LCD1602_send_command_via_I2C(0x20);
	LCD1602_send_command_via_I2C(0x2C);
	//включаем дисплей, в режиме 2-х линий
	
	delay_us(1000);
	
	LCD1602_send_command_via_I2C(0x0C);//0x0F включение мерцающего курсора
	//включаем отображение мерцающего курсора
	
	delay_us(1000);

	LCD1602_send_command_via_I2C(0x01);
	//очищаем дисплей
	
	delay_ms(1000);
	
	LCD1602_send_command_via_I2C(0x06);
	//значение DDRAM увеличивается, без сдвига экрана
		delay_ms(250);

I2C_F411_Stop();

}

//===========================================
//==============================================
void Draw_String(uint8_t adr, uint8_t *str)
{
	uint8_t data = 0;
	
	I2C_F411_Start();
I2C_F411_address_write(LCD_1602_adress);
	
	LCD1602_send_command_via_I2C(adr|0x80);
	
	while (*str)
	{
		data = *str++;
		LCD1602_send_data_via_I2C(data);
	}
	I2C_F411_Stop();
}

