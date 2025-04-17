#include "stdio.h"
#include "stdint.h"

#include "Config.h"

#define Green_led_ON GPIOD->BSRR = 1<<12
#define Green_led_OFF GPIOD->BSRR = 1<<(12+16)

#define Orange_led_ON GPIOD->BSRR = 1<<13
#define Orange_led_OFF GPIOD->BSRR = 1<<(13+16)

#define Red_led_ON GPIOD->BSRR = 1<<14
#define Red_led_OFF GPIOD->BSRR = 1<<(14+16)

#define Blue_led_ON GPIOD->BSRR = 1<<15
#define Blue_led_OFF GPIOD->BSRR = 1<<(15+16)
