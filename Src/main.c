#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f103xx_gpio_driver.h"

#define SCB_AIRCR_BASE_ADD 0xE000ED0CU

char myData[50];


volatile uint32_t count = 0;


void NVIC_SysReset(void)
{
	uint32_t* AIRCR = (uint32_t *)SCB_AIRCR_BASE_ADD;
	*AIRCR |= (1<<2);
}


void SystickEnable(void)
{
	SYSTICK_ENABLE();
//	SYSTICK->STK_CTRL|=
}


void delay(uint32_t delay_time)
{
	count = 0;

//   NVIC_SysReset();

	while(count<delay_time)
	{
		;
	}

	return;
}


void GPIOC_Init(void)
{
	GPIO_Handler_t GPIOB_conf;
	GPIO_Handler_t GPIOC_conf;

	GPIOB_conf.GPIO_PinCOnfig.PinNumber = 0;
	GPIOB_conf.GPIO_PinCOnfig.PinMode = input_pullup_pull_down;
	GPIOB_conf.GPIO_PinCOnfig.PinSpeed = reset;
	GPIOB_conf.pGPIOx = GPIOB;

	// enable portc clock
	GPIOClockControl(GPIOB,ENABLE);
	GPIOClockControl(GPIOC,ENABLE);

	GPIOInit(&GPIOB_conf);

	GPIOC_conf.GPIO_PinCOnfig.PinNumber = 13;
	GPIOC_conf.GPIO_PinCOnfig.PinMode = output_push_pull;
	GPIOC_conf.GPIO_PinCOnfig.PinSpeed = MHz_50;
	GPIOC_conf.pGPIOx = GPIOC;
	GPIOInit(&GPIOC_conf);


}

uint8_t value = 0;

int main(void)
{
	// SystickEnable();
	GPIOC_Init();
//	SystickEnable();

	while(1)
	{

//		value = GPIORead(GPIOB, 0);
//
//		if (value == 1)
//		{
//			GPIOWrite(GPIOC, 13, SET);

			GPIOToggle(GPIOC, 13);

			delay(10);
//		}

//		else
//		{
//			GPIOWrite(GPIOC, 13, RESET);
//		}
//		GPIOWrite(GPIOB, 0, SET);
//
//		for(int i=0;i<72000;i++)
//		{
//			;
//		}
//
//
//		GPIOWrite(GPIOB, 0, RESET);
//
//		for(int i=0;i<72000;i++)
//		{
//			;
//		}

	}
}



/// @brief systick interrupt handler
/// @param  void
void SysTick_Handler(void)
{
	count++;
}

