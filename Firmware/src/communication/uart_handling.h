#ifndef UART_HANDLING_H
#define UART_HANDLING_H

#include <stdint.h>

// Defines ********************************************************************

// Functions ******************************************************************
void uart_handling_periph_init(void);
void uart_handling_init(void);
void uart_handling_rx_data(void);
void uart_handling_send_data(uint8_t* data, uint16_t size);
void uart_handling_periph_deinit(void);

#endif
