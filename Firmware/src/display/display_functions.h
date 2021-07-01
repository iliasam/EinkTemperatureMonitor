#ifndef __DISPLAY_FUNCTIONS_H
#define __DISPLAY_FUNCTIONS_H

#include "stdint.h"
#include "string.h"
#include "GxEPD2_154_D67.h"

#define SYMB_DEG_CODE           0xB0 //176 dec - deg symbol

#define DISPLAY_WIDTH           200
#define DISPLAY_HEIGHT          200

#define LCD_LEFT_OFFSET         0
#define LCD_RIGHT_OFFSET        (DISPLAY_WIDTH - 0)

#define FONT_SIZE_6             6//3*5
#define FONT_SIZE_6_WIDTH       4//3*5

#define FONT_SIZE_8             8//5*7
#define FONT_SIZE_8_WIDTH       6//5*7

#define FONT_SIZE_11            12//7*11
#define FONT_SIZE_11_WIDTH      8//7*11

#define FONT_SIZE_21            21
#define FONT_SIZE_21_WIDTH     (16)

#define FONT_SIZE_48            48
#define FONT_SIZE_48_WIDTH     (32)

#define FONT_SIZE_100           100
#define FONT_SIZE_100_WIDTH     (64 + 5)

#define LCD_NEW_LINE_FLAG       1//jump to new line
#define LCD_INVERTED_FLAG       2//inverted draw

void display_full_clear(void);
void display_clear_framebuffer(void);
void display_update(void);
void display_set_pixel(uint16_t x, uint16_t y);
void display_reset_pixel(uint16_t x, uint16_t y);

void display_draw_char(uint8_t chr, uint16_t x, uint16_t y, uint8_t font_size, uint8_t flags);
void display_set_cursor_pos(uint16_t x, uint16_t y);
uint16_t display_draw_string(char *s, uint16_t x, uint16_t y, uint8_t font_size, uint8_t flags);
uint16_t display_draw_string_cur(char *s, uint8_t font_size, uint8_t flags);
uint16_t get_font_width(uint8_t font);
void draw_caption_bar(uint8_t height);
void draw_black_line(uint16_t y);
void draw_black_line2(uint16_t x1, uint16_t x2, uint16_t y);
void display_write_framebuffer(uint8_t data, uint32_t pos);
void draw_image(uint8_t *image_data, uint16_t x, uint16_t y);

#endif //__DISPLAY_FUNCTIONS_H

