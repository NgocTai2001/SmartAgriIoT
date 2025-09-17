#ifndef YL69SENSOR_H
#define YL69SENSOR_H

#include <Arduino.h>

class YL69Sensor {
  private:
    int analogPin;
    int digitalPin;
  
  public:
    YL69Sensor(int aPin, int dPin = -1);
    int readSoilAnalog();
    bool readSoilDigital();
};

#endif