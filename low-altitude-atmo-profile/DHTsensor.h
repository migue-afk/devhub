#ifndef DHTsensor_H
#define DHTsensor_H

#include <DHT.h>

// data estructure
struct ClimateData {
  float temp;
  float hum;
  float altitude;
  unsigned long timestamp;
};

// data return function
ClimateData readht22(DHT &dht22);

#endif