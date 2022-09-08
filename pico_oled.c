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

  char c[10] = {0};

  while(1){
    for(uint32_t i = 0; i < sizeof(oledFB); i++){
      oledFB[i] = getchar_timeout_us(0xffffffff);
    }

    updateSSD1331();

    sleep_ms(8);
  }

  return(1);

}



