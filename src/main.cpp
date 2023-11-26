#include "main.h"
#include <pt.h>
#include <string.h>

LCD Lcd; // LCD instance

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// declare three protothreads
static struct pt ptreaddht, ptdetectgas, ptdetectmotion, ptreadvoltage, ptdoor, ptreconnect;

static float temp;
static float humid;

// First protothread function to read DHT  every 5 second
/**
 * @brief  function "protothreadReadDHT" reads temperature and humidity values from a sensor every 5
 * seconds and prints them to the serial monitor.
 *
 * @param pt The parameter "pt" is a pointer to a struct of type "pt". This struct is used to implement
 * a protothread, which is a lightweight cooperative multitasking mechanism. The protothreadReadDHT
 * function is defined to take a pointer to this struct as a parameter so that it can use it
 */
static int protothreadReadDHT(struct pt *pt)
{
  static struct pt ptreconnect;
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > interval);
    temp = readtemp();
    humid = readhumidity();
    Serial.printf("temp: %.3f, humid: %.3f\n", temp, humid);
    Lcd.displaydht(temp, humid);
    //@todo insert user code to publish topics
    sensor.clearFields();
    sensor.addField("temperature", temp);
    sensor.addField("humidity", humid);
    PT_SPAWN(pt, &ptreconnect, protothreadreconnect(&ptreconnect));
    PT_YIELD(pt);
  }
  PT_END(pt);
}

// second protothread to check for gas presence
static int protothreaddetectgas(struct pt *pt)
{
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, Gas_detected);
    ets_printf("gas detected");
    //@todo insert user functions to signal the user
    PT_WAIT_UNTIL(pt, !Gas_detected);
    //@todo insert user code to notify )
  }
  PT_END(pt);
}

// third protothread to detect motion
static int protothreaddetectmotion(struct pt *pt)
{
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, (motiondetected));
    movement_detection();
    PT_WAIT_UNTIL(pt, (motiondetected && (millis() - lastTimeread > interval)));
    ets_printf("Motion has stopped\n ");
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    motiondetected = false;
  }
  PT_END(pt);
}

// fourth protothread to measure voltage
float avgvolt;
double avgwatt;
static int protothreadmeasurevoltage(struct pt *pt)
{
  static unsigned long lastTImeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTImeread = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTImeread > intervolt);
    avgvolt = readvoltage();
    avgwatt = getWatts();

    Serial.printf("Average voltage is %.3f, average watt is %d \n", avgvolt, avgwatt);
    Lcd.displaypower(avgwatt, avgvolt);
    // @todo insert user code to publish to broker
    PT_YIELD(pt);
  }
  PT_END(pt);
}

/**
 * @brief this protothread handles authorization of the user at the door
 * @param pt the pointer to the pt struct
 *
 * @todo implment spawning a child process to yield control
 *
 */
static bool authorize;
static int protothreadauth(struct pt *pt)
{
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > doorinterval);
    check_for_card();
    authorize = card_authorization;
    PT_WAIT_UNTIL(pt, authorize == true);
    digitalWrite(buzzer, HIGH);
    digitalWrite(lock_pin, LOW);
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > 1000);
    digitalWrite(buzzer, LOW);
    lastTimeread = millis();
    Lcd.displayauthorised(authorize);
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > 5000);
    authorize = card_authorization;
    PT_WAIT_UNTIL(pt, authorize == false);
  }
  PT_END(pt);
}

static int protothreadreconnect(struct pt *pt)
{
  static unsigned long lastTimeread = 0;
  PT_BEGIN(pt);
  while (1)
  {
    lastTimeread = millis();
    PT_WAIT_UNTIL(pt, !Client.writePoint(sensor));
    PT_WAIT_UNTIL(pt, millis() - lastTimeread > 2000);
    Serial.print("InfluxDB write failed: ");
    Serial.println(Client.getLastErrorMessage());
    PT_EXIT(pt);
  }
  PT_END(pt);
}

// RFID/Relay protothread
// static int protothreaddoor(struct pt *pt)
// {
//   static unsigned long lastTimeread = 0;
//   PT_BEGIN(pt);

//   while (1)
//   {
//     lastTimeread = millis();
//     check_for_card();
//     authorize = card_authorization();

//     if (authorize == true)
//     {
//       digitalWrite(buzzer, HIGH);
//       digitalWrite(lock_pin, LOW);
//       lastTimeread = millis();
//       PT_WAIT_UNTIL(pt, millis() - lastTimeread > 1000);
//       digitalWrite(buzzer, LOW);
//       lastTimeread = millis();
//       PT_WAIT_UNTIL(pt, millis() - lastTimeread > 5000);
//       digitalWrite(lock_pin, HIGH);
//       Lcd.displayauthorised(authorize);
//     }
//     else
//     {
//       lastTimeread = 0;
//       PT_WAIT_UNTIL(pt, millis() - lastTimeread > 1000);
//       Lcd.displayauthorised(authorize);
//     }
//   }
//   PT_END(pt);
// }

// Use events to avoid blocking code
/**
 * @brief The function "connected_to_ap" prints a message indicating that the device has successfully
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
  static boolean wifi_connected = true;
  Serial.println("[+] Connected to the WiFi network");
}

// Handle disconnection
/**
 * @brief The function handles the event of being disconnected from a WiFi access point and attempts to
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
 * @brief prints the local IP address of the ESP32 when it successfully connects to an access point.
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
  // Setting up WiFi connection
  WiFi.onEvent(connected_to_ap, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(got_ip_from_ap, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(disconnected_from_ap, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, pass);
  Serial.println("\nConnecting");

  // setting up and initializing sensors
  Lcd.lcd_initialize();
  motion_setup();
  door_initialize();
  influx_setup();

  PT_INIT(&ptreaddht);
  PT_INIT(&ptdetectgas);
  PT_INIT(&ptdetectmotion);
  PT_INIT(&ptreadvoltage);
  // PT_INIT(&ptdoor);
  PT_INIT(&ptreconnect);
}

void loop()
{
  // Getting sensor readings and implementing necesarry actions regarding them
  protothreadReadDHT(&ptreaddht);
  protothreaddetectgas(&ptdetectgas);
  protothreaddetectmotion(&ptdetectmotion);
  protothreadmeasurevoltage(&ptreadvoltage);
  protothreadreconnect(&ptreconnect);
  // protothreaddoor(&ptdoor);
}
