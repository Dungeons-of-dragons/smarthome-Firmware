#ifndef DEFS_H
#define DEFS_H 

#include "Arduino.h"

// Gpios 6, 7, 8, 9, 10 and 11 are a no go for ESP32 to use

//pinout definitions 
#define DHT11PIN 16
#define MQ2_INPUT 2
#define GAS_LED 12
#define CURRENT_PIN 34

// RFID card reader pins
#define SS_PIN 21
#define RST_PIN 22

// Led pinouts 
#define red 13
#define blue 14
#define green 12


#define lock_pin 18
#define buzzer 25


#define PIR_PIN 32

#endif

