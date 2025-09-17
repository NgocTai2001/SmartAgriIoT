#ifndef LM393LDRSENSOR_H
#define LM393LDRSENSOR_H

#include <Arduino.h>

class LM393LDRSensor {
  private:
    int analogPin;
    int digitalPin;
  
  public:
    LM393LDRSensor(int aPin, int dPin = -1);
    int readAnalog();
    bool readDigital();
};

#endif