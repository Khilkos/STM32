#include "stm32h750xx.h"
#define STM32H7
//#define STM32F4




#define res 16

#include "Delay.h"
#include "GPIO_setup.h"
#include "Core_init.h"
#include "SPI.h"
#include "DMA.h"




#define DMA1_Stream0_IRQHandler_define
void DMA1_Stream0_IRQHandler_User(void);

