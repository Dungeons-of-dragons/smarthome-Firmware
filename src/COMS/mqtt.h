#ifndef MQTT_H
#define MQTT_H


//Topics to be published
const char* Temperature = "/sensors/temperature/";
const char* Humidity = "/sensors/humidity/";
const char* Watts = "/sensors/watts/";
const char* Current = "/sensors/current/";
const char* Gas = "/sensors/gas/";

void mqtt_setup(); 
void callback();

#endif