#include "stm32f103xx_spi_driver.h"


void SPI_ClockControl(SPI_RegDef_t *pGPIOx, uint8_t status)
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