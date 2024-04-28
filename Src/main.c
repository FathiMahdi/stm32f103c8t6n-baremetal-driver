#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f103xx_gpio_driver.h"
#include "stm32f103xx_spi_driver.h"


char myData[50];

volatile uint32_t count = 0;


void GPIOC_Init(void)
{
	GPIO_Handler_t GPIOB_conf;
	GPIO_Handler_t GPIOC_conf;
	SPI_Handle_t SPI1_conf;

	GPIOB_conf.GPIO_PinCOnfig.PinNumber = 0;
	GPIOB_conf.GPIO_PinCOnfig.PinMode = IT_RT;
	GPIOB_conf.GPIO_PinCOnfig.PinSpeed = reset;
	GPIOB_conf.pGPIOx = GPIOB;

	// Enable IRQ exti0 line
	GPIO_IRQConfig(IRQ_NO_EXTI0, 0, ENABLE);

	// enable portc clock
	GPIOClockControl(AFIO,ENABLE);
	//GPIOClockControl(GPIOA,ENABLE);
	GPIOClockControl(GPIOB,ENABLE);
	GPIOClockControl(GPIOC,ENABLE);

	GPIOInit(&GPIOB_conf);

	GPIOC_conf.GPIO_PinCOnfig.PinNumber = 13;
	GPIOC_conf.GPIO_PinCOnfig.PinMode = output_push_pull;
	GPIOC_conf.GPIO_PinCOnfig.PinSpeed = MHz_50;
	GPIOC_conf.pGPIOx = GPIOC;
	GPIOInit(&GPIOC_conf);

	GPIOWrite(GPIOC,13,RESET);

	SPI1_conf.SPIConfig.SPI_DeviceMode 		=  SPI_MASTER;
	SPI1_conf.SPIConfig.SPI_CPHA  			=  0;
	SPI1_conf.SPIConfig.SPI_CPOL  			=  0;
	SPI1_conf.SPIConfig.SPI_DFF   			=  SPI_DFF_8_BIT;
	SPI1_conf.SPIConfig.SSM       			=  DISABLE;
	SPI1_conf.SPIConfig.SPI_BusConfig       =  SPI_FULLDUBLEX;
	SPI1_conf.SPIConfig.SPI_CLKSpeed        =  F_PCLK_DIV_2;

	// INITIALIZE SPI
	SPI_Init(& SPI1_conf);



}

uint8_t value = 0;

int main(void)
{

	GPIOC_Init();

	


	while(1)
	{


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
