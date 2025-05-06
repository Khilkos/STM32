#include "GT911.h"

//////extern I2C_HandleTypeDef hi2c1;
GT911Touch_TypeDef GT911Touch[5];
uint8_t TouchCount=0;
uint8_t Touch_status=0;

void InitGT911Pin(void)
{/*
	InitGPIO(GT911_GPIOPort, GT911_INT, OUT);
	InitGPIO(GT911_GPIOPort, GT911_RST, OUT);
	
	SetGPIO(GT911_GPIOPort, GT911_INT, 1);
	SetGPIO(GT911_GPIOPort, GT911_RST, 1);*/
}

void GT911_Reset(void)
{
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
	I2C_eror=I2C_STM32F4_address_read(GT911_DEFAULT_ID);
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

	GT911ConfInfo_TypeDef GT911ConfInfo;
	
	GT911ConfInfo.ConfigVersion=0x00; //0x8047
  GT911ConfInfo.XOutputMax_L=0x20;	//0x8048
  GT911ConfInfo.XOutputMax_H=0x03;	//0x8049
  GT911ConfInfo.YOutputMax_L=0xE0;	//0x804A
  GT911ConfInfo.YOutputMax_H=0x01;	//0x804B
  GT911ConfInfo.TouchNumber=0x05;		//0x804C
  GT911ConfInfo.ModuleSwitch[0]=(1<<7 | 1<<6 | 1<<3 | 1<<2 | 0);//0xcc;	//0x804D
	GT911ConfInfo.ModuleSwitch[1]=0x00; //0x20;	//0x804E
  GT911ConfInfo.ShakeCount=0x01;	//0x804F
  GT911ConfInfo.Filter=0x08;	//0x8050
  GT911ConfInfo.LargeTouch=40;	//0x8051
  GT911ConfInfo.NoiseReduction=6;//0x05;	//0x8052
  GT911ConfInfo.ScreenTouchLvl=90;//0x50;	//0x8053 Порог для обнаружения касания
  GT911ConfInfo.ScreenLeaveLvl=50;	//0x8054   Порог для снятия касания
  GT911ConfInfo.LowPowerControl=0x0;	//0x8055   Интервал для перехода в режим пониженного энергопотребления (от 0 до 15 с)
  GT911ConfInfo.RefreshRate=0x10; //0x05;	//0x8056  Скорость передачи координат (период: 5+N мс) max-15
  GT911ConfInfo.xThreshold=0x00;	//0x8057 Порог вывода координаты X: 0-255 (на основе последних сообщенных координат; если настроено на 0, GT911 будет продолжать непрерывно выводить координаты)
  GT911ConfInfo.yThreshold=0x00;	//0x8058 Порог вывода координаты Y: 0-255 (на основе последних сообщенных координат; если настроено на 0, GT911 будет продолжать непрерывно выводить координаты)
	GT911ConfInfo.xSpeedLimit=0x00;	//0x8059
	GT911ConfInfo.ySpeedLimit=0x00;	//0x805A
  GT911ConfInfo.Space[0]=0x00;	//0x805B
  GT911ConfInfo.Space[1]=0x00;	//0x805C
	GT911ConfInfo.MiniFilter=0x00;	//0x805D
  GT911ConfInfo.StretchR0=0x00;	//0x805E
  GT911ConfInfo.StretchR1=0x00;	//0x805F
  GT911ConfInfo.StretchR2=0x00;	//0x8060
  GT911ConfInfo.StretchRM=0x00;	//0x8061
  GT911ConfInfo.DrvGroupAnum=0x89;	//0x8062
  GT911ConfInfo.DrvGroupBnum=0x2A;	//0x8063
  GT911ConfInfo.SensorNum=0x0B;	//0x8064
  GT911ConfInfo.FreqAfactor=0x2D;	//0x8065
  GT911ConfInfo.FreqBfactor=0x2B;	//0x8066
  GT911ConfInfo.PannelBitFreq_L=0x0F;	//0x8067
  GT911ConfInfo.PannelBitFreq_H=0x0A;	//0x8068
  GT911ConfInfo.PannelSensorTime_L=0x00;	//0x8069
  GT911ConfInfo.PannelSensorTime_H=0x00;	//0x806A
  GT911ConfInfo.PannelTxGain=0x01;	//0x806B
  GT911ConfInfo.PannelRxGain=0xA9;	//0x806C
  GT911ConfInfo.PannelDumpShift=0x03;	//0x806D
  GT911ConfInfo.DrvFrameControl=0x2D; //0x806E
  GT911ConfInfo.ChargingLvlUp=0x00;	//0x806F
  GT911ConfInfo.ModuleSwitch3=0x01;	//0x8070
  GT911ConfInfo.GestureDis=0x11;	//0x8071
  GT911ConfInfo.GestureLongPressTime=0x00;	//0x8072
  GT911ConfInfo.XorYSlopeAdjust=0x00;	//0x8073
  GT911ConfInfo.GestureControl=0;//0x03;	//0x8074
  GT911ConfInfo.GestureSwitch1=0x00;	//0x8075
  GT911ConfInfo.GestureSwitch2=0x00;	//0x8076
  GT911ConfInfo.GestureRefreshRate=0x00;	//0x8077
  GT911ConfInfo.GestureTouchLvl=0x00;	//0x8078
  GT911ConfInfo.NewGreenWakeUpLvl=0x00;	//0x8079
  GT911ConfInfo.FreqHoppStart=50;//0x21;	//0x807A
  GT911ConfInfo.FreqHoppEnd=150;//0x59;	//0x807B
  GT911ConfInfo.NoiseDetectTimes=(2<<6 | 10);//0x94;	//0x807C
  GT911ConfInfo.HoppingFlag=(0<<7 | 0<<6 | 15);//0xC5;	//0x807D
  GT911ConfInfo.HoppingThreshold=0x02;	//0x807E
  GT911ConfInfo.NoiseThreshold=0x07;	//0x807F
  GT911ConfInfo.NoiseMinThreshold=0x00;	//0x8080
  GT911ConfInfo.reserved2=0x00;	//0x8081
  GT911ConfInfo.HoppSensorGroup=0x04;	//0x8082
  GT911ConfInfo.HoppSeg1Normalize=0x93;	//0x8083
  GT911ConfInfo.HoppSeg1Factor=0x24;	//0x8084
  GT911ConfInfo.MainClockAdjust=0x00;	//0x8085
  GT911ConfInfo.HoppSeg2Normalize=0x7D;	//0x8086
  GT911ConfInfo.HoppSeg2Factor=0x2C;	//0x8087
  GT911ConfInfo.reserved3=0x00;	//0x8088
  GT911ConfInfo.HoppSeg3Normalize=0x6B;	//0x8089
  GT911ConfInfo.HoppSeg3Factor=0x36;	//0x808A
  GT911ConfInfo.reserved4=0x00;	//0x808B
  GT911ConfInfo.HoppSeg4Normalize=0x5D;	//0x808C
  GT911ConfInfo.HoppSeg4Factor=0x42;	//0x808D
  GT911ConfInfo.reserved5=0x00;	//0x808E
  GT911ConfInfo.HoppSeg5Normalize=0x53;	//0x808F
  GT911ConfInfo.HoppSeg5Factor=0x50;	//0x8090
  GT911ConfInfo.reserved6=0x00;	//0x8091
  GT911ConfInfo.HoppSeg6Normalize=0x53;	//0x8092
  GT911ConfInfo.Key1=0x00;	//0x8093
  GT911ConfInfo.Key2=0x00;	//0x8094
  GT911ConfInfo.Key3=0x00;	//0x8095
  GT911ConfInfo.Key4=0x00;	//0x8096
  GT911ConfInfo.KeyArea=0x00;	//0x8097
  GT911ConfInfo.KeyTouchLvl=0x00;	//0x8098
  GT911ConfInfo.KeyLeaveLvl=0x00;	//0x8099
  GT911ConfInfo.KeySens[0]=0x00;	//0x809A
  GT911ConfInfo.KeySens[1]=0x00;	//0x809B
	GT911ConfInfo.KeyRestrain=0x00;	//0x809C
  GT911ConfInfo.KeyRestrainTime=0x00;	//0x809D
  GT911ConfInfo.GestureLargeTouch=0x00;	//0x809E
  GT911ConfInfo.reserved7[0]=0x00;	//0x809F
  GT911ConfInfo.reserved7[1]=0x00;	//0x80A0
	GT911ConfInfo.HotKnotNoiseMap=0x00;	//0x80A1
  GT911ConfInfo.LinkThreshold=0x00;	//0x80A2
  GT911ConfInfo.PxyThreshold=0x00;	//0x80A3
  GT911ConfInfo.GHotDumpShift=0x00;	//0x80A4
  GT911ConfInfo.GHotRXGain=0x00;	//0x80A5
  GT911ConfInfo.FreqGain0=0x00;	//0x80A6
  GT911ConfInfo.FreqGain1=0x00;	//0x80A7
  GT911ConfInfo.FreqGain2=0x00;	//0x80A8
  GT911ConfInfo.FreqGain3=0x00;	//0x80A9
  GT911ConfInfo.reserved8[0]=0x00;	//0x80AA
  GT911ConfInfo.reserved8[1]=0x00;	//0x80AB
	GT911ConfInfo.reserved8[2]=0x00;	//0x80AC
	GT911ConfInfo.reserved8[3]=0x00;	//0x80AD
	GT911ConfInfo.reserved8[4]=0x00;	//0x80AE
	GT911ConfInfo.reserved8[5]=0x00;	//0x80AF
	GT911ConfInfo.reserved8[6]=0x00;	//0x80B0
	GT911ConfInfo.reserved8[7]=0x00;	//0x80B1
	GT911ConfInfo.reserved8[8]=0x00;	//0x80B2
	GT911ConfInfo.CombineDis=0x00;	//0x80B3
  GT911ConfInfo.SplitSet=0x00;	//0x80B4
  GT911ConfInfo.reserved9[0]=0x00;	//0x80B5
	GT911ConfInfo.reserved9[1]=0x00;	//0x80B6
  GT911ConfInfo.SensorCH[0]=0x02;	//0x80B7
  GT911ConfInfo.SensorCH[1]=0x04;		//0x80B8
  GT911ConfInfo.SensorCH[2]=0x06;		//0x80B9
  GT911ConfInfo.SensorCH[3]=0x08;		//0x80BA
  GT911ConfInfo.SensorCH[4]=0x0A;		//0x80BB
  GT911ConfInfo.SensorCH[5]=0x0C;		//0x80BC
  GT911ConfInfo.SensorCH[6]=0x0E;		//0x80BD	
  GT911ConfInfo.SensorCH[7]=0x10;		//0x80BE
  GT911ConfInfo.SensorCH[8]=0x12;		//0x80BF
  GT911ConfInfo.SensorCH[9]=0x14;		//0x80C0
  GT911ConfInfo.SensorCH[10]=0x16;		//0x80C1
  GT911ConfInfo.SensorCH[11]=0xFF;		//0x80C2
  GT911ConfInfo.SensorCH[12]=0xFF;		//0x80C3
  GT911ConfInfo.SensorCH[13]=0xFF;		//0x80C4
  GT911ConfInfo.reserved10[0]=0x00;	//0x80C5
  GT911ConfInfo.reserved10[1]=0x00;	//0x80C6
  GT911ConfInfo.reserved10[2]=0x00;	//0x80C7
  GT911ConfInfo.reserved10[3]=0x00;	//0x80C8
  GT911ConfInfo.reserved10[4]=0x00;	//0x80C9
  GT911ConfInfo.reserved10[5]=0x00;	//0x80CA
  GT911ConfInfo.reserved10[6]=0x00;	//0x80CB
  GT911ConfInfo.reserved10[7]=0x00;	//0x80CC
  GT911ConfInfo.reserved10[8]=0x00;	//0x80CD	
  GT911ConfInfo.reserved10[9]=0x00;	//0x80CE
  GT911ConfInfo.reserved10[10]=0x00;	//0x80CF
  GT911ConfInfo.reserved10[11]=0x00;	//0x80D0
  GT911ConfInfo.reserved10[12]=0x00;	//0x80D1
  GT911ConfInfo.reserved10[13]=0x00;	//0x80D2
  GT911ConfInfo.reserved10[14]=0x00;	//0x80D3
  GT911ConfInfo.reserved10[15]=0x00;	//0x80D4
	GT911ConfInfo.DriverCH[0]=0x00;	//0x80D5
	GT911ConfInfo.DriverCH[1]=0x02;  	//0x80D6
	GT911ConfInfo.DriverCH[2]=0x04;		//0x80D7
	GT911ConfInfo.DriverCH[3]=0x06;		//0x80D8
	GT911ConfInfo.DriverCH[4]=0x08;		//0x80D9
	GT911ConfInfo.DriverCH[5]=0x0A;		//0x80DA
	GT911ConfInfo.DriverCH[6]=0x0F;		//0x80DB
	GT911ConfInfo.DriverCH[7]=0x10;		//0x80DC
	GT911ConfInfo.DriverCH[8]=0x12;		//0x80DD
	GT911ConfInfo.DriverCH[9]=0x16;		//0x80DE	
	GT911ConfInfo.DriverCH[10]=0x18;		//0x80DF
	GT911ConfInfo.DriverCH[11]=0x1C;		//0x80E0
	GT911ConfInfo.DriverCH[12]=0x1D;		//0x80E1
	GT911ConfInfo.DriverCH[13]=0x1E;		//0x80E2
	GT911ConfInfo.DriverCH[14]=0x1F;		//0x80E3
	GT911ConfInfo.DriverCH[15]=0x20;		//0x80E4
	GT911ConfInfo.DriverCH[16]=0x21;		//0x80E5
	GT911ConfInfo.DriverCH[17]=0x22;		//0x80E6	
	GT911ConfInfo.DriverCH[18]=0x24;		//0x80E7
	GT911ConfInfo.DriverCH[19]=0xFF;		//0x80E8
	GT911ConfInfo.DriverCH[20]=0xFF;		//0x80E9
	GT911ConfInfo.DriverCH[21]=0xFF;		//0x80EA
	GT911ConfInfo.DriverCH[21]=0xFF;		//0x80EB
	GT911ConfInfo.DriverCH[23]=0xFF;		//0x80EC
	GT911ConfInfo.DriverCH[24]=0xFF;		//0x80ED
	GT911ConfInfo.DriverCH[25]=0xFF;		//0x80EE
	GT911ConfInfo.reserved11[0]=0x00;	//0x80EF
	GT911ConfInfo.reserved11[1]=0x00;	//0x80F0
	GT911ConfInfo.reserved11[2]=0x00;	//0x80F1
	GT911ConfInfo.reserved11[3]=0x00;	//0x80F2
	GT911ConfInfo.reserved11[4]=0x00;	//0x80F3
	GT911ConfInfo.reserved11[5]=0x00;	//0x80F4
	GT911ConfInfo.reserved11[6]=0x00;	//0x80F5
	GT911ConfInfo.reserved11[7]=0x00;	//0x80F6
	GT911ConfInfo.reserved11[8]=0x00;	//0x80F7
	GT911ConfInfo.reserved11[9]=0x00;	//0x80F8
	GT911ConfInfo.reserved11[10]=0x00;	//0x80F9
	GT911ConfInfo.reserved11[11]=0x00;	//0x80FA
	GT911ConfInfo.reserved11[12]=0x00;	//0x80FB
	GT911ConfInfo.reserved11[13]=0x00;	//0x80FC
	GT911ConfInfo.reserved11[14]=0x00;	//0x80FD
	GT911ConfInfo.reserved11[15]=0x00;	//0x80FE
	GT911ConfInfo.ConfigChksum=0xD6;	//0x80FF
  GT911ConfInfo.ConfigFresh=0x01;	//0x8100

		
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
	Touch_status=status;
	if ((status & 0x80) != 0 && (status & 0x05) !=0)
	{
		for (uint8_t i = 0; i < (status & 0xF); i++)
		{
			GT911_Read(POINT1_X_ADDRESS+i*8,(uint8_t*)&GT911Touch[i],sizeof(GT911Touch[i]));
		}
	}
		uint8_t reset = 0;
		GT911_Write(STATUS_ADDRESS, &reset, 1);
	return (status & 0xF);
}
