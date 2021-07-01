#pragma once
// MESSAGE MAV_COMMAND_ACK PACKING

#define MAVLINK_MSG_ID_MAV_COMMAND_ACK 10

MAVPACKED(
typedef struct __mavlink_mav_command_ack_t {
 int32_t result; /*< Result of the command processing*/
 uint8_t cmd_id; /*< ID of the received command*/
}) mavlink_mav_command_ack_t;

#define MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN 5
#define MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN 5
#define MAVLINK_MSG_ID_10_LEN 5
#define MAVLINK_MSG_ID_10_MIN_LEN 5

#define MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC 111
#define MAVLINK_MSG_ID_10_CRC 111



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_COMMAND_ACK { \
    10, \
    "MAV_COMMAND_ACK", \
    2, \
    {  { "cmd_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_command_ack_t, cmd_id) }, \
         { "result", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_mav_command_ack_t, result) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_COMMAND_ACK { \
    "MAV_COMMAND_ACK", \
    2, \
    {  { "cmd_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mav_command_ack_t, cmd_id) }, \
         { "result", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_mav_command_ack_t, result) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_command_ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd_id ID of the received command
 * @param result Result of the command processing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_command_ack_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t cmd_id, int32_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN];
    _mav_put_int32_t(buf, 0, result);
    _mav_put_uint8_t(buf, 4, cmd_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN);
#else
    mavlink_mav_command_ack_t packet;
    packet.result = result;
    packet.cmd_id = cmd_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_COMMAND_ACK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
}

/**
 * @brief Pack a mav_command_ack message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_id ID of the received command
 * @param result Result of the command processing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_command_ack_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t cmd_id,int32_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN];
    _mav_put_int32_t(buf, 0, result);
    _mav_put_uint8_t(buf, 4, cmd_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN);
#else
    mavlink_mav_command_ack_t packet;
    packet.result = result;
    packet.cmd_id = cmd_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_COMMAND_ACK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
}

/**
 * @brief Encode a mav_command_ack struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_command_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_command_ack_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_command_ack_t* mav_command_ack)
{
    return mavlink_msg_mav_command_ack_pack(system_id, component_id, msg, mav_command_ack->cmd_id, mav_command_ack->result);
}

/**
 * @brief Encode a mav_command_ack struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_command_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_command_ack_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_command_ack_t* mav_command_ack)
{
    return mavlink_msg_mav_command_ack_pack_chan(system_id, component_id, chan, msg, mav_command_ack->cmd_id, mav_command_ack->result);
}

/**
 * @brief Send a mav_command_ack message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd_id ID of the received command
 * @param result Result of the command processing
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_command_ack_send(mavlink_channel_t chan, uint8_t cmd_id, int32_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN];
    _mav_put_int32_t(buf, 0, result);
    _mav_put_uint8_t(buf, 4, cmd_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK, buf, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
#else
    mavlink_mav_command_ack_t packet;
    packet.result = result;
    packet.cmd_id = cmd_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK, (const char *)&packet, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
#endif
}

/**
 * @brief Send a mav_command_ack message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_command_ack_send_struct(mavlink_channel_t chan, const mavlink_mav_command_ack_t* mav_command_ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_command_ack_send(chan, mav_command_ack->cmd_id, mav_command_ack->result);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK, (const char *)mav_command_ack, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_command_ack_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t cmd_id, int32_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, result);
    _mav_put_uint8_t(buf, 4, cmd_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK, buf, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
#else
    mavlink_mav_command_ack_t *packet = (mavlink_mav_command_ack_t *)msgbuf;
    packet->result = result;
    packet->cmd_id = cmd_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_COMMAND_ACK, (const char *)packet, MAVLINK_MSG_ID_MAV_COMMAND_ACK_MIN_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN, MAVLINK_MSG_ID_MAV_COMMAND_ACK_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_COMMAND_ACK UNPACKING


/**
 * @brief Get field cmd_id from mav_command_ack message
 *
 * @return ID of the received command
 */
static inline uint8_t mavlink_msg_mav_command_ack_get_cmd_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field result from mav_command_ack message
 *
 * @return Result of the command processing
 */
static inline int32_t mavlink_msg_mav_command_ack_get_result(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Decode a mav_command_ack message into a struct
 *
 * @param msg The message to decode
 * @param mav_command_ack C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_command_ack_decode(const mavlink_message_t* msg, mavlink_mav_command_ack_t* mav_command_ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_command_ack->result = mavlink_msg_mav_command_ack_get_result(msg);
    mav_command_ack->cmd_id = mavlink_msg_mav_command_ack_get_cmd_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN? msg->len : MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN;
        memset(mav_command_ack, 0, MAVLINK_MSG_ID_MAV_COMMAND_ACK_LEN);
    memcpy(mav_command_ack, _MAV_PAYLOAD(msg), len);
#endif
}
