#include "pir.h"



/**
 * The function "movement_detection" prints "Motion detected" to the serial monitor, turns on the red
 * LED and turns off the green LED, sets the variable "motiondetected" to true, and records the current
 * time in the variable "last_trigger".
 */
void IRAM_ATTR movement_detection()
{
  ets_printf("Motion detected\n "); // callbacks should not have serial prints within them 
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW); 
  motiondetected = true;
}


/**
 * The function sets up the motion sensor and initializes the necessary pins and interrupts.
 */
void motion_setup(){
  pinMode(PIR_PIN, INPUT_PULLUP);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(green, HIGH); 
  digitalWrite(red, LOW);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), movement_detection, LOW); // @bug should use rising not LOW. 
}


