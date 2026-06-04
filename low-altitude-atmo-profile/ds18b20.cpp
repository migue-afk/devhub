#include <Arduino.h>
#include "ds18b20.h"

const unsigned long conversionTime = 750; // 12 bits

ClimateDataDs reads18(OneWire &oneWire) {

  static unsigned long lastRequest = 0;
  static bool waiting = false;
  static ClimateDataDs data;

 
  if (!waiting) {
    sensors.requestTemperatures();  
    lastRequest = millis();
    waiting = true;
    return data;
  }

 
  if (millis() - lastRequest >= conversionTime) {

    data.temperature = sensors.getTempCByIndex(0);

    if (data.temperature == DEVICE_DISCONNECTED_C) {
      Serial.println("Error sensor");
    }

    waiting = false; 
  }

  return data;
}