#include "stdint.h"
#include "display_functions.h"
#include "draw_monitor.h"
#include "hardware.h"
#include "stdlib.h"
#include "stdio.h"

#include "deg_symbol.h"
#include "no_connection_symbol.h"
#include "low_batt_symbol.h"

/* Private typedef -----------------------------------------------------------*/
#define BIG_MINUS_Y     100
#define BIG_TEMP_Y      50

/* Private variables ---------------------------------------------------------*/
displayed_params_t displayed_params;

/* Private function prototypes -----------------------------------------------*/
void draw_temprature(void);
void draw_big_minus(uint8_t x_start, uint16_t length);
void draw_temprature_internal(void);
void draw_small_minus(uint8_t x_start, uint8_t y_start);
void draw_header(void);
void draw_progress(void);


/* Private functions ---------------------------------------------------------*/

void draw_monitor(void)
{
  display_clear_framebuffer();
  
  draw_header();

  if (displayed_params.no_connection_flag)
  {
    draw_image((uint8_t*)no_connection_symbol, 50, 50);
    display_draw_string("Õ≈“ —¬ﬂ«» !", 20, 160, FONT_SIZE_21, 0);
    draw_progress();
    display_update();
    return;
  }
  
  draw_temprature();
  draw_temprature_internal();
  draw_progress();

  display_update();//long!
}

void draw_progress(void)
{
  uint16_t progress_length = 
    (displayed_params.update_counter + 1) * DISPLAY_WIDTH / MAX_UPDATE_COUNTER;
  
  draw_black_line2(0, progress_length, 198);
  draw_black_line2(0, progress_length, 199);
}

void draw_header(void)
{
  if (displayed_params.low_batt_flag)
  {
    draw_image((uint8_t*)low_batt_symbol, 10, 2);
    char tmp_str[10];
    sprintf(tmp_str, "%.1fV", displayed_params.battery_voltage);
    display_draw_string(tmp_str, 90, 10, FONT_SIZE_21, 0);
  }
  else
  {
    if (displayed_params.is_charging_flag)
      display_draw_string("«¿–ﬂƒ ¿", 15, 10, FONT_SIZE_21, 0);
    else
      display_draw_string("“≈Ãœ≈–¿“”–¿", 15, 10, FONT_SIZE_21, 0);
  }
}

void draw_temprature(void)
{
  uint8_t temperature_abs = abs(displayed_params.ext_temperature_deg);
  char tmp_str[10];
  sprintf(tmp_str, "%d", temperature_abs);
  
  if (temperature_abs < 10)
  {
    display_draw_string(tmp_str, 76, BIG_TEMP_Y, FONT_SIZE_100, 0);
    if (displayed_params.ext_temperature_deg < 0)
      draw_big_minus(40, 30);
    draw_image((uint8_t*)deg_symbol, 144, BIG_TEMP_Y);
  }
  else
  {
    //abs > 10
    if (displayed_params.ext_temperature_deg > 0)
    {
      display_draw_string(tmp_str, 18, BIG_TEMP_Y, FONT_SIZE_100, 0);
      draw_image((uint8_t*)deg_symbol, 154, BIG_TEMP_Y);
    }
    else
    {
      display_draw_string(tmp_str, 33, BIG_TEMP_Y, FONT_SIZE_100, 0);
      draw_big_minus(5, 22);
      draw_image((uint8_t*)deg_symbol, 168, BIG_TEMP_Y);
    }
  }
}

void draw_temprature_internal(void)
{
  uint8_t temperature_abs = abs(displayed_params.temperature1_deg);
  char tmp_str[10];
  sprintf(tmp_str, "%d", temperature_abs);
  
  if (temperature_abs < 10)
  {
    display_draw_string(tmp_str, 92, 151, FONT_SIZE_48, 0);
    if (displayed_params.temperature1_deg < 0)
      draw_small_minus(70, 174);
  }
  else
  {
    display_draw_string(tmp_str, 60, 151, FONT_SIZE_48, 0);
    if (displayed_params.temperature1_deg < 0)
      draw_small_minus(40, 174);
  }
  display_draw_string("C", 124, 176, FONT_SIZE_21, 0);
}

void draw_big_minus(uint8_t x_start, uint16_t length)
{
  uint16_t ypos = BIG_MINUS_Y;
  draw_black_line2(x_start, x_start + length, ypos++);
  draw_black_line2(x_start - 1, x_start + length + 1, ypos++);
  draw_black_line2(x_start - 2, x_start + length + 2, ypos++);
  draw_black_line2(x_start - 2, x_start + length + 2, ypos++);
  draw_black_line2(x_start - 2, x_start + length + 2, ypos++);
  draw_black_line2(x_start - 2, x_start + length + 2, ypos++);
  draw_black_line2(x_start - 1, x_start + length + 1, ypos++);
  draw_black_line2(x_start, x_start + length, ypos++);
}

void draw_small_minus(uint8_t x_start, uint8_t y_start)
{
  uint16_t ypos = y_start;
  draw_black_line2(x_start, x_start + 15, ypos++);
  draw_black_line2(x_start, x_start + 15, ypos++);
  draw_black_line2(x_start, x_start + 15, ypos++);
}