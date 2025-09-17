#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <Arduino.h>
#include "DHT11Sensor.h"
#include "DHT11Sensor.cpp"
#include "YL69Sensor.h"
#include "YL69Sensor.cpp"
#include "LM393LDRSensor.h"
#include "LM393LDRSensor.cpp"
#include "AnemometerSensor.h"
#include "AnemometerSensor.cpp"

class SensorManager {
  private:
    DHT11Sensor dht11;
    YL69Sensor yl69;
    LM393LDRSensor ldr;
    AnemometerSensor anemometer;

  public:
    SensorManager(int dhtPin, int yl69Analog, int yl69Digital, int ldrAnalog, int ldrDigital, int anePin, float aneFactor = 1.0f);

    void begin();

    // DHT11
    float readTemperature();
    float readHumidity();

    // YL69
    int readSoilAnalog();
    bool readSoilDigital();

    // LDR
    int readLightAnalog();
    bool readLightDigital();

    // Anemometer
    float readWindSpeed();
};

#endif