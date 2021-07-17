#include "stm32f10x.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "config.h"

#include "hardware.h"
#include "gpio_common.h"

#include "delay_us_timer.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_dbgmcu.h"
#include "stm32f10x_it.h"
#include "stm32f10x_bkp.h"
#include "misc.h"

/* Private typedef -----------------------------------------------------------*/
#define RTC_STATUS_INIT_DONE            0x1234       /* RTC initialised value*/

/* Private function prototypes -----------------------------------------------*/
void hardware_init_exti(FunctionalState state);
void hardware_restart_systick(void);


/* Private functions ---------------------------------------------------------*/
void init_all_hardware(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  RCC_ClocksTypeDef RCC_Clocks;
  
  init_sys_clock();
  rtc_init();
  RCC_GetClocksFreq (&RCC_Clocks);
  if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000))
  { 
    while (1);//error
  }
  
  dwt_init();
  init_gpio();
  
  DBGMCU_Config(DBGMCU_STOP | DBGMCU_SLEEP, ENABLE);
}

void init_gpio(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
   
  gpio_common_init_clk(GPIOA);
  gpio_common_init_clk(GPIOB);
  gpio_common_init_clk(GPIOC);
  
  //Disable JTAG
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  
  hardware_disable_power();
  GPIO_InitStructure.GPIO_Pin   = POWER_SW_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(POWER_SW_GPIO, &GPIO_InitStructure);
  hardware_disable_power();
  
  GPIO_InitStructure.GPIO_Pin   = BATERRY_ADC_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_Init(BATERRY_ADC_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = BATERRY_GND_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_Init(BATERRY_GND_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin   = BATERRY_CHARGE_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
  GPIO_Init(BATERRY_CHARGE_GPIO, &GPIO_InitStructure);
}


void init_sys_clock(void)
{ 
  RCC_DeInit(); /* RCC system reset(for debug purpose) */

  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);/* Enable Prefetch Buffer */
  FLASH_SetLatency(FLASH_Latency_2);/* Flash 2 wait state */
  
  //Configure for LSI + PLL
  RCC_HCLKConfig(RCC_SYSCLK_Div1);/* HCLK = SYSCLK */
  RCC_PCLK2Config(RCC_HCLK_Div1);/* PCLK2 = HCLK */
  RCC_PCLK1Config(RCC_HCLK_Div2);
  //RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/* PLLCLK = 8MHz/2 * 16 = 64 MHz <<<<<<<<<<<<<<<<<<<<<<<<<<*/
  RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_4);/* PLLCLK = 8MHz/2 * 4 = 16 MHz <<<<<<<<<<<<<<<<<<<<<<<<<<*/
  RCC_PLLCmd(ENABLE);/* Enable PLL */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){};/* Wait till PLL is ready */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);/* Select PLL as system clock source */
  while (RCC_GetSYSCLKSource() != 0x08){}/* Wait till PLL is used as system clock source */
}


//Init ADC for single software triggered measure
void init_adc_single_measure(void)
{
  ADC_InitTypeDef  ADC_InitStructure;
  
  RCC_ADCCLKConfig(RCC_PCLK2_Div2);//12 mhz
  RCC_APB2PeriphClockCmd(BATERRY_ADC_RCC | RCC_APB2Periph_AFIO,ENABLE);
  
  ADC_DeInit(BATERRY_ADC_NAME);
  ADC_StructInit(&ADC_InitStructure);

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(BATERRY_ADC_NAME, &ADC_InitStructure);

  ADC_DMACmd(BATERRY_ADC_NAME, DISABLE);  
  ADC_Cmd(BATERRY_ADC_NAME, ENABLE);
  
  ADC_ResetCalibration(BATERRY_ADC_NAME);
  while(ADC_GetResetCalibrationStatus(BATERRY_ADC_NAME)){}; 
  ADC_StartCalibration(BATERRY_ADC_NAME);   
  while(ADC_GetCalibrationStatus(BATERRY_ADC_NAME)){};
}

void hardware_deinit_adc(void)
{
  ADC_Cmd(BATERRY_ADC_NAME, DISABLE);
  ADC_DeInit(BATERRY_ADC_NAME);
}


uint16_t readADC1(uint8_t channel)
{
  ADC_RegularChannelConfig(BATERRY_ADC_NAME, channel, 1, ADC_SampleTime_41Cycles5);
  ADC_SoftwareStartConvCmd(BATERRY_ADC_NAME, ENABLE);
  while(ADC_GetFlagStatus(BATERRY_ADC_NAME, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(BATERRY_ADC_NAME);
}


float measure_battery_voltage(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin   = BATERRY_GND_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(BATERRY_GND_GPIO, &GPIO_InitStructure);
  GPIO_ResetBits(BATERRY_GND_GPIO, BATERRY_GND_PIN);//pull  low
  
  //Dummy measurements
  readADC1(BATERRY_ADC_CHANNEL);
  readADC1(BATERRY_ADC_CHANNEL);
  readADC1(BATERRY_ADC_CHANNEL);
  
  float result = (float)readADC1(BATERRY_ADC_CHANNEL) / 620.0f;
  
  GPIO_InitStructure.GPIO_Pin   = BATERRY_GND_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_Init(BATERRY_GND_GPIO, &GPIO_InitStructure);//make floating
  
  return result;
}

//RTC is used to wakeup
void rtc_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  PWR_BackupAccessCmd(ENABLE);
  
  RCC_LSICmd(ENABLE);
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  RCC_RTCCLKCmd(ENABLE); 
  
  uint16_t rtc_state = hardware_rtc_read_16_bit_backup_value(BACKUP_STATUS_REG);
  if (rtc_state != RTC_STATUS_INIT_DONE)
  {
    BKP_WriteBackupRegister(BACKUP_STATUS_REG, RTC_STATUS_INIT_DONE);
  }
  
  RTC_WaitForSynchro();
  RTC_WaitForLastTask();
  RTC_SetPrescaler(400-1);//40khz / 400 = 100 hz -> 10 ms
  RTC_WaitForLastTask();
  
  RTC_ITConfig(RTC_IT_ALR, DISABLE);
  RTC_WaitForLastTask();
  
  RTC_ClearFlag(RTC_FLAG_ALR);
  while(RTC_GetFlagStatus(RTC_FLAG_SEC) == RESET);
}

//Update value of the counter in backup
void hardware_update_backup(void)
{
  uint16_t update_counter = 
    hardware_rtc_read_16_bit_backup_value(BACKUP_UPDATE_CNT_REG);
  update_counter++;
  if (update_counter >= MAX_UPDATE_COUNTER)
    update_counter = 0;
  BKP_WriteBackupRegister(BACKUP_UPDATE_CNT_REG, update_counter);
}



//Go to sleep mode
//Go to stanby - RAM is enabled, 2mA
void go_to_sleep_mode(uint32_t delay_ms)
{
  RTC_SetAlarm(RTC_GetCounter() + (delay_ms / 10));
  RTC_WaitForLastTask();
  
  RTC_ClearFlag(RTC_IT_ALR);
  RTC_ITConfig(RTC_IT_ALR, ENABLE);
  
  hardware_init_exti(ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  SysTick->CTRL = 0;// disable Systick
  uint32_t irq_state;
  ENTER_CRITICAL(irq_state);//Disable interrupts
  RTC_ClearFlag(RTC_IT_ALR);
  EXTI_ClearFlag(EXTI_Line17);//EXTI_Line17 - RTC alarm

  //STOP - HSI and HSE oscillators OFF
  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
  //here program is running again
  
  LEAVE_CRITICAL(irq_state);//Enable interrupts
  hardware_restart_systick();
  hardware_init_exti(DISABLE);
  init_sys_clock();
}

//Go to stanby - RAM is disabled, 5uA
void go_to_standby_mode(uint32_t delay_ms)
{
  RTC_SetAlarm(RTC_GetCounter() + (delay_ms / 10));
  RTC_WaitForLastTask();
  
  RTC_ClearFlag(RTC_IT_ALR);
  RTC_ITConfig(RTC_IT_ALR, ENABLE);
  
  hardware_init_exti(ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  PWR_WakeUpPinCmd(ENABLE);
  
  SysTick->CTRL = 0;// disable Systick
  uint32_t irq_state;
  ENTER_CRITICAL(irq_state);//Disable interrupts
  RTC_ClearFlag(RTC_IT_ALR);
  EXTI_ClearFlag(EXTI_Line17);//EXTI_Line17 - RTC alarm

  //All off
  PWR_EnterSTANDBYMode();
  //MCU will be resetted after wakeup
}

//Called after MCU wakeup
void hardware_restart_systick(void)
{
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;   
}

void hardware_init_exti(FunctionalState state)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = state;
  EXTI_Init(&EXTI_InitStructure);
}

void delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}

void hardware_enable_power(void)
{
  GPIO_ResetBits(POWER_SW_GPIO, POWER_SW_PIN);
}

void hardware_disable_power(void)
{
  GPIO_SetBits(POWER_SW_GPIO, POWER_SW_PIN);
}

// Read uint16_t value from backup data
uint16_t hardware_rtc_read_16_bit_backup_value(uint16_t register_number)
{
  return BKP_ReadBackupRegister(register_number);
}


