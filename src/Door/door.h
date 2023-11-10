#ifndef DOOR_H
#define DOOR_H

#include "Arduino.h"

#include "defs.h"

void initialize();
void check_for_card();
bool card_authorization();
void display_tag();

#endif

