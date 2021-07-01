//ILIASAM - 10.2018

#include "mavlink_handling.h"
#include "mavlink.h"
#include "draw_monitor.h"

#include "uart_handling.h"

// Defines ********************************************************************
#define MAVLINK_ACK_VALUE               1
#define MAVLINK_DRIVE_ID                10 //system id

#define MAVLINK_DRIVE_COMP_CURTAINS_ID  1  //Component

// Variables ******************************************************************

mavlink_message_t tmp_tx_mav_msg;

mavlink_status_t mavlink_status; //contains state machine
mavlink_message_t mavlink_msg;

uint8_t temperatures_recieved_flag = 0;

extern displayed_params_t displayed_params;


// Functions ******************************************************************
void mavlink_parse_curtains_cmd(mavlink_message_t* msg);
void mavlink_send_ack_msg(mavlink_mav_command_ack_t *command_ack);
void mavlink_send_message(mavlink_message_t *msg);
void mavlink_parse_lamp_cmd(mavlink_message_t* msg);
void mavlink_parse_data_request(mavlink_message_t* msg);
void mavlink_send_drive_state(void);
void mavlink_send_temperatures(void);

void mavlink_parse_temperatures(mavlink_message_t* msg);


void mavlink_parse_byte(uint8_t value)
{
  if (mavlink_parse_char(0, value, &mavlink_msg, &mavlink_status))
  {
    if (mavlink_msg.msgid == MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES)
    {
      mavlink_parse_temperatures(&mavlink_msg);
      temperatures_recieved_flag = 1;
    }
  }
}

void mavlink_parse_temperatures(mavlink_message_t* msg)
{
  mavlink_mav_temperature_values_t tmp_msg;
  mavlink_msg_mav_temperature_values_decode(msg, &tmp_msg);
  
  displayed_params.ext_temperature_deg = (int16_t)tmp_msg.temp2;
  displayed_params.temperature1_deg = (int16_t)tmp_msg.temp3;
}


uint8_t mavlink_is_data_received(void)
{
  if (temperatures_recieved_flag)
    return 1;
  else
    return 0;
}

//Send request to drive: drive should send temperatures
void mavlink_request_temperatures(void)
{
  mavlink_mav_data_request_t mav_request;
  mav_request.data_type = TEMPERATURE;
  mav_request.tar_system_id = MAVLINK_DRIVE_ID;
  mav_request.tar_component_id = MAVLINK_DRIVE_COMP_CURTAINS_ID;

  mavlink_msg_mav_data_request_encode(
            1, //system id
            MAVLINK_DRIVE_COMP_CURTAINS_ID, //component id
            &tmp_tx_mav_msg,
            &mav_request);

    mavlink_send_message(&tmp_tx_mav_msg);
}

//Test command
void mavlink_request_beep(void)
{
  mavlink_mav_curtains_cmd_t mav_cmd;
  mav_cmd.command = MAV_BEEP;

  mavlink_msg_mav_curtains_cmd_encode(
            1, //system id
            MAVLINK_DRIVE_COMP_CURTAINS_ID, //component id
            &tmp_tx_mav_msg,
            &mav_cmd);

    mavlink_send_message(&tmp_tx_mav_msg);
}


// Отправляем пакет с данными о температурах
void mavlink_send_temperatures(void)
{
  /*
  mavlink_mav_temperature_values_t tmp_msg;
  
  tmp_msg.temp1 = (float)(int16_t)temp_data[0] / 16.0f;
  tmp_msg.temp2 = (float)(int16_t)temp_data[1] / 16.0f;
  tmp_msg.temp3 = (float)(int16_t)temp_data[2] / 16.0f;
  
  
  mavlink_msg_mav_temperature_values_encode(
            MAVLINK_DRIVE_ID,
            MAVLINK_DRIVE_COMP_CURTAINS_ID,
            &tmp_tx_mav_msg,
            &tmp_msg);
  
  mavlink_send_message(&tmp_tx_mav_msg);
  */
}



// Отправить подтверждение принятой команды
void mavlink_send_ack(uint8_t msg_id)
{
  mavlink_mav_command_ack_t cmd_ack;
  cmd_ack.cmd_id = msg_id;
  cmd_ack.result = MAVLINK_ACK_VALUE;
  mavlink_send_ack_msg(&cmd_ack);
}

// Подготавивает и отправляет сообщение подтверждения
void mavlink_send_ack_msg(mavlink_mav_command_ack_t *command_ack)
{
    mavlink_msg_mav_command_ack_encode(
            MAVLINK_DRIVE_ID,
            MAVLINK_DRIVE_COMP_CURTAINS_ID,
            &tmp_tx_mav_msg,
            command_ack);

    mavlink_send_message(&tmp_tx_mav_msg);
}

// Отправить mavlink сообщение
void mavlink_send_message(mavlink_message_t *msg)
{
    if (msg == NULL)
        return;
            
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t size = mavlink_msg_to_send_buffer(buffer, msg);
    if (size > MAVLINK_MAX_PACKET_LEN)
        return;
    
    uart_handling_send_data(buffer, size);
}