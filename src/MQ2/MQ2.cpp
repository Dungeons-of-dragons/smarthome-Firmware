#include <Arduino.h> 
#include "defs.h"

volatile boolean gaspresent = false;

bool Gas_detected(){
  pinMode(GAS_LED, OUTPUT);
  int sensorout = analogRead(MQ2_INPUT); 
    if (sensorout > 1800) {   
    Serial.println("Gas");  
    digitalWrite (GAS_LED, HIGH); 
    gaspresent = true;

      return true; 
  }
  else {
    Serial.println("No Gas");
    digitalWrite (GAS_LED, LOW) ; 
    gaspresent = false; 
    return false; 
  }
}
  
