# Pico OLED Docker
Pico OLED is an add-on for Raspberry Pi-based retro gaming systems. It connects over USB and displays the current game's title + box art or Raspberry Pi system statistics (selectable with a push button) on a 1.5" 128x128 color SPI OLED. It first displays a splashscreen on boot, followed by various system stats. When a game is run, the OLED display switches to the game image and can cycle between either the game image or system vector. Upon closing the game, the system stats will again be displayed. 

Pico OLED is designed specifically for the Retro Lite CM4 dock, however should be compatible with EmulationStation/RetroPie/other frontends by changing the location of scraped metadata/image files. 

## Features
- [x] RP2040 ($1)
- [x] 1.5" 128x128 SSD1351 SPI OLED ($13)
- [x] 3D-printed housing with external USB cable
- [x] Multifunction pushbutton to switch between EmulationStation/pegasus scraped metadata/image locations

## To-do
- [x] Detect current game using `runcommand`
- [x] Add Retrolite CM4 splashscreen on boot
- [x] Rename system vectors and match to system outputs from runcommand
- [x] Downscale + convert screenshot and wheel images to 128x128 RGB565 on Pi 4 (Python)
- [ ] Detect RP2040 by Product ID (COM port?)
- [ ] Send image bitstream and system stats to RP2040 over USB 
- [ ] Display either system status (RAM usage, CPU load, temp, etc.) or box art on OLED (select with push button)
