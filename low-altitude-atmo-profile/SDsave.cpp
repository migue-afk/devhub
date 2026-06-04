#include "SDsave.h"
String myStringT = "Temp";
String myStringH = "Hum";
File myFile;
#define PIN_SPI_CS 4

void sdataw(long timeC, float maxalt, float tempds18, float tempntc){

myFile = SD.open("atmo.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(timeC);
    myFile.print(",");
    myFile.print(maxalt);
    myFile.print(",");
    myFile.print(tempds18);
    myFile.print(",");
    myFile.println(tempntc);
    myFile.close();
    //myFile.flush();

  } else {
    Serial.println(F("SD Card: error on opening file atmoprofile.txt (WRITE)"));
  }
}
  
void sdatar(){  

  myFile = SD.open("atmo.txt", FILE_READ);
  if (myFile) {
    while (myFile.available()) {
      char ch = myFile.read(); // read characters one by one from Micro SD Card
      Serial.print(ch); // print the character to Serial Monitor
    }
    myFile.close();
  } else {
    Serial.println(F("SD Card: error on opening file atmoprofile.txt"));
  }
}


void initSD(){
    if (!SD.begin(PIN_SPI_CS)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }

  Serial.println(F("SD CARD INITIALIZED."));
  Serial.println(F("--------------------"));
  SD.remove("atmo.txt"); // delete the file if existed
  Serial.println(F("remove atmoprofile.txt"));
  myFile = SD.open("atmo.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("time,Altitude,TempDS18, TempNTC");
    myFile.close();

  } else {
    Serial.println(F("SD Card: error on opening file atmoprofile.txt (WRITE)"));
  }
 

}