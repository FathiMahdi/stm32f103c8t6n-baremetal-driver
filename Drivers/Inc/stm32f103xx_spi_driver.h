#ifndef STM32F103XX_SPI_DRIVER_H_
#define STM32F103XX_SPI_DRIVER_H_

#include "stm32f103xx.h"



#define SPI_MASTER          1
#define SPI_SLAVE           0 

#define SPI_DFF_8_BIT       0
#define SPI_DFF_16_BIT      1

#define SPI_FULLDUBLEX      0
#define SPI_HALFDUPLEX      1
#define SPI_SIMPLEX         2

#define F_PCLK_DIV_2            0
#define F_PCLK_DIV_4            1
#define F_PCLK_DIV_8            2
#define F_PCLK_DIV_16           3
#define F_PCLK_DIV_32           4
#define F_PCLK_DIV_64           5
#define F_PCLK_DIV_128          6
#define F_PCLK_DIV_256          7


typedef struct 
{
    volatile uint8_t SPI_DeviceMode;
    volatile uint8_t SPI_BusConfig;
    volatile uint8_t SPI_CLKSpeed;
    volatile uint8_t SPI_DFF;
    volatile uint8_t SPI_CPOL;
    volatile uint8_t SPI_CPHA;
    volatile uint8_t SSM;
}SPI_Config_t;





typedef struct 
{
    SPI_RegDef_t *pSPIx;
    SPI_Config_t SPIConfig;
}SPI_Handle_t;


void SPI_ClockControl(SPI_RegDef_t *pSPIx, uint8_t status);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_Enable(SPI_RegDef_t *pSPIx, uint8_t en_ds);
void SPI_DeInit(SPI_RegDef_t *pSPIx );
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *Tx_data_buffer, uint32_t data_len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *Rx_data_buffer, uint32_t data_len);
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle );


#endif