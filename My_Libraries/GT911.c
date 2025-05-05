#include "GT911.h"

//////extern I2C_HandleTypeDef hi2c1;

void InitGT911Pin(void)
{/*
	InitGPIO(GT911_GPIOPort, GT911_INT, OUT);
	InitGPIO(GT911_GPIOPort, GT911_RST, OUT);
	
	SetGPIO(GT911_GPIOPort, GT911_INT, 1);
	SetGPIO(GT911_GPIOPort, GT911_RST, 1);*/
}

void GT911_Reset(void)
{
	/*uint32_t i;
	GPIO_InitTypeDef GPIO_InitStruct;
	HAL_GPIO_WritePin(TOUCH_IRQ_GPIO_Port, TOUCH_IRQ_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TOUCH_RST_GPIO_Port, TOUCH_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	for(i=0; i<500000;i=i+2){i = i-1;};
	HAL_GPIO_WritePin(TOUCH_RST_GPIO_Port, TOUCH_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(100);

	  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);
	  for(i=0; i<500000;i=i+2){i = i-1;};
	HAL_Delay(100);
*/
	TOUCH_IRQ_GPIO->BSRR = 1<<(TOUCH_IRQ_PIN+16);
	TOUCH_RST_GPIO->BSRR = 1<<(TOUCH_RST_PIN+16);
	delay_ms(100);
	TOUCH_RST_GPIO->BSRR = 1<<(TOUCH_RST_PIN);
	delay_ms(100);
	
	GPIO_DI_setup (TOUCH_IRQ_GPIO, TOUCH_IRQ_PIN,No_pull);
	
	
}

void GT911_CalculateCheckSum(GT911ConfInfo_TypeDef * GT911ConfInfo)
{
	GT911ConfInfo->ConfigChksum = 0;
	for(uint8_t i = 0 ; i < 184 ; i++){
		GT911ConfInfo->ConfigChksum += *((uint8_t*)GT911ConfInfo + i);
	}
	GT911ConfInfo->ConfigChksum = (~GT911ConfInfo->ConfigChksum) + 1;
}

void GT911_Read(uint16_t RegisterAddress, uint8_t* ReceivedBuffer, uint8_t Size)
{
	//uint8_t temp=0;
	I2C_STM32F4_Start();
	I2C_STM32F4_address_write(GT911_DEFAULT_ID);
	I2C_STM32F4_data_write((RegisterAddress&0xff00)>>8);
	I2C_STM32F4_data_write(RegisterAddress&0x00ff);
	I2C_STM32F4_Start();
	I2C_STM32F4_address_read(GT911_DEFAULT_ID);
	I2C_STM32F4_ACK_enable();
	for (uint16_t i=0; i<(Size-1); i++)
		{	*(ReceivedBuffer+i)=I2C_STM32F4_data_read(); }
	I2C_STM32F4_NASK_enable();	
	*(ReceivedBuffer+Size-1)=I2C_STM32F4_data_read();
	I2C_STM32F4_Stop();
}

void GT911_Write(uint16_t RegisterAddress, uint8_t* TransmitedBuffer, uint8_t Size)
{
	I2C_STM32F4_Start();
	I2C_STM32F4_address_write(GT911_DEFAULT_ID);
	I2C_STM32F4_data_write((RegisterAddress&0xff00)>>8);
	I2C_STM32F4_data_write(RegisterAddress&0x00ff);
	for (uint16_t i=0; i<Size; i++)
		{I2C_STM32F4_data_write(*(TransmitedBuffer+i));}
	I2C_STM32F4_Stop();
}

void GT911_Init(void)
{
	//InitGT911Pin();

	GT911ConfInfo_TypeDef GT911ConfInfo = {
		0x00, 0x00, 0x04, 0x58, 0x02, 0x0A, 0x0C, 0x20, 0x01, 0x08, 0x28, 0x05, 0x50, // 0x8047 - 0x8053
		0x3C, 0x0F, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x8054 - 0x8060
		0x00, 0x89, 0x2A, 0x0B, 0x2D, 0x2B, 0x0F, 0x0A, 0x00, 0x00, 0x01, 0xA9, 0x03, // 0x8061 - 0x806D
		0x2D, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, // 0x806E - 0x807A
		0x59, 0x94, 0xC5, 0x02, 0x07, 0x00, 0x00, 0x04, 0x93, 0x24, 0x00, 0x7D, 0x2C, // 0x807B - 0x8087
		0x00, 0x6B, 0x36, 0x00, 0x5D, 0x42, 0x00, 0x53, 0x50, 0x00, 0x53, 0x00, 0x00, // 0x8088	- 0x8094
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x8095 - 0x80A1
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80A2 - 0x80AD
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, // 0x80AE - 0x80BA
		0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, // 0x80BB - 0x80C7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80C8 - 0x80D4
		0x02, 0x04, 0x06, 0x08, 0x0A, 0x0F, 0x10, 0x12, 0x16, 0x18, 0x1C, 0x1D, 0x1E, // 0x80D5 - 0x80E1
		0x1F, 0x20, 0x21, 0x22, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, // 0x80E2 - 0x80EE
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80EF - 0x80FB
		0x00, 0x00, 0xD6, 0x01 }; // 0x80FC - 0x8100
	
	GT911ConfInfo.XOutputMax_H = 0x3;
	GT911ConfInfo.XOutputMax_L = 0x20;
		
	GT911ConfInfo.YOutputMax_H = 0x1;
	GT911ConfInfo.YOutputMax_L = 0xE0;
	
	GT911ConfInfo.TouchNumber = 5;
		
	GT911ConfInfo.LargeTouch = 40;
		
	GT911ConfInfo.ModuleSwitch[0] = 0xcc;
		
	GT911_CalculateCheckSum(&GT911ConfInfo);

	GT911_Reset();

	GT911_Write(CONFIG_VERSION, (uint8_t*)&GT911ConfInfo, 184);

	uint8_t cmd = 0x00;

	GT911_Write(COMMAND_ADDRESS, &cmd, 1);

	GPIO_DI_setup(TOUCH_IRQ_GPIO,TOUCH_IRQ_PIN,No_pull);
/*	  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	  SYSCFG->EXTICR[4 >> 2] |= (((uint32_t)TOUCH_IRQ_GPIO) & 0xFF00) >> 10;
	  //SYSCFG->EXTICR[5 >> 2] |= (((uint32_t)TOUCH_IRQ_GPIO_Port) & 0xFF00) >> 10;
	  EXTI->IMR  |= TOUCH_IRQ_PIN;
	  EXTI->FTSR |= TOUCH_IRQ_PIN;

	  NVIC_SetPriority (EXTI4_IRQn, 6);
	  NVIC_EnableIRQ(EXTI4_IRQn);*/
}

uint8_t GT911_ReadTouch(GT911Touch_TypeDef * GT911Touch)
{
	uint8_t status;

	GT911_Read(STATUS_ADDRESS, &status, 1);

	if ((status & 0x80) != 0)
	{
		for (uint8_t i = 0; i < (status & 0xF); i++)
		{
			GT911_Read(POINT1_X_ADDRESS+i*8,(uint8_t*)&GT911Touch[i],sizeof(GT911Touch[i]));
		}
		uint8_t reset = 0;
		GT911_Write(STATUS_ADDRESS, &reset, 1);
	}

	return (status & 0xF);
}
