#ifndef MAIN_H
#define MAIN_H


#include <Arduino.h>
#include "defs.h"
#include "DHT11/dht11.h"
#include "Door/door.h"
#include "MQ2/MQ2.h"
#include "arduino_secrets.h"
#include "WiFi.h"
#include "PIR/pir.h"
#include "ACS712/acs.h"

static boolean user_in = false; 


extern MFRC522 mfrc522;  
extern LiquidCrystal_I2C lcd;

extern char ssid[];
extern char pass[];

void displaydht(float temp, float humidity);

#endif