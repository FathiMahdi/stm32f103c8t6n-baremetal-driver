#include "stm32f103xx_i2c_driver.h"


/// @brief 
/// @param pSPIx 
/// @param en_ds 
void I2C_Enable(I2C_RegDef_t *pSPIx, uint8_t en_ds)
{
    if(en_ds==ENABLE)
    {
        pSPIx->I2C_CR1 |= (1<<0);                                                                                                                                                                                                                                     
    }

    else
    {
        pSPIx->I2C_CR1 &= ~(1<<0);    
    }
    
}



/// @brief 
/// @param pSPIHandle 
void I2C_Init(I2C_Handle_t *pSPIHandle)
{
    // configure the mode
    uint32_t PCLK1 = RCC_GetPCLK1();
    
    // configure the speed

    // configure the device address

    // enable/disablr the ACK
    if(pSPIHandle->I2CConfig.ack_control == I2C_ACK_ENABLE)
    {
        pSPIHandle->pI2Cx->I2C_CR1 |= (1<<10);
    }

    else
    {
        pSPIHandle->pI2Cx->I2C_CR1 &= ~(1<<10);
    }

    // configure the rise time
}





/// @brief 
/// @param pSPIx 
/// @param status 
void I2C_ClockControl(I2C_RegDef_t *pSPIx, uint8_t status)
{
    if(status == ENABLE && pSPIx==I2C1)
    {
        I2C_1_CLOCK_EN();
    }

    else if(status == DISABLE && pSPIx==I2C1)
    {
        I2C_1_CLOCK_DS();
    }


    else if(status == ENABLE && pSPIx==I2C2)
    {
        I2C_2_CLOCK_EN();
    }

    else if(status == DISABLE && pSPIx==I2C2)
    {
        I2C_2_CLOCK_DS();
    }
}




/// @brief 
/// @param IRQNumber 
/// @param IRQPriority 
/// @param EN 
void I2C_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN)
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

        SPI_IRQPriorityConfig(IRQNumber, IRQPriority);
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




void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint32_t ipr_field = IRQNumber/4;
    uint32_t ipr_section = IRQNumber%4;
    *(NVIC_IPR_BASE_ADD+(ipr_field*4)) |= (IRQPriority<<(8*ipr_section));
}


