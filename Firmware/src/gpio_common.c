
/* Includes ------------------------------------------------------------------*/
#include "gpio_common.h"
#include "stm32f10x_gpio.h"


/* Private typedef -----------------------------------------------------------*/
#define GPIO_BASE_STEP                     0x0400

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

void gpio_common_init_clk(GPIO_TypeDef* gpio)
{
  if (gpio == 0)
    return;

  switch ((uint32_t)gpio)
  {
    case (uint32_t)GPIOA:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      break;
    case (uint32_t)GPIOB:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      break;
    case (uint32_t)GPIOC:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
      break;
    case (uint32_t)GPIOD:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      break;
    case (uint32_t)GPIOE:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
      break;
    case (uint32_t)GPIOF:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
      break;
  }
}

//Take pin number like GPIO_Pin_3
//return GPIO_PinSource like GPIO_PinSource3/EXTI_PinSource3 == 3
uint8_t gpio_common_get_pin_source(uint32_t pin)
{
  for (uint8_t i = 0; i < 16; i++)
  {
    if (pin & (1 << i))
    {
      //we get index
      return i;
    }
  }
  return 0;
}

uint8_t gpio_common_calc_exti_source(GPIO_TypeDef *gpio)
{
  uint8_t exti_port_source;
  exti_port_source = (uint8_t)(((uint32_t)gpio & 0xFFFF) / GPIO_BASE_STEP);
  return exti_port_source;
}

  /*
//Take pin number like GPIO_Pin_3
void gpio_common_enable_exti_irq(GPIO_TypeDef *gpio, uint32_t pin, EXTITrigger_TypeDef trigger)
{
  EXTI_InitTypeDef exti_init_struct;
  NVIC_InitTypeDef nvic_init_struct;
    
  uint8_t exti_port_src = gpio_common_calc_exti_source(gpio);
  uint8_t exti_pin_src = gpio_common_get_pin_source(pin);
  SYSCFG_EXTILineConfig(exti_port_src, exti_pin_src);
  
  exti_init_struct.EXTI_Line = pin;
  exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
  exti_init_struct.EXTI_Trigger = trigger;
  exti_init_struct.EXTI_LineCmd = ENABLE;
  
  EXTI_Init(&exti_init_struct);
  
  //EXTI_Line3 == GPIO_Pin_3
  EXTI_ClearITPendingBit((uint32_t)pin);
  
  nvic_init_struct.NVIC_IRQChannel = gpio_common_get_exti_irq_channel(pin);
  nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x00;
  nvic_init_struct.NVIC_IRQChannelSubPriority = 0x00;
  nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_init_struct);  

}
*/

void gpio_common_disable_exti_irq(uint32_t pin)
{
  /*
  EXTI_ClearITPendingBit((uint32_t)pin);
  
  NVIC_InitTypeDef nvic_init_struct;
  nvic_init_struct.NVIC_IRQChannel = gpio_common_get_exti_irq_channel(pin);
  nvic_init_struct.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&nvic_init_struct);
  */
}

//Take pin number like GPIO_Pin_3
uint8_t gpio_common_get_exti_irq_channel(uint32_t pin)
{
    uint8_t pin_nbr = gpio_common_get_pin_source(pin);
    
    switch (pin_nbr)
    {
    case 0:
      return EXTI0_IRQn;
    case 1:
      return EXTI1_IRQn;
    case 2:
      return EXTI2_IRQn;
    case 3:
      return EXTI3_IRQn;
    case 4:
      return EXTI4_IRQn;
      
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return EXTI9_5_IRQn;
      
    default:
      return EXTI15_10_IRQn;
    }
}

