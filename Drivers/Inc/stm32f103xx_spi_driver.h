#ifndef STM32F103XX_SPI_DRIVER_H_
#define STM32F103XX_SPI_DRIVER_H_

#include "stm32f103xx.h"

typedef struct 
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_CLKSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SSM;
}SPI_Config_t;





typedef struct 
{
    SPI_RegDef_t *pSPIx;
    SPI_Config_t SPIConfig;
}SPI_Handle_t;


void SPI_ClockControl(SPI_RegDef_t *pGPIOx, uint8_t status);
void SPIInit(void);
void SPIDeInit(void);
void SPI_IRQHandler(void);


#endif