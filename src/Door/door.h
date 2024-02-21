#ifndef DOOR_H
#define DOOR_H

#include "Arduino.h"

#include "defs.h"

void door_initialize();
void check_for_card();
bool card_authorization();
void display_tag();

#define doorinterval 22000

#endif

