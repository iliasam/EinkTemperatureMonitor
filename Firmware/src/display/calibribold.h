// CalibriBold32x48.c
// Font type    : Numeric (10 characters)
// Font size    : 32x48 pixels
// Memory usage : 1924 bytes

#if defined(__AVR__)
    #include <avr/pgmspace.h>
    #define fontdatatype const uint8_t
#elif defined(__PIC32MX__)
    #define PROGMEM
    #define fontdatatype const unsigned char
#elif defined(__arm__)
    #define PROGMEM
    #define fontdatatype const unsigned char
#endif

