// Display Library for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// based on Demo Example from Good Display, available here: http://www.e-paper-display.com/download_detail/downloadsId=806.html
// Panel: GDEH0154D67 : http://www.e-paper-display.com/products_detail/productId=455.html
// Controller : SSD1681 : http://www.e-paper-display.com/download_detail/downloadsId=825.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// Converted to C by Iliasam

#ifndef _GxEPD2_154_D67_H_
#define _GxEPD2_154_D67_H_
#include <stdint.h>
#include <stdbool.h>

#define DISP_DEFAULT_COLOR      (0xFF) //white

// attributes
static const uint16_t WIDTH = 200;
static const uint16_t HEIGHT = 200;
static const bool hasColor = false;
static const bool hasPartialUpdate = true;
static const bool hasFastPartialUpdate = true;
static const uint16_t power_on_time = 100; // ms, e.g. 95583us
static const uint16_t power_off_time = 150; // ms, e.g. 140621us
static const uint16_t full_refresh_time = 2600; // ms, e.g. 2509602us
static const uint16_t partial_refresh_time = 500; // ms, e.g. 457282us



// methods (virtual)
//  Support for Bitmaps (Sprites) to Controller Buffer and to Screen
void clearScreen(uint8_t value); // init controller memory and screen (default white)
void writeScreenBuffer(uint8_t value); // init controller memory (default white)
void writeScreenBufferAgain(uint8_t value); // init previous buffer controller memory (default white)

// write to controller memory, without screen refresh; x and w should be multiple of 8
void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void writeImageForFullRefresh(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void writeImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                    int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void writeImage2(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void writeImagePart2(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap, 
                     int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);

// for differential update: set current and previous buffers equal (for fast partial update to work correctly)
void writeImageAgain(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
void writeImagePartAgain(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                         int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
// write sprite of native data to controller memory, without screen refresh; x and w should be multiple of 8
void writeNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
// write to controller memory, with screen refresh; x and w should be multiple of 8
void drawImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
void drawImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                   int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
void drawImage2(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
void drawImagePart2(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                   int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );
// write sprite of native data to controller memory, with screen refresh; x and w should be multiple of 8
void drawNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert , bool mirror_y , bool pgm );

void refresh(bool partial_update_mode ); // screen refresh from controller memory to full screen
void refresh_partial(int16_t x, int16_t y, int16_t w, int16_t h); // screen refresh from controller memory, partial screen
void powerOff(); // turns off generation of panel driving voltages, avoids screen fading over time
void hibernate(); // turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)

#endif
