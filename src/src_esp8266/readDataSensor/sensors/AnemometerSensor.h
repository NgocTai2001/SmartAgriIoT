#ifndef ANEMOMETER_SENSOR_H
#define ANEMOMETER_SENSOR_H

#include <Arduino.h>

class AnemometerSensor {
  private:
    int pin;
    float calibrationFactor; // Conversion factor (m/s per Volt)

  public:
    AnemometerSensor(int analogPin, float factor);
    void begin();

    // Function to read wind speed (m/s)
    float readWindSpeed();
};

#endif