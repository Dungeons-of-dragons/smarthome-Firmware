
// this file outlines the functions of the mqtt client.
#include "WiFi.h"
#include "arduino_secrets.h"
#include "defs.h"
#include "mqtt.h"

/**
 * @brief This function is executed when a message is received for subscribed topic.
 * 
 * @param topic This is the topic subscribed into
 * @param payload data received
 * @param length length of data received
 */
void callback(char* topic, byte* payload, unsigned int length){
    for (int i = 0; i < length; i++){
        Serial.println((char)payload[i]);
    }
}

/**
 * @brief This function sets up the client server
 * 
 */
void mqtt_setup(){
    const char* mqtt_serv = IP_ADDRESS;
    client.setServer(mqtt_serv, port);
    client.setCallback(callback);
}

/**
 * @brief This function checks if client and server is connected and reconnects if necessary.
 * and subscribe to any ncessary topics.
 * 
 * @param mqttUser This is the name of the mqtt user
 * @param mqttPassword THis holds the password of the user.
 */
void reconnect(char *mqttUser, char* mqttPassword){
    while(!client.connected()){
    Serial.println("MQTT not connected ... trying to connect");

    if(client.connect("ESP32Client", mqttUser, mqttPassword)){
      Serial.println("Connected!");
      client.subscribe(Lights);
    }
    else{
      Serial.println("Failed code =");
      Serial.println(client.state()); // gives reason why connection is not achieved
      //To be tried again after 5sec
    }
  }
}


