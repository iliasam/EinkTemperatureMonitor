#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "stm32f10x_bkp.h"

#define MAX_UPDATE_COUNTER              5
#define BACKUP_STATUS_REG               BKP_DR1  //Backup status
#define BACKUP_UPDATE_CNT_REG           BKP_DR2 //Monitor update counter

void init_all_hardware(void);
void init_gpio(void);
void init_sys_clock(void);

void init_adc_single_measure(void);

float measure_battery_voltage(void);
void rtc_init(void);
void go_to_sleep_mode(uint32_t delay_ms);
void delay_ms(uint32_t ms);
void hardware_enable_power(void);
void hardware_disable_power(void);
void go_to_standby_mode(uint32_t delay_ms);
void hardware_update_backup(void);

uint16_t hardware_rtc_read_16_bit_backup_value(uint16_t register_number);

#endif
