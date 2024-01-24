#if defined(ESP32)
#define DEVICE "ESP32"
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#endif

#include "influx.h"
#include "main.h"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient Client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Declare Data point
Point sensor("sensors");

void influx_setup()
{
  // Accurate time is necessary for certificate validation and writing in batches
  // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (Client.validateConnection())
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(Client.getServerUrl());
  }
  else
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(Client.getLastErrorMessage());
  }

  sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());
}
