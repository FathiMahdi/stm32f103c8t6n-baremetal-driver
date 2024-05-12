#ifndef STM32F103XX_I2C_DRIVER_H_
#define STM32F103XX_I2C_DRIVER_H_


#include "stm32f103xx.h"

typedef struct 
{
    uint8_t speed;
    uint8_t own_address;
    uint8_t ack_control;
    uint8_t fm_duty_cycle;
}I2C_Config_t;



typedef struct 
{
    I2C_Config_t *I2CConfig;
    I2C_RegDef_t *pI2Cx;
}I2C_Handle_t;







#endif