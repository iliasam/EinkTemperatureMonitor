//ILIASAM - 10.2018

#include "uart_handling.h"
#include "fifo_functions.h"
#include "mavlink_handling.h"
#include "gpio_common.h"
#include "config.h"
#include "misc.h"//nvic


// Defines ********************************************************************

// Length of RX FIFO buffer
#define UART_RX_FIFO_SIZE       128

// Variables ******************************************************************
volatile uint8_t uart_rx_fifo_buf[UART_RX_FIFO_SIZE];

volatile fifo_struct_t uart_rx_fifo;


// Functions ******************************************************************

// UART RX interrupts hanging
void UART_IRQ_HANDLER(void)
{
  if (USART_GetITStatus(UART_NAME, USART_IT_RXNE)) 
  {
    USART_ClearITPendingBit(UART_NAME, USART_IT_RXNE);
    
    uint8_t temp = USART_ReceiveData(UART_NAME);
    fifo_add_byte((fifo_struct_t*)&uart_rx_fifo, temp);
  }
}

// Check if data present in RX FIFO
// Should be called periodically
void uart_handling_rx_data(void)
{
  uint8_t rx_byte = 0;
  while (fifo_get_byte((fifo_struct_t*)&uart_rx_fifo, &rx_byte))
  {
    mavlink_parse_byte(rx_byte);
  }
}


// ИНициализация данных UART
void uart_handling_init(void)
{
  fifo_init_struct(
    (fifo_struct_t*)&uart_rx_fifo, 
    (uint8_t*)uart_rx_fifo_buf, sizeof(uart_rx_fifo_buf));
  uart_handling_periph_init();
}

// Initialize UART hardware
void uart_handling_periph_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  gpio_common_init_clk(UART_TX_GPIO);
  gpio_common_init_clk(UART_RX_GPIO);
  
  UART_RCC_FUNCTION(UART_RCC, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(UART_TX_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = UART_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(UART_RX_GPIO, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = UART_SPEED;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;   
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
  
  USART_Init(UART_NAME, &USART_InitStructure);
  USART_Cmd(UART_NAME, ENABLE);
  
  gpio_common_init_clk(UART_SET_GPIO);
  GPIO_InitStructure.GPIO_Pin = UART_SET_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(UART_SET_GPIO, &GPIO_InitStructure);
  GPIO_SetBits(UART_SET_GPIO, UART_SET_PIN);//uart bridge mode

  USART_ITConfig(UART_NAME, USART_IT_RXNE, ENABLE);
  
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = UART_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_RX_IRQ_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void uart_handling_periph_deinit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_Cmd(UART_NAME, DISABLE);
  USART_DeInit(UART_NAME);
  UART_RCC_FUNCTION(UART_RCC, DISABLE);
  
  GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(UART_TX_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = UART_SET_PIN;
  GPIO_Init(UART_SET_GPIO, &GPIO_InitStructure);
  
}

//Blocking!
void uart_handling_send_data(uint8_t* data, uint16_t size)
{
  uint16_t i;
  
  for (i = 0; i < size; i++)
  {
    while (USART_GetFlagStatus(UART_NAME, USART_FLAG_TXE) == RESET){}
      USART_SendData(UART_NAME, data[i]);
  }
}