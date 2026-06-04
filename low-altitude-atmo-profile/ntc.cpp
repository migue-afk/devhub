#include <Arduino.h>
#include "ntc.h"

unsigned long lastRead1 = 0;
const unsigned long intervalread = 500; // DHT22 2s
unsigned long timeDF1 = 0;

ClimateDataNtc readntc() {
  ClimateDataNtc data;

  timeDF1 = millis();

  if (timeDF1 - lastRead1 >= intervalread) {
    lastRead1 = timeDF1;

    int adc = analogRead(A0);

    if (adc <= 0 || adc >= 1023) return data;

    float Vout = (VCC * adc) / 1023.0;
    float VR = VCC - Vout;

    if (VR <= 0) return data;

    float RT = R * (Vout / VR);

    float logRatio = log(RT / RT0);
    data.tempntK = 1.0 / ((logRatio / B) + (1.0 / T0));
    data.tempntC = data.tempntK - 273.15;
  }

  return data;  
}