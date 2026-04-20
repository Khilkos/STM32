//#include "stm32h750xx.h"
#include "stm32f407xx.h"

//#define STM32H7
#define STM32F4

#include "Core_init.h"
#include "Delay.h"
#include "GPIO_setup.h"
#include "Timer.h"
#include "FSMC.h"
#include "Open407_LCD.h"
#include "Font_table.h"
#include "USART.h"
#include "DMA.h"

//#define TIM2_IRQHandler_define

//#define DMA2_Stream0_IRQHandler_define
#define DMA1_Stream5_IRQHandler_define
#define DMA1_Stream6_IRQHandler_define