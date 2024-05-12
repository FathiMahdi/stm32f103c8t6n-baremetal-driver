#include "stm32f103xx_i2c_driver.h"


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);
static void I2C_SendSlaveAddress(I2C_RegDef_t *pI2Cx, uint8_t SlaveADD);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);


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



/// @brief 
/// @param pI2CHandle 
/// @param data 
/// @param len 
/// @param SlaveADD 
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *data, uint16_t len, uint8_t SlaveADD)
{
    // generate the start condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    // confirm the start condition by reading the start bit
    while(!(pI2CHandle->pI2Cx->I2C_SR1 & 0x1))

    // send the address of the slave with w/r
    I2C_SendSlaveAddress(pI2CHandle->pI2Cx, SlaveADD);

    // confim the address by  reading the AADR
    while(!(pI2CHandle->pI2Cx->I2C_SR1 & 0x2))

    // clear the DDR flag
    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    // send data until len = 0
    while(len>0)
    {   
        while(!(pI2CHandle->pI2Cx->I2C_SR1 & 0x80));
        pI2CHandle->pI2Cx->I2C_DR = *data;
        data++;
        len--;
    }

    // wait until txe 
    while(!(pI2CHandle->pI2Cx->I2C_SR1 & 0x80));


    // wait untill btf
    while(!(pI2CHandle->pI2Cx->I2C_SR1 & 0x4));

    // send stop bit
    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
}




/// @brief Generate I2C start condition
/// @param pI2Cx 
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->I2C_CR1 |= (1<<8);
}


/// @brief Generate I2C start condition
/// @param pI2Cx 
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->I2C_CR1 |= (1<<9);
}


/// @brief 
/// @param pI2Cx 
/// @param  
static void I2C_SendSlaveAddress(I2C_RegDef_t *pI2Cx, uint8_t SlaveADD)
{
    SlaveADD = SlaveADD << 1;

    SlaveADD &= ~(1); // clear the 8th bit

    pI2Cx->I2C_DR = SlaveADD;

}


static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
    uint16_t sr1 = pI2Cx->I2C_SR1;
    uint16_t sr2 = pI2Cx->I2C_SR1;

}
