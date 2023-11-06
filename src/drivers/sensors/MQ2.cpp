#include <Arduino.h> 
const int GAS_LED = 4;
const int MQ2_INPUT = 2; 

void setup() {
  Serial.begin(115200);  
  pinMode(GAS_LED, OUTPUT);
}

bool Gas_detected(){
  int sensorout = analogRead(MQ2_INPUT); 
    if (sensorout > 1800) {   
    Serial.println("Gas");  
    digitalWrite (GAS_LED, HIGH) ; 
      return true; 
  }
  else {
    Serial.println("No Gas");
    digitalWrite (GAS_LED, LOW) ; 
    return false; 
  }
}
  
