#pragma once
// MESSAGE MAV_CURTAINS_DRIVE_STATE PACKING

#define MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE 100

MAVPACKED(
typedef struct __mavlink_mav_curtains_drive_state_t {
 uint8_t drive_state; /*< Curtains drive state*/
 uint8_t lamp_state; /*< Curtains drive lamp state*/
 uint8_t errors; /*< Curtains drive errors*/
 uint8_t brightness; /*< Light sensor value*/
}) mavlink_mav_curtains_drive_state_t;

#define MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN 4
#define MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN 4
#define MAVLINK_MSG_ID_100_LEN 4
#define MAVLINK_MSG_ID_100_MIN_LEN 4

#define MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC 26
#define MAVLINK_MSG_ID_100_CRC 26



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MAV_CURTAINS_DRIVE_STATE { \
    100, \
    "MAV_CURTAINS_DRIVE_STATE", \
    4, \
    {  { "drive_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_curtains_drive_state_t, drive_state) }, \
         { "lamp_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_curtains_drive_state_t, lamp_state) }, \
         { "errors", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_mav_curtains_drive_state_t, errors) }, \
         { "brightness", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_mav_curtains_drive_state_t, brightness) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MAV_CURTAINS_DRIVE_STATE { \
    "MAV_CURTAINS_DRIVE_STATE", \
    4, \
    {  { "drive_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_mav_curtains_drive_state_t, drive_state) }, \
         { "lamp_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_mav_curtains_drive_state_t, lamp_state) }, \
         { "errors", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_mav_curtains_drive_state_t, errors) }, \
         { "brightness", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_mav_curtains_drive_state_t, brightness) }, \
         } \
}
#endif

/**
 * @brief Pack a mav_curtains_drive_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param drive_state Curtains drive state
 * @param lamp_state Curtains drive lamp state
 * @param errors Curtains drive errors
 * @param brightness Light sensor value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_curtains_drive_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t drive_state, uint8_t lamp_state, uint8_t errors, uint8_t brightness)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN];
    _mav_put_uint8_t(buf, 0, drive_state);
    _mav_put_uint8_t(buf, 1, lamp_state);
    _mav_put_uint8_t(buf, 2, errors);
    _mav_put_uint8_t(buf, 3, brightness);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN);
#else
    mavlink_mav_curtains_drive_state_t packet;
    packet.drive_state = drive_state;
    packet.lamp_state = lamp_state;
    packet.errors = errors;
    packet.brightness = brightness;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
}

/**
 * @brief Pack a mav_curtains_drive_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param drive_state Curtains drive state
 * @param lamp_state Curtains drive lamp state
 * @param errors Curtains drive errors
 * @param brightness Light sensor value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mav_curtains_drive_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t drive_state,uint8_t lamp_state,uint8_t errors,uint8_t brightness)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN];
    _mav_put_uint8_t(buf, 0, drive_state);
    _mav_put_uint8_t(buf, 1, lamp_state);
    _mav_put_uint8_t(buf, 2, errors);
    _mav_put_uint8_t(buf, 3, brightness);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN);
#else
    mavlink_mav_curtains_drive_state_t packet;
    packet.drive_state = drive_state;
    packet.lamp_state = lamp_state;
    packet.errors = errors;
    packet.brightness = brightness;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
}

/**
 * @brief Encode a mav_curtains_drive_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mav_curtains_drive_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_curtains_drive_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mav_curtains_drive_state_t* mav_curtains_drive_state)
{
    return mavlink_msg_mav_curtains_drive_state_pack(system_id, component_id, msg, mav_curtains_drive_state->drive_state, mav_curtains_drive_state->lamp_state, mav_curtains_drive_state->errors, mav_curtains_drive_state->brightness);
}

/**
 * @brief Encode a mav_curtains_drive_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mav_curtains_drive_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mav_curtains_drive_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mav_curtains_drive_state_t* mav_curtains_drive_state)
{
    return mavlink_msg_mav_curtains_drive_state_pack_chan(system_id, component_id, chan, msg, mav_curtains_drive_state->drive_state, mav_curtains_drive_state->lamp_state, mav_curtains_drive_state->errors, mav_curtains_drive_state->brightness);
}

/**
 * @brief Send a mav_curtains_drive_state message
 * @param chan MAVLink channel to send the message
 *
 * @param drive_state Curtains drive state
 * @param lamp_state Curtains drive lamp state
 * @param errors Curtains drive errors
 * @param brightness Light sensor value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mav_curtains_drive_state_send(mavlink_channel_t chan, uint8_t drive_state, uint8_t lamp_state, uint8_t errors, uint8_t brightness)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN];
    _mav_put_uint8_t(buf, 0, drive_state);
    _mav_put_uint8_t(buf, 1, lamp_state);
    _mav_put_uint8_t(buf, 2, errors);
    _mav_put_uint8_t(buf, 3, brightness);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE, buf, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
#else
    mavlink_mav_curtains_drive_state_t packet;
    packet.drive_state = drive_state;
    packet.lamp_state = lamp_state;
    packet.errors = errors;
    packet.brightness = brightness;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE, (const char *)&packet, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
#endif
}

/**
 * @brief Send a mav_curtains_drive_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mav_curtains_drive_state_send_struct(mavlink_channel_t chan, const mavlink_mav_curtains_drive_state_t* mav_curtains_drive_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mav_curtains_drive_state_send(chan, mav_curtains_drive_state->drive_state, mav_curtains_drive_state->lamp_state, mav_curtains_drive_state->errors, mav_curtains_drive_state->brightness);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE, (const char *)mav_curtains_drive_state, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mav_curtains_drive_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t drive_state, uint8_t lamp_state, uint8_t errors, uint8_t brightness)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, drive_state);
    _mav_put_uint8_t(buf, 1, lamp_state);
    _mav_put_uint8_t(buf, 2, errors);
    _mav_put_uint8_t(buf, 3, brightness);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE, buf, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
#else
    mavlink_mav_curtains_drive_state_t *packet = (mavlink_mav_curtains_drive_state_t *)msgbuf;
    packet->drive_state = drive_state;
    packet->lamp_state = lamp_state;
    packet->errors = errors;
    packet->brightness = brightness;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE, (const char *)packet, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_MIN_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE MAV_CURTAINS_DRIVE_STATE UNPACKING


/**
 * @brief Get field drive_state from mav_curtains_drive_state message
 *
 * @return Curtains drive state
 */
static inline uint8_t mavlink_msg_mav_curtains_drive_state_get_drive_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field lamp_state from mav_curtains_drive_state message
 *
 * @return Curtains drive lamp state
 */
static inline uint8_t mavlink_msg_mav_curtains_drive_state_get_lamp_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field errors from mav_curtains_drive_state message
 *
 * @return Curtains drive errors
 */
static inline uint8_t mavlink_msg_mav_curtains_drive_state_get_errors(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field brightness from mav_curtains_drive_state message
 *
 * @return Light sensor value
 */
static inline uint8_t mavlink_msg_mav_curtains_drive_state_get_brightness(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Decode a mav_curtains_drive_state message into a struct
 *
 * @param msg The message to decode
 * @param mav_curtains_drive_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_mav_curtains_drive_state_decode(const mavlink_message_t* msg, mavlink_mav_curtains_drive_state_t* mav_curtains_drive_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mav_curtains_drive_state->drive_state = mavlink_msg_mav_curtains_drive_state_get_drive_state(msg);
    mav_curtains_drive_state->lamp_state = mavlink_msg_mav_curtains_drive_state_get_lamp_state(msg);
    mav_curtains_drive_state->errors = mavlink_msg_mav_curtains_drive_state_get_errors(msg);
    mav_curtains_drive_state->brightness = mavlink_msg_mav_curtains_drive_state_get_brightness(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN? msg->len : MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN;
        memset(mav_curtains_drive_state, 0, MAVLINK_MSG_ID_MAV_CURTAINS_DRIVE_STATE_LEN);
    memcpy(mav_curtains_drive_state, _MAV_PAYLOAD(msg), len);
#endif
}
