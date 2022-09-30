#include "pico_oled.h"

#define TEXT 1
#define IMAGE 2

extern uint8_t oledFB[127 * 127 * 2];
char str[7];
uint mode = 0;

int main()
{
  stdio_init_all();

  spi_init(SSD1351_SPI, SSD1351_SPEED);
  spi_set_format(SSD1351_SPI, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);

  SSD1351_init();

  sleep_ms(2500);

  clearSSD1351();
  updateSSD1351();
  clearSSD1351();

  while (1)
  {
    uint8_t c = 0;
    uint32_t i = 0;

    clearSSD1351();

    // get mode
    while (1){
      int c = getchar_timeout_us(0);
      if (c != PICO_ERROR_TIMEOUT){
        if (c == '1')
          mode = TEXT;
        else if (c == '2')
          mode = IMAGE;
        break;
      }
    }

    if (mode == TEXT){
      while (i < 6){
        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT)
        {
          str[i] = c;
          i++;
        }
      }
      clearSSD1351();
      putString(str, 0, 0, 0xffff);
      updateSSD1351();
    }

    else if (mode == IMAGE){
      while (i < sizeof(oledFB)){
        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT){
          oledFB[i] = c;
          i++;
        }
      }
      updateSSD1351();
    }
  }
  // updateSSD1351();
}