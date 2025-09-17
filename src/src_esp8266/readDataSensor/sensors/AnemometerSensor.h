#ifndef ANEMOMETERSENSOR_H
#define ANEMOMETERSENSOR_H

#include <Arduino.h>

class AnemometerSensor {
  private:
    int pin;
    volatile unsigned long pulseCount;
    unsigned long lastTime;
    float calibrationFactor; // pulses per second per m/s

    static void IRAM_ATTR handleInterruptWrapper(void* arg);

  public:
    AnemometerSensor(int inputPin, float factor = 1.0f);
    void begin();
    void handleInterrupt();
    float readWindSpeed(); // m/s
    void reset();
};

#endif