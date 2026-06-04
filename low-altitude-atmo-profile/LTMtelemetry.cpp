#include "LTMtelemetry.h"  

int stap = 1;  // on/off drone armed
int sats = 0;  // number of satellites
float maxalt = 0;  // max altitude
float vbat = 0;  // battery voltage
byte lastStatusByte = 0; 
float lastVbat = 0;  

byte payload[7];  
byte payloadG[14]; 

void ltmaccess() {
  
  if (droneSerial.available() >= 10) {
    char c = droneSerial.read();
    if (c == '$') {  
      while (!droneSerial.available());  
      char proto = droneSerial.read();  

      if (proto == 'T') {  
        while (!droneSerial.available());  
        char frameType = droneSerial.read();  

        if (frameType == 'S') {  
        
          int bytesRead = droneSerial.readBytes(payload, 7);
          if (bytesRead == 7) {
            
            byte statusByte = payload[6]; 
            uint16_t vbatRaw = (payload[1] << 8) | payload[0]; 
            vbat = vbatRaw / 1000.0;  

           
            if (statusByte != lastStatusByte) {
              lastStatusByte = statusByte;  
            }
            if (vbat != lastVbat) {
              lastVbat = vbat;  
            }

            Serial.print("vbat: ");
            Serial.println(lastVbat, 3);

            bool isArmed = lastStatusByte & 0x01;  
            byte flightMode = (lastStatusByte >> 2) & 0x1F;
            
            
            Serial.print(isArmed ? "[ARMED] " : "[DISARMED] ");
            
            
            if (isArmed) {
              if (stap == 1) {
                for (int i = stap; i > 0; i--){
                  armado(pixels); 
                  delay(100);
                }
              }
              stap = 0;
            } else {
              stap = 1;  
            }
            

            if (flightMode == 13) {
              Serial.println("| MODE: RTH");  
            } 
            else if (flightMode == 2) {
              Serial.println("| MODE: ANGLE"); 
            } 
            else if (flightMode == 1) {
              Serial.println("| MODE: ACRO"); 
            } 
            else {
              Serial.print("| MODE ID: ");
              Serial.println(flightMode);  
            }
          } else {
            Serial.println("Error:7 bytes incomplete");
          }
        }
    

      
      if (frameType == 'G') {
        while (!droneSerial.available());  
        int bytesRead = droneSerial.readBytes(payloadG, 14);  
        if (bytesRead == 14) {
          
          int32_t altitude = (int32_t)payloadG[9] | ((int32_t)payloadG[10] << 8) | ((int32_t)payloadG[11] << 16) | ((int32_t)payloadG[12] << 24);
          float altitudeMeters = altitude / 100.0;  
          maxalt = altitudeMeters;  
          Serial.print("MAXALT: ");
          Serial.println(maxalt);

          
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
        } else {
          Serial.println("Error: 14 bytes incomplete.");
        }
      }

    }
    } 
    estrobo(pixels);
  }
  else {
          Serial.println("Error LTM Incomplete Frame !!!");
    }
}