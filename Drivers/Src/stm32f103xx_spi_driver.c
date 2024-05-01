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


void SPI_Enable(SPI_RegDef_t *pSPIx, uint8_t en_ds)
{
    if(en_ds==ENABLE)
    {
        // set the SPI enable
        pSPIx->SPI_CR1 |= (1<<6);
    }

    else
    {
        // set the SPI enable
        pSPIx->SPI_CR1 &= ~(1<<6);
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


    // Device mode
   if(pSPIHandle->SPIConfig.SPI_DeviceMode == SPI_MASTER)
   {
       pSPIHandle->pSPIx->SPI_CR1 |= (1<<2);
   }

   else
   {
       pSPIHandle->pSPIx->SPI_CR1 &= ~(1<<2);
   }



    // set the spi clock
    pSPIHandle->pSPIx->SPI_CR1 |= (pSPIHandle->SPIConfig.SPI_CLKSpeed<<3);


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


/// @brief Send data through the SPI Bus
/// @param pSPIx 
/// @param Tx_data_buffer 
/// @param data_len 
/// @note polling mode
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *Tx_data_buffer, uint32_t data_len)
{
    // polling mode
    while(data_len>0)
    {

        // wait until the tx buffer is empty
        while( !(pSPIx->SPI_SR & (1<<1)) );
        
        
        // check the frame format
        if(pSPIx->SPI_CR1 & (1<<11))
        {
            // send two bytes to the data register
            pSPIx->SPI_DR = *((uint16_t *) Tx_data_buffer);

            data_len--;

            data_len--;

            (uint16_t *)Tx_data_buffer++; // increment the buffer address

        }

        else
        {
            // send 1 byte to the data register
            pSPIx->SPI_DR = *Tx_data_buffer;

            data_len--;

            Tx_data_buffer++;
        }

        


    }

}
