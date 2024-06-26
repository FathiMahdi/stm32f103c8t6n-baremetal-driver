#ifndef STM32F103XX_H_
#define STM32F103XX_H_

#include <stdint.h>
#include <stddef.h>
#include "stm32f103xx_rcc_driver.h"


#define REGISTER_SIZE 32

#define NVIC_IPR_BASE_ADD ((volatile uint32_t *)0xE000E400U)
#define NVIC_ISER0        ((volatile uint32_t *)0xE000E100U)
#define NVIC_ISER1        ((volatile uint32_t *)0xE000E104U)
#define NVIC_ISER2        ((volatile uint32_t *)0xE000E108U)
#define NVIC_ISER3        ((volatile uint32_t *)0xE000E10CU)
// #define NVIC_ISER4        0xE000E100U
// #define NVIC_ISER5        0xE000E100U
// #define NVIC_ISER6        0xE000E100U
// #define NVIC_ISER7        0xE000E11CU

#define NVIC_ICER0        ((volatile uint32_t *)0XE000E180U)
#define NVIC_ICER1        ((volatile uint32_t *)0xE000E104U)
#define NVIC_ICER2        ((volatile uint32_t *)0xE000E108U)
#define NVIC_ICER3        ((volatile uint32_t *)0xE000E10CU)
// #define NVIC_ICER4        0xE000E100U
// #define NVIC_ICER5        0xE000E100U
// #define NVIC_ICER6        0xE000E100U
// #define NVIC_ICER7        0xE000E19CU

#define SYSTICK_BASE_ADD  0xE000E010U


#define SYSTICK_ENABLE() (SYSTICK->STK_CTRL |= (1<<0)) 

// Memory bus base address

#define FLASH_BASE_ADD    0X08000000U // Flash memory falsh address
#define SRAM_BASE_ADD     0X20000000U // SRAM base address   
#define AHB_BASE_ADD      0X40018000U // Advanced High-speed bus base address
#define APB_2_BASE_ADD    0X40010000U // Advanced prephiral bus-2 base address 
#define APB_1_BASE_ADD    0X40000000U // Advanced prephiral bus-1 base address
#define RCC_BASE_ADD      0x40021000u // RCC base address 
#define EXTI_BASE_ADD     0x40010400U // EXTI base address
#define AFIO_BASE_ADD     0x40010000U // Alternative function base address

// Alternative fuction base addresses

#define I2C_1_BASE_ADD   0x40005400U  // I2C1 base address
#define I2C_2_BASE_ADD   0x40005800U  // I2C2 base address
#define SPI_1_BASE_ADD   0x40013000U  // SPI1 base address  
// #define SPI_2_BASE_ADD   0x40003800U  // SPI2 base address
// #define SPI_3_BASE_ADD   0x40003C00U  // SPI3 base address
#define USART_1_BASE_ADD  0x40013800U  // USART1 base address
#define USART_2_BASE_ADD  0x40004400U  // USART2 base address
#define USART_3_BASE_ADD  0x40004800U  // USART3 base address
#define UART_5_BASE_ADD   0x40005000U  // UART5 base address
#define UART_4_BASE_ADD   0x40004C00U  // UART4 base address


// GPIO BASE ADDRESSES

#define GPIO_A_BASE_ADD 0x40010800U // GPIO PORT A base address
#define GPIO_B_BASE_ADD 0x40010C00U // GPIO PORT B base address
#define GPIO_C_BASE_ADD 0x40011000U // GPIO PORT C base address
#define GPIO_D_BASE_ADD 0x40011400U // GPIO PORT D base address
#define GPIO_E_BASE_ADD 0x40011800U // GPIO PORT E base address
#define GPIO_F_BASE_ADD 0x40011C00U // GPIO PORT F base address
#define GPIO_G_BASE_ADD 0x40012000U // GPIO PORT G base address



// struct def
#define  RCC     ((RCC_RegDef_t*)   RCC_BASE_ADD)
#define  SYSTICK ((SYSTICK_RegDef_t*)SYSTICK_BASE_ADD)
#define  GPIOA   ((GPIO_RegDef_t *) GPIO_A_BASE_ADD)
#define  GPIOB   ((GPIO_RegDef_t *) GPIO_B_BASE_ADD)
#define  GPIOC   ((GPIO_RegDef_t *) GPIO_C_BASE_ADD)
#define  GPIOD   ((GPIO_RegDef_t *) GPIO_D_BASE_ADD)
#define  GPIOE   ((GPIO_RegDef_t *) GPIO_E_BASE_ADD)
#define  GPIOF   ((GPIO_RegDef_t *) GPIO_F_BASE_ADD)
#define  GPIOG   ((GPIO_RegDef_t *) GPIO_G_BASE_ADD)
#define  EXTI    ((EXTI_RegDef_t *)  EXTI_BASE_ADD)
#define  AFIO    ((AFIO_RegDef_t *) AFIO_BASE_ADD)
#define  SPI1    ((SPI_RegDef_t  *) SPI_1_BASE_ADD) 
#define  USART1  ((USART_RegDef_t  *) USART_1_BASE_ADD) 
#define  I2C1    ((I2C_RegDef_t *) I2C_1_BASE_ADD) 
#define  I2C2    ((I2C_RegDef_t *) I2C_2_BASE_ADD) 



// GPIO clock enable
#define AFIO_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<0))
#define GPIOA_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<2))
#define GPIOB_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<3))
#define GPIOC_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<4))
#define GPIOD_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<5))
#define GPIOE_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<6))
#define GPIOF_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<7))
#define GPIOG_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<8))
#define SPI1_CLOCK_EN() (RCC->RCC_ABP2BENR  |= (1<<12))
#define USART1_CLOCK_EN() (RCC->RCC_ABP2BENR  |= (1<<14))
#define I2C_1_CLOCK_EN() (RCC->RCC_ABP1BENR  |= (1<<21))
#define I2C_2_CLOCK_EN() (RCC->RCC_ABP1BENR  |= (1<<22))

#define GPIOA_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<2))
#define GPIOB_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<3))
#define GPIOC_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<4))
#define GPIOD_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<5))
#define GPIOE_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<6))
#define GPIOF_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<7))
#define GPIOG_CLOCK_DS() (RCC->RCC_ABP2BENR &= ~(1<<8))
#define SPI1_CLOCK_DS() (RCC->RCC_ABP2BENR  &= ~(1<<12))
#define USART1_CLOCK_DS() (RCC->RCC_ABP2BENR  &= ~(1<<14))
#define I2C_1_CLOCK_DS() (RCC->RCC_ABP1BENR  &= ~(1<<21))
#define I2C_2_CLOCK_DS() (RCC->RCC_ABP1BENR  &= ~(1<<22))


// ADC clock enable
#define ADC1_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<9))
#define ADC2_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<10))
#define ADC3_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<15))

// SPI clock enable 
#define SPI1_CLOCK_EN() (RCC->RCC_ABP2BENR |= (1<<12))

// EXTI IRQ position table
#define IRQ_NO_EXTI0       6
#define IRQ_NO_EXTI1       7
#define IRQ_NO_EXTI2       8 
#define IRQ_NO_EXTI3       9
#define IRQ_NO_EXTI4       10
#define IRQ_NO_EXTI9_5     23
#define IRQ_NO_EXTI15_10   40
#define IRQ_NO_SPI_1       35


#define ENABLE   1
#define DISABLE  0
#define SET      1
#define RESET    0
//RCC
typedef struct
{
	volatile uint32_t RCC_CR        ;// RCC control register 
    volatile uint32_t RCC_CFGR      ;// RCC configuration register 
    volatile uint32_t RCC_CIR       ;// RCC clock interrupt register
    volatile uint32_t RCC_APB2RSTR  ;// RCC APB2 prephiral reset register
    volatile uint32_t RCC_APB1RSTR  ;// RCC APB1 prephiral reset register
    volatile uint32_t RCC_AHBENR    ;// RCC AHB enable register
    volatile uint32_t RCC_ABP2BENR  ;// RCC APB2 enable register
    volatile uint32_t RCC_ABP1BENR  ;// RCC APB1 enable register
    volatile uint32_t RCC_BDCR      ;// RCC domain control register
    volatile uint32_t RCC_CSR       ;// RCC control register
}RCC_RegDef_t;


// SPI & I2S Registers
typedef struct
{
	volatile uint32_t SPI_CR1      ;// SPI control register 1
    volatile uint32_t SPI_CR2      ;// SPI control register 2
    volatile uint32_t SPI_SR       ;// SPI status register
    volatile uint32_t SPI_DR       ;// SPI data register 
    volatile uint32_t SPI_CRCPR    ;// SPI CRC polynomial register
    volatile uint32_t SPI_RXCRCR   ;// SPI RX CRC register
    volatile uint32_t SPI_TXCRCR   ;// SPI TX CRC register
    volatile uint32_t SPI_I2SCFGR  ;// SPI I2S configuration register
    volatile uint32_t SPI_I2SPR    ;// SPI I2S prescaller register
}SPI_RegDef_t;



typedef struct
{
    volatile uint32_t I2C_CR1;
    volatile uint32_t I2C_CR2;
    volatile uint32_t I2C_OAR1;
    volatile uint32_t I2C_OAR2;
    volatile uint32_t I2C_DR;
    volatile uint32_t I2C_SR1;
    volatile uint32_t I2C_SR2;
    volatile uint32_t I2C_CRR;
    volatile uint32_t I2C_TRISE;
}I2C_RegDef_t;


typedef struct
{
	volatile uint32_t USART_SR;// SPI control register 1
    volatile uint32_t USART_DR;// SPI control register 2
    volatile uint32_t USART_BRR;// SPI status register
    volatile uint32_t USART_CR1;// SPI data register 
    volatile uint32_t USART_CR2;// SPI CRC polynomial register
    volatile uint32_t USART_CR3;// SPI RX CRC register
    volatile uint32_t USART_GTPR;// SPI TX CRC register
}USART_RegDef_t;



// GPIO
typedef struct
{
	volatile uint32_t GPIO_CRL       ;// GPIO control register L
    volatile uint32_t GPIO_CRH       ;// GPIO control register H
    volatile uint32_t GPIO_IDR       ;// GPIO input data register
    volatile uint32_t GPIO_ODR       ;// GPIO output data register 
    volatile uint32_t GPIO_BSRR      ;// GPIO bit set/reset register
    volatile uint32_t GPIO_BRR       ;// GPIO bit reset register register
    volatile uint32_t GPIO_LCKR      ;// GPIO lock register
}GPIO_RegDef_t;




// GPIO
typedef struct
{
	volatile uint32_t exti_IMR      ;
    volatile uint32_t exti_EMR      ;
    volatile uint32_t exti_RTSR     ;
    volatile uint32_t exti_FTSR     ;
    volatile uint32_t exti_SWIER    ;
    volatile uint32_t exti_PR       ;
}EXTI_RegDef_t;



typedef struct 
{
	volatile uint32_t AFIO_EVCR    ;// 
    volatile uint32_t AFIO_MAPR    ;// 
    volatile uint32_t AFIO_EXTICR[4];// 
    volatile uint32_t AFIO_MAPR2   ;//       
}AFIO_RegDef_t;



typedef struct
{
	volatile uint32_t STK_CTRL ;// 
    volatile uint32_t STK_LOAD ;// 
    volatile uint32_t STK_VAL  ;// 
    volatile uint32_t STK_CALIB;// 
}SYSTICK_RegDef_t;







#endif