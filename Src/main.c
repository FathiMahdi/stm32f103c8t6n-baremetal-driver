#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f103xx_gpio_driver.h"
#include "stm32f103xx_spi_driver.h"


char myData[50];

volatile uint32_t count = 0;


void GPIOC_Init(void)
{

	GPIO_Handler_t SPIPIN_conf;
	SPI_Handle_t SPI1_conf;


	// enable portc clock
	GPIOClockControl(AFIO,ENABLE);
	GPIOClockControl(GPIOA,ENABLE);
	SPI_ClockControl(SPI1,ENABLE);

	// set SCK
	SPIPIN_conf.GPIO_PinCOnfig.PinNumber = 5;
	SPIPIN_conf.GPIO_PinCOnfig.PinMode = alternate_push_pull;
	SPIPIN_conf.GPIO_PinCOnfig.PinSpeed = MHz_50;
	SPIPIN_conf.pGPIOx = GPIOA;
	GPIOInit(&SPIPIN_conf);


	// set MOSI
	SPIPIN_conf.GPIO_PinCOnfig.PinNumber = 7;
	SPIPIN_conf.GPIO_PinCOnfig.PinMode = alternate_push_pull;
	SPIPIN_conf.GPIO_PinCOnfig.PinSpeed = MHz_50;
	SPIPIN_conf.pGPIOx = GPIOA;
	GPIOInit(&SPIPIN_conf);



	SPI1_conf.SPIConfig.SPI_DeviceMode 		=  SPI_MASTER;
	SPI1_conf.SPIConfig.SPI_CPHA  			=  0;
	SPI1_conf.SPIConfig.SPI_CPOL  			=  0;
	SPI1_conf.SPIConfig.SPI_DFF   			=  SPI_DFF_8_BIT;
	SPI1_conf.SPIConfig.SSM       			=  DISABLE;
	SPI1_conf.SPIConfig.SPI_BusConfig       =  SPI_FULLDUBLEX;
	SPI1_conf.SPIConfig.SPI_CLKSpeed        =  F_PCLK_DIV_4;
	SPI1_conf.pSPIx                         =  SPI1;

	// INITIALIZE SPI
	SPI_Init(&SPI1_conf);





	// No remap (NSS/PA4, SCK/PA5, MISO/PA6, MOSI/PA7)
	// Remap (NSS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)



}

uint8_t value = 0;

int main(void)
{

	GPIOC_Init();

	char buff[] = "Hello, world";

	SPI_Enable(SPI1,ENABLE);

	SPI_SendData(SPI1,(uint8_t*)buff,strlen(buff));

	SPI_Enable(SPI1,DISABLE);

	while(1)
	{

		SPI_Enable(SPI1,ENABLE);

		SPI_SendData(SPI1,(uint8_t*)buff,strlen(buff));

		SPI_Enable(SPI1,DISABLE);

		for(int i=0;i<666666;i++)
		{
			;
		}


	}
}



void EXTI0_IRQHandler(void)
{
	for(int i=0;i<6666;i++)
	{
		;
	}


	// check the pr
	GPIO_IRQHandler(0);

	// toggle pin
	GPIOToggle(GPIOC, 13);
}


// void EXTI1_IRQHandler(void)
// {
	
// }

// void EXTI2_IRQHandler(void)
// {
	
// }

// void EXTI3_IRQHandler(void)
// {
	
// }


// void EXTI4_IRQHandler(void)
// {
	
// }
