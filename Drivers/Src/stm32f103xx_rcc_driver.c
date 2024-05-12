#include "stm32f103xx_rcc_driver.h"


uint16_t AHB_Prescaller[8]  = {2,4,16,64,128,256,512};
uint16_t APB1_Prescaller[4] = {2,4,8,16};
uint16_t APB2_Prescaller[4] = {2,4,8,16};

uint32_t RCC_GetPLLOutputClock()
{
    return 0;
}



uint32_t RCC_GetPCLK1()
{
    uint32_t pclk1, SystemClk = 0;

    uint8_t clksrc,temp,ahbp,apb1p = 0 ;

    clksrc = (RCC->RCC_CFGR >> 2) & 0X03;

    if(clksrc==RCC_HSI)
    {
        SystemClk = 16000000;
    }

    else if(clksrc==RCC_HSE)
    {
        SystemClk = 8000000;
    }

    else if(clksrc==RCC_PLL)
    {
        SystemClk = RCC_GetPLLOutputClock();
    }


    // check the ABH prescaller
    temp = (RCC->RCC_CFGR>>4) & (0xF);

    if(temp<8)
    {
        ahbp = 0;
    }

    else
    {
        ahbp = AHB_Prescaller[ahbp-8];
    }



    // check the APB1 prescaller
    temp = (RCC->RCC_CFGR>>8) & (0x7);

    if(temp<4)
    {
        apb1p = 0;
    }

    else
    {
        apb1p = APB1_Prescaller[apb1p-4];
    }

    pclk1 = (SystemClk/ahbp)/apb1p;

    return pclk1;
}


uint32_t RCC_GetPCLK2()
{
    uint32_t pclk2, SystemClk = 0;

    uint8_t clksrc,temp,ahbp,apb2p = 0;

    clksrc = (RCC->RCC_CFGR >> 2) & 0X03;

    if(clksrc==RCC_HSI)
    {
        SystemClk = 16000000;
    }

    else if(clksrc==RCC_HSE)
    {
        SystemClk = 8000000;
    }

    else if(clksrc==RCC_PLL)
    {
        SystemClk = RCC_GetPLLOutputClock();
    }


    // check the ABH prescaller
    temp = (RCC->RCC_CFGR>>4) & (0xF);

    if(temp<8)
    {
        ahbp = 0;
    }

    else
    {
        ahbp = AHB_Prescaller[ahbp-8];
    }



    // check the APB1 prescaller
    temp = (RCC->RCC_CFGR>>11) & (0x7);

    if(temp<4)
    {
        apb2p = 0;
    }

    else
    {
        apb2p = APB2_Prescaller[apb2p-4];
    }

    pclk2 = (SystemClk/ahbp)/apb2p;

    return pclk2;
}
