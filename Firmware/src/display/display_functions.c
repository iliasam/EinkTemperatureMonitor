//Special framebuffer wrapper used for basic operations - text drawing
#include "display_functions.h"
#include "fonts.h"
#include "font64x100.h"
#include "font16x21.h"

uint16_t display_cursor_text_x = 0;
uint16_t display_cursor_text_y = 0;

void display_draw_char_size8(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags);
void display_draw_char_size11(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags);
void display_draw_char_size100(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags);
void display_draw_char_size21(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags);
void display_draw_char_size48(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags);

uint8_t display_framebuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

void display_write_framebuffer(uint8_t data, uint32_t pos)
{
  if (pos > sizeof(display_framebuffer))
    return;
  
  display_framebuffer[pos] = data;
}

void display_set_pixel(uint16_t x, uint16_t y)
{
  /*
  //Working, direct mode
  uint16_t loc_x = x + LCD_LEFT_OFFSET;
  if (loc_x >= DISPLAY_WIDTH)
    return;
  if (loc_x >= LCD_RIGHT_OFFSET)
    return;
  
  uint32_t byte_pos = y * (DISPLAY_WIDTH / 8) + loc_x / 8;
  uint8_t byte_val = 1 << (7 - (loc_x % 8));
  display_framebuffer[byte_pos]|= byte_val;
  */
  
  uint16_t loc_x = y + LCD_LEFT_OFFSET;
  if (loc_x >= DISPLAY_WIDTH)
    return;
  if (loc_x >= LCD_RIGHT_OFFSET)
    return;
  uint16_t loc_y = DISPLAY_WIDTH - x;
  
  uint32_t byte_pos = loc_y * (DISPLAY_WIDTH / 8) + loc_x / 8;
  uint8_t byte_val = 1 << (7 - (loc_x % 8));
  display_framebuffer[byte_pos]|= byte_val;
}

void display_reset_pixel(uint16_t x, uint16_t y)
{
  /*
  uint16_t loc_x = x + LCD_LEFT_OFFSET;
  if (loc_x >= DISPLAY_WIDTH)
    return;
  if (loc_x >= LCD_RIGHT_OFFSET)
    return;
  
  uint16_t loc_y = y / 8;//8 - size of lcd line
  uint32_t byte_pos = loc_y * DISPLAY_WIDTH + loc_x;
  uint8_t byte_val = 1 << ((y % 8));
  display_framebuffer[byte_pos]&= ~byte_val;
  */
}

void display_clear_framebuffer(void)
{
  memset(display_framebuffer, 0, sizeof(display_framebuffer));
  display_cursor_text_x = 0;
  display_cursor_text_y = 0;
}

void display_full_clear(void)
{
  memset(display_framebuffer, 0, sizeof(display_framebuffer));
  clearScreen(DISP_DEFAULT_COLOR);
  display_cursor_text_x = 0;
  display_cursor_text_y = 0;
}

void display_set_cursor_pos(uint16_t x, uint16_t y)
{
  display_cursor_text_x = x;
  display_cursor_text_y = y;
}

void display_update(void)
{
  writeImage(display_framebuffer, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, true, false, false);
  refresh(false);//full update
}

//x, y - in pixel
//return string width
//String end is 0x00 char
uint16_t display_draw_string(char *s, uint16_t x, uint16_t y, uint8_t font_size, uint8_t flags)
{
  uint16_t width = get_font_width(font_size);
  uint8_t chr_pos = 0;
  char chr = *s;
  
  while (chr && (chr_pos < 50)) 
  {
    display_draw_char(chr, x + chr_pos*width, y, font_size, flags);
    chr_pos++;
    chr = s[chr_pos];
  }
  display_cursor_text_x = x + chr_pos*width;
  display_cursor_text_y = y;
  
  return chr_pos*width;
}

uint16_t get_font_width(uint8_t font)
{
  switch (font)
  {
    case FONT_SIZE_8:  return FONT_SIZE_8_WIDTH;
    case FONT_SIZE_11: return FONT_SIZE_11_WIDTH;
    case FONT_SIZE_100: return FONT_SIZE_100_WIDTH;
    case FONT_SIZE_21: return FONT_SIZE_21_WIDTH;
    case FONT_SIZE_48: return (FONT_SIZE_48_WIDTH - 1);
    default: return 5;
  }
}

//Draw text at current cursor position
//String end is 0x00 char
uint16_t display_draw_string_cur(char *s, uint8_t font_size, uint8_t flags)
{
  uint16_t length = display_draw_string(s, display_cursor_text_x, display_cursor_text_y, font_size, flags);
  display_cursor_text_x+= length;
  if ((flags & LCD_NEW_LINE_FLAG) != 0)
  {
    display_cursor_text_y+= font_size;
    display_cursor_text_x = 0;
  }
    
  return length;
}

//x - size in pixel
//y - in pixel
//font_size - height
void display_draw_char(uint8_t chr, uint16_t x, uint16_t y, uint8_t font_size, uint8_t flags)
{
  switch (font_size)
  {
    case FONT_SIZE_8:
    {
      display_draw_char_size8(chr, x, y, flags);
      break;
    }
    case FONT_SIZE_11:
    {
      display_draw_char_size11(chr, x, y, flags);
      break;
    }
    case FONT_SIZE_100:
    {
      display_draw_char_size100(chr, x, y, flags);
      break;
    }
    case FONT_SIZE_21:
    {
      display_draw_char_size21(chr, x, y, flags);
      break;
    }
    case FONT_SIZE_48:
    {
      display_draw_char_size48(chr, x, y, flags);
      break;
    }
  }
}

//x, y - size in pixel
void display_draw_char_size8(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags)
{
  uint16_t x_pos, y_pos;
  
  //decoding symbol
  if (chr >= 32 && chr <= '~')
  {
    chr = chr - 32;
  } 
  else
  {
    if (chr >= 192)
      chr = chr - 97;
    else
    {
      if (chr == SYMB_DEG_CODE)
        chr = FONT8_TABLE_LENGTH - 6;
      else
        return;
    }
      
  }
  
  for (x_pos = 0; x_pos < (FONT_SIZE_8_WIDTH); x_pos++)
  {
    for (y_pos = 0; y_pos < FONT_SIZE_8; y_pos++)
    {
      uint8_t pixel = font_size8[chr][x_pos] & (1<<y_pos);
      if (x_pos == (FONT_SIZE_8_WIDTH-1))
        pixel = 0;
      
      if (flags & LCD_INVERTED_FLAG) 
        if (pixel) pixel = 0; else pixel = 1;
      
      if (pixel) 
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
}

//x, y - size in pixel
void display_draw_char_size11(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags)
{
  uint16_t x_pos, y_pos;
  
  //decoding symbol
  if (chr >= 32 && chr <= 128)
  {
    chr = chr - 32;
  } 
  
  for (x_pos = 0; x_pos < (FONT_SIZE_11_WIDTH - 1); x_pos++)
  {
    for (y_pos = 0; y_pos < (FONT_SIZE_11-1); y_pos++)
    {
      if (font_size11[chr][y_pos] & (1<<(x_pos))) 
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
}

//x, y - size in pixel
void display_draw_char_size48(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags)
{
  uint16_t x_pos, y_pos;
  
  //decoding symbol
  if (chr >= 48 && chr <= 57)
  {
    chr = chr - 48;
  }
  else
  {
    return;
  }
  
  /*
  uint32_t byte_pos = 0;
  uint32_t byte_pos2 = 0;
  uint32_t start_offset = chr * (FONT_SIZE_48_WIDTH / 8 * FONT_SIZE_100);
  
  for (y_pos = 0; y_pos < FONT_SIZE_48; y_pos++)
  {
    byte_pos = start_offset + y_pos * (FONT_SIZE_48_WIDTH / 8);
    for (x_pos = 0; x_pos < FONT_SIZE_48_WIDTH; x_pos++)
    {
      byte_pos2 = byte_pos + x_pos / 8;
      
      if (CalibriBold32x48[byte_pos2] & (1<<(x_pos % 8))) 
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
  */
  
    uint16_t start = chr * FONT_SIZE_48 * (FONT_SIZE_48_WIDTH / 8);
  
  for (y_pos = 0; y_pos < (FONT_SIZE_48 - 1); y_pos++)
  {
    uint16_t line_num = start + y_pos * (FONT_SIZE_48_WIDTH / 8);
    uint32_t hor_line = (uint32_t)(CalibriBold32x48[line_num + 3] << 0) | 
                        (uint32_t)(CalibriBold32x48[line_num + 2] << 8) | 
                        ((uint32_t)CalibriBold32x48[line_num + 1] << 16) | 
                        ((uint32_t)CalibriBold32x48[line_num] << 24);
      
    for (x_pos = 0; x_pos < (FONT_SIZE_48_WIDTH - 1); x_pos++)
    {
      if (hor_line & (1 << (FONT_SIZE_48_WIDTH - x_pos - 1)))
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
}

//x, y - size in pixel
void display_draw_char_size100(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags)
{
  uint16_t x_pos, y_pos;
  
  //decoding symbol
  if (chr >= 48 && chr <= 57)
  {
    chr = chr - 48;
  }
  else
  {
    return;
  }
  

  uint32_t byte_pos = 0;
  uint32_t byte_pos2 = 0;
  uint32_t start_offset = chr * (64 / 8 * FONT_SIZE_100);
  
  for (y_pos = 0; y_pos < FONT_SIZE_100; y_pos++)
  {
    byte_pos = start_offset + y_pos * (64 / 8);
    for (x_pos = 0; x_pos < 64; x_pos++)
    {
      byte_pos2 = byte_pos + x_pos / 8;
      
      if (gen_font64x100[byte_pos2] & (1<<(x_pos % 8))) 
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
}

//x, y - size in pixel
void display_draw_char_size21(uint8_t chr, uint16_t x_start, uint16_t y_start, uint8_t flags)
{
  uint16_t x_pos, y_pos;
  
  //decoding symbol
  if (chr >= 32)
  {
    chr = chr - 32;
  } 
  
  uint32_t byte_pos = 0;
  uint32_t byte_pos2 = 0;
  uint32_t start_offset = chr * (FONT_SIZE_21_WIDTH / 8 * FONT_SIZE_21);
  
  for (y_pos = 0; y_pos < FONT_SIZE_21; y_pos++)
  {
    byte_pos = start_offset + y_pos * (FONT_SIZE_21_WIDTH / 8);
    for (x_pos = 0; x_pos < FONT_SIZE_21_WIDTH; x_pos++)
    {
      byte_pos2 = byte_pos + x_pos / 8;
      
      if (gen_font16x21[byte_pos2] & (1<<(x_pos % 8))) 
        display_set_pixel(x_start + x_pos, y_start + y_pos);
      else
        display_reset_pixel(x_start + x_pos, y_start + y_pos);
    }
  }
}

//Draw black bar
void draw_caption_bar(uint8_t height)
{
  uint16_t x_pos, y_pos;
  for (x_pos = 0; x_pos < LCD_RIGHT_OFFSET; x_pos++)
  {
    for (y_pos = 0; y_pos < height; y_pos++)
    {
        display_set_pixel(x_pos, y_pos);
    }
  }
}

void draw_black_line(uint16_t y)
{
  uint16_t x_pos;
  for (x_pos = 0; x_pos < LCD_RIGHT_OFFSET; x_pos++)
  {
    display_set_pixel(x_pos, y);
  }
}

void draw_black_line2(uint16_t x1, uint16_t x2, uint16_t y)
{
  uint16_t x_pos;
  for (x_pos = x1; x_pos < x2; x_pos++)
  {
    display_set_pixel(x_pos, y);
  }
}

//width must divede to 8!!
void draw_image(uint8_t *image_data, uint16_t x, uint16_t y)
{
  uint16_t width = image_data[0] + (uint16_t)image_data[1] * 256;
  uint16_t height = image_data[2] + (uint16_t)image_data[3] * 256;
  uint16_t bytes_in_line =  width / 8;
  
  for (uint16_t y_pos = 0; y_pos < height; y_pos++) 
  {
    for (uint16_t x_pos = 0; x_pos < width; x_pos++)
    {
      int32_t byte_offset = y_pos * bytes_in_line + (x_pos / 8) + 4;
      if (image_data[byte_offset] & (1 << (7 - (x_pos % 8)))) 
        display_set_pixel(x + x_pos, y + y_pos);
      else
        display_reset_pixel(x + x_pos, y + y_pos);
    }
  }
}

