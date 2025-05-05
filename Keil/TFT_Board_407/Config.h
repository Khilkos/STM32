#include "stdio.h"
#include "stdint.h"

//#include "stm32h750xx.h"
#include "stm32f407xx.h"

//#define STM32H7
#define STM32F4

#include "Core_init.h"
#include "Delay.h"
#include "GPIO_setup.h"
#include "Timer.h"
#include "FSMC.h"
#include "SSD1963.h"
#include "Font_table.h"
#include "I2C.h"
#include "GT911.h"

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



//#define DMA2_Stream0_IRQHandler_define
