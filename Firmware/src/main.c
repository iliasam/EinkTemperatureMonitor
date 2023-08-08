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
#define DATA_REQUESTS_MAX_NUMBER        (10)

#define MONITOR_UPDATE_PERIOD_MS        (8 * 60 * 1000)

/* Private variables ---------------------------------------------------------*/
data_request_state_t data_request_state = DATA_REQUEST_IDLE;
uint32_t data_request_send_time = 0;
uint8_t data_request_counter = 0;
uint8_t monitor_updated = 0;
uint8_t force_disp_update = 0;

/* Private function prototypes -----------------------------------------------*/
void main_send_data_request(void);
void main_data_request_handling(void);
void main_monitor_handling(void);
uint8_t check_disp_need_update(void);


/* Private functions ---------------------------------------------------------*/
int main()
{
  init_all_hardware();
  if (GPIO_ReadInputDataBit(BUTTON_GPIO, BUTTON_PIN) != 0)//pressed
  {
    force_disp_update = 1;
  }
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
  

  
  displayed_params.ext_temperature_deg = 60;
  displayed_params.temperature1_deg = 60;
  
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
    uint8_t need_update_disp = check_disp_need_update();
    if (need_update_disp || force_disp_update)
    {
      draw_monitor();
    }
    hardware_update_backup(&displayed_params);//Save data to RAM
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
    
    uint32_t delay_ms = DATA_REQUEST_TIMEOUT_MS;
    if (data_request_counter >= (DATA_REQUESTS_MAX_NUMBER / 2))
      delay_ms = delay_ms * 2;//increase delay
    
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
 // mavlink_request_beep();
  SET_TIMESTAMP(data_request_send_time);
  data_request_counter++;
  data_request_state = DATA_REQUEST_WAIT_RX;
}

/// Compare new received values  with old values
/// Return 1 if need update
uint8_t check_disp_need_update(void)
{
  uint16_t old_state = 
    hardware_rtc_read_16_bit_backup_value(BACKUP_RADIO_STATE_REG);
  uint16_t new_state = (displayed_params.no_connection_flag) ? 0 : 1;
  if (old_state != new_state)
    return 1;
  
  int16_t temp_int = 
    (int16_t)hardware_rtc_read_16_bit_backup_value(BACKUP_INT_TEMPERATURE_REG);
  int16_t temp_ext = 
    (int16_t)hardware_rtc_read_16_bit_backup_value(BACKUP_EXT_TEMPERATURE_REG);
  
  if (temp_int != displayed_params.temperature1_deg)
    return 1;
  if (temp_ext != displayed_params.ext_temperature_deg)
    return 1;
  
  return 0;
}

int putchar(int c)
{
  return c;    
}



