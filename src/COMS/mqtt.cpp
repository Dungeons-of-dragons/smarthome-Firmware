// this file outlines the functions of the mqtt client.
#include "arduino_secrets.h"
#include "defs.h"
#include "WiFi.h"
#include "PubSubClient.h"


WiFiClient espClient;
PubSubClient client(espClient);

