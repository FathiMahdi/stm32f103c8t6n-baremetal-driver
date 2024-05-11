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


  // set baudrate

}




/// @brief 
/// @param  
void UART_Deinit(UART_Handle_t *USARTx)
{

}



/// @brief 
/// @param pUSARTHandle 
/// @param pTxBuffer 
/// @param Len 
void USART_SendData(UART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint16_t *pdata;
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,TXE));

    //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->UARTConfig.USART_WordLength == BITS_9)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits 
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->USART_DR = (*pdata & (uint16_t)0x01FF);
			
			//check for USART_ParityControl
			if(pUSARTHandle->UARTConfig.USART_ParityControl == NO_PARITY)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice 
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}


		else
		{
			//This is 8bit data transfer 
			pUSARTHandle->pUSARTx->USART_DR = (*pTxBuffer  & (uint8_t)0xFF);

			pTxBuffer++;
		
		} 

	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,TC));
}


/// @brief 
/// @param pUSARTHandle 
/// @param pRxBuffer 
/// @param Len 
void USART_ReceiveData(UART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,RXNE));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->UARTConfig.USART_WordLength == BITS_9)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->UARTConfig.USART_ParityControl == NO_PARITY)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->USART_DR  & (uint16_t)0x01FF);

				//Now increment the pRxBuffer two times
				pRxBuffer++;
        pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				*pRxBuffer = (pUSARTHandle->pUSARTx->USART_DR  & (uint8_t)0xFF);
				 
				//Increment the pRxBuffer
				pRxBuffer++;
  
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->UARTConfig.USART_ParityControl == NO_PARITY)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
        *pRxBuffer = (pUSARTHandle->pUSARTx->USART_DR  & (uint8_t)0xFF);
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
        *pRxBuffer = (pUSARTHandle->pUSARTx->USART_DR  & (uint8_t)0X7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}



/// @brief 
/// @param pUSARTHandle 
/// @param pRxBuffer 
/// @param Len 
/// @return 
uint8_t USART_ReceiveDataIT(UART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	// uint8_t rxstate = pUSARTHandle->TODO;

	// if(rxstate != TODO)
	// {
	// 	pUSARTHandle->RxLen = Len;
	// 	pUSARTHandle->pRxBuffer = TODO;
	// 	pUSARTHandle->RxBusyState = TODO;

	// 	//Implement the code to enable interrupt for RXNE
	// 	TODO

	// }

	// return rxstate;

}



/// @brief 
/// @param pUSARTHandle 
/// @param pTxBuffer 
/// @param Len 
/// @return 
uint8_t USART_SendDataIT(UART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	// uint8_t txstate = pUSARTHandle->TODO;

	// if(txstate != USART_BUSY_IN_TX)
	// {
	// 	pUSARTHandle->TODO = Len;
	// 	pUSARTHandle->pTxBuffer = TODO;
	// 	pUSARTHandle->TxBusyState = TODO;

	// 	//Implement the code to enable interrupt for TXE
	// 	TODO
		

	// 	//Implement the code to enable interrupt for TC 
	// 	TODO		
		

	// }

	//return txstate;

}
