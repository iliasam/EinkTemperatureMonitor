#ifndef __DRAW_MONITOR_H
#define __DRAW_MONITOR_H

typedef struct
{
  int16_t ext_temperature_deg;
  
  int16_t temperature1_deg;
  int16_t temperature2_deg;
  
  float battery_voltage;
  
  uint8_t update_counter;
  
  uint8_t is_charging_flag;
  uint8_t no_connection_flag;
  uint8_t low_batt_flag;
  
} displayed_params_t;

extern displayed_params_t displayed_params;

void draw_monitor(void);


#endif //__DRAW_MONITOR_H

