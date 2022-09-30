#include <stdio.h>
#include <string.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "font.h"

#define SSD1351_SPI spi0
#define SSD1351_SPEED  62500000  // 62.5MHz
#define SCK 2
#define MOSI 3

#define PICO 0
#define TINY2040 1

#if PICO
#define DC 14
#define RST 13

#elif TINY2040
#define DC 5
#define RST 4
#endif

#define OLED_W 128
#define OLED_H 128

#define OLED_FLIP 0

// SSD1351 Commands
#define SSD1351_CMD_SETCOLUMN 0x15      ///< See datasheet
#define SSD1351_CMD_SETROW 0x75         ///< See datasheet
#define SSD1351_CMD_WRITERAM 0x5C       ///< See datasheet
#define SSD1351_CMD_READRAM 0x5D        ///< Not currently used
#define SSD1351_CMD_SETREMAP 0xA0       ///< See datasheet
#define SSD1351_CMD_STARTLINE 0xA1      ///< See datasheet
#define SSD1351_CMD_DISPLAYOFFSET 0xA2  ///< See datasheet
#define SSD1351_CMD_DISPLAYALLOFF 0xA4  ///< Not currently used
#define SSD1351_CMD_DISPLAYALLON 0xA5   ///< Not currently used
#define SSD1351_CMD_NORMALDISPLAY 0xA6  ///< See datasheet
#define SSD1351_CMD_INVERTDISPLAY 0xA7  ///< See datasheet
#define SSD1351_CMD_FUNCTIONSELECT 0xAB ///< See datasheet
#define SSD1351_CMD_DISPLAYOFF 0xAE     ///< See datasheet
#define SSD1351_CMD_DISPLAYON 0xAF      ///< See datasheet
#define SSD1351_CMD_PRECHARGE 0xB1      ///< See datasheet
#define SSD1351_CMD_DISPLAYENHANCE 0xB2 ///< Not currently used
#define SSD1351_CMD_CLOCKDIV 0xB3       ///< See datasheet
#define SSD1351_CMD_SETVSL 0xB4         ///< See datasheet
#define SSD1351_CMD_SETGPIO 0xB5        ///< See datasheet
#define SSD1351_CMD_PRECHARGE2 0xB6     ///< See datasheet
#define SSD1351_CMD_SETGRAY 0xB8        ///< Not currently used
#define SSD1351_CMD_USELUT 0xB9         ///< Not currently used
#define SSD1351_CMD_PRECHARGELEVEL 0xBB ///< Not currently used
#define SSD1351_CMD_VCOMH 0xBE          ///< See datasheet
#define SSD1351_CMD_CONTRASTABC 0xC1    ///< See datasheet
#define SSD1351_CMD_CONTRASTMASTER 0xC7 ///< See datasheet
#define SSD1351_CMD_MUXRATIO 0xCA       ///< See datasheet
#define SSD1351_CMD_COMMANDLOCK 0xFD    ///< See datasheet

float cos_32s(float x);
float cos32(float x);
float sin32(float x);
double atan66(double x);
double atan_66s(double x);

void fast_hsv2rgb_32bit(uint16_t, uint8_t, uint8_t, uint8_t *, uint8_t *, uint8_t *);

void SSD1351WriteCommand(const uint8_t data);

void SSD1351WriteCommands(const uint8_t* data, uint num);

void SSD1351WriteData(const uint8_t data);

void setPixelSSD1351(const uint8_t x, const uint8_t y, const uint16_t color);

void drawLine(int x1, int x2, int y, uint16_t color);

void hagl_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void fillCircle(int x0, int y0, int r, uint16_t color);

void drawCursor(int iy, uint16_t color);

void drawToggle(int iy, uint16_t color, bool on);

void putLetter(int ix, int iy, int index, uint16_t color);

void putString(char* text, int ix, int iy, uint16_t color);

void drawEllipse(int xc, int yc, int xr, int yr, int angle);

void clearSSD1351(void);

void updateSSD1351(void);

void SSD1351_init();