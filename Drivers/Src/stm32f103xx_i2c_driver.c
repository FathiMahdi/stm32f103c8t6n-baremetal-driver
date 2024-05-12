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
/// @param pI2CHandle 
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    // configure the mode
    uint32_t PCLK1 = RCC_GetPCLK1() / 1000000U;
    pI2CHandle->pI2Cx->I2C_CR2 = (PCLK1 & 0x3F);

    // configure the speed
    uint16_t ccr_value = 0;

    if(pI2CHandle->I2CConfig.speed == I2C_STANDARD_SPEED)
    {   
        // set I2C standard mode
        pI2CHandle->pI2Cx->I2C_CRR &= ~(1<<15);
        ccr_value =  (RCC_GetPCLK1() /(2*pI2CHandle->I2CConfig.speed));
        
    }

    else
    {
        // set I2C fast mode
        pI2CHandle->pI2Cx->I2C_CRR |= (1<<15);
        pI2CHandle->pI2Cx->I2C_CRR |= (pI2CHandle->I2CConfig.fm_duty_cycle<<14); // set the FM duty cycle

        if(pI2CHandle->I2CConfig.fm_duty_cycle==DUTY_2)
        {
            ccr_value = (RCC_GetPCLK1()/3*pI2CHandle->I2CConfig.speed);
        }

        else
        {
            ccr_value = (RCC_GetPCLK1()/25*pI2CHandle->I2CConfig.speed);
        }

    }

    // set the ccr value
    ccr_value = (ccr_value & 0x7FF);
    pI2CHandle->pI2Cx->I2C_CRR |= (ccr_value<<0);



    // configure the device address
    pI2CHandle->pI2Cx->I2C_OAR1 |= (pI2CHandle->I2CConfig.own_address << 1);
    pI2CHandle->pI2Cx->I2C_OAR1 |= (1 << 14); // should be 1 


    // enable/disablr the ACK
    if(pI2CHandle->I2CConfig.ack_control == I2C_ACK_ENABLE)
    {
        pI2CHandle->pI2Cx->I2C_CR1 |= (1<<10);
    }

    else
    {
        pI2CHandle->pI2Cx->I2C_CR1 &= ~(1<<10);
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


