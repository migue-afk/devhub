#ifndef ntc_H
#define ntc_H

#define RT0 111000.0   
#define B   4690.0     
#define VCC 4.73       
#define R   9740.0     

const float T0 = 25.0 + 273.15; 


struct ClimateDataNtc {
  float tempntC;
  float tempntK;
};


ClimateDataNtc readntc();

#endif
