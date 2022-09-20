# Pico OLED Docker
Pico OLED is an add-on for Raspberry Pi-based retro gaming systems. It connects over USB and displays the current game's title + box art or Raspberry Pi system statistics (selectable with a push button) on a 1.5" 128x128 color SPI OLED. It first displays a splashscreen on boot, followed by various system stats. When a game is run, the OLED display switches to the game image and can cycle between either the game image or system vector. Upon closing the game, the system stats will again be displayed. 

Pico OLED is designed specifically for the Retro Lite CM4 dock, however should be compatible with EmulationStation/RetroPie/other frontends by changing the location of scraped metadata/image files. 

## Features
- [x] RP2040 ($1)
- [x] 1.5" 128x128 SSD1351 SPI OLED ($13)
- [x] 3D-printed housing with external USB cable
- [x] Multifunction push button connected to the Pico to switch between EmulationStation/pegasus scraped metadata, marquee images, system images and general Raspberry Pi stats, such as RAM usage, disc space, CPU frequencies, IP address, etc. 

## To-do
- [x] Detect current game using `runcommand`
- [x] Add Retrolite CM4 splashscreen on boot
- [x] Rename system vectors and match to system outputs from runcommand
- [x] Downscale + convert screenshot and wheel images to 128x128 RGB565 on Pi 4 (Python)
- [x] Detect RP2040 by Product/Vendor IDs (VID/PIDs) 
- [ ] Identify how to perform hardware scrolling of text on the SSD1351 for game descriptions 
- [ ] Send image bitstream and system stats to RP2040 over USB 
- [ ] Read the bit depth of image (i.e 16, 24, 32-bit) and convert to an RGB565 on the fly 
- [ ] Display either system status (RAM usage, CPU load, temp, etc.) or box art on OLED (select with push button)
- [ ] Implement a 30 timeout which writes black to the OLED with no user input and wakes up on a button press
