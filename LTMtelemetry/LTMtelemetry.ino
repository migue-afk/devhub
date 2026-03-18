#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "Efectos.h"

#define PIN 6
#define NUMPIXELS 4

int stap = 1;
int sats = 0;
float maxalt = 0;
float vbat = 0;

SoftwareSerial droneSerial(3, 11); //  RX on pin 10, TX on pin 11 (connect the drone's TX to 10)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte payload[7];
byte payloadG[14];
const int pinBoton = 10;

void setup() {
  Serial.begin(115200);
  droneSerial.begin(9600);
  droneSerial.setTimeout(1000); 
  Serial.println("LTM Listo...");
  pinMode(13, OUTPUT);
  pinMode(pinBoton, INPUT_PULLUP);
  pixels.begin();
}

void loop() {
  //We only enter if there are enough bytes for a header + frame S
  // ($ + T + S + 7 bytes = 10 bytes minimum)
  estrobo(pixels);
  if (droneSerial.available() >= 10) {
    char c = droneSerial.read();
    if (c == '$') {
      while (!droneSerial.available());
      char proto = droneSerial.read();

      if (proto == 'T'){
        while (!droneSerial.available());
            char frameType = droneSerial.read();
        
        if (frameType == 'S') {

        //We fill our payload "shelf" with the following 7 bytes
        droneSerial.readBytes(payload, 7);
        
        //  --- BIT PROCESSING ---
        byte statusByte = payload[6];
        //Merge the two bytes of uint16 (LTM uses Little Endian)
        uint16_t vbatRaw = (payload[1] << 8) | payload[0];
        //Convert millivolts to Volts
        vbat = vbatRaw / 1000.0;
        Serial.print("vbat: ");
        minbatf(pixels);

        bool isArmed = statusByte & 0x01;          // Bit 0
        byte flightMode = (statusByte >> 2) & 0x1F; // Bits 2 to 7
        
        // --- SHOW RESULTS ---
          Serial.print(isArmed ? "[ARMED] " : "[DISARMED] ");
          if (isArmed) {
            for (int i = stap; i>0; i--){
              armado(pixels);
              delay(100);
            }
              stap = 0;
          } else {
          stap = 1;
        }
        if (flightMode == 13) {
          Serial.println("| MODO: RTH");
        } 
        else if (flightMode == 2) {
          Serial.println("| MODO: ANGLE");
        } 
        else if (flightMode == 1) {
          Serial.println("| MODO: ACRO");
        } 
        else {
          Serial.print("| MODO ID: ");
          Serial.println(flightMode);
        }
        }

if (frameType == 'G') {

  if (droneSerial.readBytes(payloadG, 14) == 14) {

    int32_t altitude =
        (int32_t)payloadG[9] |
        ((int32_t)payloadG[10] << 8) |
        ((int32_t)payloadG[11] << 16) |
        ((int32_t)payloadG[12] << 24);

    float altitudeMeters = altitude / 100; // Original value to /100
    maxalt = altitudeMeters;
    Serial.print("MAXALT: ");
    Serial.println(maxalt);
    maxaltitude(pixels);
    

    byte gpsByte = payloadG[13];
    byte gpsFix = gpsByte & 0x03;
    byte satellites = gpsByte >> 2;

    Serial.print("Altitude: ");
    Serial.print(altitudeMeters);
    Serial.println(" m");

    Serial.print("Satellites: ");
    Serial.println(satellites);
    sats = satellites;
    satsnum(pixels);
    delay(100);
  }
}
      }
    }
  }
}
