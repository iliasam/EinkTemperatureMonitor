#pragma once
// MESSAGE MAV_TEMPERATURE_VALUES PACKING

#define MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES 103

MAVPACKED(
typedef struct __mavlink_mav_temperature_values_t {
 float temp1; /*< Temperature 1*/
 float temp2; /*< Temperature 2*/
 float temp3; /*< Temperature 3*/
}) mavlink_mav_temperature_values_t;

#define MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN 12
#define MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN 12
#define MAVLINK_MSG_ID_103_LEN 12
#define MAVLINK_MSG_ID_103_MIN_LEN 12

#define MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC 143
#define MAVLINK_MSG_ID_103_CRC 143



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_TEMPERATURE_VALUES { \
    103, \
    "MAV_TEMPERATURE_VALUES", \
    3, \
    {  { "temp1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_temperature_values_t, temp1) }, \
         { "temp2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_temperature_values_t, temp2) }, \
         { "temp3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_temperature_values_t, temp3) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_TEMPERATURE_VALUES { \
    "MAV_TEMPERATURE_VALUES", \
    3, \
    {  { "temp1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mav_temperature_values_t, temp1) }, \
         { "temp2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mav_temperature_values_t, temp2) }, \
         { "temp3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mav_temperature_values_t, temp3) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_temperature_values message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param temp1 Temperature 1
 * @param temp2 Temperature 2
 * @param temp3 Temperature 3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_temperature_values_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float temp1, float temp2, float temp3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN];
    _mav_put_float(buf, 0, temp1);
    _mav_put_float(buf, 4, temp2);
    _mav_put_float(buf, 8, temp3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN);
#else
    mavlink_mav_temperature_values_t packet;
    packet.temp1 = temp1;
    packet.temp2 = temp2;
    packet.temp3 = temp3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
}

/**
 * @brief Pack a mav_temperature_values message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param temp1 Temperature 1
 * @param temp2 Temperature 2
 * @param temp3 Temperature 3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_temperature_values_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float temp1,float temp2,float temp3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN];
    _mav_put_float(buf, 0, temp1);
    _mav_put_float(buf, 4, temp2);
    _mav_put_float(buf, 8, temp3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN);
#else
    mavlink_mav_temperature_values_t packet;
    packet.temp1 = temp1;
    packet.temp2 = temp2;
    packet.temp3 = temp3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
}

/**
 * @brief Encode a mav_temperature_values struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_temperature_values C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_temperature_values_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_temperature_values_t* mav_temperature_values)
{
    return mavlink_msg_mav_temperature_values_pack(system_id, component_id, msg, mav_temperature_values->temp1, mav_temperature_values->temp2, mav_temperature_values->temp3);
}

/**
 * @brief Encode a mav_temperature_values struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_temperature_values C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_temperature_values_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_temperature_values_t* mav_temperature_values)
{
    return mavlink_msg_mav_temperature_values_pack_chan(system_id, component_id, chan, msg, mav_temperature_values->temp1, mav_temperature_values->temp2, mav_temperature_values->temp3);
}

/**
 * @brief Send a mav_temperature_values message
 * @param chan MAVLink channel to send the message
 *
 * @param temp1 Temperature 1
 * @param temp2 Temperature 2
 * @param temp3 Temperature 3
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_temperature_values_send(mavlink_channel_t chan, float temp1, float temp2, float temp3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN];
    _mav_put_float(buf, 0, temp1);
    _mav_put_float(buf, 4, temp2);
    _mav_put_float(buf, 8, temp3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES, buf, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
#else
    mavlink_mav_temperature_values_t packet;
    packet.temp1 = temp1;
    packet.temp2 = temp2;
    packet.temp3 = temp3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES, (const char *)&packet, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
#endif
}

/**
 * @brief Send a mav_temperature_values message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_temperature_values_send_struct(mavlink_channel_t chan, const mavlink_mav_temperature_values_t* mav_temperature_values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_temperature_values_send(chan, mav_temperature_values->temp1, mav_temperature_values->temp2, mav_temperature_values->temp3);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES, (const char *)mav_temperature_values, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_temperature_values_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float temp1, float temp2, float temp3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, temp1);
    _mav_put_float(buf, 4, temp2);
    _mav_put_float(buf, 8, temp3);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES, buf, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
#else
    mavlink_mav_temperature_values_t *packet = (mavlink_mav_temperature_values_t *)msgbuf;
    packet->temp1 = temp1;
    packet->temp2 = temp2;
    packet->temp3 = temp3;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES, (const char *)packet, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_MIN_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_TEMPERATURE_VALUES UNPACKING


/**
 * @brief Get field temp1 from mav_temperature_values message
 *
 * @return Temperature 1
 */
static inline float mavlink_msg_mav_temperature_values_get_temp1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field temp2 from mav_temperature_values message
 *
 * @return Temperature 2
 */
static inline float mavlink_msg_mav_temperature_values_get_temp2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field temp3 from mav_temperature_values message
 *
 * @return Temperature 3
 */
static inline float mavlink_msg_mav_temperature_values_get_temp3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a mav_temperature_values message into a struct
 *
 * @param msg The message to decode
 * @param mav_temperature_values C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_temperature_values_decode(const mavlink_message_t* msg, mavlink_mav_temperature_values_t* mav_temperature_values)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_temperature_values->temp1 = mavlink_msg_mav_temperature_values_get_temp1(msg);
    mav_temperature_values->temp2 = mavlink_msg_mav_temperature_values_get_temp2(msg);
    mav_temperature_values->temp3 = mavlink_msg_mav_temperature_values_get_temp3(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN? msg->len : MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN;
        memset(mav_temperature_values, 0, MAVLINK_MSG_ID_MAV_TEMPERATURE_VALUES_LEN);
    memcpy(mav_temperature_values, _MAV_PAYLOAD(msg), len);
#endif
}
