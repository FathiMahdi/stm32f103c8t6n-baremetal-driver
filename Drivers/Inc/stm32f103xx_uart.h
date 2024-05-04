#ifndef STM32F103XX_UART_H_
#define STM32F103XX_UART_H_

#include "stm32f103xx.h"


typedef struct 
{
;
}UART_Config_t;




typedef struct 
{
    USART_RegDef_t *pUSARTx;
    UART_Config_t UARTConfig;
}SPI_Handle_t;


void UART_Init(void);
void UART_Deinit(void);
void UART_SendData(void);
void UART_ReceiveData(void);


#endif