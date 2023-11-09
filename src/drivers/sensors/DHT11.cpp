#include "defs.h"
#include "dth11.h"

DHT dht(DHT11PIN, DHT11);

float readtemp(){
    dht.begin();
    float temperature = dht.readTemperature();
    return temperature; 
}

float readhumidity(){
    dht.begin();
    float humidity = dht.readHumidity();
    return humidity;
}

