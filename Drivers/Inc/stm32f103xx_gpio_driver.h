#ifndef STM32F103XX_GPIO_DRIVER_H_
#define STM32F103XX_GPIO_DRIVER_H_

#include "stm32f103xx.h"



typedef enum
{
    reset  = 0,
    MHz_10 = 1,
    MHz_2  = 2,
    MHz_50 = 3,
}GPIO_speed;


typedef enum
{
    output_push_pull       = 0,
    output_open_drain      = 1,
    alternate_push_pull    = 2,
    alternate_open_drain   = 3,
    input_analog_mode      = 0,
    input_floating         = 1,
    input_pullup_pull_down = 2,
    IT_FT  = 3,
    IT_RT  = 4,
    IT_RFT = 5
}GPIO_mode;



typedef struct
{
    uint8_t PinNumber;
    GPIO_mode PinMode;
    GPIO_speed PinSpeed;
    GPIO_RegDef_t *port;
}GPIO_PinConfig_t;



typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinCOnfig;
}GPIO_Handler_t;




// Initialize
void GPIOInit(GPIO_Handler_t *GPIO_conf);
void GPIODeInit(GPIO_Handler_t *GPIO_conf);

// Enable disable clock
void GPIOClockControl(GPIO_RegDef_t *pGPIOx, uint8_t status);


// Read pin
uint32_t GPIORead(GPIO_RegDef_t *pGPIOx, uint8_t pin);

// Write pin
void GPIOWrite(GPIO_RegDef_t *pGPIOx, uint8_t pin, uint8_t status);

// Toggle
void GPIOToggle(GPIO_RegDef_t *pGPIOx, uint8_t pin);


// config alternate func


// Interrupt handling
void GPIOIRQConfig(void);
void GPIOIRQHandler(void);



#endif
