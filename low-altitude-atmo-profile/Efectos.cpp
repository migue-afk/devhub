#include "Efectos.h"

void armado(Adafruit_NeoPixel &pixels) {
  //Initial ignition 500 ms
  pixels.fill(pixels.Color(255, 0, 0)); // rojo
  pixels.show();
  delay(375);

  //  Fast flashing 20ms, 5 times
  for (int i = 0; i < 5; i++) {
    pixels.clear();
    pixels.show();
    delay(50);
    pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
    delay(20);
  }

  //  Final ignition 200 ms
  pixels.fill(pixels.Color(255, 0, 0));
  pixels.show();
  delay(200);

 for (int i = 0; i < 5; i++) {
    pixels.clear();
    pixels.show();
    delay(50);
    pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
    delay(20);
  }

   pixels.fill(pixels.Color(255, 0, 0));
  pixels.show();
  delay(200);
  // Turn everything off
  pixels.clear();
  pixels.show();
}

unsigned long lastTime = 0;       
const unsigned long intervalo = 2300; 
bool readyToFlash = true;

void estrobo(Adafruit_NeoPixel &pixels) {
    int lastLedIndex = pixels.numPixels() - 1;

    unsigned long currentMillis = millis();

    if (readyToFlash && currentMillis - lastTime >= intervalo) {
        //Make the flash here
        //pixels.setPixelColor(lastLedIndex, pixels.Color(0, 255, 0));
        pixels.fill(pixels.Color(0, 255, 0)); 
        pixels.show();
        delay(100);
        //pixels.setPixelColor(lastLedIndex, pixels.Color(0, 0, 0));
        pixels.fill(pixels.Color(0, 0, 0)); 
        pixels.show();

        lastTime = currentMillis;
        readyToFlash = false;     
    }

    //Allow the next cycle after the interval
    if (!readyToFlash && currentMillis - lastTime >= intervalo) {
        readyToFlash = true;
    }
}

void satsnum(Adafruit_NeoPixel &pixels){
  if (digitalRead(pinBoton) == LOW){
    int blinks = sats;     
    int delayOn = 250;        
    int delayOff = 250;       
    for (int i = 0; i < blinks; i++) {
        // --- Fade in ---
        for (int b = 0; b <= 255; b += 51) { 
            pixels.fill(pixels.Color(b, b, 0)); 
            pixels.show();
            delay(20);
        }
        // --- Fade out ---
        for (int b = 255; b >= 0; b -= 51) {
            pixels.fill(pixels.Color(b, b, 0));
            pixels.show();
            delay(20);
        }
        // Pause between blinks
        delay(delayOff);
    }
    } 
}

void maxaltitude(Adafruit_NeoPixel &pixels) {
    static unsigned long timerStart = 0;
    static bool effectActive = false;
    static int step = 0; 
    static unsigned long lastUpdate = 0;

    unsigned long now = millis();

    //Enable effect if maximum altitude > 100
    if (maxalt > 100 && !effectActive) {
        effectActive = true;
        timerStart = now;
        step = 0;
        lastUpdate = now;
    }

    if (effectActive) {
        if (now - lastUpdate >= 50) {
            lastUpdate = now;
            for (int i = 0; i < pixels.numPixels(); i++) {
                int distance = abs(i - (step % pixels.numPixels()));
                int brillo = 255 - distance * 50;
                if (brillo < 0) brillo = 0;

                // Fast pulses alternating on/off
                if ((step / 2) % 2 == 0) {
                    pixels.setPixelColor(i, pixels.Color(0, brillo, 0));
                } else {
                    pixels.setPixelColor(i, pixels.Color(0,0,0));
                }
            }
            pixels.show();
            step++;
 //Turn off effect after 10 seconds
        }
	 //Turn off effect after 10 seconds
        if (now - timerStart >= 10000) {
            pixels.clear();
            pixels.show();
            effectActive = false;
        }
    }
}

void minbatf(Adafruit_NeoPixel &pixels) {
    static unsigned long timerStart = 0;
    static bool effectActive = false;
    static int step = 0; 
    static unsigned long lastUpdate = 0;

    unsigned long now = millis();

    if (vbat <= 10.5 && !effectActive) {
        effectActive = true;
        timerStart = now;
        step = 0;
        lastUpdate = now;
    }

    if (effectActive) {
        if (now - lastUpdate >= 50) {
            lastUpdate = now;

            for (int i = 0; i < pixels.numPixels(); i++) {
                int distance = abs(i - (step % pixels.numPixels()));
                int brillo = 255 - distance * 50; 
                if (brillo < 0) brillo = 0;

                if ((step / 2) % 2 == 0) {
                    pixels.setPixelColor(i, pixels.Color(brillo, 0, 0));
                } else {
                    pixels.setPixelColor(i, pixels.Color(0,0,0));
                }
            }
            pixels.show();
            step++;
        }
        if (now - timerStart >= 10000) {
            pixels.clear();
            pixels.show();
            effectActive = false;
        }
    }
}