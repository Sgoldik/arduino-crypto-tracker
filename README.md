
# arduino-crypto-tracker
It works only with the price of bitcoin (coindesk API), in the future it is planned to transfer to the coinmarketcap API.

## Components
* Arduino Uno
* ESP8266 (ESP01)
* 1602A LCD
* Wires

## Libs
* ESP8266WiFi
* ArduinoJson
* SoftwareSerial
* LiquidCrystal_I2C

## ESP8266 Firmware
Connection diagram for ESP8266 firmware:
|ESP8266|ARDUINO UNO  |
|--|--|
|GND  |GND  |
|VIN|3.3v  |
|ENABLE|3.3v  |
|TX|TX  |
|RX|RX  |
|GPIO0|GND  |

> It is also necessary to close reset and gnd on the arduino.

Next, you need to hold down the reset button on the arduino and connect the arduino to the PC, after you hear that the USB-device is connected, you can release the button.

To update the ESP8266 firmware, you need to perform a number of manipulations with the Arduino IDE development environment.
1. Open the **/api/api.ino** file, configure the wi-fi network
2. Open **File** -> **Preferences** -> paste the link into the **Additional Board Manager URLs** http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Open **Tools** -> **Boards** -> **ESP8266 Boards** -> **Generic ESP8266 Module**
4. Install **ArduinoJson** library (**Tools** -> **Manage Libraries** -> Find and install)
5. Compile and upload it to ESP8266.
6. Profit!

## Final connection diagram
Connection diagram for ESP8266 firmware:
|ESP8266|ARDUINO UNO  |
|--|--|
|GND  |GND  |
|3V3|3.3v  |
|ENABLE|3.3v  |
|TX|Serial 3  |
|RX|Serial 2  |

|LCD 1602A|ARDUINO UNO  |
|--|--|
|GND  |GND  |
|VCC|5v  |
|SDA|A4  |
|SCL|A5 |

Update Arduino Uno firmware:

1. Open the **/main/main.ino** file
2. Open **Tools** -> **Boards** -> **Arduino AVR Board** -> **Arduino Uno**
3. Install **LiquidCrystal_I2C** library (**Tools** -> **Manage Libraries** -> Find and install)
4. Compile and upload it to ESP8266.
5. Profit!