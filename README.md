# Thermal Printer Project

This project is a software implementation for controlling the Adafruit thermal printer guts. The necessary library to run the code is included.

## Requirements/Materials
- Adafruit Thermal Printer Guts (link: https://www.adafruit.com/product/2753)
- A ESP8266 NodeMCU Microcontroller
- Jumper Wires
- Arduino IDE or Platform IO Embedded Environment in VS Code
- Necessary Hardware connections

## Installation and Implementation
1. Download .ino file to local machine
2. Use Platform IO or Arduino IDE to install the thermal printer library
3. Open the .ino file with either development platform
4. Make necessary corrections to code (Wifi, hardware connection info)
5. Upload to Microcontroller and use serial monitor info for printing

## How it Works:
1. Microcontroller connects to Wifi
2. A web server is created to input printing info (ip address provided by serial monitor)
3. Enter printing text and submit
4. Thermal Printer prints the text on receipt paper

# Contact
If you have any issues or suggestions, please contact me on my github page.
