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

/// @brief 
/// @param pSPIx 
/// @param Rx_data_buffer 
/// @param data_len 
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *Rx_data_buffer, uint32_t data_len)
{
    // polling mode
    while(data_len>0)
    {

        // wait until the rx buffer is empty
        while( !(pSPIx->SPI_SR & (1<<0)) );
        
        
        // check the frame format
        if(pSPIx->SPI_CR1 & (1<<11))
        {
            // recive two bytes to the data register
            *((uint16_t *) Rx_data_buffer) = pSPIx->SPI_DR;

            data_len--;

            data_len--;

            (uint16_t *)Rx_data_buffer++; // increment the buffer address

        }

        else
        {
            // receive 1 byte to the data register
            *Rx_data_buffer = pSPIx->SPI_DR;

            data_len--;

            Rx_data_buffer++;
        }


    }
}




/// @brief 
/// @param IRQNumber 
/// @param IRQPriority 
/// @param EN 
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN)
{
    if(EN==ENABLE)
    {
        if(IRQNumber<=31)
        {
            *NVIC_ISER0 |= (1<<IRQNumber);
        }

        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1<<IRQNumber%32);
        }

        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1<<IRQNumber%64);
        }

        SPI_IRQInterruptProorityConfig(IRQNumber, IRQPriority);
    }

    else
    {
        if(IRQNumber<=31)
        {
            *NVIC_ICER0 |= (1<<IRQNumber);
        }

        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1<<IRQNumber%32);
        }

        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1<<IRQNumber%64);
        }
    }
}



/// @brief Interrupt priority config
/// @param IRQNumber 
/// @param IRQPriority 
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint32_t ipr_field = IRQNumber/4;
    uint32_t ipr_section = IRQNumber%4;
    *(NVIC_IPR_BASE_ADD+(ipr_field*4)) |= (IRQPriority<<(8*ipr_section));

}



/// @brief 
/// @param pSPIHandle 
/// @param Tx_data_buffer 
/// @param data_len 
SPI_IT_STATUS SPI_SendDataIt(SPI_Handle_t *pSPIHandle, uint8_t *Tx_data_buffer, uint32_t data_len)
{

    if(pSPIHandle->TxState != SPI_BUSSY_TX)
    {
        // Save the tx buffer
        pSPIHandle->pTxBuffer = Tx_data_buffer;
        pSPIHandle->TxLen = data_len;

        // Mark the spi TX as bussy
        pSPIHandle->TxState = SPI_BUSSY_TX;

        // enable the TXIE
        pSPIHandle->pSPIx->SPI_CR2 |= (1<<7);
    }
    
    return pSPIHandle->TxState;
}


/// @brief 
/// @param pSPIHandle 
/// @param Tx_data_buffer 
/// @param data_len 
void SPI_ReceiveDataIt(SPI_Handle_t *pSPIHandle, uint8_t *Tx_data_buffer, uint32_t data_len)
{

}