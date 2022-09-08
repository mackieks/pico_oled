## Description
The Pico OLED project's goal is to display the current running game's title box art (in the form of a screenshot + wheel) scraped from Skyscraper, as well as toggle between on screen Pi statistics with a push button. 
Desgined to work with the Retro Lite CM4 dock, however should work with EmulationStation/RetroPie/other frontend. 

The Pi 4 will detect a specific PID sub-device and then send over a framebuffer containing the boxart of the game currently being played. 

## Planned Features/To-Do
- RP2040 MCU 
- 128x128, General 1.5inch OLED, driven by the RP2040 over SPI bus
- 3D Printed Housing 
- Compression of both screenshot and wheel images to 128x128 pixels handled by Raspberry Pi 4. Image data is to be sent to the RP2040 to be sent over UART
- Transfer 32kb images to the RP2040 (264kb) of RAM, ensuring that previous image is removed from memory when new game is launched 
- Conversion of images to RGB565 arrays to be read by the RP2040
- Identify a way to read game current being played on the Pi 4 (from runcommand) and search for the relevant related image files to the ROM file to be compressed, converted and sent to the Pi 
- Switch between on-screen box art and Pi 4 with a push button 
- Entirely written in Python (Pi 4) & C (RP2040)

Work in progress...
