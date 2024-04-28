#include "stm32f103xx_spi_driver.h"


void SPI_ClockControl(SPI_RegDef_t *pSPIx, uint8_t status)
{
    if(status == ENABLE)
    {
        SPI1_CLOCK_EN();
    }

    else
    {
        SPI1_CLOCK_DS();
    }

}


void SPI_Init(SPI_Handle_t *pSPIHandle)
{

    // set the CPHA
    if(pSPIHandle->SPIConfig.SPI_CPHA == 1)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<0);
    }

    else
    {
        pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<0);
    } 


    // set the CPOL
    if(pSPIHandle->SPIConfig.SPI_CPOL == 1)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<1);
    }

    else
    {
        pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<1);
    }  



    // set the spi clock
    pSPIHandle->pSPIx->SPI_CR1 |= (pSPIHandle->SPIConfig.SPI_CLKSpeed<<3);


    // set the SPI enable
    pSPIHandle->pSPIx->SPI_CR1 |= (1<<6);


    // set software slave management

    if(pSPIHandle->SPIConfig.SSM == ENABLE)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<9);
    }


    else
    {
        pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<9);
    }
    
    

    // set data frame format
    if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16_BIT)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<11);
    }

    else
    {
        pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<11);
    }


    // set the spi bus mode
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_FULLDUBLEX)
    {
        pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<15);
    }

    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_HALFDUPLEX)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<15);
    }

    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_SIMPLEX)
    {
        pSPIHandle->pSPIx->SPI_CR1 |= (1<<15);
    }

    
    
}



void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *Tx_data_buffer, uint32_t data_len)
{
    
}