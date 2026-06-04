#ifndef LTMtelemetry_H
#define LTMtelemetry_H

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "Efectos.h"

extern SoftwareSerial droneSerial;
extern Adafruit_NeoPixel pixels;

#define PIN 6
#define NUMPIXELS 4

void ltmaccess();

#endif






