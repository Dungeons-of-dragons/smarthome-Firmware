#include "defs.h"
#include "dht11.h"

DHT dht(DHT11PIN, DHT11);

float readtemp(){
    dht.begin();
    float temperature = dht.readTemperature();
    return temperature; 
}

float readhumidity(){
    float humidity = dht.readHumidity();
    return humidity;
}

bool fan_state(float temperature){
    if (temperature > 27.0){
        return true;
    }
    else {
        return false;
    }
}

