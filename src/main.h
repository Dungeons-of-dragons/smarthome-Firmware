#include <Arduino.h>
#include "defs.h"
#include "dht11.h"
#include "door.h"
#include "MQ2.h"
#include "arduino_secrets.h"
#include "WiFi.h"
#include "PIR/pir.h"

// volatile boolean gaspresent = false;
boolean user_in = false; 


char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS; //network password saved in a secrets file 

