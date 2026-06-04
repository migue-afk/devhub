#ifndef EFECTOS_H
#define EFECTOS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

extern int sats; 
extern float maxalt;
extern const int pinBoton;
extern float vbat;

// Declare functions that will be in the .cpp
void armado(Adafruit_NeoPixel &pixels);
void estrobo(Adafruit_NeoPixel &pixels);
void satsnum(Adafruit_NeoPixel &pixels);
void maxaltitude(Adafruit_NeoPixel &pixels);
void minbatf(Adafruit_NeoPixel &pixels);

#endif