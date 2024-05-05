#include "stm32f103xx_uart.h"



/// @brief 
/// @param pUSARTx 
/// @param ENorDs 
void USART_PriClockControl(USART_RegDef_t *pUSARTx, uint8_t ENorDs)
{
  if(pUSARTx==USART1 && ENorDs == ENABLE)
  {
    USART1_CLOCK_EN();
  }


  if(pUSARTx==USART1 && ENorDs == DISABLE)
  {
    USART1_CLOCK_DS();
  }

  // ! implemewnt for the rest io the usaret addressses

}



/// @brief 
/// @param pUSARTx 
/// @param StatusFlagName 
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, USART_STATUS_REGISTER StatusFlagName)
{
  uint32_t temp = pUSARTx->USART_SR;

  uint32_t temp2 = (1<<StatusFlagName);

  if(temp&temp2)
  {
    return 1;
  }
  
  else
  {
    return 0;
  }
  
}


/// @brief 
/// @param pUSARTx 
/// @param ENorDs 
void USART_PripheralControl(USART_RegDef_t *pUSARTx, uint8_t ENorDs)
{
  if(ENorDs == ENABLE)
  {
    pUSARTx->USART_CR1|=(1<<13);
  }

  else
  {
    pUSARTx->USART_CR1&=~(1<<13);
  } 
}





/// @brief 
/// @param  
void UART_Init(UART_Handle_t *USARTx)
{
  
  // set word length
  if(USARTx->UARTConfig.USART_WordLength == BITS_8)
  {
    USARTx->pUSARTx->USART_CR1 &= ~(1<<12) ;
  } 

  else
  {
    USARTx->pUSARTx->USART_CR1 |= (1<<12) ;
  }   



  // USART Mode
  if(USARTx->UARTConfig.USART_Mode == USART_TX)
  {
    USARTx->pUSARTx->USART_CR1 &= ~(1<<2) ;
    USARTx->pUSARTx->USART_CR1 |= (1<<3) ;
  }

  else if(USARTx->UARTConfig.USART_Mode == USART_RX)
  {
    USARTx->pUSARTx->USART_CR1 |= (1<<2) ;
    USARTx->pUSARTx->USART_CR1 &= ~(1<<3) ;
  }

  else if(USARTx->UARTConfig.USART_Mode == USART_TXRX)
  {

    USARTx->pUSARTx->USART_CR1 |= (1<<2) ;
    USARTx->pUSARTx->USART_CR1 |= (1<<3) ;
    
  }



  // Parity control
  if(USARTx->UARTConfig.USART_ParityControl == ODD_PARITY)
  {
    USARTx->pUSARTx->USART_CR1 |= (1<<10);
    USARTx->pUSARTx->USART_CR1 |= (1<<9);
  }

  else if(USARTx->UARTConfig.USART_ParityControl == EVEN_PARITY)
  {
    USARTx->pUSARTx->USART_CR1 |= (1<<10);
    USARTx->pUSARTx->USART_CR1 &= ~(1<<9);
  }

  else
  {
    USARTx->pUSARTx->USART_CR1 &= ~(1<<10);
  }



  // set number of stop bits
  if(USARTx->UARTConfig.USART_StopBits == STB_1)
  {
    USARTx->pUSARTx->USART_CR2 |= (STB_1<<12);

  }

  else if(USARTx->UARTConfig.USART_StopBits == STB_0_5)
  {
    USARTx->pUSARTx->USART_CR1 |= (STB_0_5<<12);

  }

  else if(USARTx->UARTConfig.USART_StopBits == STB_2)
  {
    USARTx->pUSARTx->USART_CR1 |= (STB_2<<12);

  }

  else if(USARTx->UARTConfig.USART_StopBits == STB_1_5)
  {
    USARTx->pUSARTx->USART_CR1 |= (STB_1_5<<12);
  }

  else
  {
    USARTx->pUSARTx->USART_CR2 |= (STB_1<<12);
  }
  

  // set hardware flow control
  if(USARTx->UARTConfig.USART_HardwareFlowControl == HWFC_NONE)
  {
    USARTx->pUSARTx->USART_CR3 &= ~(1<<9);
    USARTx->pUSARTx->USART_CR3 &= ~(1<<8);
  }

  else if(USARTx->UARTConfig.USART_StopBits == HWFC_CTS)
  {
    USARTx->pUSARTx->USART_CR3 |= (1<<9);
  }

  else if(USARTx->UARTConfig.USART_StopBits == HWFC_RTS)
  {
    USARTx->pUSARTx->USART_CR3 |= (1<<8);
  }

  else if(USARTx->UARTConfig.USART_StopBits == HWFC_CTS_RTS)
  {
    USARTx->pUSARTx->USART_CR3 |= (1<<9);
    USARTx->pUSARTx->USART_CR3 |= (1<<8);
  }



}




/// @brief 
/// @param  
void UART_Deinit(UART_Handle_t *USARTx)
{

}



/// @brief 
/// @param  
void UART_SendData(USART_RegDef_t *pUSARTx)
{

}


/// @brief 
/// @param  
void UART_ReceiveData(USART_RegDef_t *pUSARTx)
{

}
