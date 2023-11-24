#include <DHT.h>
#include "dhttest.h"

#define DHTPIN 26    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // Test the readHumidity() and readTemperature() functions
  testReadings();
}

void testReadings() {
  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  // Assert that the readings are within the expected range
  assert(h >= 0 && h <= 100);
  assert(t >= -40 && t <= 80); 
  assert(hic >= -40 && hic <= 80); 

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
}