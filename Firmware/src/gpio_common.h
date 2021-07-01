/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_COMMON_H
#define __GPIO_COMMON_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "stm32f10x_gpio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void gpio_common_init_clk(GPIO_TypeDef* gpio);
uint8_t gpio_common_get_pin_source(uint32_t pin);
uint8_t gpio_common_calc_exti_source(GPIO_TypeDef *gpio);
uint8_t gpio_common_get_exti_irq_channel(uint32_t pin);
//void gpio_common_enable_exti_irq(GPIO_TypeDef *gpio, uint32_t pin, EXTITrigger_TypeDef trigger);
void gpio_common_disable_exti_irq(uint32_t pin);

#endif /* __GPIO_COMMON_H */

