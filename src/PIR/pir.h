#ifndef PIR_H
#define PIR_H

#include "defs.h"


static volatile boolean motiondetected = false;
static const long interval = 5000;

void IRAM_ATTR movement_detection();
void motion_setup(); 

#endif 