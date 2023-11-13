#include "main.h"
#include <pt.h> 

// declare three protothreads
static struct pt ptreaddht, ptdetectgas, pt3;


// First protothread function to read DHT  every 5 second
/**
 * The function "protothreadReadDHT" reads temperature and humidity values from a sensor every 5
 * seconds and prints them to the serial monitor.
 * 
 * @param pt The parameter "pt" is a pointer to a struct of type "pt". This struct is used to implement
 * a protothread, which is a lightweight cooperative multitasking mechanism. The protothreadReadDHT
 * function is defined to take a pointer to this struct as a parameter so that it can use it
 */
static int protothreadReadDHT(struct pt *pt)
{
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > 5000);
    float temp = readtemp();
    float humid = readhumidity(); 
    Serial.printf("temp: %.3f, humid: %.3f\n ", temp, humid);
  }
  PT_END(pt);
}


//second protothread to check for gas presence
static int protothreaddetectgas(struct pt *pt){
  static unsigned long lastTimeread = 0; 
  PT_BEGIN(pt);
  while(1){
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, Gas_detected);
    ets_printf("gas detected");
    // insert user functions to signal the user 
    PT_WAIT_UNTIL(pt, !Gas_detected);
    //insert user code to notify user 
  }
  PT_END(pt);
}



// Use events to avoid blocking code
/**
 * The function "connected_to_ap" prints a message indicating that the device has successfully
 * connected to a WiFi network.
 *
 * @param wifi_event The wifi_event parameter is of type WiFiEvent_t, which is an enumeration that
 * represents different WiFi events such as connecting to a network, disconnecting from a network, etc.
 * It is used to identify the specific event that occurred.
 * @param wifi_info The wifi_info parameter is an object of type WiFiEventInfo_t, which contains
 * information about the WiFi event that occurred. This information can include details such as the
 * SSID (network name), BSSID (MAC address of the access point), channel, and signal strength.
 */
void connected_to_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info)
{
  Serial.println("[+] Connected to the WiFi network");
}

// Handle disconnection

/**
 * The function handles the event of being disconnected from a WiFi access point and attempts to
 * reconnect.
 *
 * @param wifi_event The wifi_event parameter is of type WiFiEvent_t, which is an enumeration that
 * represents different WiFi events such as connection, disconnection, authentication, etc.
 * @param wifi_info The wifi_info parameter is a structure that contains information about the WiFi
 * event that occurred. It includes details such as the reason for the disconnection, the MAC address
 * of the access point, and the signal strength.
 */
void disconnected_from_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info)
{
  Serial.println("[-] Disconnected from the WiFi AP");
  static boolean wifi_connected = false;
  WiFi.begin(ssid, pass);
}

/**
 * prints the local IP address of the ESP32 when it successfully connects to an access point.
 *
 * @param wifi_event
 * @param wifi_info
 * @todo Implement static Ip address for the ESP32
 */
void got_ip_from_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info)
{
  Serial.print("[+] Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}


void setup()
{
  Serial.begin(115200);
  delay(1000);

  WiFi.onEvent(connected_to_ap, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(got_ip_from_ap, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(disconnected_from_ap, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, pass);
  Serial.println("\nConnecting");

  motion_setup();

  PT_INIT(&ptreaddht);
  PT_INIT(&ptdetectgas);
}



void loop()
{
  protothreadReadDHT(&ptreaddht);
  protothreaddetectgas(&ptdetectgas);

  current_time = millis();
  if(motiondetected && (current_time - last_trigger > interval)) {
    Serial.println("Motion has stopped");
    digitalWrite(red, LOW);
    digitalWrite(green,HIGH);
    motiondetected = false;
  }
}


