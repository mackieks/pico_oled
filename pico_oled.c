#include "pico_oled.h"

extern uint8_t oledFB[96 * 64 * 2];

int main() {
  stdio_init_all();

  spi_init(SSD1331_SPI, SSD1331_SPEED);
  spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);

  ssd1331_init();

  sleep_ms(2500);

  clearSSD1331();
  updateSSD1331();

  uint8_t c = 0;
  // uint32_t i = 0;

  // while(1){
  //   int c = getchar_timeout_us(100);
  //   if (c != PICO_ERROR_TIMEOUT && i < sizeof(oledFB)) 
  //     oledFB[i++] = (c & 0xFF);
  //   else break;
  // }

  for (uint32_t i = 0; i < sizeof(oledFB); i++) {
            while ((c = (uint8_t) getchar_timeout_us(0)) == PICO_ERROR_TIMEOUT) {
                busy_wait_us_32(1);
            }
            oledFB[i] = c;
  }

  updateSSD1331();

  sleep_ms(8);

  return(1);

}



