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
#include "COMS/influx.h"


extern char ssid[];
extern char pass[]; //network password saved in a secrets file 

static int protothreadReadDHT(struct pt *pt);
static int protothreaddetectgas(struct pt *pt);
static int protothreaddetectmotion(struct pt *pt);
static int protothreadmeasurevoltage(struct pt *pt);
static int protothreadauth(struct pt *pt);
static int protothreadreconnect(struct pt *pt);




#endif