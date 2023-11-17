#ifndef MAIN_H
#define MAIN_H


#include <Arduino.h>
#include "defs.h"
#include "DHT11/dht11.h"
#include "Door/door.h"
#include "MQ2/MQ2.h"
#include "arduino_secrets.h"
#include <WiFi.h>
#include "PIR/pir.h"
#include "ACS712/acs.h"
#include "LCD/LCD.h"
#include "COMS/mqtt.h"


boolean user_in = false; 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS; //network password saved in a secrets file 

#endif