#ifndef STM32F103XX_UART_H_
#define STM32F103XX_UART_H_

#include "stm32f103xx.h"


typedef enum
{
    USART_TX = 0,
    USART_RX = 1,
    USART_TXRX = 2,
}USART_MODE;


typedef enum
{
    BITS_8 = 0,
    BITS_9 = 1,
}USART_WORDLEN;

typedef enum
{
    BAUD_1200   = 1200,
    BAUD_2400   = 2400,
    BAUD_9600   = 9600,
    BAUD_19200  = 19200,
    BAUD_38400  = 38400,
    BAUD_57600  = 57600,
    BAUD_115200 = 115200,
    BAUD_230400 = 230400,
    BAUD_460800 = 460800,
    BAUD_921600 = 921600,

}USART_BAUDRATE;



typedef enum
{
    STB_1     = 0,
    STB_0_5   = 1,
    STB_2     = 2,
    STB_1_5   = 3,
}USART_NOSB;


typedef enum
{
    HWFC_NONE      = 0,
    HWFC_CTS       = 1,
    HWFC_RTS       = 2,
    HWFC_CTS_RTS   = 3,
}USART_HFC;



typedef enum
{
    ODD_PARITY        = 0,
    EVEN_PARITY       = 1,
    NO_PARITY         = 2,
}USART_PARITY_BIT;


typedef enum
{
    UART_OVERSAMPLING_16        = 0,
    UART_OVERSAMPLING_8         = 1,
}USART_OVERSAMPLING;

typedef enum
{
    PE = 0,
    FE = 1,
    NE = 2,
    ORE = 3,
    IDLE = 4,
    RXNE = 5,
    TC = 6,
    TXE = 7,
    LBD = 8,
    CTS = 9,
}USART_STATUS_REGISTER;

typedef struct 
{
 uint8_t USART_Mode;
 int     USART_BoaudRate;
 uint8_t USART_WordLength;
 uint8_t USART_OVERSAMPLING;
 uint8_t USART_StopBits;
 uint8_t USART_ParityControl;
 uint8_t USART_HardwareFlowControl;
}USART_Config_t;




typedef struct 
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t UARTConfig;
}UART_Handle_t;


void USART_PriClockControl(USART_RegDef_t *pUSARTx, uint8_t ENorDs);
void USART_PripheralControl(USART_RegDef_t *pUSARTx, uint8_t ENorDs);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, USART_STATUS_REGISTER StatusFlagName);
void USART_ClearFlagStatus(USART_RegDef_t *pUSARTx, USART_STATUS_REGISTER StatusFlagName);
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDs);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t priority);
void UART_Init(UART_Handle_t *USARTx);
void UART_Deinit(UART_Handle_t *USARTx);
void USART_SendData(UART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(UART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(UART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(UART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);

#endif
