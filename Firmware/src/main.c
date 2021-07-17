//STM32F103C8T6. 64 MHz

#include "config.h"
#include "stm32f10x.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "display_spi.h"
#include "uart_handling.h"

#include "draw_monitor.h"
#include "mavlink_handling.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  DATA_REQUEST_IDLE = 0,
  DATA_REQUEST_WAIT_RX,
  DATA_REQUEST_DONE,
  DATA_REQUEST_FULL_FAIL,
  
} data_request_state_t;

#define DATA_REQUEST_TIMEOUT_MS         (2000)
#define DATA_REQUESTS_MAX_NUMBER        (5)

#define MONITOR_UPDATE_PERIOD_MS        (8 * 60 * 1000)

/* Private variables ---------------------------------------------------------*/
data_request_state_t data_request_state = DATA_REQUEST_IDLE;
uint32_t data_request_send_time = 0;
uint8_t data_request_counter = 0;
uint8_t monitor_updated = 0;

/* Private function prototypes -----------------------------------------------*/
void main_send_data_request(void);
void main_data_request_handling(void);
void main_monitor_handling(void);


/* Private functions ---------------------------------------------------------*/
int main()
{
  init_all_hardware();
  delay_ms(1000);//for connection by debugger
  uart_handling_init();
  delay_ms(50);
  hardware_enable_power();
  go_to_sleep_mode(1000);
  init_adc_single_measure();
  delay_ms(8);
  dispaly_spi_init();
  displayed_params.battery_voltage = measure_battery_voltage();
  hardware_deinit_adc();
  
  displayed_params.update_counter = 
    hardware_rtc_read_16_bit_backup_value(BACKUP_UPDATE_CNT_REG);
  
  if (displayed_params.battery_voltage < BATTER_LOW_THRESHOLD_V)
  {
    displayed_params.low_batt_flag = 1;
  }
  
  //0 - charging
  if (GPIO_ReadInputDataBit(BATERRY_CHARGE_GPIO, BATERRY_CHARGE_PIN) == 0)
  {
    displayed_params.is_charging_flag = 1;
  }
  
  displayed_params.ext_temperature_deg = 44;
  displayed_params.temperature1_deg = 44;
  

  while(1)
  {
    uart_handling_rx_data();
    main_data_request_handling();
    main_monitor_handling();
  }
}

void main_monitor_handling(void)
{
  if (monitor_updated)
    return;
  
  if ((data_request_state == DATA_REQUEST_DONE) || 
      (data_request_state == DATA_REQUEST_FULL_FAIL))
  {
    if (data_request_state == DATA_REQUEST_FULL_FAIL)
      displayed_params.no_connection_flag = 1;
    
    monitor_updated = 1;
    uart_handling_periph_deinit();
    draw_monitor();
    hardware_update_backup();
    dispaly_spi_deinit();
    hardware_disable_power();//All proccess are completed
    
    //go_to_sleep_mode(10000);//test, gebugger working
   // NVIC_SystemReset();//test, gebugger working
    go_to_standby_mode(MONITOR_UPDATE_PERIOD_MS);
    //MCU will be resetted after wakeup
  }
}

void main_data_request_handling(void)
{
  if (data_request_state == DATA_REQUEST_IDLE)
  {
    main_send_data_request();
  }
  else if (data_request_state == DATA_REQUEST_WAIT_RX)
  {
    if (mavlink_is_data_received())
    {
      data_request_state = DATA_REQUEST_DONE;
      return;
    }
    
    if (CHECK_TIMER(data_request_send_time, DATA_REQUEST_TIMEOUT_MS))
    {
      //timeout
      if (data_request_counter < DATA_REQUESTS_MAX_NUMBER)
        main_send_data_request();
      else
        data_request_state = DATA_REQUEST_FULL_FAIL;
    }
  }
}

void main_send_data_request(void)
{
  mavlink_request_temperatures();
  //mavlink_request_beep();
  SET_TIMESTAMP(data_request_send_time);
  data_request_counter++;
  data_request_state = DATA_REQUEST_WAIT_RX;
}


int putchar(int c)
{
  return c;    
}



