#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

//#include "stm32h750xx.h"
#include "stm32f407xx.h"

//#define STM32H7
#define STM32F4
#define USART_def USART1

#include "Core_init.h"
#include "Delay.h"
#include "GPIO_setup.h"
#include "Timer.h"
#include "FSMC.h"
#include "SSD1963.h"
#include "Font_table.h"
#include "I2C.h"
#include "GT911.h"
#include "img.h"
#include "DMA.h"
#include "USART.h"
#include "One_Wire.h"
#include "DS18B20.h"
#include "Graph.h"
#include "SCADA_init.h"




//==========================
//for GT911 define in Config.h
#define TOUCH_IRQ_GPIO GPIOE
#define TOUCH_IRQ_PIN 4	
#define TOUCH_RST_GPIO GPIOE
#define TOUCH_RST_PIN 5	
//==========================

//==========================
//fof I2C  define in Config.h
#define CPU_freq 168000000 
#define I2C_speed 400000
//==========================

//==========================
//for DI
#define DI0 !(GPIOA->IDR  & 1<<11)
#define DI1 !(GPIOA->IDR  & 1<<15)
#define DI2 !(GPIOC->IDR  & 1<<7)
#define DI3 !(GPIOB->IDR  & 1<<1)
#define DI4 !(GPIOB->IDR  & 1<<3)
#define DI5 !(GPIOB->IDR  & 1<<5)
#define DI6 !(GPIOB->IDR  & 1<<9)
#define DI7 !(GPIOB->IDR  & 1<<11)
//==========================


//#define DMA2_Stream0_IRQHandler_define
