#include <Arduino.h> 
#include "defs.h"

volatile boolean gaspresent = false;

bool Gas_detected(){
  pinMode(blue, OUTPUT);
  int sensorout = analogRead(MQ2_INPUT); 
    if (sensorout > 1000) {   
    digitalWrite (blue, HIGH); 
    gaspresent = true;

      return true; 
  }
  else {
    digitalWrite (blue, LOW) ; 
    gaspresent = false; 
    return false; 
  }
}
  
