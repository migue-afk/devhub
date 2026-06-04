//---------------------------------
#include "DHTsensor.h"
#include "SDsave.h"
#include "LTMtelemetry.h"
#include "ds18b20.h"
#include "ntc.h"
//---------------------------------

#define DHT22_PIN 2
DHT dht22(DHT22_PIN, DHT22);
unsigned long startMillis = millis();
//#######################################
const int SENSOR_PIN = 5;
OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);
//#######################################
unsigned long currentTime;
unsigned long startTime = 0;
unsigned long elapsedTime;
int loopCounter = 0;
bool started = false;
unsigned long lastIntervalTime = 0;
const unsigned long interval = 1000; // 1 second
//#######################################
//-----------------------------------------
//  RX on pin 3, TX on pin 10 (connect the drone's TX to 3)
SoftwareSerial droneSerial(3, 10); 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int pinBoton = 10; 
//------------------------------------------

void setup() {
  Serial.begin(115200);
  //########################################################
  initSD();
//----------------------------------------------------------

  //dht22.begin();
//#########################################################
  sensors.begin();

  sensors.setResolution(12);         
  sensors.setWaitForConversion(false); 

  sensors.requestTemperatures(); 
//----------------------------------------------------------
  droneSerial.begin(9600);
  droneSerial.setTimeout(1000); 
  Serial.println("LTM Listo...");
  pinMode(13, OUTPUT);
  pinMode(pinBoton, INPUT_PULLUP);
  pixels.begin();
//----------------------------------------------------------

}

void loop() {
  ltmaccess();
  //ClimateData clima = readht22(dht22);
  ClimateDataDs climads = reads18(oneWire); //Called to ds18b20.cpp
  ClimateDataNtc climantc = readntc();      //Called to ntc.cpp
  

  //loopCounter++;
  currentTime = millis(); 
  //Serial.print(loopCounter);
  //Serial.println("loopCounter");

  /*if (loopCounter == 10 && !started) {
    startTime = currentTime;
    initSD();
    started = true;
    Serial.print("Init logger: ");
  }*/

  if (currentTime - lastIntervalTime >= interval) {
    lastIntervalTime = currentTime;
    elapsedTime = (currentTime - startTime) / 1000;
    //Serial.println(elapsedTime);
    //Serial.println(clima.temp);
    //Serial.println(clima.hum);
    //Serial.println(climads.temperature);
    //Serial.println(climantc.tempntC);
    sdataw(elapsedTime, maxalt, climads.temperature, climantc.tempntC);
    //sdatar();

    
  unsigned long endMillis = millis();
  unsigned long elapsedTimeInCycle = endMillis - startMillis;
  Serial.print("Tiempo de ejecución: ");
  Serial.println(elapsedTimeInCycle);
  //delay(10000);
  }
}