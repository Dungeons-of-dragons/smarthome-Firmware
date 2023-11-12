#include "defs.h"


static volatile boolean motiondetected = false;
static const long interval = 5000;
static unsigned long current_time = millis();
static unsigned long last_trigger = 0;

void IRAM_ATTR movement_detection();
void motion_setup(); 