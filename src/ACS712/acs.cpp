
#include "defs.h"
#include "acs.h"
// https://www.circuitschools.com/measure-ac-current-by-interfacing-acs712-sensor-with-esp32/#:~:text=The%20Data%20pin%20OUT%20of,to%20zero%20in%20negative%20polarity.

float readvoltage()
{
    float result;
    int readValue;       // value read from the sensor
    int maxValue = 0;    // store max value here
    int minValue = 4096; // store min value here ESP32 ADC resolution

    uint32_t start_time = millis();
    while ((millis() - start_time) < 1000) // sample for 1 Sec
    {
        readValue = analogRead(CURRENT_PIN);
        // see if you have a new maxValue
        if (readValue > maxValue)
        {
            /*record the maximum sensor value*/
            maxValue = readValue;
        }
        if (readValue < minValue)
        {
            /*record the minimum sensor value*/
            minValue = readValue;
        }
    }

    // Subtract min from max
    result = ((maxValue - minValue) * 3.3) / 4096.0; // ESP32 ADC resolution 4096

    return result;
}

double getWatts()
{        
    AmpsRMS = getAmps(); 
    Watt = (AmpsRMS * 240 / 1.2);
    // note: 1.2 is author's (HAS TO BE RECALLIBRATED) empirically established calibration factor
    // as the voltage measured at D34 depends on the length of the OUT-to-D34 wire
    // 240 is the main AC power voltage – this parameter changes locally
    return Watt;
}

double getAmps()
{
    Voltage = readvoltage();
    VRMS = (Voltage / 2.0) * 0.707; // root 2 is 0.707
    AmpsRMS = ((VRMS * 1000) / mVperAmp) - 0.3; // 0.3 is the error from sensor
    return AmpsRMS;
}