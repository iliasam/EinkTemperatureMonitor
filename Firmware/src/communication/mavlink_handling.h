#ifndef MAVLINK_HANDLING_H
#define MAVLINK_HANDLING_H

#include <stdint.h>

// Defines ********************************************************************

// Functions ******************************************************************
void mavlink_parse_byte(uint8_t value);
void mavlink_send_ack(uint8_t msg_id);

void mavlink_request_temperatures(void);
void mavlink_request_beep(void);
uint8_t mavlink_is_data_received(void);

#endif
