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

WiFiClient espClient;
PubSubClient client(espClient);

const int port = 1883; //assign port number
void mqtt_setup();
void reconnect(char *mqttUser, char* mqttPassword); 
void callback(char* topic, byte* payload, unsigned int length);

#endif