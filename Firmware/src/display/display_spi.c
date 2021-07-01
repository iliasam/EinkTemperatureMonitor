
#include "config.h"
#include "display_spi.h"

void display_spi_send_byte(uint8_t data);

//todo - use dwt
void lcd_delay(unsigned long p) 
{
  unsigned long i;
  for (i = 0; i < p; i++)
    ;
}

// инициализация выводов МК для работы с дисплеем
void dispaly_spi_init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_SCK_PIN;
  GPIO_Init(DISPLAY_SPI_SCK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_MOSI_PIN;
  GPIO_Init(DISPLAY_SPI_MOSI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_DC_PIN;
  GPIO_Init(DISPLAY_SPI_DC_GPIO, &GPIO_InitStructure);
  GPIO_SetBits(DISPLAY_SPI_DC_GPIO, DISPLAY_SPI_DC_PIN);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_CS_PIN;
  GPIO_Init(DISPLAY_SPI_CS_GPIO, &GPIO_InitStructure);
  GPIO_SetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = DISPLAY_BUSY_PIN;
  GPIO_Init(DISPLAY_BUSY_GPIO, &GPIO_InitStructure);
}

void dispaly_spi_deinit(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_SCK_PIN;
  GPIO_Init(DISPLAY_SPI_SCK_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_MOSI_PIN;
  GPIO_Init(DISPLAY_SPI_MOSI_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_DC_PIN;
  GPIO_Init(DISPLAY_SPI_DC_GPIO, &GPIO_InitStructure);
  GPIO_SetBits(DISPLAY_SPI_DC_GPIO, DISPLAY_SPI_DC_PIN);
  
  GPIO_InitStructure.GPIO_Pin = DISPLAY_SPI_CS_PIN;
  GPIO_Init(DISPLAY_SPI_CS_GPIO, &GPIO_InitStructure);
  GPIO_SetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = DISPLAY_BUSY_PIN;
  GPIO_Init(DISPLAY_BUSY_GPIO, &GPIO_InitStructure);
}

void display_spi_send_byte(uint8_t data)
{
  for (uint8_t i = 0; i < 8; i++) 
  {
    GPIO_ResetBits(DISPLAY_SPI_SCK_GPIO, DISPLAY_SPI_SCK_PIN);
    lcd_delay(2);
    
    if (data & 0x80)
      GPIO_SetBits(DISPLAY_SPI_MOSI_GPIO, DISPLAY_SPI_MOSI_PIN);
    else
      GPIO_ResetBits(DISPLAY_SPI_MOSI_GPIO, DISPLAY_SPI_MOSI_PIN);
    
    lcd_delay(2);
    GPIO_SetBits(DISPLAY_SPI_SCK_GPIO, DISPLAY_SPI_SCK_PIN);
    lcd_delay(2);
    data = data << 1;
  }
}

// Send data to display
void display_spi_write_data(unsigned char data) 
{
  GPIO_ResetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  display_spi_send_byte(data);
  GPIO_SetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
}

// Send data to display
void display_spi_write_data_n(uint8_t* data, uint16_t len)
{
  GPIO_ResetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  for (uint16_t i = 0; i < len; i++)
  {
    display_spi_send_byte(*data++);
  }
  GPIO_SetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
}

// Send command to display
void display_spi_write_cmd(unsigned char command) 
{
  GPIO_ResetBits(DISPLAY_SPI_DC_GPIO, DISPLAY_SPI_DC_PIN);
  GPIO_ResetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  display_spi_send_byte(command);
  GPIO_SetBits(DISPLAY_SPI_CS_GPIO, DISPLAY_SPI_CS_PIN);
  GPIO_SetBits(DISPLAY_SPI_DC_GPIO, DISPLAY_SPI_DC_PIN);
}

uint8_t display_spi_is_busy(void)
{
  if (GPIO_ReadInputDataBit(DISPLAY_BUSY_GPIO, DISPLAY_BUSY_PIN) == Bit_SET)
    return 1;
  else
    return 0;
}


