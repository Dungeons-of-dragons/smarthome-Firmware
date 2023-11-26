#include <Arduino.h>
#include "defs.h"

volatile boolean gaspresent = false;

bool Gas_detected()
{
  pinMode(blue, OUTPUT);
  pinMode(MQ2_INPUT, INPUT);
  int sensorout = digitalRead(MQ2_INPUT);
  if (sensorout == 1)
  {
    digitalWrite(blue, HIGH);
    gaspresent = true;
    return true;
  }
  else if (sensorout == 0)
  {
    digitalWrite(blue, LOW);
    gaspresent = false;
    return false;
  }
  return false; 
}
