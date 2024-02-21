
// // this file outlines the functions of the mqtt client.
// #include "WiFi.h"
// #include "arduino_secrets.h"
// #include "defs.h"
// #include "mqtt.h"


// WiFiClient espClient;
// PubSubClient client(espClient);
// /**
//  * @brief This function is executed when a message is received for subscribed topic.
//  * 
//  * @param topic This is the topic subscribed into
//  * @param payload data received
//  * @param length length of data received
//  */
// void callback(char* topic, byte* payload, unsigned int length){
//    String message = "";
//     for (int i = 0; i < length; i++) {
//         message += (char)payload[i];
//     }

//     // Check if the topic is the LED topic
//     if (strcmp(topic, Lights) == 0) {
//         // Process the LED command
//         if (message == "ON") {
//             // Turn on the LED
//             digitalWrite(blue, HIGH);
//         } else if (message == "OFF") {
//             // Turn off the LED
//             digitalWrite(blue, LOW);
//         }
//     }
// }

// /**
//  * @brief This function sets up the client server
//  * 
//  */
// void mqtt_setup(){
//     const char* mqtt_serv = IP_ADDRESS;
//     client.setServer(mqtt_serv, port);
//     client.setCallback(callback);
//     client.connect("clientid",MQTT_USER_ARRAY, MQTT_PASS_ARRAY);
// }

// /**
//  * @brief This function checks if client and server is connected and reconnects if necessary.
//  * and subscribe to any ncessary topics.
//  * 
//  * @param mqttUser This is the name of the mqtt user
//  * @param mqttPassword THis holds the password of the user.
//  */
// void reconnect(const char *mqttUser, const char* mqttPassword){
//     while(!client.connected()){
//     Serial.println("MQTT not connected ... trying to connect");

//     if(client.connect("clientid", mqttUser, mqttPassword)){
//       Serial.println("Connected!");
//       client.subscribe(Lights);
//     }
//     else{
//       Serial.println("Failed code =");
//       Serial.println(client.state()); // gives reason why connection is not achieved
//       //To be tried again after 5sec
//       delay(5000);
//     }
//   }
// }


