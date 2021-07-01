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

#include "GxEPD2_154_D67.h"
#include "display_spi.h"
#include "hardware.h"
#include "stm32f10x_it.h"

/* Private define ------------------------------------------------------------*/
//From "display_spi.h"
#define _writeCommand           display_spi_write_cmd
#define _writeData              display_spi_write_data
#define delay                   delay_ms

#define BUSY_TIMEOUT_MS         (6000)

//After this command, data entries will be written into the BW RAM until another
// command is written. Address pointers will advance accordingly
// For Write pixel: Content of Write RAM(BW) = 1
// For Black pixel: Content of Write RAM(BW) = 0
#define WRITE_RAM_CMD           0x24

//After this command, data entries will be written into the RED RAM until another
//command is written.
#define WRITE_RAM_RED_CMD       0x26

#define DISP_UPDATE_CMD         0x22

/* Private function prototypes -----------------------------------------------*/
void _writeScreenBuffer(uint8_t command, uint8_t value);
void _writeImage(uint8_t command, const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void _writeImagePart(uint8_t command, const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                     int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm);
void _setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void _PowerOn();
void _PowerOff();
void _InitDisplay();
void _Init_Full();
void _Init_Part();
void _Update_Full();
void _Update_Part();
void _waitWhileBusy(const char* comment, uint16_t busy_time);

/* Private variables ---------------------------------------------------------*/
bool _hibernating = false;
bool _using_partial_mode = false;
bool _initial_write = true;
bool _initial_refresh = true;
bool _power_is_on = false;

void clearScreen(uint8_t value)
{
  writeScreenBuffer(value);
  refresh(true);
  writeScreenBufferAgain(value);
}

void writeScreenBuffer(uint8_t value)
{
  if (!_using_partial_mode) _Init_Part();
  if (_initial_write) _writeScreenBuffer(WRITE_RAM_RED_CMD, value); // set previous
  _writeScreenBuffer(WRITE_RAM_CMD, value); // set current
  _initial_write = false; // initial full screen buffer clean done
}

void writeScreenBufferAgain(uint8_t value)
{
  if (!_using_partial_mode) _Init_Part();
  _writeScreenBuffer(WRITE_RAM_CMD, value); // set current
}

void _writeScreenBuffer(uint8_t command, uint8_t value)
{
  _writeCommand(command);
  for (uint32_t i = 0; i < (uint32_t)WIDTH * (uint32_t)HEIGHT / 8; i++)
  {
    _writeData(value);
  }
}

void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  _writeImage(WRITE_RAM_CMD, bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void writeImageForFullRefresh(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  _writeImage(WRITE_RAM_RED_CMD, bitmap, x, y, w, h, invert, mirror_y, pgm);
  _writeImage(WRITE_RAM_CMD, bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void writeImageAgain(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  _writeImage(WRITE_RAM_CMD, bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void _writeImage(uint8_t command, const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (_initial_write) 
    writeScreenBuffer(DISP_DEFAULT_COLOR); // initial full screen buffer clean
  delay(1); // yield() to avoid WDT on ESP8266 and ESP32
  int16_t wb = (w + 7) / 8; // width bytes, bitmaps are padded
  x -= x % 8; // byte boundary
  w = wb * 8; // byte boundary
  int16_t x1 = x < 0 ? 0 : x; // limit
  int16_t y1 = y < 0 ? 0 : y; // limit
  int16_t w1 = x + w < (int16_t)WIDTH ? w : (int16_t)WIDTH - x; // limit
  int16_t h1 = y + h < (int16_t)HEIGHT ? h :(int16_t)HEIGHT - y; // limit
  int16_t dx = x1 - x;
  int16_t dy = y1 - y;
  w1 -= dx;
  h1 -= dy;
  if ((w1 <= 0) || (h1 <= 0)) return;
  if (!_using_partial_mode) _Init_Part();
  _setPartialRamArea(x1, y1, w1, h1);
  _writeCommand(command);
  for (int16_t i = 0; i < h1; i++)
  {
    for (int16_t j = 0; j < w1 / 8; j++)
    {
      uint8_t data;
      // use wb, h of bitmap for index!
      int16_t idx = mirror_y ? j + dx / 8 + ((h - 1 - (i + dy))) * wb : j + dx / 8 + (i + dy) * wb;
      if (pgm)
      {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
        data = pgm_read_byte(&bitmap[idx]);
#else
        data = bitmap[idx];
#endif
      }
      else
      {
        data = bitmap[idx];
      }
      if (invert) data = ~data;
      _writeData(data);
    }
  }
  delay(1); // yield() to avoid WDT on ESP8266 and ESP32
}

void writeImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                                    int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  _writeImagePart(WRITE_RAM_CMD, bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void writeImagePartAgain(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
    int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  _writeImagePart(WRITE_RAM_CMD, bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void _writeImagePart(uint8_t command, const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                                     int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (_initial_write) 
    writeScreenBuffer(DISP_DEFAULT_COLOR); // initial full screen buffer clean
  delay(1); // yield() to avoid WDT on ESP8266 and ESP32
  if ((w_bitmap < 0) || (h_bitmap < 0) || (w < 0) || (h < 0)) return;
  if ((x_part < 0) || (x_part >= w_bitmap)) return;
  if ((y_part < 0) || (y_part >= h_bitmap)) return;
  int16_t wb_bitmap = (w_bitmap + 7) / 8; // width bytes, bitmaps are padded
  x_part -= x_part % 8; // byte boundary
  w = w_bitmap - x_part < w ? w_bitmap - x_part : w; // limit
  h = h_bitmap - y_part < h ? h_bitmap - y_part : h; // limit
  x -= x % 8; // byte boundary
  w = 8 * ((w + 7) / 8); // byte boundary, bitmaps are padded
  int16_t x1 = x < 0 ? 0 : x; // limit
  int16_t y1 = y < 0 ? 0 : y; // limit
  int16_t w1 = x + w < (int16_t)WIDTH ? w : (int16_t)WIDTH - x; // limit
  int16_t h1 = y + h < (int16_t)HEIGHT ? h : (int16_t)HEIGHT - y; // limit
  int16_t dx = x1 - x;
  int16_t dy = y1 - y;
  w1 -= dx;
  h1 -= dy;
  if ((w1 <= 0) || (h1 <= 0)) return;
  if (!_using_partial_mode) _Init_Part();
  _setPartialRamArea(x1, y1, w1, h1);
  _writeCommand(command);
  for (int16_t i = 0; i < h1; i++)
  {
    for (int16_t j = 0; j < w1 / 8; j++)
    {
      uint8_t data;
      // use wb_bitmap, h_bitmap of bitmap for index!
      int16_t idx = mirror_y ? x_part / 8 + j + dx / 8 + ((h_bitmap - 1 - (y_part + i + dy))) * wb_bitmap : x_part / 8 + j + dx / 8 + (y_part + i + dy) * wb_bitmap;
      if (pgm)
      {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
        data = pgm_read_byte(&bitmap[idx]);
#else
        data = bitmap[idx];
#endif
      }
      else
      {
        data = bitmap[idx];
      }
      if (invert) data = ~data;
      _writeData(data);
    }
  }
  delay(1); // yield() to avoid WDT on ESP8266 and ESP32
}

void writeImage2(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (black)
  {
    writeImage(black, x, y, w, h, invert, mirror_y, pgm);
  }
}

void writeImagePart2(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                                    int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (black)
  {
    writeImagePart(black, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
  }
}

void writeNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (data1)
  {
    writeImage(data1, x, y, w, h, invert, mirror_y, pgm);
  }
}

void drawImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  writeImage(bitmap, x, y, w, h, invert, mirror_y, pgm);
  refresh_partial(x, y, w, h);
  writeImageAgain(bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void drawImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                                   int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  writeImagePart(bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
  refresh_partial(x, y, w, h);
  writeImagePartAgain(bitmap, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
}

void drawImage2(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (black)
  {
    drawImage(black, x, y, w, h, invert, mirror_y, pgm);
  }
}

void drawImagePart2(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                                   int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (black)
  {
    drawImagePart(black, x_part, y_part, w_bitmap, h_bitmap, x, y, w, h, invert, mirror_y, pgm);
  }
}

void drawNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert, bool mirror_y, bool pgm)
{
  if (data1)
  {
    drawImage(data1, x, y, w, h, invert, mirror_y, pgm);
  }
}

void refresh(bool partial_update_mode)
{
  if (partial_update_mode) 
    refresh_partial(0, 0, WIDTH, HEIGHT);
  else
  {
    if (_using_partial_mode) _Init_Full();
    _Update_Full();
    _initial_refresh = false; // initial full update done
  }
}

void refresh_partial(int16_t x, int16_t y, int16_t w, int16_t h)
{
  if (_initial_refresh) 
  {
    refresh(false); // initial update needs be full update
    return;
  }
  x -= x % 8; // byte boundary
  w -= x % 8; // byte boundary
  int16_t x1 = x < 0 ? 0 : x; // limit
  int16_t y1 = y < 0 ? 0 : y; // limit
  int16_t w1 = x + w < (int16_t)WIDTH ? w : (int16_t)WIDTH - x; // limit
  int16_t h1 = y + h < (int16_t)HEIGHT ? h : (int16_t)HEIGHT - y; // limit
  w1 -= x1 - x;
  h1 -= y1 - y;
  if (!_using_partial_mode) _Init_Part();
  _setPartialRamArea(x1, y1, w1, h1);
  _Update_Part();
}

void powerOff()
{
  _PowerOff();
}

void hibernate()
{
  _PowerOff();
  /*
  if (_rst >= 0)
  {
    _writeCommand(0x10); // deep sleep mode
    _writeData(0x1);     // enter deep sleep
    _hibernating = true;
  }
  */
}

void _setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  _writeCommand(0x11); // set ram entry mode
  _writeData(0x03);    // x increase, y increase : normal mode
  _writeCommand(0x44);
  _writeData(x / 8);
  _writeData((x + w - 1) / 8);
  _writeCommand(0x45);
  _writeData(y % 256);
  _writeData(y / 256);
  _writeData((y + h - 1) % 256);
  _writeData((y + h - 1) / 256);
  _writeCommand(0x4e);
  _writeData(x / 8);
  _writeCommand(0x4f);
  _writeData(y % 256);
  _writeData(y / 256);
}

void _PowerOn()
{
  if (!_power_is_on)
  {
    _writeCommand(DISP_UPDATE_CMD);
    _writeData(0xf8);
    _writeCommand(0x20);
    _waitWhileBusy("_PowerOn", power_on_time);
  }
  _power_is_on = true;
}

void _PowerOff()
{
  if (_power_is_on)
  {
    _writeCommand(DISP_UPDATE_CMD);
    _writeData(0x83);
    _writeCommand(0x20);
    _waitWhileBusy("_PowerOff", power_off_time);
  }
  _power_is_on = false;
  _using_partial_mode = false;
}

void _InitDisplay()
{
  delay(10); // 10ms according to specs
  _writeCommand(0x12); // soft reset
  delay(10); // 10ms according to specs
  _writeCommand(0x01); // Set gate driver output
  _writeData(0xC7);
  _writeData(0x00);
  _writeData(0x00);
  _writeCommand(0x3C); // Set panel border - BorderWavefrom
  _writeData(0x05);
  _writeCommand(0x18); // Read built-in temperature sensor
  _writeData(0x80);
  _setPartialRamArea(0, 0, WIDTH, HEIGHT);
}

void _Init_Full()
{
  _InitDisplay();
  _PowerOn();
  _using_partial_mode = false;
}

void _Init_Part()
{
  _InitDisplay();
  _PowerOn();
  _using_partial_mode = true;
}

void _Update_Full()
{
  _writeCommand(DISP_UPDATE_CMD);//Display Update Sequence Option
 // _writeData(0xf4);
  _writeData(0xf7); //Enable clock signal - DISPLAY Mode 1
  _writeCommand(0x20);
  _waitWhileBusy("_Update_Full", full_refresh_time);
}

void _Update_Part()
{
  _writeCommand(DISP_UPDATE_CMD);//Display Update Sequence Option
  //_writeData(0xfc);
  _writeData(0xff);//Enable clock signal - DISPLAY Mode 2
  _writeCommand(0x20);
  _waitWhileBusy("_Update_Part", partial_refresh_time);
}

void _waitWhileBusy(const char* comment, uint16_t busy_time)
{
  uint32_t start = HAL_GetTick();
  while (1)
  {
    if (display_spi_is_busy() != 1) 
      break;
    //delay(1);
    go_to_sleep_mode(100);
    if (HAL_GetTick() - start > BUSY_TIMEOUT_MS)
    {
      //Timeout
      asm("nop");
      break;
    }
  }
}
