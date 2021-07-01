/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"



#define MCU_VREF                        3.27f //volts

// Baterry ADC *************************************************************

//Battery low
#define BATTER_LOW_THRESHOLD_V          (3.7f)

#define BATERRY_ADC_NAME                ADC1
#define BATERRY_ADC_RCC                 RCC_APB2Periph_ADC1

#define BATERRY_ADC_CHANNEL             ADC_Channel_6

#define BATERRY_ADC_GPIO                GPIOA 
#define BATERRY_ADC_PIN                 GPIO_Pin_6

#define BATERRY_GND_GPIO                GPIOB
#define BATERRY_GND_PIN                 GPIO_Pin_4

#define BATERRY_CHARGE_GPIO             GPIOB
#define BATERRY_CHARGE_PIN              GPIO_Pin_6

// UART *************************************************************

#define UART_NAME                       USART2
#define UART_SPEED                      9600
#define UART_RCC                        RCC_APB1Periph_USART2
#define UART_RCC_FUNCTION               RCC_APB1PeriphClockCmd

#define UART_TX_GPIO                    GPIOA 
#define UART_TX_PIN                     GPIO_Pin_2

#define UART_RX_GPIO                    GPIOA 
#define UART_RX_PIN                     GPIO_Pin_3

// HC12 pin - active low
#define UART_SET_GPIO                   GPIOA
#define UART_SET_PIN                    GPIO_Pin_4

#define UART_IRQ                        USART2_IRQn
#define UART_IRQ_HANDLER                USART2_IRQHandler


// POWER SWITCH *************************************************************

// Low is ON
#define POWER_SW_GPIO                   GPIOC
#define POWER_SW_PIN                    GPIO_Pin_15

// E-INK DISPLAY *************************************************************

#define DISPLAY_SPI_SCK_GPIO            GPIOB
#define DISPLAY_SPI_SCK_PIN             GPIO_Pin_13

#define DISPLAY_SPI_MOSI_GPIO           GPIOB
#define DISPLAY_SPI_MOSI_PIN            GPIO_Pin_15

#define DISPLAY_SPI_DC_GPIO             GPIOB
#define DISPLAY_SPI_DC_PIN              GPIO_Pin_12

#define DISPLAY_SPI_CS_GPIO             GPIOA
#define DISPLAY_SPI_CS_PIN              GPIO_Pin_8

#define DISPLAY_BUSY_GPIO               GPIOA
#define DISPLAY_BUSY_PIN                GPIO_Pin_10


// INTERRUPTS *********************************************************

#define ENCODER_CAPTURE_IRQ_PRIORITY    (1)
#define ENCODER_UPDATE_IRQ_PRIORITY     (2)

#define STEPPER_IRQ_PRIORITY            (5)
#define UART_RX_IRQ_PRIORITY            (6)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __CONFIG_H */
