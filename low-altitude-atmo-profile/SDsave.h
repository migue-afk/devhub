#ifndef SDsave_H
#define SDsave_H

#include <SD.h>


extern File myFile;
// Return data
void sdataw(long timeC, float maxalt, float tempds18, float tempntc);
void sdatar();
void initSD();

#endif