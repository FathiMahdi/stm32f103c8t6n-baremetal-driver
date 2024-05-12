#ifndef STM32F103XX_RCC_DRIVER_H_
#define STM32F103XX_RCC_DRIVER_H_

#include "stm32f103xx.h"


/// @brief 
typedef enum
{
    RCC_HSI = 0,
    RCC_HSE = 1,
    RCC_PLL = 2,
    RCC_NP = 3,
}CLOCK_SWITCH_STATUS;


/// @brief 
typedef enum
{
    SYS_DIV_2   = 8,
    SYS_DIV_4   = 9,
    SYS_DIV_8   = 10,
    SYS_DIV_16  = 11,
    SYS_DIV_64  = 12,
    SYS_DIV_128 = 13,
    SYS_DIV_256 = 14,
    SYS_DIV_512 = 15
}CLOCK_AHB_PRESCALER;


uint32_t RCC_GetPCLK1();

uint32_t RCC_GetPCLK2();


#endif