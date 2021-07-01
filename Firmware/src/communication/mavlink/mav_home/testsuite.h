/** @file
 *    @brief MAVLink comm protocol testsuite generated from mav_home.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef MAV_HOME_TESTSUITE_H
#define MAV_HOME_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_mav_home(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_mav_home(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_mav_command_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_COMMAND_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_command_ack_t packet_in = {
        963497464,17
    };
    mavlink_mav_command_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.result = packet_in.result;
        packet1.cmd_id = packet_in.cmd_id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_command_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_command_ack_pack(system_id, component_id, &msg , packet1.cmd_id , packet1.result );
    mavlink_msg_mav_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_command_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.cmd_id , packet1.result );
    mavlink_msg_mav_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_command_ack_send(MAVLINK_COMM_1 , packet1.cmd_id , packet1.result );
    mavlink_msg_mav_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_data_request(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_DATA_REQUEST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_data_request_t packet_in = {
        5,72,139
    };
    mavlink_mav_data_request_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tar_system_id = packet_in.tar_system_id;
        packet1.tar_component_id = packet_in.tar_component_id;
        packet1.data_type = packet_in.data_type;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_data_request_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_data_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_data_request_pack(system_id, component_id, &msg , packet1.tar_system_id , packet1.tar_component_id , packet1.data_type );
    mavlink_msg_mav_data_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_data_request_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tar_system_id , packet1.tar_component_id , packet1.data_type );
    mavlink_msg_mav_data_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_data_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_data_request_send(MAVLINK_COMM_1 , packet1.tar_system_id , packet1.tar_component_id , packet1.data_type );
    mavlink_msg_mav_data_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_curtains_drive_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_curtains_drive_state_t packet_in = {
        5,72,139,206
    };
    mavlink_mav_curtains_drive_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.drive_state = packet_in.drive_state;
        packet1.lamp_state = packet_in.lamp_state;
        packet1.errors = packet_in.errors;
        packet1.brightness = packet_in.brightness;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_drive_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_curtains_drive_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_drive_state_pack(system_id, component_id, &msg , packet1.drive_state , packet1.lamp_state , packet1.errors , packet1.brightness );
    mavlink_msg_mav_curtains_drive_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_drive_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.drive_state , packet1.lamp_state , packet1.errors , packet1.brightness );
    mavlink_msg_mav_curtains_drive_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_curtains_drive_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_drive_state_send(MAVLINK_COMM_1 , packet1.drive_state , packet1.lamp_state , packet1.errors , packet1.brightness );
    mavlink_msg_mav_curtains_drive_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_curtains_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_CURTAINS_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_curtains_cmd_t packet_in = {
        5
    };
    mavlink_mav_curtains_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.command = packet_in.command;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_CURTAINS_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_CURTAINS_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_curtains_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_cmd_pack(system_id, component_id, &msg , packet1.command );
    mavlink_msg_mav_curtains_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.command );
    mavlink_msg_mav_curtains_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_curtains_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_curtains_cmd_send(MAVLINK_COMM_1 , packet1.command );
    mavlink_msg_mav_curtains_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_switch_lamp(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_SWITCH_LAMP >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_switch_lamp_t packet_in = {
        5,72
    };
    mavlink_mav_switch_lamp_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tar_system_id = packet_in.tar_system_id;
        packet1.command = packet_in.command;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_switch_lamp_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_switch_lamp_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_switch_lamp_pack(system_id, component_id, &msg , packet1.tar_system_id , packet1.command );
    mavlink_msg_mav_switch_lamp_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_switch_lamp_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tar_system_id , packet1.command );
    mavlink_msg_mav_switch_lamp_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_switch_lamp_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_switch_lamp_send(MAVLINK_COMM_1 , packet1.tar_system_id , packet1.command );
    mavlink_msg_mav_switch_lamp_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_temperature_values(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mav_temperature_values_t packet_in = {
        17.0,45.0,73.0
    };
    mavlink_mav_temperature_values_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.temp1 = packet_in.temp1;
        packet1.temp2 = packet_in.temp2;
        packet1.temp3 = packet_in.temp3;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_temperature_values_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mav_temperature_values_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_temperature_values_pack(system_id, component_id, &msg , packet1.temp1 , packet1.temp2 , packet1.temp3 );
    mavlink_msg_mav_temperature_values_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_temperature_values_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.temp1 , packet1.temp2 , packet1.temp3 );
    mavlink_msg_mav_temperature_values_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mav_temperature_values_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mav_temperature_values_send(MAVLINK_COMM_1 , packet1.temp1 , packet1.temp2 , packet1.temp3 );
    mavlink_msg_mav_temperature_values_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mav_home(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_mav_command_ack(system_id, component_id, last_msg);
    mavlink_test_mav_data_request(system_id, component_id, last_msg);
    mavlink_test_mav_curtains_drive_state(system_id, component_id, last_msg);
    mavlink_test_mav_curtains_cmd(system_id, component_id, last_msg);
    mavlink_test_mav_switch_lamp(system_id, component_id, last_msg);
    mavlink_test_mav_temperature_values(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAV_HOME_TESTSUITE_H
