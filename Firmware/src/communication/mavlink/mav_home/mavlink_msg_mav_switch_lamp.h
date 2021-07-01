#pragma once
// MESSAGE MAV_SWITCH_LAMP PACKING

#define MAVLINK_MSG_ID_MAV_SWITCH_LAMP 102

MAVPACKED(
typedef struct __mavlink_mav_switch_lamp_t {
 uint8_t tar_system_id; /*< Target system ID*/
 uint8_t command; /*< Command for lamp*/
}) mavlink_mav_switch_lamp_t;

#define MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN 2
#define MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN 2
#define MAVLINK_MSG_ID_102_LEN 2
#define MAVLINK_MSG_ID_102_MIN_LEN 2

#define MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC 107
#define MAVLINK_MSG_ID_102_CRC 107



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_SWITCH_LAMP { \
    102, \
    "MAV_SWITCH_LAMP", \
    2, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_switch_lamp_t, tar_system_id) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_switch_lamp_t, command) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_SWITCH_LAMP { \
    "MAV_SWITCH_LAMP", \
    2, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_switch_lamp_t, tar_system_id) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_switch_lamp_t, command) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_switch_lamp message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tar_system_id Target system ID
 * @param command Command for lamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_switch_lamp_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t tar_system_id, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN);
#else
    mavlink_mav_switch_lamp_t packet;
    packet.tar_system_id = tar_system_id;
    packet.command = command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SWITCH_LAMP;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
}

/**
 * @brief Pack a mav_switch_lamp message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tar_system_id Target system ID
 * @param command Command for lamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_switch_lamp_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t tar_system_id,uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN);
#else
    mavlink_mav_switch_lamp_t packet;
    packet.tar_system_id = tar_system_id;
    packet.command = command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_SWITCH_LAMP;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
}

/**
 * @brief Encode a mav_switch_lamp struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_switch_lamp C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_switch_lamp_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_switch_lamp_t* mav_switch_lamp)
{
    return mavlink_msg_mav_switch_lamp_pack(system_id, component_id, msg, mav_switch_lamp->tar_system_id, mav_switch_lamp->command);
}

/**
 * @brief Encode a mav_switch_lamp struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_switch_lamp C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_switch_lamp_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_switch_lamp_t* mav_switch_lamp)
{
    return mavlink_msg_mav_switch_lamp_pack_chan(system_id, component_id, chan, msg, mav_switch_lamp->tar_system_id, mav_switch_lamp->command);
}

/**
 * @brief Send a mav_switch_lamp message
 * @param chan MAVLink channel to send the message
 *
 * @param tar_system_id Target system ID
 * @param command Command for lamp
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_switch_lamp_send(mavlink_channel_t chan, uint8_t tar_system_id, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP, buf, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
#else
    mavlink_mav_switch_lamp_t packet;
    packet.tar_system_id = tar_system_id;
    packet.command = command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP, (const char *)&packet, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
#endif
}

/**
 * @brief Send a mav_switch_lamp message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_switch_lamp_send_struct(mavlink_channel_t chan, const mavlink_mav_switch_lamp_t* mav_switch_lamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_switch_lamp_send(chan, mav_switch_lamp->tar_system_id, mav_switch_lamp->command);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP, (const char *)mav_switch_lamp, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_switch_lamp_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t tar_system_id, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP, buf, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
#else
    mavlink_mav_switch_lamp_t *packet = (mavlink_mav_switch_lamp_t *)msgbuf;
    packet->tar_system_id = tar_system_id;
    packet->command = command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_SWITCH_LAMP, (const char *)packet, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_MIN_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_SWITCH_LAMP UNPACKING


/**
 * @brief Get field tar_system_id from mav_switch_lamp message
 *
 * @return Target system ID
 */
static inline uint8_t mavlink_msg_mav_switch_lamp_get_tar_system_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field command from mav_switch_lamp message
 *
 * @return Command for lamp
 */
static inline uint8_t mavlink_msg_mav_switch_lamp_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a mav_switch_lamp message into a struct
 *
 * @param msg The message to decode
 * @param mav_switch_lamp C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_switch_lamp_decode(const mavlink_message_t* msg, mavlink_mav_switch_lamp_t* mav_switch_lamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_switch_lamp->tar_system_id = mavlink_msg_mav_switch_lamp_get_tar_system_id(msg);
    mav_switch_lamp->command = mavlink_msg_mav_switch_lamp_get_command(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN? msg->len : MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN;
        memset(mav_switch_lamp, 0, MAVLINK_MSG_ID_MAV_SWITCH_LAMP_LEN);
    memcpy(mav_switch_lamp, _MAV_PAYLOAD(msg), len);
#endif
}
