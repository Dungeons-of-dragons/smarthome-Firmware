#ifndef INFLUX_H
#define INFLUX_H
#include "arduino_secrets.h"
#include "main.h"
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

extern InfluxDBClient Client;
extern Point sensor;
extern Point sensor2;
extern Point sensor3;
extern Point sensor4;
extern Point sensor5;

#define INFLUXDB_URL "http://pie.local:8086"
#define INFLUXDB_TOKEN "lL6hewimQNEme90RLdAR4BDYX0pvZruFWaeMlZV225YlhgmtpmjHrxE9oMycntbWGYWPdw8ezQlc9x2-bmqYQA=="
#define INFLUXDB_ORG "2df393258f4a9fc1"
#define INFLUXDB_BUCKET "smarthome"

// Time zone info
#define TZ_INFO "UTC3"

void influx_setup();

#endif