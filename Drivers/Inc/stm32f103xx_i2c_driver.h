#ifndef STM32F103XX_I2C_DRIVER_H_
#define STM32F103XX_I2C_DRIVER_H_


#include "stm32f103xx.h"


typedef enum
{
    I2C_STANDARD_SPEED = 100000, // 100 KHZ
    I2C_STANDARD_FM = 400000, // 400 KHZ
}I2C_SPEED;


typedef enum
{
    I2C_ACK_DISABLE = 0, 
    I2C_ACK_ENABLE = 1, 
}I2C_ACK;

// Only for FM
typedef enum
{
    DUTY_2 = 0, 
    DUTY_16_DIV_9 = 1, 
}I2C_DUTY_CYCLE;



typedef struct 
{
    uint8_t speed;
    uint8_t own_address;
    uint8_t ack_control;
    uint8_t fm_duty_cycle;
}I2C_Config_t;



typedef struct 
{
    I2C_Config_t I2CConfig;
    I2C_RegDef_t *pI2Cx;
}I2C_Handle_t;


void I2C_ClockControl(I2C_RegDef_t *pSPIx, uint8_t status);
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pSPIx );
void I2C_Enable(I2C_RegDef_t *pSPIx, uint8_t en_ds);

void I2C_IRQHandler(I2C_Handle_t *pI2CHandle );
void I2C_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);





#endif