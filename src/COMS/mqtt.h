#ifndef MQTT_H
#define MQTT_H


//Topics to be published
#define Temperature "/sensors/temperature/"
#define Humidity  "/sensors/humidity/"
#define Watts "/sensors/watts/"
#define Current "/sensors/current/"
#define Gas "/sensors/gas/"
#define Lights "/user/lights/"

const int port = 1883; //assign port number
void callback(char* topic, byte* payload, unsigned int length);
void mqtt_setup();
void reconnect(); 


#endif