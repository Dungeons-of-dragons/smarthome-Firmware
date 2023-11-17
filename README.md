
# Firmware

A repo for all firmware development for the esp32

Note: Use ESP32 core 2.0.7 due to the MFRC522 library

## arduino_secrets.h header file

The arduino_secrets.h library is a library that holds sensitive information. Its content are not pushed to github as it is under the .gitignore file.

To setup your arduino_secrets.h file, create an 'arduino_secrets.h' file under the include directory. Populate the file with the following content:

```#ifndef ARDUINO_SECRETS_H
#define ARDUINO_SECRETS_H

#define SECRET_SSID "" //enter your wifi SSID
#define SECRET_PASS ""// enter your WiFi password
#define IP_ADDRESS "" // enter your IP address
#define MQTT_USER "" // enter user name
#define MQTT_PASS "" // enter mqtt password

#endif```
