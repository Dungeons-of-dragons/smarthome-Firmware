#include <Arduino.h>
#include "defs.h"
#include "dth11.h"
#include "door.h"
#include "MQ2.h"

volatile boolean gaspresent = false;
volatile boolean motiondetected = false; 

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  float humidity = readhumidity();
  float temperature = readtemp();
}

