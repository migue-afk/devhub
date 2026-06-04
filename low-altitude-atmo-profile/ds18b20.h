#ifndef ds18b20_H
#define ds18b20_H

#include <OneWire.h>
#include <DallasTemperature.h>

extern DallasTemperature sensors;
extern OneWire oneWire;


struct ClimateDataDs {
  float temperature;
};


ClimateDataDs reads18(OneWire &oneWire);

#endif

