#include <Arduino.h>
#include "DHTsensor.h"

unsigned long lastRead = 0;
const unsigned long intervalread = 3000; // DHT22 2s
unsigned long timeDF = 0;


ClimateData readht22(DHT &dht22) {
timeDF = millis();

 if (timeDF - lastRead >= intervalread) {
    lastRead = timeDF;

  ClimateData data;

  data.hum = dht22.readHumidity();
  data.temp = dht22.readTemperature();

  if (isnan(data.hum) || isnan(data.temp)) {
    Serial.println("Error leyendo DHT22");
    data.hum = -1;
    data.temp = -100;
  }

  return data;
 }
}