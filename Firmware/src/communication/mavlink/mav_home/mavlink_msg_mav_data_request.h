#pragma once
// MESSAGE MAV_DATA_REQUEST PACKING

#define MAVLINK_MSG_ID_MAV_DATA_REQUEST 11

MAVPACKED(
typedef struct __mavlink_mav_data_request_t {
 uint8_t tar_system_id; /*< Target system ID*/
 uint8_t tar_component_id; /*< Target component ID*/
 uint8_t data_type; /*< Type of the needed data*/
}) mavlink_mav_data_request_t;

#define MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN 3
#define MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN 3
#define MAVLINK_MSG_ID_11_LEN 3
#define MAVLINK_MSG_ID_11_MIN_LEN 3

#define MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC 244
#define MAVLINK_MSG_ID_11_CRC 244



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_DATA_REQUEST { \
    11, \
    "MAV_DATA_REQUEST", \
    3, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_data_request_t, tar_system_id) }, \
         { "tar_component_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_data_request_t, tar_component_id) }, \
         { "data_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_mav_data_request_t, data_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_DATA_REQUEST { \
    "MAV_DATA_REQUEST", \
    3, \
    {  { "tar_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_data_request_t, tar_system_id) }, \
         { "tar_component_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_data_request_t, tar_component_id) }, \
         { "data_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_mav_data_request_t, data_type) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_data_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param data_type Type of the needed data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_data_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t tar_system_id, uint8_t tar_component_id, uint8_t data_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, tar_component_id);
    _mav_put_uint8_t(buf, 2, data_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN);
#else
    mavlink_mav_data_request_t packet;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.data_type = data_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_DATA_REQUEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
}

/**
 * @brief Pack a mav_data_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param data_type Type of the needed data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_data_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t tar_system_id,uint8_t tar_component_id,uint8_t data_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, tar_component_id);
    _mav_put_uint8_t(buf, 2, data_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN);
#else
    mavlink_mav_data_request_t packet;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.data_type = data_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_DATA_REQUEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
}

/**
 * @brief Encode a mav_data_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_data_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_data_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_data_request_t* mav_data_request)
{
    return mavlink_msg_mav_data_request_pack(system_id, component_id, msg, mav_data_request->tar_system_id, mav_data_request->tar_component_id, mav_data_request->data_type);
}

/**
 * @brief Encode a mav_data_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_data_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_data_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_data_request_t* mav_data_request)
{
    return mavlink_msg_mav_data_request_pack_chan(system_id, component_id, chan, msg, mav_data_request->tar_system_id, mav_data_request->tar_component_id, mav_data_request->data_type);
}

/**
 * @brief Send a mav_data_request message
 * @param chan MAVLink channel to send the message
 *
 * @param tar_system_id Target system ID
 * @param tar_component_id Target component ID
 * @param data_type Type of the needed data
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_data_request_send(mavlink_channel_t chan, uint8_t tar_system_id, uint8_t tar_component_id, uint8_t data_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN];
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, tar_component_id);
    _mav_put_uint8_t(buf, 2, data_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST, buf, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
#else
    mavlink_mav_data_request_t packet;
    packet.tar_system_id = tar_system_id;
    packet.tar_component_id = tar_component_id;
    packet.data_type = data_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
#endif
}

/**
 * @brief Send a mav_data_request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_data_request_send_struct(mavlink_channel_t chan, const mavlink_mav_data_request_t* mav_data_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_data_request_send(chan, mav_data_request->tar_system_id, mav_data_request->tar_component_id, mav_data_request->data_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST, (const char *)mav_data_request, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_data_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t tar_system_id, uint8_t tar_component_id, uint8_t data_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, tar_system_id);
    _mav_put_uint8_t(buf, 1, tar_component_id);
    _mav_put_uint8_t(buf, 2, data_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST, buf, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
#else
    mavlink_mav_data_request_t *packet = (mavlink_mav_data_request_t *)msgbuf;
    packet->tar_system_id = tar_system_id;
    packet->tar_component_id = tar_component_id;
    packet->data_type = data_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_DATA_REQUEST, (const char *)packet, MAVLINK_MSG_ID_MAV_DATA_REQUEST_MIN_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN, MAVLINK_MSG_ID_MAV_DATA_REQUEST_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_DATA_REQUEST UNPACKING


/**
 * @brief Get field tar_system_id from mav_data_request message
 *
 * @return Target system ID
 */
static inline uint8_t mavlink_msg_mav_data_request_get_tar_system_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field tar_component_id from mav_data_request message
 *
 * @return Target component ID
 */
static inline uint8_t mavlink_msg_mav_data_request_get_tar_component_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field data_type from mav_data_request message
 *
 * @return Type of the needed data
 */
static inline uint8_t mavlink_msg_mav_data_request_get_data_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a mav_data_request message into a struct
 *
 * @param msg The message to decode
 * @param mav_data_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_data_request_decode(const mavlink_message_t* msg, mavlink_mav_data_request_t* mav_data_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_data_request->tar_system_id = mavlink_msg_mav_data_request_get_tar_system_id(msg);
    mav_data_request->tar_component_id = mavlink_msg_mav_data_request_get_tar_component_id(msg);
    mav_data_request->data_type = mavlink_msg_mav_data_request_get_data_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN? msg->len : MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN;
        memset(mav_data_request, 0, MAVLINK_MSG_ID_MAV_DATA_REQUEST_LEN);
    memcpy(mav_data_request, _MAV_PAYLOAD(msg), len);
#endif
}
