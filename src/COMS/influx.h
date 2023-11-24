#ifndef INFLUX_H 
#define INFLUX_H 
#include "arduino_secrets.h"
#include "main.h"
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>


extern InfluxDBClient Client;
extern Point sensor; 


void influx_setup();
void reloop(); 

#define INFLUXDB_BUCKET "testdht"

// Time zone info
#define TZ_INFO "UTC3"



#endif 