#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>


//Topics to be published
#define Temperature "/sensors/temperature/"
#define Humidity  "/sensors/humidity/"
#define Watts "/sensors/watts/"
#define Volt "/sensors/current/"
#define Gas "/sensors/gas/"
#define PIR "/sensors/motion"

//Topics to be subscribed into
#define Lights "/user/lights/"

extern WiFiClient espClient;
extern PubSubClient client;

const int port = 1885; //assign port number
void mqtt_setup();
void reconnect(const char *mqttUser, const char* mqttPassword); 
void callback(char* topic, byte* payload, unsigned int length);

#endif