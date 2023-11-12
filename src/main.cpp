#include "main.h"

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
}



void loop()
{
  float humidity = readhumidity();
  float temperature = readtemp();

  current_time = millis();
  if(motiondetected && (current_time - last_trigger > interval)) {
    Serial.println("Motion has stopped");
    digitalWrite(red, LOW);
    digitalWrite(green,HIGH);
    motiondetected = false;
  }
}
