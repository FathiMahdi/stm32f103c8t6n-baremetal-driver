#include "stm32f103xx_gpio_driver.h"



/// @brief GPIO clock control
/// @param pGPIOx 
/// @param status 
void GPIOClockControl(GPIO_RegDef_t *pGPIOx, uint8_t status)
{
    if(status==ENABLE)
    {
        if(pGPIOx==AFIO)
        {
            AFIO_CLOCK_EN();
        }

        else if(pGPIOx == GPIOA)
        {
            GPIOA_CLOCK_EN();
        }

        else if(pGPIOx == GPIOB)
        {
            GPIOB_CLOCK_EN();
        }

        else if(pGPIOx == GPIOC)
        {
            GPIOC_CLOCK_EN();
        }

        else if(pGPIOx == GPIOD)
        {
            GPIOD_CLOCK_EN();
        }

        else if(pGPIOx == GPIOE)
        {
            GPIOE_CLOCK_EN();
        }

        else if(pGPIOx == GPIOF)
        {
            GPIOF_CLOCK_EN();
        }

        else if(pGPIOx == GPIOG)
        {
            GPIOG_CLOCK_EN();
        }
    }

    else if(status==DISABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_CLOCK_DS();
        }

        else if(pGPIOx == GPIOB)
        {
            GPIOB_CLOCK_DS();
        }

        else if(pGPIOx == GPIOC)
        {
            GPIOC_CLOCK_DS();
        }

        else if(pGPIOx == GPIOD)
        {
            GPIOD_CLOCK_DS();
        }

        else if(pGPIOx == GPIOE)
        {
            GPIOE_CLOCK_DS();
        }

        else if(pGPIOx == GPIOF)
        {
            GPIOF_CLOCK_DS();
        }

        else if(pGPIOx == GPIOG)
        {
            GPIOG_CLOCK_DS();
        }
    }
}

 

/// @brief GPIO initialization
/// @param pGPIOx 
/// @param mode 
/// @param speed 
void GPIOInit(GPIO_Handler_t *GPIO_conf)
{
   
    if (GPIO_conf->GPIO_PinCOnfig.PinMode == output_push_pull)
    {
   

        if  (GPIO_conf->GPIO_PinCOnfig.PinNumber>7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-30));
            
            // set gpio speed MODE
            GPIO_conf->pGPIOx->GPIO_CRH |= (1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));
        }

        else if  (GPIO_conf->GPIO_PinCOnfig.PinNumber <= 7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRL &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+2));


            // set the gpio speed
            GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinSpeed<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)));
   
        }

    }


    else if (GPIO_conf->GPIO_PinCOnfig.PinMode == output_open_drain)
    {
        if  (GPIO_conf->GPIO_PinCOnfig.PinNumber>7)
        {
            // set GIO mode
            GPIO_conf->pGPIOx->GPIO_CRH |= (1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE-2));
            
            // set gpio speed
            GPIO_conf->pGPIOx->GPIO_CRH |= (GPIO_conf->GPIO_PinCOnfig.PinSpeed<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));
        }

        else if  (GPIO_conf->GPIO_PinCOnfig.PinNumber <= 7)
        {
            // set GIO mode
            GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+2));

            // set the gpio speed
            GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinSpeed<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)));
        }
    }

    else if(GPIO_conf->GPIO_PinCOnfig.PinMode == input_floating || GPIO_conf->GPIO_PinCOnfig.PinMode == input_pullup_pull_down)
    {
        if  (GPIO_conf->GPIO_PinCOnfig.PinNumber>7)
        {
            // set GIO mode
            GPIO_conf->pGPIOx->GPIO_CRH |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE-2));
            
            // set gpio speed
            GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));
        }

        else if  (GPIO_conf->GPIO_PinCOnfig.PinNumber <= 7)
        {
            // set GIO mode
            //GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+3));
        	GPIO_conf->pGPIOx->GPIO_CRL &= ~(1<<2);
        	GPIO_conf->pGPIOx->GPIO_CRL |=  (2<<2);


            // set the gpio speed as resset
            GPIO_conf->pGPIOx->GPIO_CRL &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)));
        }
    }

    else if( GPIO_conf->GPIO_PinCOnfig.PinMode == IT_FT)
    {          
        // set GIO mode
        // GPIO_conf->pGPIOx->GPIO_CRH |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE-2));
        
        // // set gpio speed
        // GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));

        EXTI->exti_FTSR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_RTSR &= ~(1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_IMR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        uint32_t temp1 = GPIO_conf->GPIO_PinCOnfig.PinNumber/4;

        uint32_t temp2 = GPIO_conf->GPIO_PinCOnfig.PinNumber%4;

        if(GPIO_conf->pGPIOx == GPIOA)
        {
            AFIO->AFIO_EXTICR[temp1] &= ~(1<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOB)
        {
            AFIO->AFIO_EXTICR[temp1] |= (1<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOC)
        {
            AFIO->AFIO_EXTICR[temp1] |= (2<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOD)
        {
            AFIO->AFIO_EXTICR[temp1] |= (3<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOE)
        {
            AFIO->AFIO_EXTICR[temp1] |= (4<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOF)
        {
            AFIO->AFIO_EXTICR[temp1] |= (5<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOG)
        {
            AFIO->AFIO_EXTICR[temp1] |= (6<<4*temp2);
        }
    }

    else if( GPIO_conf->GPIO_PinCOnfig.PinMode == IT_RT)
    {          
        // set GIO mode
        //GPIO_conf->pGPIOx->GPIO_CRH |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE-2));
        
        // // set gpio speed
        GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));

        EXTI->exti_RTSR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_FTSR &= ~(1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_IMR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);
        
        uint32_t temp1 = GPIO_conf->GPIO_PinCOnfig.PinNumber/4;

        uint32_t temp2 = GPIO_conf->GPIO_PinCOnfig.PinNumber%4;

        if(GPIO_conf->pGPIOx == GPIOA)
        {
            AFIO->AFIO_EXTICR[temp1] &= ~(1<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOB)
        {
            AFIO->AFIO_EXTICR[temp1] |= (1<<4*temp2); 
        }

        else if(GPIO_conf->pGPIOx == GPIOC)
        {
            AFIO->AFIO_EXTICR[temp1] |= (2<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOD)
        {
            AFIO->AFIO_EXTICR[temp1] |= (3<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOE)
        {
            AFIO->AFIO_EXTICR[temp1] |= (4<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOF)
        {
            AFIO->AFIO_EXTICR[temp1] |= (5<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOG)
        {
            AFIO->AFIO_EXTICR[temp1] |= (6<<4*temp2);
        }
        
    }

    else if( GPIO_conf->GPIO_PinCOnfig.PinMode == IT_RFT)
    {            
        // // set GIO mode
        // GPIO_conf->pGPIOx->GPIO_CRH |= (GPIO_conf->GPIO_PinCOnfig.PinMode<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE-2));
            
        // // set gpio speed
        // GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));

        EXTI->exti_RTSR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_FTSR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        EXTI->exti_IMR |= (1<<GPIO_conf->GPIO_PinCOnfig.PinNumber);

        uint32_t temp1 = GPIO_conf->GPIO_PinCOnfig.PinNumber/4;

        uint32_t temp2 = GPIO_conf->GPIO_PinCOnfig.PinNumber%4;
        
        if(GPIO_conf->pGPIOx == GPIOA)
        {
            AFIO->AFIO_EXTICR[temp1] &= ~(1<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOB)
        {
            AFIO->AFIO_EXTICR[temp1] |= (1<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOC)
        {
            AFIO->AFIO_EXTICR[temp1] |= (2<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOD)
        {
            AFIO->AFIO_EXTICR[temp1] |= (3<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOE)
        {
            AFIO->AFIO_EXTICR[temp1] |= (4<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOF)
        {
            AFIO->AFIO_EXTICR[temp1] |= (5<<4*temp2);
        }

        else if(GPIO_conf->pGPIOx == GPIOG)
        {
            AFIO->AFIO_EXTICR[temp1] |= (6<<4*temp2);
        }
            
    }



    else if (GPIO_conf->GPIO_PinCOnfig.PinMode == alternate_push_pull)
    {
   

        if  (GPIO_conf->GPIO_PinCOnfig.PinNumber>7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRH &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-30));
            GPIO_conf->pGPIOx->GPIO_CRH |= (2<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-30));
            
            // set gpio speed MODE
            GPIO_conf->pGPIOx->GPIO_CRH |= (1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));
        }

        else if  (GPIO_conf->GPIO_PinCOnfig.PinNumber <= 7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRL &= ~(1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+2));
            GPIO_conf->pGPIOx->GPIO_CRL |= (2<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+2));


            // set the gpio speed
            GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinSpeed<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)));
   
        }

    }



    else if (GPIO_conf->GPIO_PinCOnfig.PinMode == alternate_open_drain)
    {
   

        if  (GPIO_conf->GPIO_PinCOnfig.PinNumber>7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRH |= (3<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-30));
            
            // set gpio speed MODE
            GPIO_conf->pGPIOx->GPIO_CRH |= (1<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)-REGISTER_SIZE));
        }

        else if  (GPIO_conf->GPIO_PinCOnfig.PinNumber <= 7)
        {
            // set GIO mode CONF
            GPIO_conf->pGPIOx->GPIO_CRL |= (3<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)+2));


            // set the gpio speed
            GPIO_conf->pGPIOx->GPIO_CRL |= (GPIO_conf->GPIO_PinCOnfig.PinSpeed<<(4*(GPIO_conf->GPIO_PinCOnfig.PinNumber)));
   
        }

    }

    
}

// void GPIODeInit(GPIO_Handler_t GPIO_conf)
// {

// }

/// @brief GPIO pin write
/// @param pGPIOx GPIO base address
/// @param status SET/RESET
void GPIOWrite(GPIO_RegDef_t *pGPIOx, uint8_t pin, uint8_t status)
{
    if (status == SET)
    {
        pGPIOx->GPIO_BSRR |= (1<<pin);
    }

    if (status == RESET)
    {
        pGPIOx->GPIO_BRR |= (1<<pin);
    }      
}


uint32_t GPIORead(GPIO_RegDef_t *pGPIOx, uint8_t pin)
{
    uint32_t input = 0x00000000U;
    uint32_t cmp   = 0x00000000U;
    input |= (1<<pin);
    cmp   |= (1<<pin);
    input &= pGPIOx->GPIO_IDR;

    if(input == cmp)
    {
        return 1;
    }

    else 
    {
        return 0;
    }

 
}


/// @brief Toggle pin
/// @param pGPIOx 
/// @param pin 
void GPIOToggle(GPIO_RegDef_t *pGPIOx, uint8_t pin)
{
    pGPIOx->GPIO_ODR ^= (1<<pin);

}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN)
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

        GPIO_IRQPriorityConfig(IRQNumber, IRQPriority);
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
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint32_t ipr_field = IRQNumber/4;
    uint32_t ipr_section = IRQNumber%4;
    *(NVIC_IPR_BASE_ADD+(ipr_field*4)) |= (IRQPriority<<(8*ipr_section));

}


/// @brief 
/// @param PinNumber 
void GPIO_IRQHandler(uint8_t PinNumber)
{

    // clear the pr register
    if(EXTI->exti_PR & (1<<PinNumber))
    {
        EXTI->exti_PR |= (1<<PinNumber);
    }

}
