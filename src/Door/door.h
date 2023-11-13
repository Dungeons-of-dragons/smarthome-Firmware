#ifndef DOOR_H
#define DOOR_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Arduino.h"


#include "defs.h"

void initialize();
void check_for_card();
bool card_authorization();
void display_tag();

#endif

