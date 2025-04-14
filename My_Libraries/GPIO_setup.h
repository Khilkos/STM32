#ifndef __GPIO_setup_H
#define __GPIO_setup_H

#include "Config.h"
#include "stdint.h"



#define Input 0
#define Output 1
#define Alternate 2
#define Analog 3

#define Low 0
#define Medium 1
#define Fast 2
#define High 3

#define No_pull 0
#define Pull_up 1
#define Pull_down 2

#define Push_pull 0
#define Open_drain 1

#define AF0 0
#define AF1 1
#define AF2 2
#define AF3 3
#define AF4 4
#define AF5 5
#define AF6 6
#define AF7 7
#define AF8 8
#define AF9 9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15


void GPIO_DO_setup (GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t Output_speed);
void GPIO_DI_setup (GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t Pull_mode);
void GPIO_Alternate(GPIO_TypeDef *PORT, uint32_t PIN_number, uint32_t OTYPER, uint32_t Output_speed, uint32_t Pull_mode, uint32_t Alternate_function);
void GPIO_Analog_setup (GPIO_TypeDef *PORT, uint32_t PIN_number);




#endif








