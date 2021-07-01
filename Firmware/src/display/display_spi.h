#ifndef __DISPLAY_SPI_H
#define __DISPLAY_SPI_H

#include <stdint.h>
#include "stm32f10x.h"
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void dispaly_spi_init(void);
void dispaly_spi_deinit(void);
void display_spi_write_data(unsigned char data);
void display_spi_write_cmd(unsigned char command);
void display_spi_write_data_n(uint8_t* data, uint16_t len);
uint8_t display_spi_is_busy(void);

#endif //__DISPLAY_SPI_H
