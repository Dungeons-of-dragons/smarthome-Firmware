#ifndef MAIN_H
#define MAIN_H


#include <Arduino.h>
#include "defs.h"
#include "DHT11/dht11.h"
#include "Door/door.h"
#include "MQ2/MQ2.h"
#include "arduino_secrets.h"
#include "WiFi.h"
#include "pir.h"
#include "acs.h"

static boolean user_in = false; 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS; //network password saved in a secrets file 

#endif